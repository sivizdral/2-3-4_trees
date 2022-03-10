#ifndef _akcija_h_
#define _akcija_h_

struct Akcija {
	char naziv[256];
	int prioritet;
	inline bool operator== (Akcija a) {
		if (strcmp(a.naziv, naziv) == 0 && a.prioritet == prioritet) return true;
		return false;
	}
};



#endif