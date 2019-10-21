#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <utility>
#include <vector>
#include <initializer_list>
#include <list>
#include <forward_list>

#include "hash.ok"

int main () {
	using namespace std;
	using namespace std::chrono;


	ifstream input = ifstream("WarAndPeace.txt");

	// On cré le vecteur
	HashMap<string, int> maMap;

	//vector <pair<std::string, int> > vecteurMots;

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])"); // le chapeau c'est la négation
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"

		// ici on vérifie si le mot est déjà dans le vecteur
		int *quantity = maMap.get(word);

		if (quantity != nullptr) ++(*quantity);
		else		  		maMap.put(word, 1);
		nombre_lu++;
	}
	input.close();

    cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
	cout << "Parsing took "
			  << duration_cast<milliseconds>(end - start).count()
			  << "ms.\n";

	cout << "Found a total of " << nombre_lu   << " words." << endl;
	cout << "Nombre d\'occurence de \"war\"   :" << *(maMap.get("war")) << endl;
	cout << "Nombre d\'occurence de \"peace\" :" << *(maMap.get("peace")) << endl;

	size_t nbrToto=0;
	if(maMap.get("toto") != nullptr) nbrToto=*(maMap.get("toto"));

	cout << "Nombre d\'occurence de \"toto\"  :" << nbrToto << endl;

	cout << "Le nombre de mots uniques comptés dans la HashMap: " << maMap.getMotsUnique()<< endl;
	cout << "Le nombre de mots total comptés dans la HashMap  : " << maMap.getMots() << endl;

	cout << endl << "Maintenant on copie la HashMap dans un vecteur" << endl << endl;

	// On met dans un vecteur
	//vector<pair<std::string, int>> vecteurMots(maMap.hashMaptoVector());

	for (auto & p : maMap){
		vecteurMots.push_back(make_pair(p->key, p->value));
	}
	cout << "Nombre de case du vecteur après la copie : " << vecteurMots.size() << endl;
	// On trie le vecteur
	std::sort(vecteurMots.begin(), vecteurMots.end(), [] (const auto & a,const auto & b) {return a.second	> b.second ;});

	// On affiche les dix premiers du vecteur
	cout << endl << "On classe les mots par quantité et on affiche les 10 premiers : " << endl;
	for(size_t i=0;i<10;i++){
		cout << vecteurMots[i].first << ":" << vecteurMots[i].second << endl;
	}

    return 0;
}
