#ifndef _stablo_h_
#define _stablo_h_

#include "cvor.h"

class Stablo {
public:
	Cvor* koren;

	Stablo() {
		koren = nullptr;
	}

	~Stablo() {
		queue<Cvor*> red;
		Cvor* sled;
		if (koren) {
			sled = koren;
			red.push(sled);
			while (!red.empty()) {
				sled = red.front();
				red.pop();
				if (sled->p0) red.push(sled->p0);
				if (sled->p1) red.push(sled->p1);
				if (sled->p2) red.push(sled->p2);
				if (sled->p3) red.push(sled->p3);
				delete sled;
			}
		}
		koren = nullptr;
	}

	Cvor* pretrazi(Akcija a) const;

	void pretraziPrioritet(int prioritet) const;

	void umetni(Akcija a);

	friend ostream& operator<<(ostream& os, Stablo& stablo);

	friend void crvenoCrniIspis(Stablo& stablo);

	int brojCvorovaZadatogPrioriteta(int prioritet);

	int visinaStabla() const;

	void obrisi(Akcija a);

	void obrisiNajvisu();

	void izmeniPrioritet(Akcija a, int novi);

};

#endif