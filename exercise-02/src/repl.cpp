#include <stdio.h>

#include <iostream>
#include <map>

#include "arithmetic.cpp"

using namespace std;

int main() {
    string var;
    float var_value;
    bool var_exists = false;
    bool var_is_writeable = false;

    while (true) {
        string inp;

        cout << ">>> ";
        getline(cin, inp);

        if (inp == "exit") {
            break;

        } else if (inp == "help") {
            cout << "This is a simple REPL for evaluating infix expressions." << endl;
            cout << "Type 'exit' to exit." << endl;
            cout << "Type 'help' to show this message." << endl;
            cout << "Type 'set <variable>' to create a variable." << endl;
            continue;

        } else if (inp.length() >= 4 && inp.substr(0, 4) == "set ") {
            var = inp.substr(4, inp.length() - 4);
            if (var.length() == 0 || var == " ") {
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
                // var has been created in previous prompt and should now be set to the result of the expression
                if (var_is_writeable) {
                    var_value = evaluate_infix(inp);
                    cout << var << " = " << var_value << endl;

                // replace all occurences of var with its value
                } else {
                    for (int i = 0; i < inp.length(); i++) {
                        if (inp.find(var) == string::npos) {
                            break;
                        }
                        inp = inp.replace(inp.find(var), var.length(), to_string(var_value));
                    }
                    float result = evaluate_infix(inp);
                    cout << "Ergebnis: " << result << endl;
                }
                var_is_writeable = false;

            // no variable set previously, just evaluate the expression
            } else {
                float result = evaluate_infix(inp);
                cout << "Ergebnis: " << result << endl;
            }
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
