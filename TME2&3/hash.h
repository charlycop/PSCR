#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <utility>
#include <vector>
#include <initializer_list>
#include <list>
#include <forward_list>




template <typename K, typename V>
class HashMap{

	struct Entry{
		const K key;
		V value;
		Entry (const K& key, const V& value)
		: key(key), value(value){}
	};

	// attribut
	std::vector <std::forward_list<Entry>> buckets;


	class iterator{
			typename std::vector<std::forward_list<Entry> >::iterator vit;
			typename std::forward_list<Entry>::iterator lit;
			std::vector <std::forward_list<Entry>> * pbuckets;

			public:

			iterator (typename std::vector<std::forward_list<Entry> >::iterator vit,
			typename std::forward_list<Entry>::iterator lit, std::vector <std::forward_list<Entry>> * pbuckets): vit(vit),lit(lit),pbuckets(pbuckets){}

			iterator& operator++(){
				++lit;

				if (lit !=  vit->end()) // fin de la liste du bucket *vit courant
					return *this;

				++vit;
				while( vit->empty() )
					++vit;

				if (vit != buckets.end())  // si l'iterateur vit est différent de l'iterateur de fin de bucket
					lit = vit->begin();     // Alors on met l'itérateur de début de la liste du bucket dans lit

				return *this;
			}

				Entry & operator*() {
					return (*lit);
				}

				bool operator!=(typename std::forward_list<Entry>::iterator &other){
					return (lit != other);
				}


		};
	/////////////////////////////////////////////

//////////////////////////////

public :



	HashMap(){ // Constructeur
		for (size_t i=0; i<25000 ; i++){
			buckets.push_back(std::forward_list<Entry>());
		}
	};

	iterator begin(){
		for (auto &buc : buckets){
			for(auto &lis : buc){
				if(lis.begin() != nullptr)
					return iterator(lis.begin());
			}
		}
		return nullptr;
	}

	iterator end(){
		for (auto it=buckets.end(), _end = buckets.begin(); it != _end ; --it){
			for(auto &lis : it){
				if(lis.begin() != nullptr)
					return iterator(lis.end());
			}
		}
		return nullptr;
	}

	V* get(const K& key) {
		size_t h = std::hash<K>()(key);
		h = h%buckets.size();
		for(Entry &ent : buckets[h]){
			if(ent.key == key){
				return & ent.value;
			}
		}
		return nullptr;
	}

	void put (const K& key, const V& value){
		size_t h = std::hash<K>()(key);
		h = h%buckets.size();
		bool foundit=false;

		for(Entry &ent : buckets[h]){
			if(ent.key == key) {
				ent.value=value;
				foundit = true;
				break;
			}
		}
		if(!foundit) buckets[h].push_front(Entry(key,value));
	}

	size_t getMotsUnique(){
		size_t nbMots=0;
		for (auto &L : buckets){
			for(auto &ent : L) ++nbMots;
		}
		return nbMots;
	}

	size_t getMots(){
		size_t nbMots=0;
		for (auto &L : buckets){
			for(auto &ent : L) nbMots += ent.value;
		}
		return nbMots;
	}

	std::vector <std::pair<K,V>> hashMaptoVector(){
		std::vector <std::pair<K,V>> vecteur;
		for (auto &L : buckets){
			for(auto &ent : L){
				vecteur.push_back(make_pair(ent.key,ent.value));
			}
		}
		return vecteur;
	}

};


