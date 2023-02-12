#ifndef LIST_H
#define LIST_H


namespace zzstl
{
	template <typename Type>
	struct Node
	{
		inline constexpr Node(const Type& Val, Node* NextNode) noexcept : m_Val(Val), m_Next(NextNode) {}
		inline constexpr Node(Type&& Val, Node* NextNode) noexcept : m_Val(std::move(Val)), m_Next(NextNode) {}
		inline constexpr Node(const Node& Rhs) noexcept : m_Val(Rhs.m_Val), m_Next(Rhs.m_Next) {}
		inline constexpr ~Node() noexcept;

		inline constexpr Node* GetNext() const noexcept { return m_Next; }

	private:	// Private member functions
		friend std::ostream& operator<<(std::ostream& os, const Node<Type>& Node) noexcept;

	private:	//Private member attributes
		Type  m_Val;
		Node* m_Next;
	};

	template <typename Type>
	constexpr Node<Type>::~Node() noexcept
	{
		Node<Type>* Node = GetNext();
		while (Node) 
		{
			zzstl::Node<Type>* Next = Node->GetNext();
			delete Node;
			Node = Next;
		}
	}

	template <typename Type>
	std::ostream& operator<<(std::ostream& os, const Node<Type>& Node) noexcept
	{
		std::cout << Node.m_Val << " | ";
		std::cout << std::endl;
		return os;
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	List Class both singly and doubly based on: bool IsDoubly; 
	//	Singly by default;
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, bool IsDoubly = false>
	class List
	{
	public:
		using Node = zzstl::Node<Type>;

	public:		//Public constructors	
		inline constexpr List() noexcept : m_Head(nullptr) {}
		inline constexpr List(const Type& Val)  : m_Head(new Node(Val, nullptr)) {}
		inline constexpr List(Type&& Val) : m_Head(new Node(std::move(Val), nullptr)) {}
		inline constexpr List(const List& Rhs) noexcept;
		inline constexpr ~List() noexcept { delete m_Head; }

	public:		//Public functionality
		constexpr void Print() const noexcept;

		constexpr void Push_Back(const Type& Val) noexcept;
		//constexpr void Push_Back(Type&& Val) noexcept;
		//constexpr void Push_Front(const Type& Val) const noexcept;
		//constexpr void Push_Front(Type&& Val) const noexcept;


	private:	//Private member attributes
		Node* m_Head;
#if IsDoubly
		Node* m_Back;
#endif
	};

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	List Constructors
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, bool IsDoubly>
	inline constexpr List<Type, IsDoubly>::List(const List& Rhs) noexcept
	{
		m_Head = new Node(Rhs);

	}



	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//	Public functionality
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Print() const noexcept
	{
		const Node* Node = m_Head;
		while (Node)
		{
			std::cout << *Node << " | ";
			Node = Node->GetNext();
		}
		std::cout << std::endl;
	}

	template <typename Type, bool IsDoubly>
	constexpr void List<Type, IsDoubly>::Push_Back(const Type& Val) noexcept
	{
#if IsDoubly
		m_Back->GetNext() = new zzstl::Node(Val, nullptr);
		m_Back = m_Back->GetNext();
#else
		const Node* Node = m_Head;
		while (Node->GetNext()) Node = Node->GetNext();
		Node->GetNext() = new zzstl::Node<Type>(Val, nullptr);
		return;
#endif
	}

//	template <typename Type, bool IsDoubly>
//	constexpr void List<Type, IsDoubly>::Push_Back(Type&& Val) noexcept
//	{
//#if IsDoubly
//		m_Back->GetNext() = new zzstl::Node(std::move(Val), nullptr);
//		m_Back = m_Back->GetNext();
//#else
//		const Node* Node = m_Head;
//		while (Node->GetNext()) Node = Node->GetNext();
//		Node->GetNext() = new zzstl::Node<Type>(std::move(Val), nullptr);
//		return;
//#endif
//	}
}

#endif 