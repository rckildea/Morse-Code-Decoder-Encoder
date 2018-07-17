#pragma once
#include "Binary_Tree.h"
#include <map>
#include <string>

template<typename Item_Type>
class Morse_Code_Tree : public Binary_Tree<Item_Type> {

public:
	std::map<std::string, std::string> morse_code_map;

	static void get_morse_code_map();

};

template<typename Item_Type>
static void Morse_Code_Tree<Item_Type>::get_morse_code_map() {
	std::ifstream in;
	in.open("symbol_list.txt");

	std::string line;

	while (in >> line) {
		morse_code_map[std::string(1, line[0])] = line.substr(1);
	}
}