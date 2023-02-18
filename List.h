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
	struct NodeBase 
	{
		constexpr NodeBase(const Type& Val) noexcept : m_Val(Val), m_pNext(nullptr) {}
		constexpr NodeBase(Type&& Val) noexcept : m_Val(std::move(Val)), m_pNext(nullptr) {}
		//constexpr ~NodeBase() noexcept;

		constexpr const Type& GetVal() const noexcept {return m_Val;}

	private:	//	Private member attributes
		Type  m_Val;
		NodeBase* m_pNext;

		//	friend classes/functions
		template <typename T, bool IsDoubly> friend class List;
		friend std::ostream& operator<<(std::ostream& os, const NodeBase& node) { return os << node.m_Val << " | "; }
	};

	template <typename Type>
	struct NodeBase<Type, true> 
	{
		constexpr NodeBase(const Type& Val) noexcept : m_Val(Val), m_pNext(nullptr), m_pPrev(nullptr) {}
		constexpr NodeBase(Type&& Val) noexcept : m_Val(std::move(Val)), m_pNext(nullptr), m_pPrev(nullptr) {}
		//constexpr ~NodeBase() noexcept;

	private:	//	Private member attributes
		Type  m_Val;
		NodeBase* m_pNext;
		NodeBase* m_pPrev;

		//	friend classes/functions
		template <typename T, bool IsDoubly> friend class List;
		friend std::ostream& operator<<(std::ostream& os, const NodeBase& node) { return os << node.m_Val << " | "; }
	};


	template <typename Type, bool IsDoubly>
	struct Node : public NodeBase<Type, IsDoubly>
	{
		using NodeBase = zzstl::NodeBase<Type, IsDoubly>;

		//	Ctors
		constexpr Node(const Type& Val) noexcept : NodeBase(Val) {}
		constexpr Node(Type&& Val) noexcept : NodeBase(std::move(Val)) {}

	};


	//template <typename Type, bool IsDoubly>
	//constexpr Node<Type, IsDoubly>::~Node() noexcept
	//{
	//	if (!m_pNext) return;
	//	
	//	delete m_pNext;
	//	m_pNext = nullptr;
	//	m_pPrev = nullptr;
	//}


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
		using NodeBase = Node::NodeBase;

	public:		///	Public constructors	
		inline constexpr List() noexcept : m_pHead(nullptr), m_pTail(nullptr) {}
		inline constexpr List(const Type& Val)  : m_pHead(new Node(Val)), m_pTail(m_pHead) {}
		inline constexpr List(Type&& Val) : m_pHead(new Node(std::move(Val))), m_pTail(m_pHead) {}
		inline constexpr ~List() noexcept { delete m_pHead;  m_pHead = m_pTail = nullptr; }

	public:		///	Public functionality

		//	Print functionality
		constexpr void Print_Forward() const noexcept;
		constexpr void Print_Backward() const noexcept requires IsDoubly;


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
	constexpr void List<Type, IsDoubly>::Print_Forward() const noexcept
	{
		const NodeBase* Node = m_pHead;
		while (Node)
		{
			std::cout << *Node;
			Node = Node->m_pNext;
		}
		std::cout << std::endl;
	}


	//template <typename Type, bool IsDoubly>
	//constexpr void List<Type, IsDoubly>::Print_Backward() const noexcept requires IsDoubly
	//{
	//	const Node* Node = m_pTail;
	//	while (Node)
	//	{
	//		std::cout << *Node;
	//		Node = Node->m_pPrev;
	//	}
	//	std::cout << std::endl;
	//}

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

/*	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Push_Back(Type&& Val) noexcept
	{
		if (!m_pHead) {
			m_pHead = new zzstl::Node<Type, IsDoubly>(std::move(Val));
			m_pTail = m_pHead;
			m_pHead->m_pNext = nullptr;
			

			m_pHead->m_pPrev = nullptr;

		}

		else {
			m_pTail->m_pNext = new zzstl::Node<Type, IsDoubly>(std::move(Val));

			m_pTail->m_pNext->m_pPrev = m_pTail;

			m_pTail = m_pTail->m_pNext;
	*/	//}
//	}
}

#endif 