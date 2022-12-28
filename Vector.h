#ifndef Vector_H
#define Vector_H

#include <cassert>
#include <ostream>

#include "Utility.h"

namespace zzstl {
	template <typename T>
	class Vector {
	public:
		Vector(size_t size = 2) : m_Size(0), m_Capacity(size) {
			ReAlloc(m_Capacity);
		}

		Vector(size_t size, const T& val) : m_Size(size), m_Capacity(size) {
			ReAlloc(m_Capacity);
			fill(m_Data, size, val);
		}

		Vector(const Vector& rhs) : m_Size(rhs.Size()), m_Capacity(rhs.Capacity()) {
			ReAlloc(m_Capacity);
			for (size_t i = 0; i < m_Size; ++i) m_Data[i] = rhs[i];
		}

		Vector(Vector&& rhs) : m_Size(rhs.Size()), m_Capacity(rhs.Capacity()) {
			m_Data = rhs.Data();
			rhs.Data() = nullptr;
			/*rhs.Size() = 0;
			rhs.Capacity() = 0;*/
		}

		~Vector() {
			for (size_t i = 0; i < m_Size; ++i) {
				m_Data[i].~T();
			}
		}

		T& operator[] (size_t pos)  {
			assert(m_Size > pos, "Index out of bounds");

			assert((m_Data != nullptr));
			return m_Data[pos];
		}

		const T& operator[] (size_t pos) const {
			assert(m_Size > pos, "Index out of bounds");

			assert(m_Data != nullptr);
			return m_Data[pos];
		}

		size_t Size() const { return m_Size; }
		size_t Capacity() const { return m_Capacity; }

		T*& Data() { return m_Data; }
		T* Data() const { return m_Data; }

		void PushBack(const T& val) {
			if (m_Size == m_Capacity) ReAlloc(m_Capacity + m_Capacity / 2);
			
			assert(m_Data != nullptr);
			//m_Data[m_Size] = val;
			new (&m_Data[m_Size]) T(val);
			++m_Size;
		}

		void PushBack(T&& val) {
			if (m_Size == m_Capacity) ReAlloc(m_Capacity + m_Capacity / 2);

			assert(m_Data != nullptr);
			new (&m_Data[m_Size]) T(std::move(val));
			++m_Size;
		}

		void PopBack() {
			assert(m_Size != 0, "Cannot pop from an empty vector.");
			m_Data[--m_Size].~T();
		}

		template <typename... Args>
		void EmplaceBack(Args&&... args) {
			if (m_Size == m_Capacity) ReAlloc(m_Capacity + m_Capacity / 2);

			assert(m_Data != nullptr);
			new (&m_Data[m_Size]) T(std::forward<Args>(args)...);
			++m_Size;
		}

		void Resize(size_t newCapacity) {
			ReAlloc(newCapacity);
			m_Size = newCapacity;
		}

		void Clear() {
			for (size_t i = 0; i < m_Size; ++i) m_Data[i].~T();
			m_Size = 0;
		}

	private:
		void ReAlloc(size_t NewCapacity) {
#if DEBUG
			assert(m_Size <= NewCapacity, "Possible loss of data");
#endif

			T* NewBlock = (T*) ::operator new(NewCapacity * sizeof(T));
			//T* NewBlock = new T[NewCapacity];

			//assert(m_Data != nullptr);
			size_t size = m_Size < NewCapacity ? m_Size : NewCapacity;
			for (size_t i = 0; i < size; ++i) new (&NewBlock[i]) T(std::move(m_Data[i]));

		//	::operator delete(m_Data, m_Capacity * sizeof(T));
			for (size_t i = 0; i < m_Size; ++i) m_Data[i].~T();
			m_Data = NewBlock;

			m_Capacity = NewCapacity;
		}

	private:
		size_t m_Size;
		size_t m_Capacity;
		T* m_Data = nullptr;
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, zzstl::Vector<T>& vector) {
		std::cout << "-------------------------\n";
		std::cout << vector.Size() << " | " << vector.Capacity() << std::endl;
		for (size_t i = 0; i < vector.Size(); ++i) os << vector[i] << " | ";
		std::cout << "\n-------------------------\n";

		os << std::endl;
		return os;
	}
}
#endif