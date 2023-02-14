#ifndef Array_H
#define Array_H

#include <cassert>
#include "Utility.h"
using namespace std;

namespace zzstl 
{
	/*
		New things learned:		. aggregate types,	. memory allocation is done before calling ctors
	*/

	template <typename Type, size_t S>
	class Array_Const_Iterator
	{
	public:

		//	Constructors
		explicit constexpr Array_Const_Iterator(const Type* Data, size_t pos) noexcept : m_DataPtr(Data + pos), m_Offset(pos) { m_CheckOffset(m_Offset); }
		constexpr Array_Const_Iterator(const Array_Const_Iterator& rhs) noexcept : m_DataPtr(rhs.m_DataPtr), m_Offset(rhs.m_Offset) {}
		constexpr Array_Const_Iterator& operator=(const Array_Const_Iterator& rhs) noexcept {
			if (*this == rhs) return *this;
			m_DataPtr = rhs.m_DataPtr;
			m_Offset = rhs.m_Offset;
			return *this;
		}
		constexpr Array_Const_Iterator(Array_Const_Iterator&& rhs) = delete;
		constexpr Array_Const_Iterator& operator=(Array_Const_Iterator&& rhs) = delete;

		//	Overloaded operators
		constexpr const Type& operator[](size_t pos) const noexcept { return m_DataPtr[pos]; }
		constexpr const Type* operator->() const noexcept { return m_DataPtr; }
		constexpr const Type& operator*() const noexcept { return *m_DataPtr; }
		constexpr bool operator==(const Array_Const_Iterator& rhs) const noexcept { return m_DataPtr == rhs.m_DataPtr; }
		constexpr bool operator!=(const Array_Const_Iterator& rhs) const noexcept { return m_DataPtr != rhs.m_DataPtr; }
		constexpr void operator++() noexcept { m_CheckOffset(m_Offset + 1); ++m_DataPtr; ++m_Offset; }
		constexpr void operator--() noexcept { m_CheckOffset(m_Offset - 1); --m_DataPtr; --m_Offset; }

	private: //	private member functions
		constexpr bool m_CheckOffset(size_t Offset) const noexcept {
			assert(Offset >= 0, "Cannot iterator past the container start");
			assert(Offset < S, "Cannot iterator past the container end");
			return true;
		}

	private: // private data attributes
		const Type* m_DataPtr;
		size_t m_Offset; // offset of ptr to beginning of contaner
	};

	template <typename Type, size_t S>
	class Array_Iterator : public Array_Const_Iterator<Type, S>
	{
	public:
		using Super = Array_Const_Iterator<Type, S>;

		explicit constexpr Array_Iterator(Type* Data, size_t pos) noexcept : Super(Data, pos) {}
		constexpr Array_Iterator(const Array_Iterator& rhs) noexcept : Super(rhs) {}
		constexpr Array_Iterator& operator=(const Array_Iterator& rhs) noexcept {	// NEEDS TEST!!
			Super::operator=(rhs);												
			return *this;
		}

		constexpr Type& operator[](size_t pos) const noexcept { return const_cast<Type&>(Super::operator[](pos)); }
		constexpr Type* operator->() const noexcept { return const_cast<Type*>(Super::operator->()); }
		constexpr Type& operator*() const noexcept { return const_cast<Type&>(Super::operator*()); }
	};


	template <typename Type, size_t S>
	struct  Array
	{
		// Type alias
		using ValueType = Type;
		using Const_Iterator = Array_Const_Iterator<Type, S>;
		using Iterator = Array_Iterator<Type, S>;

		/*	Ctors ommited to enable aggregate initialization
		Array() = default;
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

		// Iterators functionality
		inline constexpr Const_Iterator begin() const noexcept { return Const_Iterator(m_Data, 0); }
		inline constexpr Iterator begin() noexcept { return Iterator(m_Data, 0); }
		inline constexpr Const_Iterator cbegin() const noexcept { return begin(); }

		inline constexpr Const_Iterator end() const noexcept { return Const_Iterator(m_Data, S); }
		inline constexpr Iterator end() noexcept { return Iterator(m_Data, S); }
		inline constexpr Const_Iterator cend() const noexcept { return end(); }

		//	Underlaying container
		Type m_Data[S];
	};


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