#include "pch.h"
#include <iostream>
#include "BinarySearchTree.h"
#include <vector>
#include <string>


class UserInterface {
	public:
		void initialize() {
			std::cout << "Welcome to the Binary Search Tree implementation of an Electronic Phonebook\n\n";
			runInputLoop();
		};

	private:
		void runInputLoop() {
			std::cout << "Options:(1) Add Person\n\t(2) Get Phone Number\n\t(3) Delete Person\n\t(4) Display Phonebook\n\t(5) Quit (write phonebook to file)" << std::endl;
			int userChoice;
			std::cin >> userChoice;
		}
};

int main()
{
	UserInterface *phonebookInterface = new UserInterface();
	phonebookInterface->initialize();
}