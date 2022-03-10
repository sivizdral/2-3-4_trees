#ifndef _cvor_h_
#define _cvor_h_

#include <cstring>
#include <iostream>
#include <queue>
#include "akcija.h"
using namespace std;

class Cvor {
public:

	Akcija a1, a2, a3;
	Cvor* p0, * p1, * p2, * p3;
	Cvor* otac = nullptr;

	Cvor(Akcija a, Akcija b, Akcija c, Cvor* p = nullptr, Cvor*q = nullptr, Cvor* r = nullptr, Cvor* s = nullptr) {
		a1 = a;
		a2 = b;
		a3 = c;
		p0 = p;
		p1 = q;
		p2 = r;
		p3 = s;
	}

	bool list() const;

	int brojacCvorova() const;

	bool punCvor() const;

	bool dvaCvor() const;

	bool triCvor() const;

	bool cetiriCvor() const;

	friend ostream& operator<<(ostream& os, const Cvor* cvor);
};

#endif
