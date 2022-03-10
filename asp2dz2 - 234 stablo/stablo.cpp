#include "stablo.h"

Cvor* Stablo::pretrazi(Akcija a) const
{
	Cvor* sled = koren;
	while (!sled->list()) {
		if (a == sled->a1 || a == sled->a2 || a == sled->a3) return sled;
		if (sled->a1.prioritet && (a.prioritet < sled->a1.prioritet ||
			(a.prioritet == sled->a1.prioritet && strcmp(a.naziv, sled->a1.naziv) < 0))) sled = sled->p0;
		else if (a.prioritet < sled->a2.prioritet ||
			(a.prioritet == sled->a2.prioritet && strcmp(a.naziv, sled->a2.naziv) < 0)) sled = sled->p1;
		else if (!sled->a3.prioritet || (a.prioritet < sled->a3.prioritet ||
			(a.prioritet == sled->a3.prioritet && strcmp(a.naziv, sled->a3.naziv) < 0))) sled = sled->p2;
		else if (sled->a3.prioritet) sled = sled->p3;
	}
	if (a == sled->a1 || a == sled->a2 || a == sled->a3) return sled;
	else return nullptr;
}

void Stablo::pretraziPrioritet(int prioritet) const
{
	Cvor* sled = koren;
	while (!sled->list()) {
		if (sled->a1.prioritet == prioritet) {
			Cvor* sin = sled->p0;
			if (sin->a1.prioritet == prioritet || sin->a2.prioritet == prioritet || sin->a3.prioritet == prioritet) sled = sin;
			else {
				cout << "Leksikografski prva akcija datog prioriteta je: " << sled->a1.naziv << endl;
			}
		}
		else if (sled->a2.prioritet == prioritet) {
			Cvor* sin = sled->p1;
			if (sin->a1.prioritet == prioritet || sin->a2.prioritet == prioritet || sin->a3.prioritet == prioritet) sled = sin;
			else {
				cout << "Leksikografski prva akcija datog prioriteta je: " << sled->a2.naziv << endl;
			}
		}
		else if (sled->a3.prioritet == prioritet) {
			Cvor* sin = sled->p2;
			if (sin->a1.prioritet == prioritet || sin->a2.prioritet == prioritet || sin->a3.prioritet == prioritet) sled = sin;
			else {
				cout << "Leksikografski prva akcija datog prioriteta je: " << sled->a3.naziv << endl;
			}
		}
		else {
			if (prioritet < sled->a1.prioritet) sled = sled->p0;
			else if (prioritet < sled->a2.prioritet) sled = sled->p1;
			else if (prioritet < sled->a3.prioritet) sled = sled->p2;
			else sled = sled->p3;
		}
	}
	if (sled->a1.prioritet == prioritet) {
		cout << "Leksikografski prva akcija datog prioriteta je: " << sled->a1.naziv << endl;
	}
	else if (sled->a2.prioritet == prioritet) {
		cout << "Leksikografski prva akcija datog prioriteta je: " << sled->a2.naziv << endl;
	}
	else if (sled->a3.prioritet == prioritet) {
		cout << "Leksikografski prva akcija datog prioriteta je: " << sled->a3.naziv << endl;
	}
	else cout << "Nije pronadjen cvor sa zadatim prioritetom!" << endl;
}

void Stablo::umetni(Akcija a)
{
	Akcija nula = { "", 0 };
	if (!koren) {
		koren = new Cvor(nula, a, nula);
	}
	else {
		Cvor* sled = koren;
		while (!sled->list()) {
			if (sled->a1.prioritet && (a.prioritet < sled->a1.prioritet || 
				(a.prioritet == sled->a1.prioritet && strcmp(a.naziv, sled->a1.naziv)<0))) sled = sled->p0;
			else if (a.prioritet < sled->a2.prioritet ||
				(a.prioritet == sled->a2.prioritet && strcmp(a.naziv, sled->a2.naziv)<0)) sled = sled->p1;
			else if (!sled->a3.prioritet || (a.prioritet < sled->a3.prioritet ||
				(a.prioritet == sled->a3.prioritet && strcmp(a.naziv, sled->a3.naziv) < 0))) sled = sled->p2;
			else if (sled->a3.prioritet) sled = sled->p3;
		}
		bool zavrseno = false;
		Cvor* pretsled = nullptr, *pretdesni = nullptr;
		while (!zavrseno) {
			if (sled->dvaCvor()) {
				if (a.prioritet < sled->a2.prioritet ||
					(a.prioritet < sled->a2.prioritet && strcmp(a.naziv, sled->a2.naziv) < 0)) {
					sled->a1 = a;
					sled->p0 = pretsled;
					sled->p1 = pretdesni;
				}
				else {
					sled->a3 = a;
					sled->p2 = pretsled;
					sled->p3 = pretdesni;
				}
				zavrseno = true;
			}
			else if (sled->triCvor()) {
				if (sled->a1.prioritet) {
					if (a.prioritet < sled->a1.prioritet ||
						(a.prioritet == sled->a1.prioritet && strcmp(a.naziv, sled->a1.naziv) < 0)) {
						sled->a3 = sled->a2;
						sled->a2 = sled->a1;
						sled->a1 = a;
					}
					else if (a.prioritet < sled->a2.prioritet ||
						(a.prioritet == sled->a2.prioritet && strcmp(a.naziv, sled->a2.naziv) < 0)) {
						sled->a3 = sled->a2;
						sled->a2 = a;
					}
					else sled->a3 = a;
				}
				else {
					if (a.prioritet > sled->a3.prioritet ||
						(a.prioritet == sled->a3.prioritet && strcmp(a.naziv, sled->a1.naziv) >= 0)) {
						sled->a1 = sled->a2;
						sled->a2 = sled->a3;
						sled->a3 = a;
					}
					else if (a.prioritet > sled->a2.prioritet ||
						(a.prioritet == sled->a2.prioritet && strcmp(a.naziv, sled->a2.naziv) >= 0)) {
						sled->a1 = sled->a2;
						sled->a2 = a;
					}
					else sled->a1 = a;
				}
				zavrseno = true;
			}
			else if (sled->cetiriCvor()) {
				Cvor* otac = sled->otac;
				Cvor* desni = new Cvor(nula, sled->a3, nula);
				desni->otac = sled->otac;
				desni->p1 = sled->p2;
				desni->p2 = sled->p3;
				sled->p2 = sled->p1;
				sled->p1 = sled->p0;
				sled->p3 = nullptr;
				sled->p0 = nullptr;
				if (otac && otac->dvaCvor()) {
					//Cvor* desni = new Cvor(nula,sled->a3,nula);
					if (otac->p2 == sled) {
						otac->a3 = sled->a2;
						otac->p3 = desni;
						sled->a2 = sled->a1;
						sled->a1 = sled->a3 = nula;
						if (a.prioritet > otac->a3.prioritet
							|| (a.prioritet == otac->a3.prioritet && strcmp(a.naziv, otac->a3.naziv) < 0)) sled = desni;
					}
					else {
						otac->a1 = sled->a2;
						otac->p0 = sled;
						otac->p1 = desni;
						sled->a2 = sled->a1;
						sled->a1 = sled->a3 = nula;
						if (a.prioritet > otac->a1.prioritet
							|| (a.prioritet == otac->a1.prioritet && strcmp(a.naziv, otac->a1.naziv) < 0)) sled = desni;
					}
				}
				else if (otac && otac->triCvor()) {
					//Cvor* desni = new Cvor(nula,sled->a3,nula);
					if (otac->p3 == sled) {
						otac->p0 = otac->p1;
						otac->p1 = otac->p2;
						otac->p2 = sled;
						otac->p3 = desni;
						otac->a1 = otac->a2;
						otac->a2 = otac->a3;
						otac->a3 = sled->a2;
						sled->a2 = sled->a1;
						sled->a1 = sled->a3 = nula;
						if (a.prioritet > otac->a3.prioritet
							|| (a.prioritet == otac->a3.prioritet && strcmp(a.naziv, otac->a3.naziv) < 0)) sled = desni;
					}
					else if (otac->p2 == sled && (!otac->a1.prioritet)) {
						otac->p0 = otac->p1;
						otac->p1 = sled;
						otac->p2 = desni;
						otac->a1 = otac->a2;
						otac->a2 = sled->a2;
						sled->a2 = sled->a1;
						sled->a1 = sled->a3 = nula;
						if (a.prioritet > otac->a2.prioritet
							|| (a.prioritet == otac->a2.prioritet && strcmp(a.naziv, otac->a2.naziv) < 0)) sled = desni;
					}
					else if (otac->p2 == sled) {
						otac->p3 = desni;
						otac->a3 = sled->a2;
						sled->a2 = sled->a1;
						sled->a1 = sled->a3 = nula;
						if (a.prioritet > otac->a3.prioritet
							|| (a.prioritet == otac->a3.prioritet && strcmp(a.naziv, otac->a3.naziv) < 0)) sled = desni;
					}
					else if (otac->p1 == sled && (!otac->a1.prioritet)) {
						otac->p0 = sled;
						otac->p1 = desni;
						otac->a1 = sled->a2;
						sled->a2 = sled->a1;
						sled->a1 = sled->a3 = nula;
						if (a.prioritet > otac->a1.prioritet
							|| (a.prioritet == otac->a1.prioritet && strcmp(a.naziv, otac->a1.naziv) < 0)) sled = desni;
					}
					else if (otac->p1 == sled) {
						otac->p3 = otac->p2;
						otac->p2 = desni;
						otac->a3 = otac->a2;
						otac->a2 = sled->a2;
						sled->a2 = sled->a1;
						sled->a1 = sled->a3 = nula;
						if (a.prioritet > otac->a2.prioritet
							|| (a.prioritet == otac->a2.prioritet && strcmp(a.naziv, otac->a2.naziv) < 0)) sled = desni;
					}
					else if (otac->p0 == sled) {
						otac->p3 = otac->p2;
						otac->p2 = otac->p1;
						otac->p1 = desni;
						otac->a3 = otac->a2;
						otac->a2 = otac->a1;
						otac->a1 = sled->a2;
						sled->a2 = sled->a1;
						sled->a1 = sled->a3 = nula;
						if (a.prioritet > otac->a1.prioritet
							|| (a.prioritet == otac->a1.prioritet && strcmp(a.naziv, otac->a1.naziv) < 0)) sled = desni;
					}
				}
				else if (otac && otac->cetiriCvor()) {
					Akcija gore = sled->a2;
					sled->a2 = sled->a1;
					sled->a1 = sled->a3 = nula;
					if (a.prioritet < sled->a2.prioritet || (a.prioritet == sled->a2.prioritet && strcmp(a.naziv, sled->a2.naziv) < 0)) {
						sled->a1 = a;
						sled->p0 = pretsled;
						sled->p1 = pretdesni;
						if (pretsled) pretsled->otac = pretdesni->otac = sled;
					}
					else if (a.prioritet < gore.prioritet || (a.prioritet == gore.prioritet && strcmp(a.naziv, gore.naziv) < 0)) {
						sled->a3 = a;
						sled->p2 = pretsled;
						sled->p3 = pretdesni;
						if (pretsled) pretsled->otac = pretdesni->otac = sled;
					}
					else if (a.prioritet < desni->a2.prioritet || (a.prioritet == desni->a2.prioritet && strcmp(a.naziv, desni->a2.naziv) < 0)) {
						desni->a1 = a;
						desni->p0 = pretsled;
						desni->p1 = pretdesni;
						if (pretsled) pretsled->otac = pretdesni->otac = desni;
					}
					else {
						desni->a3 = a;
						desni->p2 = pretsled;
						desni->p3 = pretdesni;
						if (pretsled) pretsled->otac = pretdesni->otac = desni;
					}
					pretsled = sled;
					pretdesni = desni;
					sled = otac;
					a = gore;
				}
				else if (!otac) {
					Akcija gore = sled->a2;
					sled->a2 = sled->a1;
					sled->a1 = sled->a3 = nula;
					Cvor* novikoren = new Cvor(nula, gore, nula);
					if (a.prioritet < sled->a2.prioritet || (a.prioritet == sled->a2.prioritet && strcmp(a.naziv, sled->a2.naziv) < 0)) {
						sled->a1 = a;
						sled->p0 = pretsled;
						sled->p1 = pretdesni;
						if (pretsled) pretsled->otac = pretdesni->otac = sled;
					}
					else if (a.prioritet < gore.prioritet || (a.prioritet == gore.prioritet && strcmp(a.naziv, gore.naziv) < 0)) {
						sled->a3 = a;
						sled->p2 = pretsled;
						sled->p3 = pretdesni;
						if (pretsled) pretsled->otac = pretdesni->otac = sled;
					}
					else if (a.prioritet < desni->a2.prioritet || (a.prioritet == desni->a2.prioritet && strcmp(a.naziv, desni->a2.naziv) < 0)) {
						desni->a1 = a;
						desni->p0 = pretsled;
						desni->p1 = pretdesni;
						if (pretsled) pretsled->otac = pretdesni->otac = desni;
					}
					else {
						desni->a3 = a;
						desni->p2 = pretsled;
						desni->p3 = pretdesni;
						if (pretsled) pretsled->otac = pretdesni->otac = desni;
					}
					novikoren->p1 = sled;
					novikoren->p2 = desni;
					sled->otac = novikoren;
					desni->otac = novikoren;
					koren = novikoren;
					zavrseno = true;
				}
			}
		}
	}

}

int Stablo::brojCvorovaZadatogPrioriteta(int prioritet)
{
	int broj = 0;
	queue <Cvor*> red;
	red.push(koren);
	while (red.size()) {
		Cvor* sled = red.front();
		red.pop();
		if (sled->a1.prioritet == prioritet) broj++;
		if (sled->a2.prioritet == prioritet) broj++;
		if (sled->a3.prioritet == prioritet) broj++;
		if (sled->p0) red.push(sled->p0);
		if (sled->p1) red.push(sled->p1);
		if (sled->p2) red.push(sled->p2);
		if (sled->p3) red.push(sled->p3);
	}
	return broj;
}

int Stablo::visinaStabla() const
{
	int visina = 0, br_elem;
	queue<Cvor*> red;
	red.push(koren);
	do {
		br_elem = red.size();
		visina++;
		while (br_elem > 0) {
			Cvor* sled = red.front();
			red.pop();
			if (sled->p0) red.push(sled->p0);
			if (sled->p1) red.push(sled->p1);
			if (sled->p2) red.push(sled->p2);
			if (sled->p3) red.push(sled->p3);
			br_elem--;
		}
	} while (!red.empty());
	return visina;
}

void Stablo::obrisi(Akcija a)
{
	Cvor* tren = pretrazi(a);
	Akcija nula = { "", 0 };
	if (!tren) {
		cout << "Trazena akcija ne postoji u stablu!" << endl;
		return;
	}
	bool zavrseno = false;
	bool spajanje = false;
	while (!zavrseno) {
		if (tren->list() || spajanje) {
			if (a.prioritet == tren->a1.prioritet && strcmp(a.naziv, tren->a1.naziv) == 0) { //brise se crveni iz lista i to a1
				tren->a1 = nula;
			}
			else if (a.prioritet == tren->a3.prioritet && strcmp(a.naziv, tren->a3.naziv) == 0) { //brise se crveni iz lista i to a3
				tren->a3 = nula;
			}
			else {								//brise se crni iz lista
				if (tren->a1.prioritet) { //ako moze menja se sa a1
					tren->a2 = tren->a1;
					tren->a1 = nula;
				}
				else if (tren->a3.prioritet) { //ako ne sa a1, onda sa a3
					tren->a2 = tren->a3;
					tren->a3 = nula;
				}
				else { //ako nema ni a3, gledamo rodjenog brata
					Cvor* otac = tren->otac;
					Cvor* brat = nullptr;
					if (tren == otac->p0) {
						brat = otac->p1;
						if (brat) {
							if (brat->a1.prioritet && !brat->a3.prioritet) { //brat je oblika ABX
								tren->a2 = otac->a1;
								otac->a1 = brat->a1;
								brat->a1 = nula;
							}
							else if (!brat->a1.prioritet && brat->a3.prioritet) { //brat je oblika XAB
								tren->a2 = otac->a1;
								otac->a1 = brat->a2;
								brat->a2 = brat->a3;
								brat->a3 = nula;
							}
							else if (brat->cetiriCvor()) { //brat je pun pa vrsim izmestanje
								tren->a2 = otac->a1;
								otac->a1 = brat->a2;
								brat->a2 = brat->a3;
								tren->a3 = brat->a1;
								brat->a1 = brat->a3 = nula;
							}
							else {
								brat->a3 = brat->a2; //ni brat nema dovoljno pa vrsim spajanje
								brat->a2 = otac->a1;
								otac->a1 = nula;
								otac->p0 = nullptr;
								brat->p1 = tren->p1;
								spajanje = false;
								delete tren;
							}
						}
						//kad brisem najlevlji ili najdesniji uvek imam rodjenog brata pa ne moram da razmatram slucaj da on ne postoji
					}
					else if (tren == otac->p1) {
						brat = otac->p0;
						if (brat) {
							if (brat->a1.prioritet && !brat->a3.prioritet) {
								tren->a2 = otac->a1;
								tren->p2 = tren->p1;
								tren->p1 = brat->p2;
								if (tren->p1) tren->p1->otac = tren;
								otac->a1 = brat->a2;
								brat->a2 = brat->a1;
								brat->a1 = nula;
								brat->p2 = brat->p1;
								brat->p1 = brat->p0;
								brat->p0 = nullptr;
							}
							else if (!brat->a1.prioritet && brat->a3.prioritet) {
								tren->a2 = otac->a1;
								tren->p2 = tren->p1;
								tren->p1 = brat->p3;
								if (tren->p1) tren->p1->otac = tren;
								brat->p3 = nullptr;
								otac->a1 = brat->a3;
								brat->a3 = nula;
							}
							else if (brat->cetiriCvor()) {
								tren->a2 = otac->a1;
								tren->p2 = tren->p1;
								tren->p1 = brat->p3;
								if (tren->p1) tren->p1->otac = tren;
								brat->p3 = nullptr;
								tren->p0 = brat->p2;
								if (tren->p0) tren->p0->otac = tren;
								brat->p2 = brat->p1;
								brat->p1 = brat->p0;
								brat->p0 = nullptr;
								otac->a1 = brat->a2;
								tren->a1 = brat->a3;
								brat->a2 = brat->a1;
								brat->a1 = brat->a3 = nula;
							}
							else {
								if (!spajanje) {
									brat->a1 = brat->a2;
									brat->a2 = otac->a1;
									otac->a1 = nula;
									otac->p0 = nullptr;
									otac->p1 = brat;
									delete tren;
									tren = brat;
								}
								else {
									tren->a2 = otac->a1;
									tren->a1 = brat->a2;
									otac->a1 = nula;
									tren->p2 = tren->p1;
									tren->p1 = brat->p2;
									tren->p0 = brat->p1;
									otac->p0 = nullptr;
									delete brat;
								}
							}
							spajanje = false;
						}
						else {
							Cvor* sused = otac->p2;
							if (sused) {
								if (sused->dvaCvor()) {
									if (!otac->dvaCvor()) {
										sused->a3 = sused->a2;
										sused->a2 = otac->a2;
										if (spajanje) {
											sused->p0 = tren->p1;
											tren->p1->otac = sused;
										}
										delete tren;
										otac->a2 = otac->a3;
										otac->a3 = nula;
										otac->p1 = otac->p2;
										otac->p2 = otac->p3;
										otac->p3 = nullptr;
										spajanje = false;
									}
									else {
										tren->a2 = otac->a2;
										tren->a3 = sused->a2;
										tren->p2 = sused->p1;
										tren->p3 = sused->p2;
										if (tren->p2) tren->p2->otac = tren;
										if (tren->p3) tren->p3->otac = tren;
										delete sused;
										otac->p2 = nullptr;
										otac->a2 = nula;
										spajanje = true;
									}
								}
								else if (sused->cetiriCvor()) {
									if (!otac->dvaCvor()) {
										tren->a2 = otac->a2;
										otac->a1 = sused->a2;
										tren->a3 = sused->a1;
										sused->a2 = sused->a3;
										sused->a1 = sused->a3 = nula;
										otac->a2 = otac->a3;
										otac->a3 = nula;
										otac->p0 = otac->p1;
										otac->p1 = otac->p2;
										otac->p2 = otac->p3;
										otac->p3 = nullptr;
										tren->p2 = sused->p0;
										if (tren->p2) tren->p2->otac = tren;
										tren->p3 = sused->p1;
										if (tren->p3) tren->p3->otac = tren;
										sused->p0 = nullptr;
										sused->p1 = sused->p2;
										sused->p2 = sused->p3;
										sused->p3 = nullptr;
										spajanje = false;
									}
									else {
										tren->a2 = otac->a2;
										otac->a2 = sused->a2;
										tren->a3 = sused->a1;
										sused->a2 = sused->a3;
										sused->a1 = sused->a3 = nula;
										tren->p2 = sused->p0;
										if (tren->p2) tren->p2->otac = tren;
										tren->p3 = sused->p1;
										if (tren->p3) tren->p3->otac = tren;
										sused->p0 = nullptr;
										sused->p1 = sused->p2;
										sused->p2 = sused->p3;
										sused->p3 = nullptr;
										spajanje = false;
									}
								}
								else if (!sused->a1.prioritet && sused->a3.prioritet) {
									if (!otac->dvaCvor()) {
										tren->a2 = otac->a2;
										otac->a2 = otac->a3;
										otac->a3 = nula;
										otac->a1 = sused->a2;
										sused->a2 = sused->a3;
										sused->a3 = nula;
										otac->p0 = otac->p1;
										otac->p1 = otac->p2;
										otac->p2 = otac->p3;
										otac->p3 = nullptr;
										tren->p2 = sused->p0;
										if (tren->p2) tren->p2->otac = tren;
										sused->p0 = nullptr;
										sused->p1 = sused->p2;
										sused->p2 = sused->p3;
										sused->p3 = nullptr;
										spajanje = false;
									}
									else {
										tren->a2 = otac->a2;
										otac->a2 = sused->a2;
										sused->a2 = sused->a3;
										sused->a3 = nula;
										tren->p2 = sused->p1;
										if (tren->p2) tren->p2->otac = tren;
										sused->p1 = sused->p2;
										sused->p2 = sused->p3;
										sused->p3 = nullptr;
										spajanje = false;
									}
								}
								else if (sused->a1.prioritet && !sused->a3.prioritet) {
									if (!otac->dvaCvor()) {
										tren->a2 = otac->a2;
										otac->a2 = otac->a3;
										otac->a3 = nula;
										otac->a1 = sused->a1;
										sused->a1 = nula;
										otac->p0 = otac->p1;
										otac->p1 = otac->p2;
										otac->p2 = otac->p3;
										otac->p3 = nullptr;
										tren->p2 = sused->p0;
										if (tren->p2) tren->p2->otac = tren;
										sused->p0 = nullptr;
										spajanje = false;
									}
									else {
										tren->a2 = otac->a2;
										otac->a2 = sused->a1;
										sused->a1 = nula;
										tren->p2 = sused->p0;
										sused->p0 = nullptr;
										if (tren->p2) tren->p2->otac = tren;
										spajanje = false;
									}
								}
							}
						}
					}
					else if (tren == otac->p2) {
						brat = otac->p3;
						if (brat) {
							if (brat->a1.prioritet && !brat->a3.prioritet) {
								tren->a2 = otac->a3;
								otac->a3 = brat->a1;
								brat->a1 = nula;
								tren->p2 = brat->p0;
								if (tren->p2) tren->p2->otac = tren;
								brat->p0 = nullptr;
							}
							else if (!brat->a1.prioritet && brat->a3.prioritet) {
								tren->a2 = otac->a3;
								otac->a3 = brat->a2;
								brat->a2 = brat->a3;
								brat->a3 = nula;
								tren->p2 = brat->p1;
								if (tren->p2) tren->p2->otac = tren;
								brat->p1 = brat->p2;
								brat->p2 = brat->p3;
								brat->p3 = nullptr;
							}
							else if (brat->cetiriCvor()) {
								tren->a2 = otac->a3;
								otac->a3 = brat->a2;
								tren->a3 = brat->a1;
								brat->a2 = brat->a3;
								brat->a1 = brat->a3 = nula;
								tren->p2 = brat->p0;
								if (tren->p2) tren->p2->otac = tren;
								tren->p3 = brat->p1;
								if (tren->p3) tren->p3->otac = tren;
								brat->p1 = brat->p2;
								brat->p2 = brat->p3;
								brat->p3 = nullptr;
							}
							else {
								if (!spajanje) {
									brat->a3 = brat->a2;
									brat->a2 = otac->a3;
									otac->a3 = nula;
									otac->p3 = nullptr;
									otac->p2 = brat;
									delete tren;
									tren = brat;
								}
								else {
									tren->a2 = otac->a3;
									tren->a3 = brat->a2;
									otac->a3 = nula;
									tren->p2 = brat->p1;
									tren->p3 = brat->p2;
									delete brat;
									tren->p2->otac = tren;
									tren->p3->otac = tren;
								}
							}
							spajanje = false;
						}
						else {
							Cvor* sused = otac->p1;
							if (sused) {
								if (sused->dvaCvor()) {
									if (!otac->dvaCvor()) {
										sused->a1 = sused->a2;
										sused->a2 = otac->a2;
										sused->p0 = sused->p1;
										sused->p1 = sused->p2;
										if (spajanje) {
											sused->p2 = tren->p1;
											sused->p2->otac = sused;
										}
										delete tren;
										otac->a2 = otac->a1;
										otac->a1 = nula;
										otac->p2 = otac->p1;
										otac->p1 = otac->p0;
										otac->p0 = nullptr;
										spajanje = false;
									}
									else {
										tren->a2 = otac->a2;
										tren->a1 = sused->a2;
										tren->p2 = tren->p1;
										tren->p1 = sused->p2;
										if (tren->p1) tren->p1->otac = tren;
										tren->p0 = sused->p1;
										if (tren->p0) tren->p0->otac = tren;
										delete sused;
										otac->a2 = nula;
										otac->p1 = otac->p2;
										otac->p2 = nullptr;
										spajanje = true;
									}
								}
								else if (sused->cetiriCvor()) {
									if (!otac->dvaCvor()) {
										tren->a2 = otac->a2;
										otac->a3 = sused->a2;
										tren->a1 = sused->a3;
										sused->a2 = sused->a1;
										sused->a1 = sused->a3 = nula;
										otac->a2 = otac->a1;
										otac->a1 = nula;
										otac->p3 = otac->p2;
										otac->p2 = otac->p1;
										otac->p1 = otac->p0;
										otac->p0 = nullptr;
										tren->p2 = tren->p1;
										tren->p1 = sused->p3;
										if (tren->p1) tren->p1->otac = tren;
										tren->p0 = sused->p2;
										if (tren->p0) tren->p0->otac = tren;
										sused->p2 = sused->p1;
										sused->p1 = sused->p0;
										sused->p0 = sused->p3 = nullptr;
										spajanje = false;
									}
									else {
										tren->a2 = otac->a2;
										otac->a2 = sused->a2;
										sused->a2 = sused->a1;
										tren->a1 = sused->a3;
										sused->a1 = sused->a3 = nula;
										tren->p2 = tren->p1;
										tren->p1 = sused->p3;
										if (tren->p1) tren->p1->otac = tren;
										tren->p0 = sused->p2;
										if (tren->p0) tren->p0->otac = tren;
										sused->p2 = sused->p1;
										sused->p1 = sused->p0;
										sused->p0 = sused->p3 = nullptr;
										spajanje = false;
									}
								}
								else if (!sused->a1.prioritet && sused->a3.prioritet) {
									if (!otac->dvaCvor()) {
										tren->a2 = otac->a2;
										otac->a2 = otac->a1;
										otac->a1 = nula;
										otac->a3 = sused->a3;
										sused->a3 = nula;
										otac->p3 = otac->p2;
										otac->p2 = otac->p1;
										otac->p1 = otac->p0;
										otac->p0 = nullptr;
										tren->p2 = tren->p1;
										tren->p1 = sused->p3;
										if (tren->p1) tren->p1->otac = tren;
										sused->p3 = nullptr;
										spajanje = false;
									}
									else {
										tren->a2 = otac->a2;
										otac->a2 = sused->a3;
										sused->a3 = nula;
										tren->p2 = tren->p1;
										tren->p1 = sused->p3;
										if (tren->p1) tren->p1->otac = tren;
										sused->p3 = nullptr;
										spajanje = false;
									}
								}
								else if (sused->a1.prioritet && !sused->a3.prioritet) {
									if (!otac->dvaCvor()) {
										tren->a2 = otac->a2;
										otac->a2 = otac->a1;
										otac->a1 = nula;
										otac->a3 = sused->a2;
										sused->a2 = sused->a1;
										sused->a1 = nula;
										otac->p3 = otac->p2;
										otac->p2 = otac->p1;
										otac->p1 = otac->p0;
										otac->p0 = nullptr;
										tren->p2 = tren->p1;
										tren->p1 = sused->p2;
										if (tren->p1) tren->p1->otac = tren;
										sused->p2 = sused->p1;
										sused->p1 = sused->p0;
										spajanje = false;
									}
									else {
										tren->a2 = otac->a2;
										otac->a2 = sused->a2;
										sused->a2 = sused->a1;
										sused->a1 = nula;
										tren->p2 = tren->p1;
										tren->p1 = sused->p2;
										if (tren->p1) tren->p1->otac = tren;
										sused->p2 = sused->p1;
										sused->p1 = sused->p0;
										sused->p0 = nullptr;
										spajanje = false;
									}
								}
							}
						}

					}
					else if (tren == otac->p3) {
						brat = otac->p2;
						if (brat) {
							if (brat->a1.prioritet && !brat->a3.prioritet) { //brat je oblika ABX
								tren->a2 = otac->a3;
								otac->a3 = brat->a2;
								brat->a2 = brat->a1;
								brat->a1 = nula;
							}
							else if (!brat->a1.prioritet && brat->a3.prioritet) { //brat je oblika XAB
								tren->a2 = otac->a3;
								otac->a3 = brat->a3;
								brat->a3 = nula;
							}
							else if (brat->cetiriCvor()) { //brat je pun pa vrsim izmestanje
								tren->a2 = otac->a3;
								otac->a3 = brat->a2;
								brat->a2 = brat->a1;
								tren->a1 = brat->a3;
								brat->a1 = brat->a3 = nula;
							}
							else {
								brat->a1 = brat->a2; //ni brat nema dovoljno pa vrsim spajanje
								brat->a2 = otac->a3;
								otac->a3 = nula;
								otac->p3 = nullptr;
								brat->p2 = tren->p1;
								spajanje = false;
								delete tren;
							}
						}
					}
				}
			}
			if (spajanje) {
				if (tren->otac == koren) {
					koren = tren;
					delete tren->otac;
					zavrseno = true;
				}
				else {
					tren = tren->otac;
				}
			}
			else zavrseno = true;
		}
		else { //brisanje iz unutrasnjeg cvora
			Cvor* sled;
			Akcija sledbenik;
			if (a == tren->a1) sled = tren->p1;
			else if (a == tren->a2) sled = tren->p2;
			else sled = tren->p3;
			while (!sled->list()) {
				sled = sled->p0;
			}
			if (sled->a1.prioritet) sledbenik = sled->a1;
			else sledbenik = sled->a2;
			if (a == tren->a1) tren->a1 = sledbenik;
			else if (a == tren->a2) tren->a2 = sledbenik;
			else tren->a3 = sledbenik;
			tren = sled;
			a = sledbenik;
		}
	}
}

void Stablo::obrisiNajvisu()
{
	Cvor* tren = koren;
	while (!tren->list()) {
		if (tren->p3) tren = tren->p3;
		else tren = tren->p2;
	}
	if (tren->a3.prioritet) {
		cout << "Akcija najviseg prioriteta je: " << tren->a3.naziv << " [" << tren->a3.prioritet << "]" << endl;
		obrisi(tren->a3);
		cout << "Akcija je uspesno obrisana!" << endl;
 	}
	else {
		cout << "Akcija najviseg prioriteta je: " << tren->a2.naziv << " [" << tren->a2.prioritet << "]" << endl;
		obrisi(tren->a2);
		cout << "Akcija je uspesno obrisana!" << endl;
	}
}

void Stablo::izmeniPrioritet(Akcija a, int novi)
{
	obrisi(a);
	a.prioritet = novi;
	umetni(a);
}

ostream& operator<<(ostream& os, Stablo& stablo)
{
	int visina = stablo.visinaStabla(), br_elem;
	int nivo[1000] = { 0 }, sled_nivo[1000] = { 0 }, trenutni_nivo = 1;
	queue<Cvor*> red;
	int br_razmaka_spolja = 80;
	int br_razmaka_unutra = 160;
	red.push(stablo.koren);
	nivo[0] = 1;
	while (trenutni_nivo <= visina) {
		br_elem = red.size();
		for (int i = 0; i < br_razmaka_spolja; i++) cout << " ";
		for (int i = 0; i < pow(4, trenutni_nivo - 1); i++) {
			if (nivo[i]) {
				Cvor* sled = red.front();
				red.pop();
				cout << sled;
				if (sled->p0) {
					red.push(sled->p0);
					sled_nivo[4 * i] = 1;
				}
				if (sled->p1) {
					red.push(sled->p1);
					sled_nivo[4 * i + 1] = 1;
				}
				if (sled->p2) {
					red.push(sled->p2);
					sled_nivo[4 * i + 2] = 1;
				}
				if (sled->p3) {
					red.push(sled->p3);
					sled_nivo[4 * i + 3] = 1;
				}
			}
			if (i != pow(4, trenutni_nivo - 1) - 1) {
				for (int i = 0; i < br_razmaka_unutra; i++) cout << " ";
			}
		}
		for (int i = 0; i < 1000; i++) {
			nivo[i] = sled_nivo[i];
			sled_nivo[i] = 0;
		}
		for (int i = 0; i < br_razmaka_spolja; i++) cout << " ";
		cout << endl << endl;
		trenutni_nivo++;
		br_razmaka_spolja /= 4;
		br_razmaka_unutra /= 4;
	}
	return os;
}

void crvenoCrniIspis(Stablo& stablo)
{
	int visina = stablo.visinaStabla(), br_elem;
	int nivo[1000] = { 0 }, sled_nivo[1000] = { 0 }, trenutni_nivo = 1;
	int br_razmaka_spolja = 80;
	int br_razmaka_unutra = 160;
	struct Elem {
		Cvor* c;
		int br;
	};
	queue<Elem> red;
	red.push({ stablo.koren,1 });
	nivo[0] = 1;
	while (red.size()) {
		for (int i = 0; i < br_razmaka_spolja; i++) cout << " ";
		for (int i = 0; i < pow(4, trenutni_nivo - 1); i++) {
			if (nivo[i]) {
				Elem sled = red.front();
				red.pop();
				if (sled.br == 1) {
					cout << sled.c->a2.prioritet;
					if (sled.c->a1.prioritet && !sled.c->a3.prioritet) {
						sled.br++;
						red.push(sled);
						sled_nivo[2 * i] = 1;
						if (sled.c->p2) {
							sled_nivo[2 * i + 1] = 1;
							red.push({ sled.c->p2,1 });
						}
					}
					else if (!sled.c->a1.prioritet && sled.c->a3.prioritet) {
						sled.br++;
						if (sled.c->p1) {
							red.push({ sled.c->p1,1 });
							sled_nivo[2 * i] = 1;
						}
						red.push(sled);
						sled_nivo[2 * i + 1] = 1;
					}
					else if (sled.c->cetiriCvor()) {
						sled.br++;
						red.push(sled);
						sled_nivo[2 * i] = 1;
						sled_nivo[2 * i + 1] = 1;
					}
					else {
						if (sled.c->p1) {
							red.push({ sled.c->p1,1 });
							sled_nivo[2 * i] = 1;
						}
						if (sled.c->p2) {
							sled_nivo[2 * i + 1] = 1;
							red.push({ sled.c->p2,1 });
						}
					}
				}
				else {
					if (sled.c->a1.prioritet && !sled.c->a3.prioritet) {
						cout << "\033[31m" << sled.c->a1.prioritet << "\033[0m";
						if (sled.c->p0) {
							sled_nivo[2 * i] = 1;
							red.push({ sled.c->p0,1 });
						}
						if (sled.c->p1) {
							sled_nivo[2 * i + 1] = 1;
							red.push({ sled.c->p1,1 });
						}
					}
					else if (!sled.c->a1.prioritet && sled.c->a3.prioritet) {
						cout << "\033[31m" << sled.c->a3.prioritet << "\033[0m";
						if (sled.c->p2) {
							sled_nivo[2 * i] = 1;
							red.push({ sled.c->p2,1 });
						}
						if (sled.c->p3) {
							sled_nivo[2 * i + 1] = 1;
							red.push({ sled.c->p3,1 });
						}
					}
					else {
						cout << "\033[31m" << sled.c->a1.prioritet << "\033[0m";
						if (sled.c->p0) {
							sled_nivo[2 * i] = 1;
							red.push({ sled.c->p0,1 });
						}
						if (sled.c->p1) {
							sled_nivo[2 * i + 1] = 1;
							red.push({ sled.c->p1,1 });
						}
						for (int j = 0; j < br_razmaka_unutra; j++) cout << " ";
						i++;
						cout << "\033[31m" << sled.c->a3.prioritet << "\033[0m";
						if (sled.c->p2) {
							sled_nivo[2 * i] = 1;
							red.push({ sled.c->p2,1 });
						}
						if (sled.c->p3) {
							sled_nivo[2 * i + 1] = 1;
							red.push({ sled.c->p3,1 });
						}
					}
				}
			}
			if (i != pow(4, trenutni_nivo - 1) - 1) {
				for (int i = 0; i < br_razmaka_unutra; i++) cout << " ";
			}
		}
		for (int i = 0; i < 1000; i++) {
			nivo[i] = sled_nivo[i];
			sled_nivo[i] = 0;
		}
		for (int i = 0; i < br_razmaka_spolja; i++) cout << " ";
		cout << endl << endl;
		trenutni_nivo++;
		br_razmaka_spolja /= 2;
		br_razmaka_unutra /= 2;
	}
}
