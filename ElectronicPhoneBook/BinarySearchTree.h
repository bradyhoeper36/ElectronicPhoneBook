#include <string>
#include <iostream>
#include <stack>

class Person {
public:
	Person() : mFirst_Name(""), mLast_Name(""), mPhone_Number("") {}
	Person(std::string first_name, std::string last_name, std::string phone_number) : mFirst_Name(first_name), mLast_Name(last_name), mPhone_Number(phone_number) {};
	void setFirstName(std::string first_name);
	void setLastName(std::string last_name);
	void setPhoneNumber(std::string phone_number);
	std::string getFirstName();
	std::string getLastName();
	std::string getPhoneNumber();
	Person *left;
	Person *right;
private:
	std::string mFirst_Name;
	std::string mLast_Name;
	std::string mPhone_Number;
};

class Book {
public:
	Book() : root(nullptr) {}
	//Display the tree in alphabetical order
	void Display() const;
	//Add a node to the tree
	bool Add(Person *person);
	//Remove a node from the tree
	bool Delete(std::string first_name, std::string last_name);
	//Find a node and return the phone number
	std::string Find(std::string first_name, std::string last_name);
	//Save the tree to a text file and quit
	void Quit();
	void ReadFile();

private:
	Person *root;
};