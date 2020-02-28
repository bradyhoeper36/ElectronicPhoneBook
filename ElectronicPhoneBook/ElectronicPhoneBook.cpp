
#include "pch.h"
#include <iostream>
#include "BinarySearchTree.h"
#include <vector>
#include <string>

int main()
{
	Person *person1 = new Person("Brady", "Hoeper", "5135181417");
	Person *person2 = new Person("Sam", "Brown", "5135153603");
	Person *person3 = new Person("Asher", "Straubing", "5132133680");
	Person *person4 = new Person("Bri", "Mariles", "5137466646");
	Person *person5 = new Person("Jacqueline", "Lazar", "5131234567");
	Person *person6 = new Person("Cam", "Newton", "5135131416");

	Book *phonebook = new Book();
	phonebook->Add(person1);
	phonebook->Add(person2);
	phonebook->Add(person3);
	phonebook->Add(person4);
	phonebook->Add(person5);
	phonebook->Add(person6);
	phonebook->Display();
	//phonebook->Delete("Asher", "Straubing");
	phonebook->Delete("Bri", "Mariles");
	//phonebook->Add(person1);
	phonebook->Display();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
