#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "Binary_Tree.h"
#include "BTNode.h"

//void create_tree(Binary_Tree<std::pair<std::string, std::string>> bt, const std::string letters[28], const std::string symbols[28], int num);
//Binary_Tree<std::pair<std::string, std::string>> create_tree();
void decode(std::string message, Binary_Tree<std::string> morse_code_tree);
void encode(std::string message, std::map<std::string, std::string> morse_code_map);

int main() {

	std::ifstream in;
	in.open("symbol_list.txt");

	std::string line;
	std::map<std::string, std::string> morse_code_map;

	while (in >> line) {
		morse_code_map[std::string(1, line[0])] = line.substr(1);
	}

	Binary_Tree<std::string>* morse_tree = new Binary_Tree<std::string>("");
	

	for (std::map<std::string, std::string>::iterator map_iter = morse_code_map.begin(); map_iter != morse_code_map.end(); ++map_iter) {

		BTNode<std::string>* current_node = morse_tree->getRoot();
		std::string current_morse_code = map_iter->second;

		for (std::string::iterator string_iter = current_morse_code.begin(); string_iter != current_morse_code.end(); ++string_iter) {
			if (*string_iter == '.') {
				if (current_node->left == nullptr) {
					current_node->left = (new BTNode<std::string>("test"));
				}
				current_node = current_node->left;
			}
			else if (*string_iter == '_') {
				if (current_node->right == nullptr) {
					current_node->right = (new BTNode<std::string>("test"));
				}
				current_node = current_node->right;
			}
			else {
				// Return error
			}
		}
		current_node->data = map_iter->first;
	}

	std::string morse_code = ".... . ._.. ._.. ___";
	decode(morse_code, *morse_tree);

	std::string hello = "hello";
	encode(hello, morse_code_map);

	return 0;
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
			else {
				std::cout << "ERROR: Only '.' and '_' are acceptable for decoder.  Exiting decoder." << std::endl;
				return;
			}

			if (i == token.size() - 1) {

				if (temp_tree.getRoot() == NULL) {
					std::cout << "ERROR: Morse code message is invalid.  Please check and try again." << std::endl;
					return;
				}

				decoded += temp_tree.getRoot()->data;
			}
		}
	}

	std::cout << decoded << std::endl;
}

void encode(std::string message, std::map<std::string, std::string> morse_code_map)
{
	std::string encoded = "";

	for (int i = 0; i < message.length(); ++i) {
		if (isalpha(message[i])) {
			encoded += morse_code_map.at(std::string(1, message[i])) + " ";
		}
		else {
			std::cout << "ERROR: Encode message is invalid.  Please check and try again." << std::endl;
			return;
		}
	}

	std::cout << encoded << std::endl;
}