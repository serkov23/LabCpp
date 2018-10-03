#pragma once
#define UNICODE
#include<Windows.h>
#include<windowsx.h>
#include<sstream>
#include<string>
#include"KDeque.h"
class KStream {
protected:
	HWND hwnd;
	const size_t maxn = 1000;
public:
	explicit KStream(HWND hwnd);;

};

class KOstream :public KStream
{
public:
	explicit KOstream(HWND hwnd);

	void clear();

	template<typename T>
	KOstream& operator<<(const T& val);
	
};

class KIstream :public KStream
{
public:
	explicit KIstream(HWND hwnd);;

	template<class T>
	KIstream& operator>>(T& val);
};

template<typename T>
KOstream &KOstream::operator<<(const T &val) {
	std::stringstream ss;
	ss <<std::boolalpha<< val;
	auto str = new char[maxn];
	ss.get(str, maxn);
	SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)str);
	delete[] str;
	return *this;
}


template<class T>
KIstream &KIstream::operator>>(T &val) {
	auto str = new char[maxn];
	GetWindowTextA(hwnd, str, maxn);
	std::stringstream ss(str);

	ss >> val;

	delete[]str;
	if (!ss)
		throw std::runtime_error("invalid input");
	return *this;
}



template<class T, size_t grow_const>
KOstream& operator<< (KOstream& out, const KDeque<T, grow_const>& deq) {
	out.clear();
	Iterator<T> it(deq);
	try {
		while (true) {
			out << it.current();
			if (!it.has_next())
				break;
			it.next();
		} 
	}
	catch (...) {
		;
	}
	out << (std::string("size: ")+std::to_string(deq.size()) + "       capacity: " + std::to_string(deq.capacity()));
	return out;
}