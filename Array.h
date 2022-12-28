#ifndef Array_H
#define Array_H

#include "Utility.h"

namespace zzstl {

	template <typename T, size_t S>
	class Array {
	public:
		explicit Array() { memset(m_Data, 0, S * sizeof(T)); }
		Array(const Array& rhs) = default;
		Array& operator=(const Array& rhs) = default;
		Array(Array&& rhs) = default;
		Array& operator=(Array&& rhs) = default;
		~Array() = default;

		constexpr size_t Size() const { return S; }

		T& operator[] (size_t pos) {
			if (S < pos) __debugbreak();
			return m_Data[pos];
		}

		const T& operator[] (size_t pos) const {
			if (S < pos) __debugbreak();
			return m_Data[pos];
		}

		T* Data() { return m_Data; }
		const T* Data() const { return m_Data; }

		void swap(Array& rhs) {
			for (size_t i = 0; i < S; ++i) zk::swap(m_Data[i], rhs[i]);
		}

		void fill(const T& value) {
			for (size_t i = 0; i < S; ++i) m_Data[i] = value;
		}

	private:
		T m_Data[S];
	};

}
#endif