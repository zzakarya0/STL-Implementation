#ifndef Utility_H
#define Utility_H

namespace zzstl {
#define DEBUG 1

	template <typename T>
	inline void Swap(T& lhs, T& rhs) {
		T Temp(std::move(lhs));
		lhs = std::move(rhs);
		rhs = std::move(Temp);
	}

	//Expect error with Vector(int,T)
	template <typename T>
	inline void Fill(T* startPos, size_t numElements, const T& val) {
		for (size_t i = 0; i < numElements; ++i) {

			startPos[i] = val;
			//new (&startPos[i]) T(val);
		}
	}

	template <typename T, typename... Args>
	inline void Fill_InPlace(T* startPos, size_t numElements, Args&&... args) {
		for (size_t i = 0; i < numElements; ++i) new (&startPos[i]) T(std::forward<Args>(args)...);
	}

	template <typename T>
	constexpr inline const T& Min(const T& val1, const T& val2) noexcept {
		return val1 < val2 ? val1 : val2;
	}

	template <typename T>
	constexpr inline const T& Max(const T& val1, const T& val2) noexcept {
		return val1 > val2 ? val1 : val2;
	}
}

#endif
