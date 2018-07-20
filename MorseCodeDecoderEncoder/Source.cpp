#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include "Binary_Tree.h"
#include "BTNode.h"

// Ryan Kildea
// CS 303
// 07/22/18

// This program constructs a map and a binary tree from a morse code symbol list.
// It then uses the map to encode messages into morse code, and the tree to decode messages from morse code.

/** Constructs a map from a formatted input file
@return The morse code map
*/
std::map<std::string, std::string> get_map();

/** Constructs a tree using the morse code map
@param morse_code_map The symbol-to-letter morse code map
@return The decoding tree
*/
Binary_Tree<std::string>* construct_tree(std::map<std::string, std::string> morse_code_map);

/** Takes a user message written in morse code and outputs the decoded text
@param message The user-submitted message in morse code
@param morse_code_tree The morse code binary tree
*/
void decode(std::string message, Binary_Tree<std::string> morse_code_tree);

/** Takes a user message and converts it to morse code
@param message The user-submitted message
@param morse_code_map The symbol-to-letter morse code map
*/
void encode(std::string message, std::map<std::string, std::string> morse_code_map);

int main() {
	std::map<std::string, std::string> morse_code_map = get_map();
	std::string morse_code = ".... . ._.. ._.. ___";
	std::string hello = "helLO";

	
	try {
		Binary_Tree<std::string>* morse_tree = construct_tree(morse_code_map);
		decode(morse_code, *morse_tree);
		encode(hello, morse_code_map);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

std::map<std::string, std::string> get_map() {
	std::map<std::string, std::string> morse_code_map;
	std::ifstream in;

	try {
		in.open("symbol_list.txt");
	}
	catch (std::exception& e) {
		std::cout << "ERROR: 'symbol_list.txt' could not be found" << std::endl;
	}
	
	std::string line;

	while (in >> line) {
		morse_code_map[std::string(1, line[0])] = line.substr(1); // Morse code (everything after the first character), then alphabetical character
	}

	return morse_code_map;
}

Binary_Tree<std::string>* construct_tree(std::map<std::string, std::string> morse_code_map) {
	Binary_Tree<std::string>* morse_tree = new Binary_Tree<std::string>(""); // Start with a blank tree

	for (std::map<std::string, std::string>::iterator map_iter = morse_code_map.begin(); map_iter != morse_code_map.end(); ++map_iter) { // Get all items from the map

		BTNode<std::string>* current_node = morse_tree->getRoot(); // Every new morse code symbol starts at the root of the tree
		std::string current_morse_code = map_iter->second; // Value to be stored in the tree

		for (std::string::iterator string_iter = current_morse_code.begin(); string_iter != current_morse_code.end(); ++string_iter) {
			if (*string_iter == '.') { // '.' means go left
				if (current_node->left == nullptr) {
					current_node->left = (new BTNode<std::string>("")); // Create an empty placeholder node
				}
				current_node = current_node->left;
			}
			else if (*string_iter == '_') { // '_' means go right
				if (current_node->right == nullptr) {
					current_node->right = (new BTNode<std::string>("")); // Create an empty placeholder node
				}
				current_node = current_node->right;
			}
			else {
				throw std::runtime_error(std::string() + "ERROR: Invalid character " + std::to_string(*string_iter) + " located when constructing tree.  Check symbol_list.txt");
			}
		}
		current_node->data = map_iter->first;
	}
	
	return morse_tree;
}

void decode(std::string message, Binary_Tree<std::string> morse_code_tree)
{
	std::istringstream in(message);
	std::string token = "", decoded = "";

	while (in >> token) {

		Binary_Tree<std::string> temp_tree = morse_code_tree;

		for (int i = 0; i < token.size(); ++i) {

			if (token[i] == '.') {
				temp_tree = temp_tree.get_left_subtree();
			}
			else if (token[i] == '_') {
				temp_tree = temp_tree.get_right_subtree();
			}
			else { // Symbol was not a '.' or '_'
				throw std::runtime_error("ERROR: Only '.' and '_' are acceptable for decoder.  Exiting decoder.");
			}

			if (i == token.size() - 1) {
				if (temp_tree.getRoot() == NULL) { // Landed at an invalid node
					throw std::runtime_error("ERROR: Morse code message is invalid.  Please check and try again.");
				}

				decoded += temp_tree.getRoot()->data;
			}
		}
	}

	std::cout << decoded << std::endl;
}

void encode(std::string message, std::map<std::string, std::string> morse_code_map)
{
	std::transform(message.begin(), message.end(), message.begin(), ::tolower); // Make the user-submitted message lowercase
	std::string encoded = "";

	for (int i = 0; i < message.length(); ++i) {
		if (isalpha(message[i])) {
			encoded += morse_code_map.at(std::string(1, message[i])) + " ";
		}
		else { // Found a symbol/number
			throw std::runtime_error("ERROR: Encode message is invalid.  Please check and try again.");
		}
	}

	std::cout << encoded << std::endl;
}