#include <iostream>
#include "Grocery.h" // Include the Header file for the GroceryTracker class

int main() {
	GroceryTracker tracker; // Create an instance of the GroceryTracker
	bool running = true; // Control variable for the main loop

	while (running) { //Main loop for the menu program by displaing the menu option to the user
		std::cout << "\nChada Corner Grocery Item Tracking System\n";
		std::cout << "--------------------------------------------------\n";
		std::cout << "1. Search for an item's frequency                -\n";
		std::cout << "2. Display all item frequencies                  -\n";
		std::cout << "3. Display histogram of item frequencies         -\n";
		std::cout << "4. Exit                                          -\n";
		std::cout << "--------------------------------------------------\n\n";
		std::cout << "Enter your choice: ";

		int choice;
		std::cin >> choice; //Read the user choice

		std::cin.clear(); // Clear the input buffer to handle any input errors
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice) {
		case 1: {
			std::string item;
			std::cout << "Enter the item name: ";
			getline(std::cin, item); //Read the item name from the user
			tracker.displaySpecificItemFrequency(item); //Display the frequency of the specified item
			break;
		}
		case 2:
			tracker.displayAllFrequencies(); //Display the frequency of all items
			break;
		case 3:
			tracker.displayHistogram(); //Display the histogram of item frequencies
			break;
		case 4:
			std::cout << "Exiting program." << std::endl;
			running = false; //Set running to false to exit the lopp and end the program
			break;
		default:
			std::cout << "Invalid choice. Please input an valid input." << std::endl;
			break;
		}
	}
	return 0; //Return 0 to indicate successful completion
}