#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

#define TABLE_SIZE 13

#define PRIME 7
#define RESET "\033[0m"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"

#define BOLDRED "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDBLUE "\033[1m\033[34m"
#define BOLDWHITE "\033[1m\033[37m"

class HashFunction
{

    int *hashTable;
    int curr_size;
    string username;
    string hashcode;

public:
    bool isFull()
    {

        return (curr_size == TABLE_SIZE);
    }

    int hash1(int key)
    {
        return (key % TABLE_SIZE);
    }

    int hash2(int key)
    {
        return (PRIME - (key % PRIME));
    }

    HashFunction()
    {
        hashTable = new int[TABLE_SIZE];
        curr_size = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
            hashTable[i] = -1;
    }

    void insertuser(string key)
    {
        username = key;
    }

    string getusername()
    {
        return username;
    }

    void insertHash(int key)
    {
        if (isFull())
            return;

        int index = hash1(key);
        if (hashTable[index] != -1)
        {

            int index2 = hash2(key);
            int i = 1;
            while (1)
            {
                int newIndex = (index + i * index2) % TABLE_SIZE;

                if (hashTable[newIndex] == -1)
                {
                    hashTable[newIndex] = key;
                    break;
                }
                i++;
            }
        }

        else
            hashTable[index] = key;
        curr_size++;
    }

    void buildthashcode()
    {

        for (int i = 0; i < TABLE_SIZE; i++)
        {

            hashcode += to_string(i);
            if (hashTable[i] != -1)
                hashcode += to_string(hashTable[i]);
            else
            {
                hashcode += "0";
            }
        }

        int n = hashcode.length();

        string binarycode = "";

        for (int i = 0; i <= n; i++)
        {
            int val = int(hashcode[i]);

            string bin = "";
            while (val > 0)
            {

                if (val % 2)
                {
                    bin.push_back('1');
                }

                else
                {
                    bin.push_back('0');
                }
                val /= 2;
            }
            reverse(bin.begin(), bin.end());
            binarycode += bin;
        }
        hashcode = binarycode;
    }

    string gethashcode()
    {
        return (hashcode);
    }

    void displayhashtable()
    {
        cout << BOLDWHITE "\nHash Table\n"
             << endl;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (hashTable[i] != -1)
                cout << i << " --> "
                     << hashTable[i] << endl;
            else
                cout << i << endl
                     << RESET;
        }
    }

    bool validatehash(string pass)
    {
        HashFunction t;
        t.cleartemp();
        for (int i = 0; pass[i] != '\0'; i++)
        {
            t.insertHash(pass[i]);
        }
        t.buildthashcode();
        if (hashcode == t.gethashcode())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void cleartemp()
    {

        hashTable = new int[TABLE_SIZE];
        curr_size = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
            hashTable[i] = -1;
        username = "";
        hashcode = "";
    }
};

int main()
{
    int f = 1, choice, n;
    bool flag;
    string user, pass;
    vector<HashFunction> array;
    HashFunction temp;
    while (f)
    {

        cout << "\nPress 1 to enter username and password: ";
        cout << "\nPress 2 to validate password: ";
        cout << "\nPress 3 to display Hash Table and Hashcode:";
        cout << "\nPress any other key to exit: \n"
             << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter Username:";
            cin >> user;
            cout << "Enter Password:";
            cin >> pass;
            n = pass.length();
            temp.cleartemp();
            temp.insertuser(user);
            for (int i = 0; pass[i] != '\0'; i++)
            {
                temp.insertHash(pass[i]);
            }
            temp.buildthashcode();
            array.push_back(temp);
            break;

        case 2:

            cout << "Enter Username:";
            cin >> user;
            cout << "Enter Password:";
            cin >> pass;
            flag = 0;
            for (auto i = array.begin(); i < array.end(); i++)
            {
                if (i->getusername() == user)
                {

                    flag = 1;

                    if (i->validatehash(pass))

                    {
                        cout << GREEN;
                        cout << "\n-----------------\n";
                        cout << "| " << RESET << BOLDGREEN << "Authenticated." << RESET << GREEN << " |";
                        cout << "\n-----------------\n"
                             << RESET;
                        break;
                    }
                    else
                    {
                        cout << RED;
                        cout << "\n-------------------\n";
                        cout << "| " << RESET << BOLDRED << "Wrong password." << RESET << RED << " |";
                        cout << "\n-------------------\n"
                             << RESET;
                        break;
                    }
                }
            }
            if (flag == 0)
            {
                cout << RED;
                cout << "\n-------------------\n";
                cout << "| " << RESET << BOLDRED << "User not found." << RESET << RED << " |";
                cout << "\n-------------------\n"
                     << RESET;
            }
            break;

        case 3:
            cout << "Enter username:\n";
            cin >> user;
            flag = 0;
            for (auto i = array.begin(); i < array.end(); i++)
            {
                if (i->getusername() == user)
                {
                    flag = 1;
                    i->displayhashtable();
                    cout << BLUE;
                    cout << endl
                         << RESET;
                    cout << BOLDBLUE << "Hashcode\n"
                         << RESET
                         << endl;
                    cout << BLUE << i->gethashcode();
                    cout << endl
                         << RESET;
                    break;
                }
            }
            if (flag == 0)
            {
                cout << RED;
                cout << "\n-------------------\n";
                cout << "| " << RESET << BOLDRED << "User not found." << RESET << RED << " |";
                cout << "\n-------------------\n"
                     << RESET;
            }
            break;
        default:
            f = 0;
            break;
        }
    }
    return 0;
}
