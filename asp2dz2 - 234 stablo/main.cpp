#define _CRT_SECURE_NO_WARNINGS
#include "stablo.h"
#include <fstream>
#include <cstring>

int main() {
	ifstream dat;
	int izbor = 12;
	int i = 0, prioritet, broj;
	char c;
	Akcija a;
	Stablo stablo;
	string s;
	char naziv[300];
	while (izbor!=11) {
		cout << "U meniju izaberite stavku koju zelite" << endl;
		cout << "1. Kreiranje praznog stabla" << endl;
		cout << "2. Umetanje proizvoljne akcije u stablo" << endl;
		cout << "3. Uvoz akcija u stablo iz datoteke" << endl;
		cout << "4. Pretrazivanje stabla na zadati prioritet" << endl;
		cout << "5. Brisanje zadate akcije iz stabla" << endl;
		cout << "6. Brisanje akcije najviseg prioriteta" << endl;
		cout << "7. Ispis 2-3-4 oblika stabla" << endl;
		cout << "8. Ispis crveno-crnog oblika stabla" << endl;
		cout << "9. Izmena prioriteta zadate akcije" << endl;
		cout << "10. Pronalazenje ukupnog broja akcija zadatog prioriteta" << endl;
		cout << "11. Brisanje stabla i zavrsetak rada" << endl;
		cin >> izbor;
		switch (izbor) {
		case 1:
			cout << "Stvoreno novo stablo!" << endl;
			break;
		case 2:
			cout << "Unesite ime akcije koju zelite da umetnete: ";
			scanf(" %[^\n]s", a.naziv);
			cout << "Unesite prioritet akcije koju zelite da umetnete: ";
			cin >> a.prioritet;
			stablo.umetni(a);
			break;
		case 3:
			cout << "Unesite ime datoteke iz koje zelite da uvezete podatke: ";
			cin >> s;
			dat.open(s);
			if (!dat.is_open()) {
				cout << "Doslo je do greske prilikom otvaranja datoteke!" << endl;
			}
			else {
				while ((c=dat.get() != EOF)) {
					naziv[0] = c;
					i = 1;
					while ((c=dat.get()) != '\n') {
						naziv[i] = c;
						i++;
					}
					broj = 1;
					i--;
					prioritet = 0;
					while (naziv[i] >= '0' && naziv[i] <= '9') {
						prioritet += broj * (naziv[i]-'0');
						broj = broj * 10;
						i--;
					}
					naziv[i] = '\0';
					for (broj = 0; broj <= i; broj++) {
						a.naziv[i] = naziv[i];
					}
					a.prioritet = prioritet;
					stablo.umetni(a);
				}
				dat.close();
			}
			break;
		case 4:
			cout << "Unesite prioritet koji zelite da pretrazite: ";
			cin >> prioritet;
			stablo.pretraziPrioritet(prioritet);
			break;
		case 5:
			cout << "Unesite ime akcije koju zelite da obrisete: ";
			scanf(" %[^\n]s", a.naziv);
			cout << "Unesite prioritet akcije koju zelite da obrisete: ";
			cin >> a.prioritet;
			if (stablo.pretrazi(a)) {
				stablo.obrisi(a);
				cout << "Akcija je uspesno obrisana!" << endl;
			}
			else {
				cout << "Akcija ne postoji u stablu!" << endl;
			}
			break;
		case 6:
			stablo.obrisiNajvisu();
			break;
		case 7:
			cout << stablo;
			break;
		case 8:
			crvenoCrniIspis(stablo);
			break;
		case 9:
			cout << "Unesite ime akcije koju zelite da izmenite: ";
			scanf(" %[^\n]s", a.naziv);
			cout << "Unesite prioritet akcije koju zelite da izmenite: ";
			cin >> a.prioritet;
			cout << "Unesite novi prioritet: ";
			int novi;
			cin >> novi;
			stablo.izmeniPrioritet(a, novi);
			break;
		case 10:
			cout << "Unesite prioritet koji zelite da prebrojite: ";
			cin >> prioritet;
			broj = stablo.brojCvorovaZadatogPrioriteta(prioritet);
			cout << "Broj cvorova zadatog prioriteta je " << broj << endl;
			break;
		default:
			break;
		}
	}
	return 0;
}