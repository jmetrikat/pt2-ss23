#include <stdio.h>

#include <iostream>
#include <map>

#include "arithmetic.cpp"

using namespace std;

typedef struct var {
    string name;
    float value;
    struct var *next;
} Variable;

// returns true if the variable was added successfully, false otherwise
bool add_new_variable(string new_var_name, float new_var_value, Variable *&head) {
    Variable *new_var = new Variable();
    new_var->name = new_var_name;
    new_var->value = new_var_value;
    new_var->next = nullptr;

    // list is empty, create new head
    if (head == nullptr) {
        head = new_var;
        cout << "Created: " << new_var_name << " = " << new_var_value << endl;
        return true;
    }

    // list is not empty, check if variable already exists
    for (Variable *tmp = head; tmp != nullptr; tmp = tmp->next) {
        if (tmp->name == new_var_name) {
            tmp->value = new_var_value;
            cout << "Updated: " << new_var_name << " = " << new_var_value << endl;
            return true;
        }
    }

    // variable does not exist, add it to the list
    new_var->next = head;
    head = new_var;
    cout << "Created: " << new_var_name << " = " << new_var_value << endl;
    return true;
}

// repl loop for evaluating infix expressions
int main() {
    Variable *head = nullptr;
    string new_var_name;
    bool var_exists = false;
    bool var_is_writeable = false;

    while (true) {
        string inp;

        cout << ">>> ";
        getline(cin, inp);

        if (inp == "exit") {
            Variable *current = head;
            while (current != nullptr) {
                Variable *next = current->next;
                delete current;
                current = next;
            }
            break;

        } else if (inp == "help") {
            cout << "This is a simple REPL for evaluating infix expressions." << endl;
            cout << "Type 'exit' to exit." << endl;
            cout << "Type 'help' to show this message." << endl;
            cout << "Type 'set <variable>' to create a variable." << endl;
            continue;

        } else if (inp.length() >= 4 && inp.substr(0, 4) == "set ") {
            new_var_name = inp.substr(4, inp.length() - 4);
            if (new_var_name.length() == 0 || new_var_name == " " || new_var_name == "set" || new_var_name == "help" || new_var_name == "exit") {
                cout << "Invalid variable name." << endl;
                continue;
            }

            var_exists = true;
            var_is_writeable = true;
            continue;
        }

        try {
            if (inp.length() == 0) {
                continue;
            }

            // variable has been set in previous prompt
            if (var_exists) {
                // variable value should now be set to the result of the expression
                if (var_is_writeable) {
                    float new_var_value = evaluate_infix(inp);
                    if (!add_new_variable(new_var_name, new_var_value, head)) {
                        cout << "Variable could not be created." << endl;
                        continue;
                    }

                // replace all occurences of variables with their value
                } else {
                    for (Variable *tmp = head; tmp != nullptr; tmp = tmp->next) {
                        string var = tmp->name;
                        string var_value = to_string(tmp->value);

                        for (int i = 0; i < inp.length(); i++) {
                            if (inp.find(var) == string::npos) {
                                break;
                            }
                            inp = inp.replace(inp.find(var), var.length(), var_value);
                        }
                    }
                    float result = evaluate_infix(inp);
                    cout << "Ergebnis: " << result << endl;
                }
                var_is_writeable = false;

            // no variables set previously, just evaluate the expression
            } else {
                float result = evaluate_infix(inp);
                cout << "Ergebnis: " << result << endl;
            }
        } catch (const std::invalid_argument &e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
