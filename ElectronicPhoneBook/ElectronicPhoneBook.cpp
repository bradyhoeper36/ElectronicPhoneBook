#include "pch.h"
#include <iostream>
#include "BinarySearchTree.h"
#include <vector>
#include <string>


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
