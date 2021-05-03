#include<iostream>
#include <fstream>
using namespace std;

class User
{
private:

    string name;
    int age;
    User* nextName;
    User* nextAge;

public:

    User(string name, int age)
    {
        this->name = name;
        this->age = age;
        this->nextName = NULL;
        this->nextAge = NULL;
    }

    string getName()
	{
        return name;
    }
    void setName(string newName)
    {
        name = newName;
    }

    int getAge()
    {
        return age;
    }
    void setAge(int newAge)
    {
        age = newAge;
    }

    User* getNextName()
    {
        return nextName;
    }
    void setNextName(User* newNextName)
    {
        nextName = newNextName;
    }

    User* getNextAge()
    {
        return nextAge;
    }
    void setNextAge(User* newNextAge)
    {
        nextAge = newNextAge;
    }

};

class Database
{
private:

    User* firstName;
    User* firstAge;

public:

    Database()
    {
        firstName = NULL;
        firstAge = NULL;
    }

    void add(string name, int age)
    {
        User* theNewUser = new User(name, age);
        
        if(firstName == NULL) 
        {
            firstName = theNewUser;
        }
        else if(firstName->getName() > name)
        {
            theNewUser->setNextName(firstName);
            firstName = theNewUser;
        }
        else
        {
            User* current = firstName;
            while(current->getNextName() != NULL && current->getNextName()->getName() < name) 
                current = current->getNextName();
            theNewUser->setNextName(current->getNextName());
            current->setNextName(theNewUser);
        }
        
        if(firstAge == NULL) 
        {
            firstAge = theNewUser;
        }
        else if(firstAge->getAge() > age)
        {
            theNewUser->setNextAge(firstAge);
            firstAge = theNewUser;
        }
        else
        {
            User* current = firstAge;
            while(current->getNextAge() != NULL && current->getNextAge()->getAge() < age) 
                current = current->getNextAge();
            theNewUser->setNextAge(current->getNextAge());
            current->setNextAge(theNewUser);
        }        
    }

    bool remove(string name)
    {
        if(firstName == NULL) 
            return false;

        User* removingUser = NULL;
        User* current = NULL;
        if(firstName != NULL && firstName->getName() == name)
        {
            removingUser = firstName;
            firstName = removingUser->getNextName();
        }
        else
        {
            current = firstName;
            while(current->getNextName() != NULL && current->getNextName()->getName() != name)
                current = current->getNextName();
            if(current ->getNextName() != NULL)
            {
                removingUser = current->getNextName();
                current->setNextName(removingUser->getNextName());
            }
        }

        if(removingUser == NULL) 
            return false;
        
        if(firstAge == removingUser)
        {
            firstAge = removingUser->getNextAge();
        }
        else
        {
            current = firstAge;
            while(current->getNextAge() != removingUser)
                current = current->getNextAge();
            current->setNextAge(removingUser->getNextAge());
        }

        delete removingUser;
        return true;
        
    }

    void update(string name, int age)
    {
        User* current = firstName;
        while(current->getName() != name)
        {
            current = current->getNextName();
        }

        if(current != NULL)
            current->setAge(age);
        
    }

    void printByAge()
    {
        User* current = firstAge;
        while(current != NULL)
        {
            cout << current->getName() << " " << current->getAge() << endl;
            current = current->getNextAge();
        }
    }

    void printByName()
    {
        User* current = firstName;
        while(current != NULL)
        {
            cout << current->getName() << " " << current->getAge() << endl;
            current = current->getNextName();
        }
    }

    void loadFile(string filename)
    {
        string name;
        int age;
        ifstream theFile(filename);
        if(theFile.is_open())
        {
            while(theFile >> name >> age)
                this->add(name, age);
            theFile.close();
        }
    }

    void saveToFileByAge(string filename)
    {
        ofstream theFile(filename);
        if(theFile.is_open())
        {
            User* current = firstAge;
            while(current != NULL)
            {
                theFile << current->getName() << " " << current->getAge() << endl;
                current = current->getNextAge();
            }
            theFile.close();
        }
    }

    void saveToFileByName(string filename)
    {
        ofstream theFile(filename);
        if(theFile.is_open())
        {
            User* current = firstName;
            while(current != NULL)
            {
                theFile << current->getName() << " " << current->getAge() << endl;
                current = current->getNextName();
            }
            theFile.close();
        }
    }

    ~Database()
    {
        User* tmp = NULL;
        while(firstName != NULL)
        {
            tmp = firstName;
            firstName = tmp->getNextName();
            delete tmp;
        }
    }

};

int main()
{
    Database database1;

    database1.loadFile("db.txt");

    cout << endl << "Print By Name" << endl;
    database1.printByName();

    cout << endl << "Print By Age" << endl;
    database1.printByAge();

    database1.add("ali", 55);
    database1.remove("bugra");
    database1.update("can", 44);

    database1.saveToFileByName("name.txt");
    database1.saveToFileByAge("age.txt");
    return 0;
}
