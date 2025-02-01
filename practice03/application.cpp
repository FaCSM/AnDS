#include "application.h"
#include "trees/bin-tree.h"
#include "trees/avl-tree.h"

#include <iostream>
#include <iomanip>
#include <fstream>


int TApplication::execute() {
    std::string path = std::getenv("INPUT_FILE_PATH");
    std::ifstream iFile(path);
    if (!iFile.is_open()) {
        std::cerr << "FileNotFoundError. No such file: `" << path << "`\n";
        return -1;
    }
    std::string input;
    std::getline(iFile, input);
    iFile.close();

    int width = int(input.length()) / 2;
    std::cout << "\033[30;47m" << std::setw(width + 9) << std::setfill('-')
              << "BINARY TREE" << std::setw(width + 2) << "\033[0m" << "\n";
    std::cout << "Input: " << input << std::endl;

    BinTree binTree;
    try {
        binTree = BinTree(input);
        std::cout << " Tree:\n";
        std::cout << binTree;
    }
    catch (std::invalid_argument& e) {
        std::cerr << "Invalid argument. " << e.what() << std::endl;
        system("pause");
        return -1;
    }
    catch (std::runtime_error& e) {
        std::cerr << "Runtime error. " << e.what() << std::endl;
        system("pause");
        return -2;
    }

    std::vector<int> values = binTree.depthFirstTraversal();
    std::cout << "  DFT: ";
    for (auto &el : values) std::cout << el << ' ';
    std::cout << "\n\n";

    std::cout << "\033[30;47m" << std::setw(width + 7) << std::setfill('-')
              << "AVL TREE" << std::setw(width + 4) << "\033[0m" << "\n";
    AVLTree avlTree(values);
    std::cout << "Tree:\n" << avlTree;

    std::cout << "  BFT: ";
    avlTree.breadthFirstTraversal();
    std::cout << "\n   In: ";
    avlTree.inOrderTraversal();
    std::cout << "\n  Pre: ";
    avlTree.preOrderTraversal();
    std::cout << "\n Post: ";
    avlTree.postOrderTraversal();
    std::cout << std::endl;

    system("pause");

    return 0;
}