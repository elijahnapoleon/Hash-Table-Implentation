#ifndef hashtable_h
#define hashtable_h

template <typename K, typename V>
cop4530::HashTable<K,V>::HashTable(size_t size) : theLists(prime_below(size))
{
  makeEmpty();
  currentSize=0;
}

template <typename K, typename V>
cop4530::HashTable<K,V>::~HashTable()
{
  makeEmpty();
}

template <typename K, typename V>
void cop4530::HashTable<K,V>::makeTable(size_t size)
{
  theLists.resize(7);
  makeEmpty();
  currentSize = 0;
}

template <typename K, typename V>
bool cop4530::HashTable<K,V>::contains(const K & k)
{
  for(auto i = theLists[myhash(k)].begin(); i!=theLists[myhash(k)].end();++i)
  {
    if(i->first == k){return true;}
  }
  return false;
}

template <typename K, typename V>
bool cop4530::HashTable<K,V>::match(const std::pair<K,V>&kv)
{
  auto & whichList = theLists[myhash(kv.first)];
  return find(begin(whichList), end(whichList), kv) != end(whichList);
}

template <typename K, typename V>
bool cop4530::HashTable<K,V>::insert(const std::pair<K,V>&kv)
{
  if(contains(kv.first))
  {
  auto & whichList = theLists[myhash(kv.first)];
  for(auto i = whichList.begin();i!=whichList.end();++i)
  {
    if(i->first == kv.first)
    {
      auto j = whichList.erase(i);
      whichList.insert(j,kv);
    }
  }
  return true;
  }
  else
  {
  theLists[myhash(kv.first)].push_back(kv);

  if(++currentSize>theLists.size())
  {
    rehash();
  }
  
    return true;
  }

  return false;
}

template <typename K, typename V>
bool cop4530::HashTable<K,V>::insert(std::pair<K,V>&&kv)
{
  const std::pair<K,V> p = std::move(kv); 
  return insert(p);
}

template <typename K, typename V>
bool cop4530::HashTable<K,V>::remove(const K & k)
{
   auto & whichList = theLists[myhash(k)];
  for(auto i = whichList.begin();i!=whichList.end();++i)
  {
    if(i->first == k)
    {
      i = whichList.erase(i);
      currentSize--;
      return true;
    }
  }
  return false;

}

template <typename K, typename V>
void cop4530::HashTable<K,V>::clear()
{
  makeEmpty();
}

template <typename K, typename V>
size_t cop4530::HashTable<K,V>::size()
{
  return currentSize;
}

template <typename K, typename V>
bool cop4530::HashTable<K,V>::load(const char * filename)
{
  ifstream infile;
  infile.open(filename);
  std::pair<K,V> data;
  if(infile)
  {
  while(!infile.eof())
  {
    infile >> data.first >> data.second;
    insert(data);
  }
  infile.close();
  return true;
  }
  else
  {
    return false;
  }
}

template <typename K, typename V>
void cop4530::HashTable<K,V>::dump()
{
  for(int i = 0; i < theLists.size();i++)
  {
    cout << "v[" << i << "]:";
    for(auto j = theLists[i].begin(); j != theLists[i].end();++j)
    {
      if(j != theLists[i].begin())
      {
        cout <<" : ";
      }
      cout << j->first << " " << j->second;;
    }
    cout << endl;
  }
}

template <typename K, typename V>
bool cop4530::HashTable<K,V>::write_to_file(const char* filename)
{
  ofstream outfile;
  outfile.open(filename);
  if(outfile)
  {
    for(int i = 0; i < theLists.size();i++)
  {
    for(auto j = theLists[i].begin();j!= theLists[i].end();++j)
    {
      outfile << j->first << " " << j->second << endl;
    }
  }
  outfile.close();
    return true;
  }
  else
  {
    return false;
  }
}

template <typename K, typename V>
void cop4530::HashTable<K,V>::makeEmpty()
{
  for(auto & thisList : theLists){thisList.clear();}
  currentSize = 0;
}

template <typename K, typename V>
void cop4530::HashTable<K,V>::rehash()
{
  vector<list<pair<K,V>>> oldLists = theLists;

  theLists.resize(prime_below(2*theLists.size()));
  for(auto & thisList : theLists)
    thisList.clear();

  currentSize = 0;
  for(auto & thisList : oldLists)
    for(auto & x : thisList)
      insert(std::move(x));
}

template <typename K, typename V>
size_t cop4530::HashTable<K,V>::myhash(const K& k)
{
  static hash<K> hf;
  return hf(k) % theLists.size();
}


// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long cop4530::HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void cop4530::HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

#endif