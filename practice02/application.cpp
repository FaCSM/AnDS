#include "application.h"
#include "quicksort.h"
#include "timsort.h"

#include <iostream>
#include <iomanip>
#include <chrono>


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


void printTimeDurationCast(auto start, bool isEndOfLine = true) {
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << std::scientific << std::setprecision(1);
    std::cout << elapsed.count() / 1e9 << " s";
    if (isEndOfLine) std::cout << std::endl;
    std::cout << std::defaultfloat;
}


bool isSorted(List &list) {
    for (struct Node *curr = list[0]; curr; curr = curr->next)
        if (curr->next && curr->value > curr->next->value) return false;
    return true;
}


/// Execute the main thread
int TApplication::execute() {
    char userChoice;

    // Get values
    int size;
    std::cout << "<< Enter the size of the list:\n>> ";
    if (!inputNumber(size, true, true)) return -1;
    int values[size];
    std::cout << "<< Enter 0 to fill with random numbers or";
    std::cout << " enter " << size << " elements separated by space:\n>> ";
    bool isRandFill = false;
    for (int i = 0; i < size; ++i) {
        if (!inputNumber(values[i])) break;
        if (i == 0 && values[i] == 0) {
            isRandFill = true;
            break;
        }
    }
    if (isRandFill) for (auto &el : values) el = 1 + std::rand() % 1000;

    // Create the list
    List unsortedList(size, values);
    List list(size, values);
    std::cout << "List created.\n";


    while (true) {
        // Get command from the keyboard
        if (!menu(userChoice)) continue; // Error occurred
        if (userChoice == '0') break;    // Exit command

        // Execute
        switch (userChoice) {
            // QuickSort
            case '1': {
                std::cout << "Sorting via quickSort..\n";
                auto start = std::chrono::steady_clock::now();
                quickSort(list);
                std::cout << "Sorted. Elapsed time: ";
                printTimeDurationCast(start, false);
                std::cout << "; isSorted - " << isSorted(list) << std::endl;
                break;
            }

            // TimSort
            case '2': {
                std::cout << "Sorting via timSort..\n";
                auto start = std::chrono::steady_clock::now();
                timSort(list);
                std::cout << "Sorted. Elapsed time: ";
                printTimeDurationCast(start, false);
                std::cout << "; isSorted - " << isSorted(list) << std::endl;
                break;
            }

            // Insert
            case 'i': {
                // Get user choice
                int choice;
                std::cout << "<< Choose the way of addition: '1' to push back and '2' to insert by index:\n>> ";
                if (!inputNumber(choice, true, true)) break;

                // InputError
                if (choice != 1 && choice != 2) {
                    std::cout << "InputError: Unknown command '" << choice << "'\n";
                    break;
                }

                // Get value
                int value;
                std::cout << "<< Enter the value:\n>> ";
                if (!inputNumber(value, true, false)) break;

                // Append or insert
                if (choice == 1) {
                    list.append(value);
                } else if (choice == 2) {
                    unsigned index;
                    std::cout << "<< Enter the index:\n>> ";
                    if (!inputNumber(index, true, true)) break;
                    list.insert(index, value);
                }

                std::cout << "Updated list: " << list << std::endl;

                break;
            }

            // Print list
            case 'p': {
                std::cout << list << "(size = " << list.getSize() << ")\n";
                break;
            }

            // Reset list to the unsorted state
            case 'r': {
                list = unsortedList;
                std::cout << "List updated.\n";
                break;
            }

            // Help menu
            case 'h': {
                help();
                break;
            }

            // Runtime error. Unknown command
            default: std::cout << "Runtime error. Unknown command\n";
        }
        system("pause");
    }

    return 0;
}


/// Print available Dynamic Array commands
void TApplication::help() {
    std::cout << "Available commands:\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "h: Help (this menu)\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "1: Sort list via QuickSort\n";
    std::cout << "2: Sort list via TimSort\n";
    std::cout << "i: Insert element\n";
    std::cout << "p: Print list\n";
    std::cout << "r: Reset to the unsorted\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "0: Exit\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << std::setfill(' ');
}


/**
 * Prints the menu of commands and reads the user action input via cin
 * @param[out] userChoice Reference to a declared user's choice variable
 * @return True if input was correct, else false (error)
 */
bool TApplication::menu(char &userChoice) {
    std::cout << "<< Action:\n>> ";
    std::cin >> userChoice;

    // Error handler (i.e. more than one symbol input)
    if (std::cin.fail() || std::cin.get() != '\n') {
        std::cout << "RuntimeError. Unknown command\n";
        std::cin.clear();
        std::cin.ignore(100000, '\n');
        return false;
    }
    return true;
}