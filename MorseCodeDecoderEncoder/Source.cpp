#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include "Binary_Tree.h"
#include "BTNode.h"

void create_tree(Binary_Tree<std::pair<std::string, std::string>> bt, const std::string letters[28], const std::string symbols[28], int num);
Binary_Tree<std::pair<std::string, std::string>> create_tree();
void decode(std::string message, Binary_Tree<std::pair<std::string, std::string>> bt);
void encode(std::string message, Binary_Tree<std::pair<std::string, std::string>> bt);

int main() {

	Binary_Tree<std::pair<std::string, std::string>> tree = create_tree();

	std::string morse_code = ".... . ._.. ._.. ___";
	decode(morse_code, tree);


	return 0;
}

void create_tree(Binary_Tree<std::pair<std::string, std::string>> bt, const std::string letters[28], const std::string symbols[28], int num) {
	if (num >= 14) {
		return;
	}
	else {
		std::pair <std::string, std::string> temp_left(letters[num * 2 + 1], symbols[num * 2 + 1]);
		std::pair <std::string, std::string> temp_right(letters[num * 2 + 2], symbols[num * 2 + 2]);

		BTNode<std::pair <std::string, std::string>>* left_node = new BTNode<std::pair <std::string, std::string>>(temp_left);
		BTNode<std::pair <std::string, std::string>>* right_node = new BTNode<std::pair <std::string, std::string>>(temp_right);

		BTNode<std::pair <std::string, std::string>>* current_node = bt.getRoot();

		current_node->left = left_node;
		current_node->right = right_node;

		create_tree(bt.get_left_subtree(), letters, symbols, num * 2 + 1);
		create_tree(bt.get_right_subtree(), letters, symbols, num * 2 + 2);
	}

}

Binary_Tree<std::pair<std::string, std::string>> create_tree()
{
	const std::string LETTERS[] = { "NULL", "e", "t", "i", "a", "n", "m", "s", "u", "r", "w", "d", "k", "g", "o", "h", "v", "f", "NULL", "l", "NULL", "p", "j", "b", "x", "c", "y", "z", "q" };
	const std::string SYMBOLS[] = { "NULL", ".", "_", "..", "._", "_.", "__", "...", ".._", "._.", ".__", "_..", "_._", "__.", "___", "....", "..._", ".._.", "NULL", "._..", "NULL", ".__.", ".___", "_...", "_.._", "_._.", "_.__", "__..", "__._" };

	std::pair <std::string, std::string> temp(LETTERS[0], SYMBOLS[0]);

	Binary_Tree<std::pair<std::string, std::string>> bt(temp);
	int starting_node = 0;

	create_tree(bt, LETTERS, SYMBOLS, starting_node);

	return bt;
}

void decode(std::string message, Binary_Tree<std::pair<std::string, std::string>> bt)
{
	std::istringstream in(message);
	std::string token = "", decoded = "";

	while (in >> token) {
		Binary_Tree<std::pair<std::string, std::string>> temp_tree = bt;
		for (int i = 0; i < token.size(); ++i) {
			if (token[i] == '.') {
				temp_tree = temp_tree.get_left_subtree();
			}
			else if (token[i] == '_' && temp_tree.getRoot() != NULL) {
				temp_tree = temp_tree.get_right_subtree();
			}
			else {
				std::cout << "ERROR: Only '.' and '_' are acceptable for decoder.  Exiting decoder." << std::endl;
				return;
			}
			if (temp_tree.getRoot() == NULL) {
				std::cout << "ERROR: Morse code message is invalid.  Please check and try again." << std::endl;
				return;
			}
			if (i == token.size() - 1) {
				std::pair <std::string, std::string> temp_pair = temp_tree.getRoot()->data;
				decoded += temp_pair.first;
			}
		}
	}

	std::cout << decoded << std::endl;
}

void encode(std::string message, Binary_Tree<std::pair<std::string, std::string>> bt)
{
}
