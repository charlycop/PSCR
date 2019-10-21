#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

/*
 *
*/
void Banque::transfert(size_t deb, size_t cred, unsigned int val) {


	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];

	if (deb < cred){
		debiteur.lock();
		crediteur.lock();
	}else{
		crediteur.lock();
		debiteur.lock();
	}


	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}

	debiteur.unlock(); crediteur.unlock();
}

void Banque::afficheSolde(size_t numCompte){
	Compte & compte = comptes[numCompte];
	cout << "SOLDE de compte[" << numCompte << "] = " << compte.getSolde() << "euro" << endl;
}

size_t Banque::size() const {
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) const {
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) {
		compte.lock(); // On lock tous les comptes déjà itérés
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}

	// On unlock tous les comptes
	for (const auto & compte : comptes)
			compte.unlock();

	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	else{
		//cout << "Bilan Comptable OK" << endl;
	}

	return bilan == attendu;
}
}
