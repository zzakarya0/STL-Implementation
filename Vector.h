#ifndef Vector_H
#define Vector_H

#include <cassert>
#include <ostream>

#include "Utility.h"

namespace zzstl 
{
	template <typename T>
	class Vector 
	{
	public:
		Vector() : m_Size(0), m_Capacity(0), m_Data(nullptr) {}

		Vector(size_t size) {
			ReAlloc(size);
			m_Size = m_Capacity;
			for (size_t i = 0; i < m_Size; ++i) new (&m_Data[i]) T();
		}

		Vector(size_t size, const T& val) {
			ReAlloc(size);
			m_Size = size;
			Fill(m_Data, size, val);
		}

		Vector(const Vector& rhs) {
			ReAlloc(rhs.Capacity());
			m_Size = rhs.Size();
			for (size_t i = 0; i < m_Size; ++i) new (&m_Data[i]) T(rhs[i]);
		}

		Vector& operator=(const Vector& rhs)
		{
			if (m_Capacity != rhs.Capacity()) ReAlloc(rhs.Capacity());
			
			for (size_t i = 0; i < m_Size; ++i) m_Data[i].~T();
			for (size_t i = 0; i < rhs.Size(); ++i) new (&m_Data[i]) T(rhs[i]);
			m_Size = rhs.Size();
			return *this;
		}

		//FIX ME!!
		Vector(Vector&& rhs) : m_Size(rhs.Size()), m_Capacity(rhs.Capacity()) {
			m_Data = rhs.Data();
			//rhs.Data() = nullptr;
			/*rhs.Size() = 0;
			rhs.Capacity() = 0;*/
		}

		~Vector() {
			Clear();
			::operator delete(m_Data, m_Capacity * sizeof(T));
		}

	public:
		inline size_t Size() const { return m_Size; }
		inline size_t Capacity() const { return m_Capacity; }

		inline T* Data() { return m_Data; }
		inline const T* Data() const { return m_Data; }

		T& operator[] (size_t pos)  
		{
			assert(m_Size > pos, "Index out of bounds");
			assert((m_Data != nullptr));
			return m_Data[pos];
		}

		const T& operator[] (size_t pos) const 
		{
			assert(m_Size > pos, "Index out of bounds");
			assert(m_Data != nullptr);
			return m_Data[pos];
		}

		void PushBack(const T& val) 
		{
			if (m_Size == m_Capacity) ReAlloc(Max(static_cast<size_t>(2), m_Capacity + m_Capacity / 2));
			assert(m_Data != nullptr);

			new (&m_Data[m_Size]) T(val);
			++m_Size;
		}

		void PushBack(T&& val) 
		{
			if (m_Size == m_Capacity) ReAlloc(Max(static_cast<size_t>(2), m_Capacity + m_Capacity / 2));
			assert(m_Data != nullptr);

			new (&m_Data[m_Size]) T(std::move(val));
			++m_Size;
		}

		void PopBack() 
		{
			assert(m_Size != 0, "Cannot pop from an empty vector.");
			m_Data[--m_Size].~T();
		}

		template <typename... Args>
		void EmplaceBack(Args&&... args) 
		{
			if (m_Size == m_Capacity) ReAlloc(Max(static_cast<size_t>(2), m_Capacity + m_Capacity / 2));

			assert(m_Data != nullptr);
			new (&m_Data[m_Size]) T(std::forward<Args>(args)...);
			++m_Size;
		}

		void ShrinkToFit() 
		{
			if (m_Size == m_Capacity) return;
			ReAlloc(m_Size);
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

	private:
		void ReAlloc(size_t NewCapacity) 
		{
			T* NewBlock = static_cast<T*>(::operator new(NewCapacity * sizeof(T)));

			size_t size = Min(m_Size, NewCapacity);
			for (size_t i = 0; i < size; ++i) new (&NewBlock[i]) T(std::move(m_Data[i]));

			for (size_t i = 0; i < m_Size; ++i) m_Data[i].~T();
			::operator delete(m_Data, m_Capacity * sizeof(T));

			m_Data = NewBlock;
			m_Capacity = NewCapacity;
		}

	private:
		size_t m_Size = 0;
		size_t m_Capacity = 0;
		T* m_Data;
	};

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