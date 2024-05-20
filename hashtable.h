#ifndef COP4530_HASHTABLE_H
#define COP4530_HASHTABLE_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>

using namespace std;

namespace cop4530
{
    template <typename K,typename V>
    class HashTable
    {
        public:
        HashTable(size_t size = 101);
        ~HashTable();
        void makeTable(size_t size);
        bool contains(const K & k);
        bool match(const std::pair<K,V> & kv);
        bool insert(const std::pair<K,V>&kv);
        bool insert(std::pair<K,V>&&kv);
        bool remove(const K & k);
        void clear();
        bool load(const char* filename);
        void dump();
        size_t size();
        bool write_to_file(const char* filename);

        private:
        // max_prime is used by the helpful functions provided
        // to you.
        static const unsigned int max_prime = 1301081;
        // the default_capacity is used if the initial capacity 
        // of the underlying vector of the hash table is zero. 
        static const unsigned int default_capacity = 11;

        vector<list<pair<K,V>>> theLists;
        int currentSize;
        void makeEmpty();
        void rehash();
        size_t myhash(const K& k);
        unsigned long prime_below(unsigned long);
        void setPrimes(vector<unsigned long>&);

    };


    #include "hashtable.hpp"
}






 
#endif
