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
	//zzstl::Vector<int> v;

	//v.PushBack(1);
	//v.PushBack(2);
	//v.PushBack(3);
	//v.PushBack(4);
	//v.PushBack(5);
	//v.PushBack(6);
	//v.PushBack(7);
	//v.PushBack(8);
	//v.PushBack(9);
	//v.PushBack(10);
	//std::cout << v;

	////for (zzstl::Iterator<int> it = v.begin(); it != v.end(); ++it) std::cout << *it << std::endl;
	//for (int i : v) std::cout << i << std::endl;

	std::vector<Vector3> v;
	std::vector<Vector3>::iterator it = v.begin();
	it->f();

	zzstl::Vector<Vector3> v11;
	zzstl::Vector<Vector3>::Iterator it11 = v11.begin();
	(*it11).f();
	it11->f();

	Vector3 v3;
	Vector3* pv3 = &v3;
	pv3->f();

	std::cin.get();
}