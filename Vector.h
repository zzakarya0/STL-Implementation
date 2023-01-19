#ifndef Vector_H
#define Vector_H

#include <cassert>
#include <ostream>

#include "Utility.h"

namespace zzstl 
{
	template <typename Vector>
	class Vector_Iterator 
	{
	public:
		using ValueType = typename Vector::ValueType;

	public:
		constexpr Vector_Iterator(ValueType* Data) noexcept : m_ptr(Data) {}
		constexpr Vector_Iterator(const Vector_Iterator& rhs) noexcept : m_ptr(rhs.m_ptr) {}

		constexpr Vector_Iterator operator++() noexcept
		{
			++m_ptr;
			return *this;
		}

		constexpr Vector_Iterator operator++(int) noexcept
		{
			Vector_Iterator temp(*this);
			++m_ptr;
			return temp;
		}

		constexpr Vector_Iterator operator--() noexcept
		{
			--m_ptr;
			return *this;
		}

		constexpr Vector_Iterator operator--(int) noexcept
		{
			Vector_Iterator temp(*this);
			--m_ptr;
			return temp;
		}

		constexpr ValueType& operator[](size_t pos) { return *(m_ptr + pos); }
		constexpr bool operator==(const Vector_Iterator rhs) noexcept { return m_ptr == rhs.m_ptr; }
		constexpr bool operator!=(const Vector_Iterator rhs) noexcept { return m_ptr != rhs.m_ptr; }
		constexpr ValueType* operator->() noexcept { return m_ptr; }
		constexpr ValueType& operator*() { return *m_ptr; }

	private:
		ValueType* m_ptr;
	};


	template <typename T>
	class Vector 
	{
	public:
		using ValueType = T;
		using PType = ValueType*;
		using RefType = ValueType&;
		using Iterator = typename Vector_Iterator<Vector<T>>;


	public: // public constructors offered by the vector class

		/// Vector default constructor
		constexpr Vector() noexcept : m_Size(0), m_Capacity(0), m_Data(nullptr) {} 
		
		/// Constructor taking the size/capacity of container and intiallizing with default value 
		explicit Vector(size_t size) {
			ReAlloc(size);
			m_Size = m_Capacity;
			for (size_t i = 0; i < m_Size; ++i) new (&m_Data[i]) T();
		}
		
		/// Constuctor 
		explicit Vector(size_t size, const T& val) {
			ReAlloc(size);
			m_Size = size;
			Fill(m_Data, size, val);
		}

		Vector(const Vector& rhs) 
		{
			if (rhs.m_Data)
			{
				ReAlloc(rhs.Capacity());
				for (size_t i = 0; i < rhs.m_Size; ++i) new (&m_Data[i]) T(rhs[i]);
			}

			m_Size = rhs.m_Size;
			m_Capacity = rhs.m_Capacity;
		}

		Vector& operator=(const Vector& rhs)
		{
			if (*this == rhs) return *this;

			Clear();
			if (m_Capacity != rhs.Capacity()) ReAlloc(rhs.Capacity());
			for (size_t i = 0; i < rhs.m_Size; ++i) new (&m_Data[i]) T(rhs[i]);
			m_Size = rhs.m_Size;

			return *this;
		}

		
		Vector(Vector&& rhs) noexcept : m_Size(rhs.Size()), m_Capacity(rhs.Capacity())
		{
			m_Data = rhs.Data();

			rhs.m_Size = 0;
			rhs.m_Capacity = 0;
			rhs.m_Data = nullptr;
		}

		Vector& operator=(Vector&& rhs)
		{
			if (*this == rhs) return *this;

			for (size_t i = 0; i < m_Size; ++i) m_Data[i].~T();
			m_Size = rhs.Size();
			m_Capacity = rhs.Capacity();
			m_Data = rhs.Data();
			
			rhs.m_Size = 0;
			rhs.m_Capacity = 0;
			rhs.m_Data = nullptr;
			return *this;
		}

		// Vector destructor
		~Vector() 
		{
			Clear();
			::operator delete(m_Data, m_Capacity * sizeof(T));
		}
	
	public: // Public member functions offered by the class

		//	Returns current number of elements in the container
		constexpr inline size_t Size() const noexcept { return m_Size; }

		//	Returns number of elements the container can take before a re-allocation
		constexpr inline size_t Capacity() const  noexcept { return m_Capacity; }

		constexpr inline bool Empty() const noexcept { return m_Size == 0; }

		//	Pointer to internal data array
		constexpr inline PType Data() noexcept { return m_Data; }
		constexpr inline const PType Data() const noexcept { return m_Data; }

		constexpr Iterator begin() noexcept { return Iterator(m_Data); }
		constexpr Iterator end() noexcept { return Iterator(m_Data + m_Size); }


		constexpr RefType Front()
		{
			assert(m_Size >= 0, "Cannot retrieve from empty vector");
			return *m_Data;
		}

		constexpr const RefType Front() const 
		{
			assert(m_Size >= 0, "Cannot retrieve from empty vector");
			return *m_Data;
		}

		constexpr RefType Back()
		{
			assert(m_Size >= 0, "Cannot retrieve from empty vector");
			return m_Data[m_Size - 1];
		}

		constexpr const RefType Back() const
		{
			assert(m_Size >= 0, "Cannot retrieve from empty vector");
			return m_Data[m_Size - 1];
		}

		constexpr RefType operator[] (size_t pos)  
		{
			assert(m_Size > pos, "Index out of bounds");
			return m_Data[pos];
		}

		constexpr const RefType operator[] (size_t pos) const 
		{
			assert(m_Size > pos, "Index out of bounds");
			return m_Data[pos];
		}

		void PushBack(const RefType val) 
		{
			if (m_Size == m_Capacity) ReAlloc(Max(static_cast<size_t>(2), m_Capacity + m_Capacity / 2));

			new (&m_Data[m_Size]) T(val);
			++m_Size;
		}

		void PushBack(T&& val) 
		{
			if (m_Size == m_Capacity) ReAlloc(Max(static_cast<size_t>(2), m_Capacity + m_Capacity / 2));

			new (&m_Data[m_Size]) T(std::move(val));
			++m_Size;
		}

		void PopBack() 
		{
			static_assert(m_Size != 0, "Cannot pop from an empty vector.");
			m_Data[--m_Size].~T();
		}

		template <typename... Args>
		void EmplaceBack(Args&&... args) 
		{
			if (m_Size == m_Capacity) ReAlloc(Max(static_cast<size_t>(2), m_Capacity + m_Capacity / 2));

			new (&m_Data[m_Size]) T(std::forward<Args>(args)...);
			++m_Size;
		}

		void ShrinkToFit() 
		{
			if (m_Size == m_Capacity) return;
			
			for (size_t i = m_Size; i < m_Capacity; ++i) (m_Data[i]).~T();
			::operator delete(m_Data[m_Size], m_Capacity - m_Size);
			m_Capacity = m_Size;
		}

		void Resize(size_t NewSize)
		{
			if (NewSize < m_Size) {
				for (size_t i = NewSize; i < m_Size; ++i) m_Data[i].~T();
			}
			else {
				ReAlloc(NewSize);
				Fill_InPlace(&m_Data[m_Size], NewSize - m_Size);
			}
			m_Size = NewSize;
		}

		void Clear() 
		{
			for (size_t i = 0; i < m_Size; ++i) m_Data[i].~T();
			m_Size = 0;
		}

	private: //	Utility functions only used internally by the public interface functions

		//	Re-alloc to either expand/shrink internal m_Data container
		void ReAlloc(size_t NewCapacity) 
		{
			T* NewBlock = static_cast<T*>(::operator new(NewCapacity * sizeof(T)));

			size_t size = Min(m_Size, NewCapacity);
			for (size_t i = 0; i < size; ++i) new (&NewBlock[i]) T(std::move(m_Data[i]));

			for (size_t i = 0; i < m_Size; ++i) m_Data[i].~T();
			::operator delete(m_Data, m_Capacity * sizeof(T));

			m_Data = NewBlock;
			m_Capacity = NewCapacity;
			assert(m_Data);
		}

	private: //	Member Data
		size_t m_Size = 0;
		size_t m_Capacity = 0;
		PType m_Data;
	};

	//	Function to facilitate printing of entire vector elements
	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) 
	{
		std::cout << "-------------------------\n";
		std::cout << vector.Size() << " | " << vector.Capacity() << std::endl;
		for (size_t i = 0; i < vector.Size(); ++i) os << vector[i] << " | ";
		std::cout << "\n-------------------------\n";

		os << std::endl;
		return os;
	}
}
#endif