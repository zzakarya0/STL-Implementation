#ifndef LIST_H
#define LIST_H


namespace zzstl
{
	template <typename Type>
	struct Node
	{
		inline constexpr Node(Type Val, Node* NextNode) noexcept : m_Val(Val), m_Next(NextNode) {}
		inline constexpr Node(const Node& Rhs) noexcept : m_Val(Rhs.m_Val), m_Next(Rhs.m_Next) {}
		constexpr ~Node() noexcept;

		inline constexpr Node* GetNext() noexcept { return m_Next; }

	private:	//Private member attributes
		Type  m_Val;
		Node* m_Next;
	};

	template <typename Type>
	constexpr Node<Type>::~Node() noexcept
	{
		while (m_Next) 
		{
			Node* nxtNode = m_Next->m_Next;
			delete m_Next;
			m_Next = nxtNode;
		}
	}

	template <typename Type, bool IsDoubly = false>
	class List
	{
	public:
		using Node = Node<Type>;

	public:		//Public constructors	
		inline constexpr List() noexcept : m_Head(nullptr) {}
		inline constexpr List(Type Val)  : m_Head(new Node(Val, nullptr)) {}
		inline constexpr List(const List& Rhs) noexcept;
		inline constexpr ~List() noexcept { delete m_Head; }

	public:		//Public functionality
		constexpr void Print() noexcept;

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
	constexpr void List<Type, IsDoubly>::Print() noexcept
	{
		Node* tempPtr = m_Head;
		while (tempPtr) 
		{
			std::cout << *tempPtr << " | ";
			tempPtr = m_Head->GetNext();
		}
		std::cout << std::endl;
	}
}

#endif 