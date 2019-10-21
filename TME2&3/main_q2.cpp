#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <utility>
#include <vector>


int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("WarAndPeace.txt");

	// On cré le vecteur
	vector <pair<std::string, int> > vecteurMots;

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


		bool findit=false;


		// ici on vérifie si le mot est déjà dans le vecteur
		if (!(vecteurMots.empty())){
			unsigned int i=0;
			while (i < vecteurMots.size() && !findit){
				if (word == (vecteurMots.at(i).first)){
					++(vecteurMots.at(i).second);
					findit = true;
				}
				++i;
			}
		}

		// ici on met le mot dans le vecteur si il n'y est pas déjà
		if (!findit) vecteurMots.push_back(make_pair(word,1));

		/*
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << "Taille vecteur : " << vecteurMots.size() << endl;
		*/
		nombre_lu++;
	}
	input.close();

    cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
	cout << "Parsing took "
			  << duration_cast<milliseconds>(end - start).count()
			  << "ms.\n";

	cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "Found a total of " << vecteurMots.size() << " unique words." << endl;

	// On affiche
    for (unsigned int i=0 ; i < vecteurMots.size() ; ++i){
    	if (vecteurMots[i].first == "war" || vecteurMots[i].first == "peace" || vecteurMots[i].first == "toto")
    	cout << vecteurMots[i].first << " = " << vecteurMots[i].second << endl;
    }



    return 0;
}
