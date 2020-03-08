#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <stack>

const char *FILENAME = "phonebook.txt";

enum color{ red, black };

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

	bool IsOnLeft() 
	{ 
		return this == parent->left; 
	}

	bool HasRedChild() 
	{
		return (left != nullptr && left->Color == red) ||
			(right != nullptr && right->Color == red);
	}

	Person *Sibling() 
	{
		if (parent == nullptr)
			return nullptr;

		if (IsOnLeft())
			return parent->right;

		return parent->left;
	}

	void MoveDown(Person *nParent) {
		if (parent != nullptr) {
			if (IsOnLeft()) {
				parent->left = nParent;
			}
			else {
				parent->right = nParent;
			}
		}
		nParent->parent = parent;
		parent = nParent;
	}
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
		root = BSTAdd(root, person);

		if (root == nullptr) // Person already existed
			return false;

		FixViolation(root, person);
	}

	Person *BSTAdd(Person *root, Person *person)
	{
		/* If the tree is empty, return a new node */
		if (root == nullptr)
			return person;

		/* Otherwise, recur down the tree */
		if (person->lastName < root->lastName)
		{
			root->left = BSTAdd(root->left, person);
			root->left->parent = root;
		}
		else if (person->lastName > root->lastName)
		{
			root->right = BSTAdd(root->right, person);
			root->right->parent = root;
		}
		else
		{
			if (person->firstName < root->firstName)
			{
				root->left = BSTAdd(root->left, person);
				root->left->parent = root;
			}
			else if (person->firstName > root->firstName)
			{
				root->right = BSTAdd(root->right, person);
				root->right->parent = root;
			}
			else
				return nullptr;
		}

		return root;
	}

	void FixViolation(Person *&root, Person *&person)
	{
		Person *parentPerson = nullptr;
		Person *grandParentPerson = nullptr;

		while ((person != root) && (person->Color != black) && (person->parent->Color == red))
		{
			parentPerson = person->parent;
			grandParentPerson = person->parent->parent;

			if (parentPerson == grandParentPerson->left) // Parent of Person is left child of Grand parent of Person
			{
				Person *unclePerson = grandParentPerson->right;

				if (unclePerson != nullptr && unclePerson->Color == red) // Uncle of person is red
				{
					grandParentPerson->Color = red;
					parentPerson->Color = black;
					unclePerson->Color = black;
					person = grandParentPerson;
				}

				else
				{
					if (person == parentPerson->right) // Person is the right child
					{
						RotateLeft(root, parentPerson);
						person = parentPerson;
						parentPerson = person->parent;
					}
					// Person is the left child
					RotateRight(root, grandParentPerson);
					std::swap(parentPerson->Color, grandParentPerson->Color);
					person = parentPerson;
				}
			}
			else // Parent of pt is right child of Grand-parent of pt
			{
				Person *unclePerson = grandParentPerson->left;
				
				if ((unclePerson != nullptr) && (unclePerson->Color == red)) // Uncle of person is red
				{
					grandParentPerson->Color = red;
					parentPerson->Color = black;
					unclePerson->Color = black;
					person = grandParentPerson;
				}
				else
				{
					if (person == parentPerson->left) // Person is the left child
					{
						RotateRight(root, parentPerson);
						person = parentPerson;
						parentPerson = person->parent;
					}
					// Person is the right child
					RotateLeft(root, grandParentPerson);
					std::swap(parentPerson->Color, grandParentPerson->Color);
					person = parentPerson;
				}
			}
		}

		root->Color = black;
	}

	void RotateLeft(Person *&root, Person *&person)
	{
		Person *rightPerson = person->right;

		person->right = rightPerson->left;

		if (person->right != nullptr)
			person->right->parent = person;

		rightPerson->parent = person->parent;

		if (person->parent == nullptr)
			root = rightPerson;

		else if (person == person->parent->left)
			person->parent->left = rightPerson;

		else
			person->parent->right = rightPerson;

		rightPerson->left = person;
		person->parent = rightPerson;
	}

	void RotateRight(Person *&root, Person *&person)
	{
		Person *leftPerson = person->left;

		person->left = leftPerson->right;

		if (person->left != nullptr)
			person->left->parent = person;

		leftPerson->parent = person->parent;

		if (person->parent == nullptr)
			root = leftPerson;

		else if (person == person->parent->left)
			person->parent->left = leftPerson;

		else
			person->parent->right = leftPerson;

		leftPerson->right = person;
		person->parent = leftPerson;
	}

	void LeftRotate(Person *person) 
	{
		Person *newParent = person->right;
		if (person == root)
			root = newParent;

		person->MoveDown(newParent);
		person->right = newParent->left;

		if (newParent->left != nullptr)
			newParent->left->parent = person;

		newParent->left = person;
	}

	void RightRotate(Person *person) {
		Person *newParent = person->left; 

		if (person == root)
			root = newParent;

		person->MoveDown(newParent);
		person->left = newParent->right;

		if (newParent->right != nullptr)
			newParent->right->parent = person;

		newParent->right = person;
	}

	void FixDoubleBlack(Person *x)
	{
		if (x == root)
			return;

		Person *sibling = x->Sibling(), *parent = x->parent;

		if (sibling == nullptr) 
			FixDoubleBlack(parent);
		else 
		{
			if (sibling->Color == red) 
			{
				parent->Color = red;
				sibling->Color = black;
				if (sibling->IsOnLeft()) 
					RightRotate(parent);
				else 
					LeftRotate(parent);

				FixDoubleBlack(x);
			}
			else 
			{
				if (sibling->HasRedChild()) 
				{
					if (sibling->left != nullptr && sibling->left->Color == red) 
					{
						if (sibling->IsOnLeft()) // left left 
						{
							sibling->left->Color = sibling->Color;
							sibling->Color = parent->Color;
							RightRotate(parent);
						}
						else // right left 
						{
							sibling->left->Color = parent->Color;
							RightRotate(sibling);
							LeftRotate(parent);
						}
					}
					else 
					{
						if (sibling->IsOnLeft()) // left right 
						{
							sibling->right->Color = parent->Color;
							LeftRotate(sibling);
							RightRotate(parent);
						}
						else // right right 
						{
							sibling->right->Color = sibling->Color;
							sibling->Color = parent->Color;
							LeftRotate(parent);
						}
					}

					parent->Color = black;
				}
				else // 2 black children 
				{
					sibling->Color = red;

					if (parent->Color == black)
						FixDoubleBlack(parent);
					else
						parent->Color = black;
				}
			}
		}
	}

	Person *successor(Person *person) 
	{
		Person *temp = person;

		while (temp->left != nullptr)
			temp = temp->left;

		return temp;
	}

	Person *BSTreplace(Person *person) 
	{
		if ((person->left != nullptr) && (person->right != nullptr)) // Two children
			return successor(person->right);

		if ((person->left == nullptr) && (person->right == nullptr))
			return nullptr;

		if (person->left != nullptr) // Single Child
			return person->left;
		else
			return person->right;
	}

	void SwapValues(Person *person1, Person *person2) {
		std::string temp;
		temp = person1->lastName;
		person1->lastName = person2->lastName;
		person2->lastName = temp;

		temp = person1->firstName;
		person1->firstName = person2->firstName;
		person2->firstName = temp;

		temp = person1->phoneNumber;
		person1->phoneNumber = person2->phoneNumber;
		person2->phoneNumber = temp;
	}

	void DeleteNode(Person *person) 
	{
		Person *replacePerson = BSTreplace(person);
		bool bothBlack = ((replacePerson == nullptr || replacePerson->Color == black) && (person->Color == black));
		Person *parent = person->parent;

		if (replacePerson == nullptr)
		{
			if (person == root)
				root = nullptr;
			else 
			{
				if (bothBlack) 
					FixDoubleBlack(person);
				else 
				{
					if (person->Sibling() != nullptr)
						person->Sibling()->Color = red;
				}

				if (person->IsOnLeft()) 
					parent->left = nullptr;
				else 
					parent->right = nullptr;
			}

			delete person;
			return;
		}

		if (person->left == nullptr || person->right == nullptr) 
		{
			if (person == root) // one child
			{
				person->lastName = replacePerson->lastName;
				person->firstName = replacePerson->firstName;
				person->phoneNumber = replacePerson->phoneNumber;
				person->left = person->right = nullptr;
				delete replacePerson;
			}
			else 
			{
				if (person->IsOnLeft())
				{
					parent->left = replacePerson;
				}
				else
				{
					parent->right = replacePerson;
				}

				delete person;
				replacePerson->parent = parent;

				if (bothBlack)
					FixDoubleBlack(replacePerson);
				else 
					replacePerson->Color = black;
			}

			return;
		}

		SwapValues(replacePerson, person);
		DeleteNode(replacePerson);
	}

	Person *Search(std::string first_name, std::string last_name) 
	{
		Person *temp = root;

		while (temp != nullptr)
		{
			if (last_name < temp->lastName)
			{
				if (temp->left == nullptr)
					break;
				else
					temp = temp->left;
			}
			else if (last_name > temp->lastName)
			{
				if (temp->right == nullptr)
					break;
				else
					temp = temp->right;
			}
			else
			{

				if (first_name < temp->firstName)
				{
					if (temp->left == nullptr)
						break;
					else
						temp = temp->left;
				}
				else if (first_name > temp->firstName)
				{
					if (temp->right == nullptr)
						break;
					else
						temp = temp->right;
				}
				else
				{
					return temp;
				}
			}
		}
		return temp;
	}

	bool Delete(std::string first_name, std::string last_name) //Remove a node from the tree
	{
		if (root == nullptr)
			return false;

		Person *v = Search(first_name, last_name);

		if (v->lastName != last_name && v->firstName != first_name)
			return false;

		DeleteNode(v);
		return true;
	}

	std::string Find(std::string first_name, std::string last_name) //Find a node and return the phone number
	{
		if (root == nullptr)
			return "No phone number found";

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
		std::ofstream file(FILENAME); // open file

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
		std::ifstream file(FILENAME); // open file
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