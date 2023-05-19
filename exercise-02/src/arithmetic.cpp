#include <stdio.h>

#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "Queue.h"
#include "Stack.h"

using namespace std;

// returns the precedence of the operator
int get_precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}

// checks if the given character is an operator
int is_operator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/';
}

// check if the given expression is valid infix
string is_valid_expression(string inp) {
    // check if there are spaces between numbers
    bool prev_was_number = false;
    for (int i = 0; i < inp.length(); i++) {
        if (isdigit(inp[i])) {
            if (i != 0 && inp[i - 1] == ' ' && prev_was_number) {
                throw std::invalid_argument("Invalid expression");
            }
            prev_was_number = true;
        } else if (inp[i] != ' ') {
            prev_was_number = false;
        }
    }

    // replace all whitespaces
    regex r("\\s+");
    inp = regex_replace(inp, r, "");

    // check if all numbers are seperated by only one operator and if brackets are correct
    bool prev_was_operator = true;
    int bracketCounter = 0;
    for (int i = 0; i < inp.length(); i++) {
        char t = inp[i];

        if (is_operator(t)) {
            if (prev_was_operator) {
                throw std::invalid_argument("Invalid expression");
            }
            prev_was_operator = true;
        } else if (t == '(') {
            bracketCounter++;
        } else if (t == ')') {
            bracketCounter--;
        } else if (isdigit(t) || t == '.') {
            prev_was_operator = false;
        } else {
            throw std::invalid_argument("Invalid expression");
        }
        if (bracketCounter < 0) {
            throw std::invalid_argument("Invalid expression");
        }
    }
    if (bracketCounter != 0 || prev_was_operator) {
        throw std::invalid_argument("Invalid expression");
    }

    return inp;
}

// converts infix expression to postfix expression using the shunting yard algorithm
string infix_to_postfix(string inp) {
    string postfix = "";
    Stack<char> stack;
    Queue<char> queue;

    inp = is_valid_expression(inp);
    for (int i = 0; i < inp.length(); i++) {
        char t = inp[i];

        if (t == '(') {
            stack.push(t);

        } else if (t == ')') {
            // put operators into queue until we find the matching opening bracket
            while (!stack.is_empty() && stack.top() != '(') {
                queue.enqueue(' ');
                queue.enqueue(stack.pop());
                if (i != inp.length() - 1) {
                    queue.enqueue(' ');
                }
            }

            // remove opening bracket
            stack.pop();

        } else if (is_operator(t)) {
            // put operators with higher precedence into queue
            while (!stack.is_empty() && is_operator(t) && get_precedence(stack.top()) >= get_precedence(t)) {
                queue.enqueue(stack.pop());
                queue.enqueue(' ');
            }
            stack.push(t);

        } else {
            queue.enqueue(t);
            if (is_operator(inp[i + 1])) {
                queue.enqueue(' ');
            }
        }
    }

    // put remaining operators into queue
    while (!stack.is_empty()) {
        queue.enqueue(' ');
        queue.enqueue(stack.pop());
    }

    // convert queue to string
    while (!queue.is_empty()) {
        postfix += queue.dequeue();
    }

    return postfix;
}

// take care of the calculation part
void calculate(Stack<float> &vals, Stack<string> &ops) {
    string op = ops.pop();
    double v = vals.pop();

    if (op == "+")
        v = vals.pop() + v;
    else if (op == "-")
        v = vals.pop() - v;
    else if (op == "*")
        v = vals.pop() * v;
    else if (op == "/")
        v = vals.pop() / v;

    vals.push(v);
}

// evaluate the given infix expression
float evaluate_infix(string inp) {
    Stack<float> vals;
    Stack<string> ops;

    string postfix = infix_to_postfix(inp);

    for (int i = 0; i < postfix.length(); i++) {
        // whitespace or bracket
        if (postfix[i] == '(' || postfix[i] == ' ' || postfix[i] == ')') {
            continue;

        // operator
        } else if (is_operator(postfix[i])) {
            ops.push(string(1, postfix[i]));
            calculate(vals, ops);

        // number
        } else {
            string token = "";
            while ((isdigit(postfix[i]) || postfix[i] == '.') && i < postfix.length()) {
                token += postfix[i];
                i++;
            }
            vals.push(stof(token));
        }
    }

    return vals.pop();
}
