#include <iostream>

#include "Vector.h"
#include <vector>
#include <string>

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
};

std::ostream& operator<<(std::ostream& os, const Vector3& v3)  {
	std::cout << "(" << v3._x << "," << v3._y << "," << v3._z << ")";
	return os;
}

int main() {
	/*zk::Vector<Vector3> v;

	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(11.f, 13.f,19.f));
	std::cout << v;

	v.PopBack();
	std::cout << v;
	v.EmplaceBack();
	v.EmplaceBack(5.f);
	v.EmplaceBack(1.f, 2.f, 3.f);
	std::cout << v;

	v.PopBack();
	v.PopBack();
	v.PopBack();
	std::cout << v;

	v.Clear();
	std::cout << v;*/


	zzstl::Vector<std::string> v;

	v.PushBack("a");
	v.PushBack("b");
	const std::string str("CST");
	v.PushBack(str);
	std::cout << v;

	v.PopBack();
	std::cout << v;
	v.EmplaceBack();
	v.EmplaceBack("c");
	v.EmplaceBack("d");
	std::cout << v;

	v.PopBack();
	v.PopBack();
	v.PopBack();
	std::cout << v;

	v.Clear();
	std::cout << v;

	std::cin.get();
}