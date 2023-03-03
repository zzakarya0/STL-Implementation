#include <iostream>
#include "List.h"
#include <list>


struct Vector3 {
	float _x, _y, _z;
	Vector3(float f = 0.f) : _x(f), _y(f), _z(f) { //std::cout << "Constr\n";
	}
	Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) { //std::cout << "Constr\n";
	}
	Vector3(const Vector3& v) { std::cout << "Copy Constr\n";
		_x = v._x;
		_y = v._y;
		_z = v._z;
	}
	Vector3(Vector3&& v) { //std::cout << "Move Constr\n";
		_x = v._x;
		_y = v._y;
		_z = v._z;

	v._x = 0;
	v._y = 0;
	v._z = 0;
	}
	Vector3& operator=(const Vector3& v) { 
		std::cout << "Copy operat\n"; 
		_x = v._x;
		_y = v._y;
		_z = v._z;
		return *this;
	}
	Vector3& operator=(Vector3&& v) { 
		//std::cout << "Move operat\n";
		_x = v._x;
		_y = v._y;
		_z = v._z;
		return *this;
	}
	~Vector3() { //std::cout << "Destructor\n"; 
	}

	bool operator<(const Vector3& rhs) const {
		return (_x + _y + _z) < (rhs._x + rhs._y + rhs._z);;
	}
	void f() {};
};

std::ostream& operator<<(std::ostream& os, const Vector3& v3)  {
	std::cout << "(" << v3._x << "," << v3._y << "," << v3._z << ")";
	return os;
}

int main()
{
	//std::list<int> stdL(3);
	//int a = 5;
	//stdL.push_back(a);
	//stdL.size();
	
	Vector3 v9(9.f);
	Vector3 v10(10.f);
	Vector3 vn4(-4.f);
	Vector3 vn5(-5.f);

	zzstl::List<Vector3> lst(Vector3(0.f, 1.f, 2.f));
	lst.pushBack(Vector3(3.f, 4.f, 5.f));
	lst.pushBack(Vector3(6.f));
	lst.pushBack(Vector3(7.f));
	lst.pushBack(Vector3(8.f));

	std::cout << "Size: " << lst.size() << std::endl;
	lst.printForward();
	//lst.Print_Backward();

	lst.pushFront(Vector3(-1.f));
	lst.pushFront(Vector3(-2.f));
	lst.pushFront(Vector3(-3.f));

	std::cout << "Size: " << lst.size() << std::endl;
	lst.printForward();
	//lst.Print_Backward();

	lst.pushBack(v9);
	lst.pushBack(v10);
	lst.pushFront(vn4);
	lst.pushFront(vn5);

	std::cout << "Size: " << lst.size() << std::endl;
	lst.printForward();
	//lst.Print_Backward();

	lst.popBack();
	lst.popBack();

	std::cout << "Size: " << lst.size() << std::endl;
	lst.printForward();
	//lst.Print_Backward();

	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	lst.popBack();
	std::cout << "Size: " << lst.size() << std::endl;

	lst.pushFront(Vector3(-1.f));
	lst.pushFront(Vector3(-2.f));
	lst.pushFront(Vector3(-3.f));

	std::cout << "Size: " << lst.size() << std::endl;
	lst.printForward();

	lst.pushBack(std::move(v9));
	lst.pushBack(std::move(v10));
	lst.pushFront(std::move(vn4));
	lst.pushFront(std::move(vn5));

	std::cout << "Size: " << lst.size() << std::endl;
	lst.printForward();

	lst.pushBack(v9);
	lst.pushBack(v10);
	lst.pushFront(vn4);
	lst.pushFront(vn5);

	std::cout << "Size: " << lst.size() << std::endl;
	lst.printForward();

	std::cin.get();
}