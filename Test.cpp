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
};

std::ostream& operator<<(std::ostream& os, const Vector3& v3)  {
	std::cout << "(" << v3._x << "," << v3._y << "," << v3._z << ")";
	return os;
}

int main() {
	//std::vector<Vector3> v1;
	//v1.front()

	zzstl::Vector<int> v11;
	v11.PushBack(1);
	//std::cout << v11.Front() << std::endl;
	//v11.Back() = 3100;
	//std::cout << v11.Front() << std::endl;


	auto v(std::move(v11));
	std::cout << v;
	std::cout << v11;

	/*std::vector<int> v1(10);
	std::cout << v1.size() << " | " << v1.capacity() << std::endl;
	for (int val : v1) std::cout << val << " | ";
	std::cout << std::endl;

	std::vector<int> v2;
	v2.push_back(10);
	v2.push_back(100);

	std::cout << v2.size() << " | " << v2.capacity() << std::endl;
	for (int val : v2) std::cout << val << " | ";
	std::cout << std::endl;

	v2 = v1;
	std::cout << v2.size() << " | " << v2.capacity() << std::endl;
	for (int val : v2) std::cout << val << " | ";
	std::cout << std::endl;

	std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";

	zzstl::Vector<int> v11(10);

	zzstl::Vector<int> v21;
	v21.PushBack(10);
	v21.PushBack(100);

	std::cout << v21; 

	v21 = v11;
	std::cout << v21;*/


	/*zzstl::Vector<Vector3> v(2, Vector3(1.f));

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
	std::cout << v;


	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	v.PushBack(Vector3(10.f));
	std::cout << v;*/


	//zzstl::Vector<std::string> v(2);
	//v.PushBack("a");
	//v.PushBack("b");
	//const std::string str("CST");
	//v.PushBack(str);
	//std::cout << v;

	//v.PopBack();
	//std::cout << v;
	//v.EmplaceBack();
	//v.EmplaceBack("c");
	//v.EmplaceBack("d");
	//std::cout << v;

	//v.PopBack();
	//v.PopBack();
	//v.PopBack();
	//std::cout << v;

	//v.Clear();
	//std::cout << v;

	/*std::vector<Vector3> v(10, Vector3(2005));
	std::cout << v.size() << " | " << v.capacity() << std::endl;
	std::cout << "-------------------------\n";
	std::cout << v.size() << " | " << v.capacity() << std::endl;
	for (size_t i = 0; i < v.size(); ++i) std::cout << v[i] << " | ";
	std::cout << "\n-------------------------\n";

	v.resize(5);
	std::cout << v.size() << " | " << v.capacity() << std::endl;
	std::cout << "-------------------------\n";
	std::cout << v.size() << " | " << v.capacity() << std::endl;
	for (size_t i = 0; i < v.size(); ++i) std::cout << v[i] << " | ";
	std::cout << "\n-------------------------\n";

	std::cout << "****************************************************************************************\n";
	zzstl::Vector<Vector3> v2(10, Vector3(2005));
	std::cout << v2;

	v2.Resize(5);
	std::cout << v2;*/



	//zzstl::Vector<Vector3> v(2, Vector3(1.f));
	//v.PushBack(Vector3(10.f));
	//v.PushBack(Vector3(11.f, 13.f,19.f));
	//std::cout << v;

	//v.PopBack();
	//std::cout << v;
	//v.EmplaceBack();
	//v.EmplaceBack(5.f);
	//v.EmplaceBack(1.f, 2.f, 3.f);
	//std::cout << v;

	//v.PushBack(Vector3(10.f));
	//std::cout << v;

	std::cin.get();
}