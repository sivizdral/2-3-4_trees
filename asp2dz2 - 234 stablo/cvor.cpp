#include "cvor.h"

bool Cvor::list() const
{
	if (!p0 && !p1 && !p2 && !p3) return true;
	else return false;
}

int Cvor::brojacCvorova() const
{
	int i = 0;
	if (a1.prioritet != 0) i++;
	if (a2.prioritet != 0) i++;
	if (a3.prioritet != 0) i++;
	return i;
}

bool Cvor::punCvor() const
{
	if (a1.prioritet && a2.prioritet && a3.prioritet) return true;
	else return false;
}

bool Cvor::dvaCvor() const
{
	return (brojacCvorova() == 1);
}

bool Cvor::triCvor() const
{
	return (brojacCvorova() == 2);
}

bool Cvor::cetiriCvor() const
{
	return (brojacCvorova() == 3);
}

ostream& operator<<(ostream& os, const Cvor* cvor)
{
	return os << "[" << cvor->a1.prioritet << "|" << cvor->a2.prioritet << "|" << cvor->a3.prioritet << "]";
}
