#pragma once
#include <thread>
#include <mutex>
using namespace std;

namespace pr {

class Compte {
	mutable std::recursive_mutex m;
	int solde;
public :
	Compte(int solde=0):solde(solde) {}
	Compte(const Compte & other);
	void crediter (unsigned int val) ;
	bool debiter (unsigned int val) ;
	int getSolde() const  ;

	inline void lock() const;  // Lock le mutx
	inline void unlock() const;// Unlock le mutex
	inline bool try_lock() const;     //


};

inline void Compte::lock() const  {   m.lock();  }
inline void Compte::unlock()const {   m.unlock();}
inline bool Compte::try_lock()const  {   return m.try_lock(); }


}
