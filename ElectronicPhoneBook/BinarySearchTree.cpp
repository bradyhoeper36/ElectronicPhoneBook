#include "BinarySearchTree.h"

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
		// Get to very left
		while (tempPerson != nullptr)
		{
			// Left sub-tree
			stk.push(tempPerson);
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
			// Compare last names first
			if (person->getLastName() < tempPerson->getLastName())
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
			// Last names are identical, compare first names
			else
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
		// Same last name
		else if (last_name == tempPerson->getLastName())
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
	return 0;
}

void Book::Quit()
{
}
