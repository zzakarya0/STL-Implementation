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

	bool operator<(const Vector3& rhs) const {
		return (_x + _y + _z) < (rhs._x + rhs._y + rhs._z);;
	}
	void f() {};
};

std::ostream& operator<<(std::ostream& os, const Vector3& v3)  {
	std::cout << "(" << v3._x << "," << v3._y << "," << v3._z << ")";
	return os;
}

int main() {
	zzstl::Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.PushBack(5);
	//v.PushBack(6);
	//v.PushBack(7);
	//v.PushBack(8);
	//v.PushBack(9);
	//v.PushBack(10);
	//zzstl::Vector<int>::Iterator it = v.begin();

	//std::cout << it[0] << std::endl;
	//std::cout << it[3] << std::endl;
	//std::cout << it[5] << std::endl;
	//std::cout << it[9] << std::endl;
	//std::cout << it[10] << std::endl;


	std::vector<int> v1 = { 1, 2, 3, 4, 5 };
	std::vector<int>::iterator it1 = v1.begin();
	v1.insert(it1 + 2, 0);
	for (auto i : v1) std::cout << i << std::endl;


	zzstl::Vector<int>::Iterator it = v.begin(); ++it; ++it;
	std::cout << *it << std::endl;
	v.insert(it, 0);
	std::cout << v;

	return 0;
}