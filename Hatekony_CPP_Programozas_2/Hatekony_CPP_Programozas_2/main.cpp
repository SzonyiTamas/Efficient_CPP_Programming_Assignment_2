#include "binarySearchTree.h"

#include <iostream>

int main()
{
	/*std::cout << std::boolalpha;

	BinarySearchTree<int, std::string> tree;*/

	/*std::cout << "tree.empty(): " << tree.empty() << "\n\n";*/

	/*std::cout << "insert(10, \"tiz\"): " << tree.insert(10, "tiz") << "\n";
	std::cout << "insert(5, \"ot\"): " << tree.insert(5, "ot") << "\n";
	std::cout << "insert(15, \"tizenot\"): " << tree.insert(15, "tizenot") << "\n";
	std::cout << "insert(3, \"harom\"): " << tree.insert(3, "harom") << "\n";
	std::cout << "insert(7, \"het\"): " << tree.insert(7, "het") << "\n";
	std::cout << "insert(12, \"tizenketto\"): " << tree.insert(12, "tizenketto") << "\n";
	std::cout << "insert(18, \"tizennyolc\"): " << tree.insert(18, "tizennyolc") << "\n";
	std::cout << "insert(10, \"masik tiz\"): " << tree.insert(10, "masik tiz") << "  // duplikalt kulcs\n\n";*/

	/*std::cout << tree << "\n\n";*/

	/*std::cout << "contains(7): " << tree.contains(7) << "\n";
	std::cout << "contains(99): " << tree.contains(99) << "\n\n";*/

	/*tree[7] = "modositott het";
	tree[20] = "husz";
	std::cout << "tree[7]: " << tree[7] << "\n";
	std::cout << "tree[20]: " << tree[20] << "\n";
	std::cout << tree << "\n\n";*/

	/*const BinarySearchTree<int, std::string>& constTree = tree;

	try
	{
		std::cout << "constTree[10]: " << constTree[10] << "\n";
		std::cout << "constTree[100]: " << constTree[100] << "\n";
	}
	catch (const std::out_of_range& ex)
	{
		std::cout << "Kivetel elkapva: " << ex.what() << "\n";
	}
	std::cout << "\n";*/

	/*for (BinarySearchTree<int, std::string>::Iterator it = tree.begin(); it != tree.end(); ++it)
	{
		auto [key, value] = *it;
		std::cout << "(" << key << ": " << value << ") ";
	}
	std::cout << "\n\n";

	for (auto entry : tree)
	{
		std::cout << "[" << entry.first << " => " << entry.second << "] ";
	}
	std::cout << "\n\n";*/

	/*std::cout << "remove(3): " << tree.remove(3) << "\n";
	std::cout << tree << "\n\n";

	std::cout << "remove(18): " << tree.remove(18) << "\n";
	std::cout << tree << "\n\n";

	std::cout << "remove(10): " << tree.remove(10) << "\n";
	std::cout << tree << "\n\n";

	std::cout << "remove(999): " << tree.remove(999) << "\n\n";*/

	/*BinarySearchTree<int, std::string> copyTree(tree);
	std::cout << "copyTree: " << copyTree << "\n\n";

	BinarySearchTree<int, std::string> assignedTree;
	assignedTree = tree;
	std::cout << "assignedTree: " << assignedTree << "\n\n";

	BinarySearchTree<int, std::string> movedTree(std::move(copyTree));
	std::cout << "movedTree: " << movedTree << "\n";
	std::cout << "copyTree (move utan): " << copyTree << "\n\n";

	BinarySearchTree<int, std::string> moveAssignedTree;
	moveAssignedTree = std::move(assignedTree);
	std::cout << "moveAssignedTree: " << moveAssignedTree << "\n";
	std::cout << "assignedTree (move utan): " << assignedTree << "\n\n";*/

	/*tree.clear();
	std::cout << "tree.clear() utan: " << tree << "\n";
	std::cout << "tree.empty(): " << tree.empty() << "\n";*/
}
