#include "Banque.h"
#include "Compte.h"
#include <iostream>   //std::cout
#include <thread>     //std::thread
#include <mutex>


using namespace std;
using namespace pr;

const int NB_THREAD    = 10;
const int SOLDEINITIAL = 10000;
const int NBCOMPTES    = 100;
bool ready(false);

void transactions (Banque& B){

	while(!ready){this_thread::yield();}
	for (int n=0; n<1000 ; ++n ){

		int i(rand()%(NBCOMPTES-1)), j(rand()%(NBCOMPTES-1)), m(rand()%(100));
		B.transfert(i, j, m);
		//this_thread::sleep_for(std::chrono::milliseconds(20));
        //B.afficheSolde(i);
	}
}

void comptabilise (Banque& B, int attendu){

	while(!ready){this_thread::yield();}
	for(int i = 0; i<10000 ; ++i){
		B.comptabiliser(attendu);
		//this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

int main () {

	pr::Banque maBanque(NBCOMPTES, SOLDEINITIAL);
	int attendu = SOLDEINITIAL * NBCOMPTES;

	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé

	for(int i=1 ; i <= NB_THREAD ; ++i){
		threads.push_back(thread (transactions, ref(maBanque)));
	}


	threads.push_back(thread (comptabilise,ref(maBanque),attendu));

	srand(time(NULL)); // initialisation de rand


	ready=true;
	//transactions(maBanque);
	cout << "READY"  << endl;

	for (auto & t : threads) {
		t.join();
	}
	cout << "FINISHED" << endl;

	maBanque.comptabiliser(attendu);

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
