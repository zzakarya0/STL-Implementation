#ifndef Utility_H
#define Utility_H

namespace zzstl {
#define DEBUG 1

	template <typename T>
	void swap(T& lhs, T& rhs) {
		T Temp(std::move(lhs));
		lhs = std::move(rhs);
		rhs = std::move(Temp);
	}

	template <typename T>
	void fill(T* startPos, size_t numElements, const T& val) {
		for (size_t i = 0; i < numElements; ++i) startPos[i] = val;
	}


}

#endif
