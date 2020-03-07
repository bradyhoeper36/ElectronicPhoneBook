#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <stack>

enum color{ red, black};

struct Person {
	Person() : firstName(""), lastName(""), phoneNumber(""), Color(color::black), left(nullptr), right(nullptr), parent(nullptr) {}
	Person(std::string first_name, std::string last_name, std::string phone_number) : firstName(first_name), lastName(last_name), phoneNumber(phone_number), Color(color::black), left(nullptr), right(nullptr), parent(nullptr) {};
	Person *left;
	Person *right;
	Person *parent;
	std::string firstName;
	std::string lastName;
	std::string phoneNumber;
	color Color;
};

class Book {
	Person *root;
public:
	Book() : root(nullptr) {}
	void Display() const //Display the tree in alphabetical order
	{
		std::stack<Person *> stk;
		Person *tempPerson = root;
		std::cout << "Phonebook: " << std::endl;

		while (tempPerson != nullptr || stk.empty() == false)
		{
			while (tempPerson != nullptr) // Get to very left
			{
				stk.push(tempPerson); // Left sub-tree
				tempPerson = tempPerson->left;
			}

			tempPerson = stk.top();
			stk.pop();
			std::cout << "\t" << tempPerson->firstName << " " << tempPerson->lastName << " (" << tempPerson->phoneNumber << ")" << std::endl;
			tempPerson = tempPerson->right; // Do right sub-tree
		}
	}
	
	bool Add(Person *person) //Add a node to the tree
	{
		
	}

	bool Delete(std::string first_name, std::string last_name) //Remove a node from the tree
	{
		
	}

	std::string Find(std::string first_name, std::string last_name) //Find a node and return the phone number
	{
		if (root == nullptr)
			return false;

		if (root->lastName == last_name && root->firstName == first_name)
		{
			return root->phoneNumber;
		}

		Person *tempPerson = root;

		while (tempPerson != nullptr)
		{
			if (tempPerson->lastName == last_name && tempPerson->firstName == first_name)
			{
				return tempPerson->phoneNumber;
			}

			if (last_name < tempPerson->lastName && tempPerson->left != nullptr)
			{
				tempPerson = tempPerson->left;
			}
			else if (last_name > tempPerson->lastName && tempPerson->right != nullptr)
			{
				tempPerson = tempPerson->right;
			}
			else if (last_name == tempPerson->lastName) // Same last name
			{
				if (first_name < tempPerson->firstName && tempPerson->left != nullptr)
				{
					tempPerson = tempPerson->left;
				}
				else if (first_name > tempPerson->firstName && tempPerson->right != nullptr)
				{
					tempPerson = tempPerson->right;
				}
			}
		}
	}
	void Quit() //Save the tree to a text file and quit
	{
		std::ofstream file("phonebook.txt"); // open file

		if (root == nullptr)
			return;

		std::stack<Person*> stk; // Create a stack to hold Person nodes
		stk.push(root);

		while (stk.empty() == false) // Pop the top item from stack and print it 
		{
			Person *person = stk.top();
			if (file.is_open()) // Check that we successfully opened the text file
			{
				file << person->firstName << " " << person->lastName << " " << person->phoneNumber << std::endl; // Write the Person information
			}

			stk.pop();

			if (person->right)
				stk.push(person->right); // Push right child to the stack
			if (person->left)
				stk.push(person->left); // Push left child to the stack
		}

		file.close(); // close file
	}
	void ReadFile()
	{
		std::ifstream file("phonebook.txt"); // open file
		std::string str;
		size_t pos = 0;
		int i = 0;
		std::string firstName;
		std::string lastName;
		std::string phoneNumber;

		while (std::getline(file, str))
		{
			i = 0;
			while ((pos = str.find(" ")) != std::string::npos)
			{
				if (i == 0)
				{
					firstName = str.substr(0, pos);
				}
				else if (i == 1)
				{
					lastName = str.substr(0, pos);
				}

				i++;
				str.erase(0, pos + 1);
			}

			if (i == 2)
			{
				phoneNumber = str.substr(0, pos);
			}

			Person *person = new Person(firstName, lastName, phoneNumber);
			this->Add(person);
		}
	}
};

class UserInterface {
	private:
		std::vector<std::string> args;

		void setAddStringArgs(std::string first_name, std::string last_name, std::string phone_number)
		{
			args.clear();
			args.push_back(first_name);
			args.push_back(last_name);
			args.push_back(phone_number);
		}

		void setFindDeleteStringArgs(std::string first_name, std::string last_name)
		{
			args.clear();
			args.push_back(first_name);
			args.push_back(last_name);
		}

	public:
		UserInterface() {}

		void initialize()
		{
			std::cout << "Welcome to the Binary Search Tree implementation of an Electronic Phonebook\n\n";
		};

		int runInputLoop()
		{
			std::cout << "Options:(1) Add Person\n\t(2) Get Phone Number\n\t(3) Delete Person\n\t(4) Display Phonebook\n\t(5) Quit (write phonebook to file)\n\t(6) Read file" << std::endl;
			int userChoice;
			std::cin >> userChoice;

			std::string firstName;
			std::string lastName;
			std::string phoneNumber;
			std::string parseString;
			size_t pos = 0;
			int i = 0;

			switch (userChoice)
			{
			case (1):
				std::cout << "Enter Information with spaces: FirstName LastName PhoneNumber: ";
				std::getline(std::cin >> std::ws, parseString);

				while ((pos = parseString.find(" ")) != std::string::npos)
				{
					if (i == 0)
					{
						firstName = parseString.substr(0, pos);
					}
					else if (i == 1)
					{
						lastName = parseString.substr(0, pos);
					}

					i++;
					parseString.erase(0, pos + 1);
				}

				if (i == 2)
				{
					phoneNumber = parseString.substr(0, pos);
				}

				if (firstName.empty() || lastName.empty() || phoneNumber.empty()) // Invalid inputs
				{
					std::cout << "Invalid inputs for Add\n";
					break;
				}

				std::cout << "\n";

				setAddStringArgs(firstName, lastName, phoneNumber);
				return 1;
				break;

			case (2):
				std::cout << "Enter Information with spaces: FirstName LastName: ";
				std::getline(std::cin >> std::ws, parseString);

				while ((pos = parseString.find(" ")) != std::string::npos)
				{
					if (i == 0)
					{
						firstName = parseString.substr(0, pos);
					}
					
					i++;
					parseString.erase(0, pos + 1);
				}

				lastName = parseString.substr(0, pos);

				if (firstName.empty() || lastName.empty())
				{
					std::cout << "Invalid inputs for Find\n";
					break;
				}

				std::cout << "\n";
				setFindDeleteStringArgs(firstName, lastName);
				return 2;
				break;

			case (3):
				std::cout << "Enter Information with spaces: FirstName LastName: ";
				std::getline(std::cin >> std::ws, parseString);

				while ((pos = parseString.find(" ")) != std::string::npos)
				{
					if (i == 0)
					{
						firstName = parseString.substr(0, pos);
					}

					i++;
					parseString.erase(0, pos + 1);
				}

				lastName = parseString.substr(0, pos);
				std::cout << "\n";
				setFindDeleteStringArgs(firstName, lastName);
				return 3;
				break;

			case (4): // Display ()
				return 4;
				break;

			case (5): // Quit ()
				return 5;
				break;
			case (6): // Read ()
				return 6;
				break;
			}
		}
		std::vector <std::string> getStringArgs()
		{
			return args;
		}
};

int main()
{
	Book *phonebook = new Book();
	UserInterface *phonebookInterface = new UserInterface();
	phonebookInterface->initialize();

	while (int option = phonebookInterface->runInputLoop())
	{
		std::vector <std::string> args;
		if (option == 1) // Perform Add()
		{
			args = phonebookInterface->getStringArgs();
			Person *person = new Person(args[0], args[1], args[2]);
			phonebook->Add(person);
		}
		else if (option == 2) // Perform Find()
		{
			args = phonebookInterface->getStringArgs();
			std::cout << "Phone Number of " << args[0] << " " << args[1] << ": " << phonebook->Find(args[0], args[1]) << std::endl;
		}
		else if (option == 3) // Perform Delete()
		{
			args = phonebookInterface->getStringArgs();
			bool didDelete = phonebook->Delete(args[0], args[1]);
			if (didDelete)
				std::cout << "Deleted Person: " << args[0] << " " << args[1] << std::endl;
			else
				std::cout << args[0] << " " << args[1] << " does not exist\n";

		}
		else if (option == 4) // Perform Display()
		{
			phonebook->Display();
		}
		else if (option == 5) // Perform Quit()
		{
			phonebook->Quit();
			exit(0);
		}
		else if (option == 6) // Perform Read()
		{
			phonebook->ReadFile();
		}
	}
}
