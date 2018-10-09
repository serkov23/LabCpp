#pragma once
#include "Visitor.h"


class Avereger :
	public Visitor
{
	double sum=0;
	size_t ammount=0;
public:
	Avereger() = default;
	Avereger(const Avereger& a):sum(a.sum),ammount(a.ammount) {}
	void visit(const int val) {
		visit((double)val);
	}
	void visit(const double val) {
		sum += val;
		ammount++;
	}
	void visit(const std::string& val) {
		visit((double)val.size());
	}

	void visit(const Base_element& val) {
		visit((int)val);
	}

	double get_average() {
		return ammount==0? 0 :(sum / ammount);
	}
};

