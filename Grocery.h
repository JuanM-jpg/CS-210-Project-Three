#pragma once
#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H
#include <string>
#include <map>

class GroceryTracker { //Declaraction of the groceryTracker class
private:
	std::map<std::string, int> itemFrequencies; //Map to store item frequencies

public:
	GroceryTracker(); //Constructor declaration

	void readItemsFromFile(const std::string& filename); //Member function declaration
	void displaySpecificItemFrequency(const std::string& item) const;
	void displayAllFrequencies() const;
	void displayHistogram() const;
	void writeFrequenciesToFile(const std::string& filename) const;
};
#endif 