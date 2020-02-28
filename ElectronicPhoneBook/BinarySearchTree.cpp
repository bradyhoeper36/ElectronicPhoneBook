#include "BinarySearchTree.h"
#include <algorithm>
#include <fstream>

void Person::setFirstName(std::string first_name)
{
	mFirst_Name = first_name;
}

void Person::setLastName(std::string last_name)
{
	mLast_Name = last_name;
}

void Person::setPhoneNumber(std::string phone_number)
{
	mPhone_Number = phone_number;
}

std::string Person::getFirstName()
{
	return mFirst_Name;
}

std::string Person::getLastName()
{
	return mLast_Name;
}

std::string Person::getPhoneNumber()
{
	return mPhone_Number;
}

void Book::Display() const
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
		std::cout << "\t" << tempPerson->getFirstName() << " " << tempPerson->getLastName() << " (" << tempPerson->getPhoneNumber() << ")" << std::endl; 
		tempPerson = tempPerson->right; // Do right sub-tree
	}
}

bool Book::Add(Person *person)
{
	if (root == nullptr)
	{
		root = person;
		return true;
	}
	else
	{
		Person *tempPerson = root;
		while (tempPerson != nullptr)
		{
			if (person->getLastName() < tempPerson->getLastName()) // Compare last names first
			{
				if (tempPerson->left == nullptr)
				{
					tempPerson->left = person;
					return true;
				}
				tempPerson = tempPerson->left;
			}
			else if (person->getLastName() > tempPerson->getLastName())
			{
				if (tempPerson->right == nullptr)
				{
					tempPerson->right = person;
					return true;
				}
				tempPerson = tempPerson->right;
			}
			else // Last names are identical, compare first names
			{
				if (person->getFirstName() < tempPerson->getFirstName())
				{
					if (tempPerson->left == nullptr)
					{
						tempPerson->left = person;
						return true;
					}
					tempPerson = tempPerson->left;
				}
					
				else if (person->getFirstName() > tempPerson->getFirstName())
				{
					if (tempPerson->right == nullptr)
					{
						tempPerson->right = person;
						return true;
					}
					tempPerson = tempPerson->right;
				}
				else // Name already exists
					return false;
			}
		}
		return false;
	}
}

bool Book::Delete(std::string first_name, std::string last_name)
{
	if (root == nullptr) 
		return false;

	if (root->getLastName() == last_name && root->getFirstName() == first_name)
	{
		// TO DO: Delete root
		return true;
	}

	Person *parent = nullptr;
	Person *tempPerson = root;

	while (tempPerson != nullptr)
	{
		if (tempPerson->getLastName() == last_name && tempPerson->getFirstName() == first_name)
		{
			if (tempPerson->left == nullptr && tempPerson->right == nullptr) // Node has no children so we can just delete
			{
				delete tempPerson;
				return true;
			}
			
			if ((tempPerson->left != nullptr) && (tempPerson->right == nullptr)) // Node has a left child and no right child
			{
				if (tempPerson == parent->left) // Deleting node is the left child of parent, the left child needs to be the left child of parent
				{
					parent->left = tempPerson->left;
				}
				
				if (tempPerson == parent->right) // Deleting node is the right child of parent, the left child needs to be the right child of parent
				{
					parent->right = tempPerson->left;
				}

				delete tempPerson;
				return true;
			}

			else if ((tempPerson->left == nullptr) && (tempPerson->right != nullptr)) // Node has a right child and no left child
			{
				if (tempPerson == parent->left) // Deleting node is the left child of parent, the right child needs to be left child of parent
				{
					parent->left = tempPerson->right;
				}

				if (tempPerson == parent->right) // Deleting node is the right child of parent, the right child needs to be right child of parent
				{
					parent->right = tempPerson->right;
				}

				delete tempPerson;
				return true;
			}
			
			else // Deleting node has two children
			{
				if (tempPerson == parent->left)
				{
					parent->left = tempPerson->right;
					tempPerson->right->left = tempPerson->left;
				}

				if (tempPerson == parent->right)
				{
					parent->right = tempPerson->left;
					tempPerson->left->right = tempPerson->right;
				}

				delete tempPerson;
				return true;
			}

			return false;
		}

		if (last_name < tempPerson->getLastName() && tempPerson->left != nullptr)
		{
			parent = tempPerson;
			tempPerson = tempPerson->left;
		}
		else if (last_name > tempPerson->getLastName() && tempPerson->right != nullptr)
		{
			parent = tempPerson;
			tempPerson = tempPerson->right;
		}
		else if (last_name == tempPerson->getLastName()) // Same last name
		{
			if (first_name < tempPerson->getFirstName() && tempPerson->left != nullptr)
			{
				parent = tempPerson;
				tempPerson = tempPerson->left;
			}
			else if (first_name > tempPerson->getFirstName() && tempPerson->right != nullptr)
			{
				parent = tempPerson;
				tempPerson = tempPerson->right;
			}
		}
	}
}

std::string Book::Find(std::string first_name, std::string last_name)
{
	if (root == nullptr)
		return false;

	if (root->getLastName() == last_name && root->getFirstName() == first_name)
	{
		return root->getPhoneNumber();
	}

	Person *tempPerson = root;

	while (tempPerson != nullptr)
	{
		if (tempPerson->getLastName() == last_name && tempPerson->getFirstName() == first_name)
		{
			return tempPerson->getPhoneNumber();
		}

		if (last_name < tempPerson->getLastName() && tempPerson->left != nullptr)
		{
			tempPerson = tempPerson->left;
		}
		else if (last_name > tempPerson->getLastName() && tempPerson->right != nullptr)
		{
			tempPerson = tempPerson->right;
		}
		else if (last_name == tempPerson->getLastName()) // Same last name
		{
			if (first_name < tempPerson->getFirstName() && tempPerson->left != nullptr)
			{
				tempPerson = tempPerson->left;
			}
			else if (first_name > tempPerson->getFirstName() && tempPerson->right != nullptr)
			{
				tempPerson = tempPerson->right;
			}
		}
	}
}

void Book::Quit()
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
			file << person->getFirstName() << " " << person->getLastName() << " " << person->getPhoneNumber() << std::endl; // Write the Person information
		}

		stk.pop();

		if (person->right) 
			stk.push(person->right); // Push right child to the stack
		if (person->left)
			stk.push(person->left); // Push left child to the stack
	}
	
	file.close(); // close file
}

void Book::ReadFile()
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
