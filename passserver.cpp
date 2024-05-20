#include "passserver.h"
#include "hashtable.h"

using namespace std;
using namespace cop4530;

PassServer::PassServer(size_t size)
{
   ht.makeTable(size);
}

PassServer::~PassServer()
{
    ht.clear();
}

bool PassServer::load(const char* filename)
{
    ifstream infile;
    infile.open(filename);
    std::pair<string,string> data;
    if(infile)
    {
    while(!infile.eof())
    {
        infile >> data.first >> data.second;
        ht.insert(data);
    }
    infile.close();
    return true;
    }
    else
    {
        return false;
    }
}

bool PassServer::addUser(std::pair<string,string> & kv)
{
   kv.second = encrypt(kv.second);
   return ht.insert(kv);
}

bool PassServer::addUser(std::pair<string,string> && kv)
{
    std::pair<string,string> p= std::move(kv);
    return addUser(p);
}

bool PassServer::removeUser(const string & k)
{
    return ht.remove(k);
}

bool PassServer::changePassword(const std::pair<string,string> &p, const string & newpassword)
{
    std::pair<string,string> p2 = p;
    p2.second = encrypt(p2.second);
    string s = encrypt(newpassword);
    std::pair<string,string> newacc = p2;
    newacc.second = s;
    
    if(!ht.match(p2) || ht.match(newacc) == true)
    {
        return false;
    }
    else
    {
        ht.insert(newacc);
        return true;
    }
}

bool PassServer::find(const string & user) 
{
    return ht.contains(user);
}

void PassServer::dump() 
{
    ht.dump();
}

size_t PassServer::size()
{
    return ht.size();
}

bool PassServer::write_to_file(const char* filename)
{
    return ht.write_to_file(filename);
}

string PassServer::encrypt(const string & str)
{
    char salt[] = "$1$########";
	
    string password = crypt(str.c_str(),salt);
    password.erase(0,12);
	
    return password;
}