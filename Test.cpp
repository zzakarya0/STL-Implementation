#include <iostream>

#include <array>
#include "Array.h"
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

int main()
{
	//std::array<Vector3, 2> z{ Vector3(1.f), Vector3(2.f) };
	//std::array<Vector3, 2> z1{ Vector3(9.f), Vector3(8.f) };
	//z.swap(z1);
	//for (auto& c : z) std::cout << c << " | "; std::cout << "\n";
	//for (auto& c : z1) std::cout << c << " | "; std::cout << "\n";
	//std::cout << z.at(0) << std::endl;;
	//std::cout << z1.at(0) << std::endl;
	//auto it = z.begin();
	//it[0] = Vector3(100.f);
	//it.operator[](3);
	//for (auto& c : z) std::cout << c << " | "; std::cout << "\n";


	////why must use {} instead of ()
	//constexpr std::array<char[3], 5> d{ "ab", "b", "c", "d", "e" };
	//std::cout << d.empty() << std::endl;
	//for (auto n : d) std::cout << n << std::endl;
	//std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
	//std::cout << d.at(0) << std::endl;

	//constexpr zzstl::Array<char[2], 2> a("a", "b");
	//std::cout << a[0] << std::endl;
	//a.Front();
	//a.Print();
	//std::cout << a.At(0) << std::endl;

	std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
	zzstl::Array<Vector3, 2> a2{ Vector3(1.f), Vector3(2.f) };
	zzstl::Array<Vector3, 2>  a3{Vector3(9.f), Vector3(8.f)};
	/*a2.Swap(a3);
	a2.Print();
	a3.Print();
	std::cout << a2.At(0) << std::endl;
	std::cout << a3.At(0) << std::endl;*/
	//auto itr = a2.begin();
	zzstl::Array<Vector3, 2>::Const_Iterator itr = a2.begin();	//why trying to call move ctor
	std::cout << *itr << std::endl;

	++itr;
	std::cout << *itr << std::endl;


	std::cin.get();
}