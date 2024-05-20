#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"

#include <utility> 
#include <string> 
#include <cstring> 
#include <unistd.h>
#include <crypt.h>
#include <iostream> 

using namespace std;
using namespace cop4530;

class PassServer  //implemented as an adaptor class, with the HashTable as the adaptee class.
{
	public: //Public interfaces:
	
		PassServer(size_t size = 101); 
		~PassServer(); 
		bool load(const char* filename); 
		bool addUser(std::pair<string, string> & kv); 
		bool addUser(std::pair<string, string> && kv); 
		bool removeUser(const string & k); 
		bool changePassword(const pair<string, string> &p, const string & newpassword); 
		bool find(const string & user);
		void dump();
		size_t size();
		bool write_to_file(const char* filename); 
	private: 
	
    	string encrypt(const string & str); 
		HashTable<string, string> ht; 
};

#include "passserver.cpp"

#endif