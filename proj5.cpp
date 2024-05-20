#include <iostream>
#include "hashtable.h"
#include "passserver.h"


using namespace std;
using namespace cop4530;

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main()
{
  int num;
	char choice = ' ';
	char filename[50];
	string user, password;
	cout << "Enter preffered hash table capacity: \n";
	cin >> num;
	PassServer t1(num);
	
	while(choice != 'x')
	{
		Menu();
		cin >> choice;
		
		if(choice == 'l')
		{
			cout << "Enter file to load from: \n";
			cin >> filename;
			if(t1.load(filename))
			{
				cout << "File loaded successfully\n";
			}
			else
			{
				cout << "Error while loading file\n";
			}
		}
		else if(choice == 'a')
		{
			cout << "Enter username: \n";
			cin >> user;
      cout << "Enter password: \n";
      cin >> password;
      std::pair<string,string> p(user,password);

			if(t1.addUser(p))
			{
				cout << "User " << user << " added.\n";
			}
			else
			{
				cout << "Error\n";
			}
		}
		else if(choice == 'r')
		{
			cout << "Enter user: \n";
			cin >> user;
			if(t1.removeUser(user))
			{
				cout << "User " << user << " deleted.\n";
			}
      else
      {
        cout << "Error: User not found. Could not delete user.\n";
      }
		}
		else if(choice == 'c')
		{
			cout << "Enter username: \n";
      cin >> user;
      if(t1.find(user))
      {
        cout << "Enter password: \n";
        cin >> password;

        std::pair<string,string> p(user,password);
		string newpassword;
		cout << "Enter new password: \n";
        cin >> newpassword;


        if(t1.changePassword(p,newpassword))
        {
          cout << "Password changed for user " << p.first << endl;
        }
		else
		{
			cout << "Error. Could not change password\n";
		}

      }
	  else
	  {
		cout << "Error. User not found\n";
	  }
		}
		else if(choice == 'f')
		{
			cout << "Enter user: \n";
			cin >> user;
			if(t1.find(user))
			{
				cout << "User " << user << " found.\n";
			}
			else
			{
				cout << "User " << user <<" not found.";
			}
		}
		else if(choice == 'd')
		{
			t1.dump();
		}
		else if(choice == 's')
		{
			cout << "Size of hashtable: " << t1.size() << endl;
		}
		else if(choice == 'w')
		{
			cout << "Enter file name to write to: \n";
			cin >> filename;
			if(t1.write_to_file(filename))
			{
				cout << "Written successfully\n";
			}
			else
			{
				cout << "Error";
			}
		}
		else if(choice == 'x')
		{
			break;
		}
		else
		{
			cin >> choice;
		}

}

}
