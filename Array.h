#ifndef Array_H
#define Array_H

#include <cassert>
#include "Utility.h"

namespace zzstl 
{
	/*
	*	New things learned:		. aggregate types	
	*/

	template <typename Array>
	class Array_Iterator
	{
	public:
		using ValueType = Array::ValueType;

		/*constexpr Array_Iterator(ValueType* Data) noexcept : DataPtr(Data) {}
		constexpr Array_Iterator(const Array_Iterator& rhs) : DataPtr(rhs.DataPtr) {}
		constexpr operator=(const Array_Iterator& rhs) : DataPtr(rhs.DataPtr) {}
		constexpr Array_Iterator(Array_Iterator&& rhs) = delete;
		constexpr operator=(Array_Iterator&& rhs) = delete;*/

		constexpr const ValueType& operator[](size_t pos) const noexcept { return DataPtr[pos]; }
		constexpr const ValueType* operator->() const noexcept { return DataPtr; }
		constexpr const ValueType& operator*() const noexcept { return *DataPtr; }

	private:
		ValueType* DataPtr;
	};

	template <typename Type, size_t S>
	struct  Array
	{
		// Type alias
		using ValueType = Type;

		//	Constructors offered by the Array class
		/*Array() = default;
		Array(const Array& rhs) = default;
		Array& operator=(const Array& rhs) = default;
		Array(Array&& rhs) = default;
		Array& operator=(Array&& rhs) = default;
		~Array() = default;*/

		// Public accessors 
		inline constexpr size_t Size() const noexcept { return S; }
		inline constexpr Type* Data() noexcept { return m_Data; }
		inline constexpr const Type* Data() const noexcept { return m_Data; }
		inline constexpr Type& Front() noexcept { return m_Data[0]; }
		inline constexpr const Type& Front() const noexcept { return m_Data[0]; }

		//	Overloaded operators
		Type& operator[] (size_t pos) noexcept;
		const Type& operator[] (size_t pos) const noexcept;

		//	Other functionnality
		inline constexpr bool Empty() const noexcept { return false; }
		constexpr void Print() const noexcept;
		void Fill(const Type& Val) noexcept;
		void Swap(Array& rhs) noexcept;
		constexpr const Type& At(size_t Where) const noexcept;

		//	Underlaying class container
		Type m_Data[S];
	};

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	Constructors provided by the class
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Default ctor, dtor to get aggregate intialization. (Can't even be  = default)
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	Overloaded operators
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, size_t S>
	Type& Array<Type, S>::operator[] (size_t pos) noexcept
	{
		assert(pos < S, "index out of array bounds");
		return m_Data[pos];
	}

	template <typename Type, size_t S>
	const Type& Array<Type, S>::operator[] (size_t pos) const noexcept
	{
		assert(pos < S, "index out of array bounds");
		return m_Data[pos];
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	Other functionality
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, size_t S>
	constexpr void Array<Type, S>::Print() const noexcept
	{
		for (size_t i = 0; i < S - 1; ++i) std::cout << m_Data[i] << " | ";
		std::cout << m_Data[S - 1] << std::endl;
	}

	template <typename Type, size_t S>
	void Array<Type, S>::Fill(const Type& Val) noexcept
	{
		for (size_t i = 0; i < S; ++i) m_Data[i].~T();
		for (size_t i = 0; i < S; ++i) m_Data[i] = Val;  
	}

	template <typename Type, size_t S>
	void Array<Type, S>::Swap(Array& rhs) noexcept
	{
		/*m_Data = &rhs.m_Data;
		rhs.m_Data = &temp;*/
		for (size_t i = 0; i < S; ++i)
			zzstl::Swap(m_Data[i], rhs.m_Data[i]);
	}

	template <typename Type, size_t S>
	constexpr const Type& Array<Type, S>::At(size_t Where) const noexcept
	{
		assert(Where < S, "index out of array bounds");
		return m_Data[Where];
	}
}
#endif