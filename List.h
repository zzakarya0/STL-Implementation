#ifndef LIST_H
#define LIST_H


namespace zzstl
{
	/*
		New things learned:		. access modifier for friend functions doesn't matter
								. function inside a template class is not a function template
	*/

	template <typename Type, bool IsDoubly>
	struct Node
	{
		template <typename T, bool IsDoubly> friend class List;
		friend std::ostream& operator<<(std::ostream& os, const Node& node) { return os << node.m_Val << " | "; }


		inline constexpr Node(const Type& Val) noexcept : m_Val(Val), m_pNext(nullptr) 
#if IsDoubly	
		, m_pPrev(nullptr) 
#endif	
		{}

		inline constexpr Node(Type&& Val) noexcept : m_Val(std::move(Val)), m_pNext(nullptr)
#if IsDoubly	
		, m_pPrev(nullptr)
#endif	
		{}

		inline constexpr ~Node() noexcept;


	private:	//Private member attributes
		Type  m_Val;
		Node* m_pNext;
#if IsDoubly
		Node* m_pPrev;
#endif
	};

	template <typename Type, bool IsDoubly>
	constexpr Node<Type, IsDoubly>::~Node() noexcept
	{
		if (!m_pNext) return;
		
		delete m_pNext;
		m_pNext = nullptr;
#if IsDoubly
		m_pPrev = nullptr;
#endif
	}


	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	List Class both singly and doubly based on: bool IsDoubly; 
	//	Singly by default;
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, bool IsDoubly = false>
	class List
	{
	public:
		using Node = zzstl::Node<Type, IsDoubly>;

	public:		//Public constructors	
		inline constexpr List() noexcept : m_pHead(nullptr), m_pTail(nullptr) {}
		inline constexpr List(const Type& Val)  : m_pHead(new Node(Val)), m_pTail(m_pHead) {}
		inline constexpr List(Type&& Val) : m_pHead(new Node(std::move(Val))), m_pTail(m_pHead) {}
		//inline constexpr List(const List& Rhs) noexcept;
		inline constexpr ~List() noexcept { delete m_pHead;  m_pHead = m_pTail = nullptr; }

	public:		//Public functionality
		constexpr void Print() const noexcept;

		//constexpr void Push_Back(const Type& Val) noexcept;
		constexpr void Push_Back(Type&& Val) noexcept;
		//constexpr void Push_Front(const Type& Val) const noexcept;
		//constexpr void Push_Front(Type&& Val) const noexcept;


	private:	//Private member attributes
		Node* m_pHead;
		Node* m_pTail;
	};

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	List Constructors
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	Public functionality
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Print() const noexcept
	{
		const Node* Node = m_pHead;
		while (Node)
		{
			std::cout << *Node;
			Node = Node->m_pNext;
		}
		std::cout << std::endl;
	}

//	template <typename Type, bool IsDoubly>
//	constexpr void List<Type, IsDoubly>::Push_Back(const Type& Val) noexcept
//	{
//#if IsDoubly
//		m_pTail->m_Next = new zzstl::Node(Val, nullptr);
//		m_pTail = m_pTail->m_Next;
//#else
//		Node* Node = m_pHead;
//		while (Node->m_pNext) Node = Node->m_pNext;
//		Node->m_pNext = new zzstl::Node<Type, IsDoubly>(Val, nullptr);
//		return;
//#endif
//	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Push_Back(Type&& Val) noexcept
	{
#if IsDoubly
		/*m_pTail->m_Next = new zzstl::Node(std::move(Val), nullptr);
		m_pTail = m_pTail->m_Next;*/
#else
		m_pTail->m_pNext = new zzstl::Node<Type, IsDoubly>(std::move(Val));
		m_pTail = m_pTail->m_pNext;
#endif
	}
}

#endif 