#include <iostream>
#include "List.h"
#include <list>


struct Vector3 {
	float _x, _y, _z;
	Vector3(float f = 0.f) : _x(f), _y(f), _z(f) { std::cout << "Constr\n";
	}
	Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) { std::cout << "Constr\n";
	}
	Vector3(const Vector3& v) { std::cout << "Copy Constr\n";
	_x = v._x;
	_y = v._y;
	_z = v._z;
	}
	Vector3(Vector3&& v) { std::cout << "Move Constr\n";
	_x = v._x;
	_y = v._y;
	_z = v._z;
	}
	Vector3& operator=(const Vector3& v) { 
		std::cout << "Copy operat\n"; 
		_x = v._x;
		_y = v._y;
		_z = v._z;
		return *this;
	}
	Vector3& operator=(Vector3&& v) { 
		std::cout << "Move operat\n";
		_x = v._x;
		_y = v._y;
		_z = v._z;
		return *this;
	}
	~Vector3() { std::cout << "Destructor\n"; }

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
	std::list<int> stdL(3);
	int a = 5;
	stdL.push_back(a);

	zzstl::List<Vector3> lst(Vector3(0.f));
	lst.Push_Back(Vector3(4.f));
	lst.Print();


	std::cin.get();
}