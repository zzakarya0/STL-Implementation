#ifndef LIST_H
#define LIST_H


namespace zzstl
{
	/*
		New things learned:		. access modifier for friend functions doesn't matter
								. function inside a template class is not a function template
								. function template require
								. template class specialization
	*/

	template <typename Type, bool IsDoubly>
	class Node
	{
		constexpr Node(const Type& Val) noexcept : m_Val(Val), m_pNext(nullptr) {}
		constexpr Node(Type&& Val) noexcept : m_Val(std::move(Val)), m_pNext(nullptr) {}
		constexpr ~Node() noexcept { m_pNext = nullptr; }

	private:
		Type m_Val;
		Node* m_pNext;

		// Friend functions/classes
		template <typename T, bool IsDoubly> friend class List;
		friend constexpr std::ostream& operator<<(std::ostream& os, const Node& Node) noexcept { os << Node.m_Val << " --> "; return os; }
	};

	template <typename Type>
	class Node<Type, true>
	{
	public:
		constexpr Node(const Type& Val) noexcept : m_Val(Val), m_pNext(nullptr), m_pPrev(nullptr) {}
		constexpr Node(Type&& Val) noexcept : m_Val(std::move(Val)), m_pNext(nullptr), m_pPrev(nullptr) {}
		constexpr ~Node() noexcept { m_pNext = m_pPrev = nullptr; }

	private:
		Type m_Val;
		Node* m_pNext;
		Node* m_pPrev;

		// Friend functions/classes
		template <typename T, bool IsDoubly> friend class List;
		friend constexpr std::ostream& operator<<(std::ostream& os, const Node& Node) noexcept { os << Node.m_Val << " --> "; return os; }
	};


	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	List Class both singly and doubly based on: bool IsDoubly; 
	//	Singly by default;
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, bool IsDoubly = false> 
	class List
	{
	public:
		using Node = zzstl::Node<Type, IsDoubly>;
	
		constexpr List() noexcept : m_pHead(nullptr), m_pTail(nullptr) {}
		constexpr List(const Type& Val)  : m_pHead(new Node(Val)), m_pTail(m_pHead) {}
		constexpr List(Type&& Val) : m_pHead(new Node(std::move(Val))), m_pTail(m_pHead) {}
		constexpr ~List() noexcept;

	public:
		// 
		constexpr bool IsEmpty() const noexcept { return m_pHead == nullptr; }

		//	Print functionality
		constexpr void Print_Forward() const noexcept;
		constexpr void Print_Backward() const noexcept requires IsDoubly;

		//	Add to list
		constexpr void Push_Back(const Type& Val) noexcept;
		constexpr void Push_Back(Type&& Val) noexcept;
		constexpr void Push_Back(const Type& Val) noexcept requires IsDoubly;
		constexpr void Push_Back(Type&& Val) noexcept requires IsDoubly;
		constexpr void Push_Front(const Type& Val) noexcept;
		constexpr void Push_Front(Type&& Val) noexcept;
		constexpr void Push_Front(const Type& Val) noexcept requires IsDoubly;
		constexpr void Push_Front(Type&& Val) noexcept requires IsDoubly;

		// Pop from list
		constexpr void Pop_Back() noexcept;
		constexpr void Pop_Front() noexcept;
		constexpr void Pop_Back() noexcept requires IsDoubly;
		constexpr void Pop_Front() noexcept requires IsDoubly;

	private:
		Node* m_pHead;
		Node* m_pTail;
		size_t Size;
	};

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	List Ctors
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, bool IsDoubly>
	constexpr List<Type, IsDoubly>::~List() noexcept
	{
		while (m_pHead) {
			Node* temp = m_pHead->m_pNext;

			delete m_pHead;
			m_pHead = temp;
		}
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	Print functionality
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Print_Forward() const noexcept
	{
		const Node* CurrNode = m_pHead;
		while (CurrNode)
		{
			std::cout << *CurrNode;
			CurrNode = CurrNode->m_pNext;
		}
		std::cout << "Null\n";
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Print_Backward() const noexcept requires IsDoubly
	{
		const Node* CurrNode = m_pTail;
		while (CurrNode)
		{
			std::cout << *CurrNode;
			CurrNode = CurrNode->m_pPrev;
		}
		std::cout << "Null\n";
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	Add to list
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Push_Back(const Type& Val) noexcept
	{
		if (!m_pHead)
		{
			m_pHead = new zzstl::Node<Type, IsDoubly>(Val);
			m_pTail = m_pHead;
		}
		else
		{
			m_pTail->m_pNext = new zzstl::Node<Type, IsDoubly>(Val);
			m_pTail = m_pTail->m_pNext;
		}
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Push_Back(Type&& Val) noexcept
	{
		if (!m_pHead) 
		{
			m_pHead = new zzstl::Node<Type, IsDoubly>(std::move(Val));
			m_pTail = m_pHead;
		}
		else 
		{
			m_pTail->m_pNext = new zzstl::Node<Type, IsDoubly>(std::move(Val));
			m_pTail = m_pTail->m_pNext;
		}
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Push_Back(const Type& Val) noexcept requires IsDoubly
	{
		if (!m_pHead)
		{
			m_pHead = new zzstl::Node<Type, IsDoubly>(Val);
			m_pTail = m_pHead;
		}
		else
		{
			m_pTail->m_pNext = new zzstl::Node<Type, IsDoubly>(Val);
			m_pTail->m_pNext->m_pPrev = m_pTail;
			m_pTail = m_pTail->m_pNext;
		}
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Push_Back(Type&& Val) noexcept requires IsDoubly
	{
		if (!m_pHead)
		{
			m_pHead = new zzstl::Node<Type, IsDoubly>(std::move(Val));
			m_pTail = m_pHead;
		}
		else
		{
			m_pTail->m_pNext = new zzstl::Node<Type, IsDoubly>(std::move(Val));
			m_pTail->m_pNext->m_pPrev = m_pTail;
			m_pTail = m_pTail->m_pNext;
		}
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Push_Front(const Type& Val) noexcept
	{
		Node* NewNode = new zzstl::Node<Type, IsDoubly>(Val);
		if (!m_pHead)
		{
			m_pHead = NewNode;
			m_pTail = m_pHead;
		}
		else
		{
			NewNode->m_pNext = m_pHead;
			m_pHead = NewNode;
		}
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Push_Front(const Type& Val) noexcept requires IsDoubly
	{
		if (!m_pHead)
		{
			m_pHead = new zzstl::Node<Type, IsDoubly>(Val);
			m_pTail = m_pHead;
		}
		else
		{
			m_pHead->m_pPrev = new zzstl::Node<Type, IsDoubly>(Val);
			m_pHead->m_pPrev->m_pNext = m_pHead;
			m_pHead = m_pHead->m_pPrev;
		}
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Push_Front(Type&& Val) noexcept
	{
		Node* NewNode = new zzstl::Node<Type, IsDoubly>(std::move(Val));
		if (!m_pHead)
		{
			m_pHead = NewNode;
			m_pTail = m_pHead;
		}
		else
		{
			NewNode->m_pNext = m_pHead;
			m_pHead = NewNode;
		}
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Push_Front(Type&& Val) noexcept requires IsDoubly
	{
		if (!m_pHead)
		{
			m_pHead = new zzstl::Node<Type, IsDoubly>(std::move(Val));
			m_pTail = m_pHead;
		}
		else
		{
			m_pHead->m_pPrev = new zzstl::Node<Type, IsDoubly>(std::move(Val));
			m_pHead->m_pPrev->m_pNext = m_pHead;
			m_pHead = m_pHead->m_pPrev;
		}
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	Pop from list
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Pop_Back() noexcept
	{
		if (IsEmpty()) return;

		Node* Curr = m_pHead;
		while (Curr->m_pNext->m_pNext) Curr = Curr->m_pNext;

		delete Curr->m_pNext;
		m_pTail = Curr;
		m_pTail->m_pNext = nullptr;
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Pop_Back() noexcept requires IsDoubly
	{
		if (IsEmpty()) return;

		Node* PrevTail = m_pTail;
		m_pTail = m_pTail->m_pPrev;
		delete PrevTail;
		m_pTail->m_pNext = nullptr;
	}
}

#endif 