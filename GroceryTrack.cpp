#include "Grocery.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <Windows.h> //Include Window.h for accessing the Windows API for console commands
#include <iomanip> //Include iomanip for output formatting

GroceryTracker::GroceryTracker() { //Constructor of the GroceryTracker class
	readItemsFromFile("CS210_Project_Three_Input_File.txt"); //Read the items from the input file and populate the frequncy map
	writeFrequenciesToFile("frequency.dat"); //Write the initial frequencies to the backup file
}

void GroceryTracker::readItemsFromFile(const std::string& filename) { //Reads item frequncies from a file and stores them in a map
	std::ifstream file(filename);
	if (!file) { // Check to see if the file can be opened
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}
	std::string item; //Variable to store each item read from the file
	while (file >> item) { //Read items and update their frequncies
		itemFrequencies[item]++;
	}
	file.close(); //close the file stream
}

void GroceryTracker::displaySpecificItemFrequency(const std::string& item) const { //Display the frequency of a specific item
	std::cout << "\n" << std::endl; //Padding before frequency
	auto it = itemFrequencies.find(item); //Search for the item in the frequency map
	if (it != itemFrequencies.end()) { //If found, print the item and its frequency
		std::cout << item << ": " << it->second << std::endl;
	}
	else {
		std::cout << "Item not found." << std::endl; //if not found, it inform the user
	}
}

void GroceryTracker::displayAllFrequencies() const { //Display all item frequencies in a list
	std::cout << "\n" << std::endl; //Padding before frequencies
	for (const auto& pair : itemFrequencies) { //Iterate through the map and print each item's frequency
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
}

void GroceryTracker::displayHistogram() const { //Displays a Histogram of item frequency with a heat map color scheme
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //handle to the console
	size_t longestNameLength = 0; //Determine the longest item name for formatting
	for (const auto& pair : itemFrequencies) {
		if (pair.first.length() > longestNameLength) {
			longestNameLength = pair.first.length();
		}
	}

	int maxFrequency = 0; //Find the maximum frequency for scaling the heat map
	for (const auto& pair : itemFrequencies) {
		if (pair.second > maxFrequency) {
			maxFrequency = pair.second;
		}
	}

	std::cout << "\n" << std::endl; //padding before histrogram

	for (const auto& pair : itemFrequencies) { //Display each item frequency with color coding representing the heat map
		double ratio = pair.second / (double)maxFrequency;
		//Assign a color code based on the frecuency
		int colorCode;
		if (ratio < 0.2) {
			colorCode = 1; //Blue for the lowest frequencies
		}
		else if (ratio < 0.4) {
			colorCode = 3; //Cyan for the lower frequencies
		}
		else if (ratio < 0.6) {
			colorCode = 6; //Yellow for medium frecuencies
		}
		else if (ratio < 0.8) {
			colorCode = 12; //Orange for higher frequencies
		}
		else {
			colorCode = 4; // Dark red for the highest frequencies
		}

		SetConsoleTextAttribute(hConsole, colorCode); //Apply the color setting 
		std::cout << std::left << std::setw(longestNameLength) << pair.first << " : "; //Output the item name, padded for alignment, followed by its histogram
		for (int i = 0; i < pair.second; i++) {
			std::cout << "*";
		}
		std::cout << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 7); //Reset the console to defualt color
}

void GroceryTracker::writeFrequenciesToFile(const std::string& filename) const { //writes the item frequencies to a backup file
	std::ofstream file(filename); //output file stream
	if (!file) { //Check if the file can be opened
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}
	for (const auto& pair : itemFrequencies) { //Write each item and its frequency to the file
		file << pair.first << " " << pair.second << std::endl;
	}
	file.close(); //Close the file stream
}