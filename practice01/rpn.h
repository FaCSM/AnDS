#ifndef
#define


#include "structures/stack.h"
#include <vector>
#include <string>
#include <unordered_map>

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <cmath>



std::vector<std::string> splitString(std::string str) {
    if (str.empty()) throw std::invalid_argument("Empty string");

    std::vector<std::string> tokens;
    char operators[7] = {'(', ')', '+', '-', '*', '/', '^'};

    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    std::string number;
    for (size_t i = 0; i < str.size(); ++i) {
        char c = str[i];
        std::string s(1, c);

        if (isdigit(c)) {
            number += c;
            continue;
        }

        if ((c == 's' || c == 'c') && i+2 < str.size()) {
            std::string substr = str.substr(i, 3);
            if (substr == "sin" || substr == "cos") tokens.push_back(substr);
            else throw std::runtime_error("Неизвестный оператор: " + substr);
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
            i += 2;
            continue;
        }

        if (std::find(std::begin(operators), std::end(operators), c) != std::end(operators)) {
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
            tokens.push_back(s);
            continue;
        }

        throw std::runtime_error("Неизвестный символ: " + s);
    }
    if (!number.empty()) tokens.push_back(number);
    return tokens;
}


void printDebug(const std::vector<std::string> &result, const Stack &opStack, const std::vector<std::string> &tokens) {
    int size = 7;
    for (auto &op : tokens) if (op != "(" && op != ")") size += int(op.length()) + 1;
    std::cout << "Result: ";
    for (const std::string &token : result) {
        std::cout << token << ' ';
        size -= int(token.length()) + 1;
    }
    std::cout << std::setw(size) << "Стэк: " << opStack << std::endl;
}


std::vector<std::string> toRPN(const std::string& expr, bool isDebugMode = false) {
    std::vector<std::string> result;

    Stack opStack;
    std::vector<std::string> tokens = splitString(expr);
    std::unordered_map<std::string, int> precedences {
            {"+", 1}, {"-", 1},
            {"*", 2}, {"/", 2},
            {"^", 3},
            {"sin", 4}, {"cos", 4}
    };

    if (isDebugMode) std::cout << "Перевод в RPN...\n";

    for (std::string token : tokens) {

        if (isdigit(token[0])) {
            result.push_back(token);
        }
        else if (token == "(") {
            opStack.push(token);
        }
        else if (token == ")") {
            while (*opStack.top() != "(") result.push_back(opStack.pop());
            if (opStack.isEmpty()) throw std::runtime_error("Незакрытая скоба");
            opStack.pop();
        }
        else if (precedences.count(token) > 0) {
            while (!opStack.isEmpty() && *opStack.top() != "(" && precedences[token] <= precedences[*opStack.top()])
                result.push_back(opStack.pop());
            opStack.push(token);
        }
        else {
            throw std::runtime_error("Недопустимый синтаксис: " + token);
        }

        if (isDebugMode) printDebug(result, opStack, tokens);
    }

    while (!opStack.isEmpty()) {
        if (*opStack.top() == "(") throw std::runtime_error("Незакрытая скоба");
        result.push_back(opStack.pop());
        if (isDebugMode) printDebug(result, opStack, tokens);
    }

    return result;
}


double calculate(std::string op, double a, double b) {
    switch (op[0]) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': {
            if (b == 0)
                throw std::runtime_error("Деление на ноль: " + std::to_string(a) + " / " + std::to_string(b));
            return a / b;
        }
        case '^': return pow(a, b);
        case 's': return sin(a);
        case 'c': return cos(a);
        default: throw std::invalid_argument("Неправильный оператор: " + op);
    }
}


double evaluate(const std::vector<std::string>& expr, bool isDebugMode = false) {
    Stack opStack;
    for (std::string token : expr) {
        if (isdigit(token[0])) {
            opStack.push(token);
            if (isDebugMode)
                std::cout << "Число найдено. \tСтек: " << opStack << std::endl;
        } else {
            if (token != "sin" && token != "cos" && opStack.getSize() < 2)
                throw std::runtime_error("Нечего рассчитывать");

            std::string calc;
            double op2 = std::stod(opStack.pop());
            double op1;
            if (token == "sin" || token == "cos") {
                calc = std::to_string(calculate(token, op2, 0));
            } else {
                op1 = std::stod(opStack.pop());
                calc = std::to_string(calculate(token, op1, op2));
            }

            opStack.push(calc);
            if (isDebugMode)
                std::cout << "Оценивать " << op1 << token << op2 << ". \tСтэк: " << opStack << std::endl;
        }
    }
    return std::stod(opStack.pop());
}

#endif