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
		constexpr Node(const Type& Val) noexcept : m_val(Val), m_pNext(nullptr) {}
		constexpr Node(Type&& Val) noexcept : m_val(std::move(Val)), m_pNext(nullptr) {}
		constexpr ~Node() noexcept { m_pNext = nullptr; }

	private:
		Type m_val;
		Node* m_pNext;

		// Friend functions/classes
		template <typename T, bool IsDoubly> friend class List;
		friend constexpr std::ostream& operator<<(std::ostream& os, const Node& Node) noexcept { os << Node.m_val << " --> "; return os; }
	};

	template <typename Type>
	class Node<Type, true>
	{
	public:
		constexpr Node(const Type& Val) noexcept : m_val(Val), m_pNext(nullptr), m_pPrev(nullptr) {}
		constexpr Node(Type&& Val) noexcept : m_val(std::move(Val)), m_pNext(nullptr), m_pPrev(nullptr) {}
		constexpr ~Node() noexcept { m_pNext = m_pPrev = nullptr; }

	private:
		Type m_val;
		Node* m_pNext;
		Node* m_pPrev;

		// Friend functions/classes
		template <typename T, bool IsDoubly> friend class List;
		friend constexpr std::ostream& operator<<(std::ostream& os, const Node& Node) noexcept { os << Node.m_val << " --> "; return os; }
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
	
		constexpr List() noexcept : m_pHead(nullptr), m_pTail(nullptr), m_size(0) {}
		constexpr List(const Type& Val)  : m_pHead(new Node(Val)), m_pTail(m_pHead), m_size(1) {}
		constexpr List(Type&& Val) : m_pHead(new Node(std::move(Val))), m_pTail(m_pHead), m_size(1) {}
		constexpr ~List() noexcept;

	public:
		// 
		constexpr bool isEmpty() const noexcept { return m_pHead == nullptr; }
		constexpr size_t size() const noexcept { return m_size; }

		//	Print functionality
		constexpr void printForward() const noexcept;
		constexpr void printBackward() const noexcept requires IsDoubly;

		//	Add to list
		constexpr void pushBack(const Type& Val) noexcept;
		constexpr void pushBack(Type&& Val) noexcept;
		constexpr void pushFront(const Type& Val) noexcept;
		constexpr void pushFront(Type&& Val) noexcept;

		constexpr void pushBack(const Type& Val) noexcept requires IsDoubly;
		constexpr void pushBack(Type&& Val) noexcept requires IsDoubly;
		constexpr void pushFront(const Type& Val) noexcept requires IsDoubly;
		constexpr void pushFront(Type&& Val) noexcept requires IsDoubly;

		// Pop from list
		constexpr void popBack() noexcept;
		constexpr void popFront() noexcept;	// no need for specialized popFront()

		constexpr void popBack() noexcept requires IsDoubly;

	private:
		Node* m_pHead;
		Node* m_pTail;
		size_t m_size;
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
	constexpr void List<Type, IsDoubly>::printForward() const noexcept
	{
		const Node* curNode = m_pHead;
		while (curNode)
		{
			std::cout << *curNode;
			curNode = curNode->m_pNext;
		}
		std::cout << "Null\n";
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::printBackward() const noexcept requires IsDoubly
	{
		const Node* curNode = m_pTail;
		while (curNode)
		{
			std::cout << *curNode;
			curNode = curNode->m_pPrev;
		}
		std::cout << "Null\n";
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	Add to list
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::pushBack(const Type& Val) noexcept
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
		++m_size;
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::pushBack(Type&& Val) noexcept
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
		++m_size;
	}
	
	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::pushFront(const Type& Val) noexcept
	{
		Node* newNode = new zzstl::Node<Type, IsDoubly>(Val);
		if (!m_pHead)
		{
			m_pHead = newNode;
			m_pTail = m_pHead;
		}
		else
		{
			newNode->m_pNext = m_pHead;
			m_pHead = newNode;
		}
		++m_size;
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::pushFront(Type&& Val) noexcept
	{
		Node* newNode = new zzstl::Node<Type, IsDoubly>(std::move(Val));
		if (!m_pHead)
		{
			m_pHead = newNode;
			m_pTail = m_pHead;
		}
		else
		{
			newNode->m_pNext = m_pHead;
			m_pHead = newNode;
		}
		++m_size;
	}


	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::pushBack(const Type& Val) noexcept requires IsDoubly
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
		++m_size;
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::pushBack(Type&& Val) noexcept requires IsDoubly
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
		++m_size;
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::pushFront(const Type& Val) noexcept requires IsDoubly
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
		++m_size;
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::pushFront(Type&& Val) noexcept requires IsDoubly
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
		++m_size;
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	Pop from list
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::popFront() noexcept
	{
		if (isEmpty()) return;

		Node* newHead = m_pHead->m_pNext;
		delete m_pHead;
		m_pHead = newHead;
		--m_size;
	}
		
	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::popBack() noexcept
	{
		if (isEmpty()) return;
		if (m_size == 1) {
			delete m_pHead;
			m_pHead = m_pTail = nullptr;
			m_size = 0;
			return;
		}

		Node* curr = m_pHead;
		while (curr->m_pNext->m_pNext) curr = curr->m_pNext;

		delete curr->m_pNext;
		m_pTail = curr;
		m_pTail->m_pNext = nullptr;
		--m_size;
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::popBack() noexcept requires IsDoubly
	{
		if (isEmpty()) return;

		Node* newTail = m_pTail->m_pPrev;
		delete m_pTail;
		m_pTail = newTail;
		m_pTail->m_pNext = nullptr;
		--m_size;
	}
}

#endif 