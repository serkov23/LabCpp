#pragma once
#include <string>
#include <iostream>

class Base_element;

class Visitor {
public:
	virtual void visit(const int ) = 0;
	virtual void visit(const double) = 0;
	virtual void visit(const Base_element&) = 0;
	virtual void visit(const std::string&) = 0;
};

class Base_element {
public:
	virtual operator int() const = 0;
	virtual void accept(Visitor&) = 0;
};
class Person final:public Base_element{
	int age;
public:
	Person() = default;
	Person(int a) :age(a) {}

	void accept(Visitor& visitor) override{
		visitor.visit(*this);
	}
	operator int() const {
		return age;
	}
	operator int&() {
		return age;
	}
	/*friend std::ostream& operator<<(std::ostream& out, const Person& a) {
		out << a.age;
		return out;
	}
	friend std::istream& operator>>(std::istream& in, Person& a) {
		in >> a.age;
		return in;
	}*/
};