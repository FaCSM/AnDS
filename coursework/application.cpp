#include "application.h"
#include "structures/graph.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>


template <typename NumType>
bool inputNumber(NumType &variable, bool isSpaceSep = false, bool isUnsigned = false) {
    std::cin >> variable;
    if (std::cin.fail() || (isUnsigned && variable < 0) || (isSpaceSep && std::cin.peek() != '\n')) {
        std::cout << "Invalid input\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}





void parseFile(std::vector<char> &names, std::vector<std::vector<int>> &values) {
    std::string path = "../input.txt";
    std::ifstream iFile(path);
    if (!iFile.is_open()) throw std::runtime_error("FileNotFound: Couldn't open '" + path + "' file");
    std::string line;

    std::getline(iFile, line);
    std::string name;
    for (auto &c : line) {
        if (c == ' ') {
            if (!name.empty()) names.push_back(name[0]);
            name.clear();
        } else {
            name += c;
            if (name.length() > 1) throw std::runtime_error("InvalidName: Invalid vertex name");
        }
    }
    names.push_back(name[0]);

    while (std::getline(iFile, line)) {
        std::vector<int> row;
        std::string number;
        for (auto &c : line) {
            if (c == ' ') {
                if (!number.empty()) row.push_back(std::stoi(number));
                number.clear();
            } else if (isdigit(c)) {
                number += c;
            } else {
                throw std::runtime_error("InvalidValue: Invalid character '" + std::string(1, c) + "' in file");
            }
        }
        row.push_back(std::stoi(number)); // Last row element
        if (!values.empty() && row.size() != values[0].size())
            throw std::runtime_error("InvalidSize: Invalid row size");
        values.push_back(row);
    }
    if (values.size() != values[0].size()) throw std::runtime_error("InvalidSize: Invalid matrix size");
    for (int i = 0; i < values.size(); ++i)
        if (values[i][i] != 0) throw std::runtime_error("LoopError: Non-zero diagonals");

    iFile.close();
}


int TApplication::execute() {
    std::vector<char> names;
    std::vector<std::vector<int>> values;
    parseFile( names, values);
    Graph graph(names, values);

    std::vector<Vertex*> dfs = graph.depthFirstSearch();
    std::vector<Vertex*> bfs = graph.breadthFirstSearch();
    std::cout << "DFS: ";
    for (auto *el : dfs) std::cout << *el << ' ';
    std::cout << "\nBFS: ";
    for (auto *el : bfs) std::cout << *el << ' ';
    std::cout << '\n';

    std::vector<Edge> sorted = graph.getSortedByWeight();
    std::cout << "Edges sorted by weight:\n";
    for (auto &edge : sorted)
        std::cout << "     " << edge << '\n';

    std::vector<Edge> mst = graph.getMST();

    std::sort(
        mst.begin(), mst.end(),
        [](Edge& a, Edge& b) {
            std::string aNames = std::string(1, a.getU()->getName()) + std::string(1, a.getV()->getName());
            std::string bNames = std::string(1, b.getU()->getName()) + std::string(1, b.getV()->getName());
            return aNames < bNames;
        }
    );

    std::cout << "Minimum Spanning Tree:\n";
    int weight = 0;
    for (auto &edge : mst) {
        std::cout << "     " << edge << '\n';
        weight += edge.getWeight();
    }
    std::cout << "     Full weight = " << weight << '\n';

    // Write answer to the output file
    std::ofstream oFile(std::getenv("../output.txt"));
    if (!oFile.is_open()) throw std::runtime_error("FileNotFound: Couldn't open 'output.txt' file");
    for (auto &edge: mst) oFile << *(edge.getU()) << ' ' << *(edge.getV()) << '\n';
    oFile << weight;
    oFile.close();
    std::cout << "Answer has been written to the `output.txt` file\n";

    return 0;
}
