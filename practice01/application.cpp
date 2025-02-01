#include "application.h"

#include "structures/dl_list.h"
#include "structures/dynamic_array.h"
#include "structures/stack.h"
#include "rpn.h"
#include <vector>

#include <iostream>
#include <iomanip>

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


int TApplication::execute() {

    std::cout.setf(std::ios::boolalpha);

    char userChoice;
    while (true) {
        std::cout << "Выберите поток:\n";
        std::cout << "1. Двусвязный список\n";
        std::cout << "2. Динамический массив\n";
        std::cout << "3. Стек\n";
        std::cout << "4. Обратная польская нотация\n";

        if (!menu(userChoice)) continue;
        if (userChoice == '0') break;
        system("cls");

        if (userChoice == '1') {
            std::cout << "Список выполненных потоков. Введите 'h', чтобы получить список команд\n";
            executeList();
        } else if (userChoice == '2') {
            std::cout << "Выполнен поток динамического массива. Введите 'h', чтобы получить список команд\n";
            executeDArr();
        }
        else if (userChoice == '3') {
            std::cout << "Выполнен поток стека. Введите 'h', чтобы получить список команд\n";
            executeStack();
        } else if (userChoice == '4') {
            std::cout << "Выполнен поток польской нотации.\n";
            executeRPN();
        } else {
            std::cout << "RuntimeError. Неизвестная команда\n";
        }

        system("cls");
    }

    return 0;
}


int TApplication::executeList() {
    char userChoice;
    List list;

    while (true) {
        if (!menu(userChoice)) continue;
        if (userChoice == '0') break;


        switch (userChoice) {

            case '1': {

                int size;
                std::cout << "<< Введите размер списка:\n>> ";
                if (!inputNumber<int>(size, true, true)) break;
                int values[size];
                std::cout << "<< Введите " << size << " элементы, разделенные пробелом:\n>> ";
                for (auto &el: values)
                    if (!inputNumber<int>(el)) break;

                list = List(size, values);
                std::cout << "Создан список: " << list << std::endl;

                break;
            }

            case '2': {
                std::cout << list << "(размер = " << list.getSize() << ")\n";
                break;
            }

            case '3': {
                int choice;
                std::cout << "<< Выберите способ поиска: '1' для поиска по индексу и '2' для поиска по значению:\n>> ";
                if (!inputNumber(choice, true, true)) break;

                if (choice == 1) {
                    int index;
                    std::cout << "<< Введите индекс:\n>> ";
                    if (!inputNumber(index, true, false)) break;

                    struct Node *element = list[index];
                    if (element) std::cout << "Element " << element->value << " found\n";
                    else std::cout << "Элемент не найден\n";
                } else if (choice == 2) {
                    int value;
                    std::cout << "Введите значение:\n>> ";
                    if (!inputNumber(value, true, false)) break;

                    int index = list.find(value);
                    if (index != -1) std::cout << "Элемент найден. Индекс: " << index << std::endl;
                    else std::cout << "Элемент не найден\n";
                } else {
                    std::cout << "InputError: Неизвестная команда '" << choice << "'\n";
                }

                break;
            }

            case '4': {
                int choice;
                std::cout << "<< Выберите способ сложения: '1' для отталкивания и '2' для вставки по индексу:\n>> ";
                if (!inputNumber(choice, true, true)) break;

                if (choice != 1 && choice != 2) {
                    std::cout << "InputError: Неизвестная команда '" << choice << "'\n";
                    break;
                }

                int value;
                std::cout << "<< Введите значение:\n>> ";
                if (!inputNumber(value, true, false)) break;

                if (choice == 1) {
                    list.append(value);
                } else if (choice == 2) {
                    unsigned index;
                    std::cout << "<< Введите индекс:\n>> ";
                    if (!inputNumber(index, true, true)) break;
                    list.insert(index, value);
                }

                std::cout << "Обновленный список: " << list << std::endl;

                break;
            }

            case '5': {
                unsigned index;
                std::cout << "<< Введите индекс существующего узла:\n>> ";
                if (!inputNumber(index, true, true)) break;

                list.remove(index);

                std::cout << "Обновленный список: " << list << std::endl;

                break;
            }

            case '6': {
                unsigned index1, index2;
                std::cout << "<< Введите первый индекс:\n>> ";
                if (!inputNumber(index1, true, true)) break;
                std::cout << "<< Введите 2-й индекс:\n>> ";
                if (!inputNumber(index2, true, true)) break;

                list.swap(index1, index2);

                std::cout << "Обновленный список: " << list << std::endl;

                break;
            }

            case 'h': {
                helpList();
                break;
            }

            default: std::cout << "RuntimeError. Неизвестная команда\n";
        }
        system("pause");
    }

    return 0;
}


int TApplication::executeDArr() {
    char userChoice;
    DArray arr;

    while (true) {
        if (!menu(userChoice)) continue;
        if (userChoice == '0') break;

        switch (userChoice) {
            case '1': {
                int size;
                std::cout << "<< Введите размер массива:\n>> ";
                if (!inputNumber(size, true, true)) break;
                int values[size];
                std::cout << "<< Введите " << size << " элементы, разделенные пробелом:\n>> ";
                for (auto &el : values)
                    if (!inputNumber(el)) break;

                arr = DArray(size, values);
                std::cout << "Создан массив: " << arr << std::endl;

                break;
            }

            case '2': {
                std::cout << arr << "(size = " << arr.getSize() << ", capacity = " << arr.getCapacity() << ")\n";
                break;
            }

            case '3': {
                int choice;
                std::cout << "<< Выберите способ поиска: '1' для поиска по индексу и '2' для поиска по значению:\n>> ";
                if (!inputNumber(choice, true, true)) break;

                if (choice == 1) {
                    int index;
                    std::cout << "<< Введите индекс:\n>> ";
                    if (!inputNumber(index, true, true)) break;

                    int *value = arr[index];
                    if (value) std::cout << "Элемент " << *value << " найден\n";
                    else std::cout << "Элемент не найден\n";
                } else if (choice == 2) {
                    int value;
                    std::cout << "Введите значение:\n>> ";
                    if (!inputNumber(value, true, true)) break;

                    int index = arr.find(value);
                    if (index != -1) std::cout << "Элемент найден. Индекс: " << index << std::endl;
                    else std::cout << "Элемент не найден\n";
                } else {
                    std::cout << "InputError: Неизвестная команда '" << choice << "'\n";
                }

                break;
            }

            case '4': {
                int choice;
                std::cout << "<< Выберите способ сложения: '1' для отталкивания и '2' для вставки по индексу:\n>> ";
                if (!inputNumber(choice, true, true)) break;

                if (choice != 1 && choice != 2) {
                    std::cout << "InputError: Неизвестная команда '" << choice << "'\n";
                    break;
                }

                int value;
                std::cout << "<< Введите значение:\n>> ";
                if (!inputNumber(value, true, false)) break;

                if (choice == 1) {
                    arr.append(value);
                } else {
                    unsigned index;
                    std::cout << "<< Введите индекс:\n>> ";
                    if (!inputNumber(index, true, true)) break;
                    arr.insert(index, value);
                }

                std::cout << "Обновленный массив: " << arr << std::endl;

                break;
            }


            case '5': {
                unsigned index;
                std::cout << "<< Введите индекс существующего элемента:\n>> ";
                if (!inputNumber(index, true, true)) break;

                arr.remove(index);

                std::cout << "Обновленный массив: " << arr << std::endl;

                break;
            }

            case 'h': {
                helpDArr();
                break;
            }

            default: std::cout << "Runtime error. Неизвестная команда\\n";
        }
        system("pause");
    }

    return 0;
}



int TApplication::executeStack() {
    char userChoice;
    Stack stack;

    while (true) {
        if (!menu(userChoice)) continue;
        if (userChoice == '0') break;

        switch (userChoice) {
            case '1': {
                std::string input;
                std::cout << "<< Введите строку для отталкивания:\n>> ";
                getline (std::cin, input);
                stack.push(input);
                std::cout << "Обновленный стек: " << stack << std::endl;
                break;
            }

            case '2': {
                std::cout << stack.pop() << std::endl;
                std::cout << "Обновленный стек: " << stack << std::endl;
                break;
            }

            case '3': {
                std::cout << stack << " (размер = " << stack.getSize() << ")\n";
                break;
            }

            case 'h': {
                helpStack();
                break;
            }

            default: std::cout << "Runtime error. Unknown command\n";
        }
        system("pause");
    }

    return 0;
}


int TApplication::executeRPN() {
    bool isDebugMode = true;
    while (true) {
        try {
            std::cout << "<< Введите выражение ['0' - выход, 'd' - переход в режим отладки]\n>> ";
            std::string expr;
            std::getline(std::cin, expr);

            if (expr == "0")
                break;
            if (expr == "d") {
                isDebugMode = !isDebugMode;
                std::cout << "Режим отладки переключен на " << isDebugMode << '\n';
                continue;
            }

            std::vector<std::string> rpn = toRPN(expr, isDebugMode);
            double rpnAnswer = evaluate(rpn, isDebugMode);

            std::cout << std::setw(64) << std::setfill('-') << ' ' << std::setfill(' ');
            std::cout << "\n Ввод: " << expr << "\n RPN: ";
            for (auto &token : rpn) std::cout << token << ' ';
            std::cout << "\nОтвет: " << rpnAnswer << std::endl;
        }
        catch (std::invalid_argument& e) { std::cerr << "Недопустимый аргумент. " << e.what() << std::endl; }
        catch (std::runtime_error& e) { std::cerr << "Runtime error. " << e.what() << std::endl; }
    }

    return 0;
}


void TApplication::helpList() {
    std::cout << "Доступные команды:\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "h: Справка (это меню)\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "1: Создать список\n";
    std::cout << "2: Печать списка\n";
    std::cout << "3: Найти элемент\n";
    std::cout << "4: Добавить новый узел\n";
    std::cout << "5: Удалить существующий узел\n";
    std::cout << "6: Поменять местами два элемента\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "0: Выход\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << std::setfill(' ');
}


void TApplication::helpDArr() {
    std::cout << "Доступные команды:\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "h: Справка (это меню)\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "1: Создаем динамический массив\n";
    std::cout << "2: Печать динамического массива\n";
    std::cout << "3: Найти элемент\n";
    std::cout << "4: Добавить новый элемент\n";
    std::cout << "5: Удалить существующий элемент\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "0: Выход\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << std::setfill(' ');
}


void TApplication::helpStack() {
    std::cout << "Доступные команды:\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "h: Справка (это меню)\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "1: Вернуть\n";
    std::cout << "2: Вытащить элемент\n";
    std::cout << "3: Вывести стэк\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "0: Выход\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << std::setfill(' ');
}



bool TApplication::menu(char &userChoice) {
    std::cout << "<< Действие:\n>> ";
    std::cin >> userChoice;

    if (std::cin.fail() || std::cin.get() != '\n') {
        std::cout << "RuntimeError. Неизвестная команда\n";
        std::cin.clear();
        std::cin.ignore(100000, '\n');
        return false;
    }
    return true;
}