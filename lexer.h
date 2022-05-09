#ifndef LEXER
#define LEXER

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int lexer() {
    ifstream in;
    ofstream out;

    string s, w, num;
    int state = 0;
    int column;
    bool flag = true;

    // Initialize variables for syntax analyzer
    int count = 0;

    // Defining FSM - mimics the FSM defined in the documentation
    int fsm[10][8] = {  {1, 3, 7, 8, 0, 0, 8, 9}, 
                        {1, 1, 2, 2, 1, 2, 2, 2}, 
                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                        {5, 3, 5, 5, 5, 5, 4, 5}, 
                        {6, 4, 6, 6, 6, 6, 6, 6}, 
                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                        {9, 9, 9, 9, 9, 9, 9, 0} };
    
    // Array of operators
    char op[8] = {'+', '-', '*', '/', '=', '%', '<', '>'};

    // Array of separators
    char sep[10] = {'[', ']', '(', ')', '{', '}', ',', '.', ';', ':'};

    // Array of keywords
    string keywords[21] = {"int", "float", "bool", "True", "False", "if", "else", "then", "endif", "endelse", "while", "whileend", 
        "do", "enddo", "for", "endfor", "STDinput", "STDoutput", "and", "or", "not"};

    in.open("input.txt");
    out.open("output.txt");

    if(!in.is_open()) {
        cout << "ERROR: File cannot be opened/found\n";
        system("pause");
        exit(1);
    }

    cout << endl;
    cout << "\tTOKENS\t\t\t     LEXEMES\n\n";
    out << "\tTOKENS\t\t\t     LEXEMES\n\n";

    while(getline(in, s)) {
        for(char c : s) {
            // Operator check
            if(state == 0) {
                for(int i = 0; i < 8; i++) {
                    // Operator column
                    column = 2;
                    if(c == op[i]) {
                        // Changing states
                        state = fsm[state][column];
                        cout << "OPERATOR\t\t=\t\t" << c << endl;
                        out << "OPERATOR\t\t=\t\t" << c << endl;
                        count++;
                    }
                    // Revert back to state 0 after output
                    state = 0;          
                }
            }

            // Separator check
            if(state == 0){
                for(int i = 0; i < 10; i++) {
                    // Separator column
                    column = 3;
                    if(c == sep[i]) {
                        // Changing states
                        state = fsm[state][column];
                        cout << "SEPARATOR\t\t=\t\t" << c << endl;
                        out << "SEPARATOR\t\t=\t\t" << c << endl;
                        count++;
                    }
                    // Revert back to state 0 after output
                    state = 0;
                }
            }

            // Checks for comment blocks in txt file
            if(c == '!' && state == 0) {
                // Changing states
                state = 9;
            }
            else if(c == '!' && state == 9) {
                // Revert back to state 0 after end of comment block
                state = 0;
            }

            // Character check
            column = 0;
            if(isalpha(c) && state == 0) {
                state = fsm[state][column];
                // Concatonate char to w string
                w += c;
            }

            else if((isalpha(c) || isdigit(c) || c == '$' || c == '_') && state == 1) {
                // Concatonate char to w string
                w += c;
            }

            else if(!isalpha(c) && !isdigit(c) && c != '$' && c != '_' && state == 1) {
                // Keyword check
                for(int i = 0; i < 21; i++) {
                    if(w == keywords[i]) {
                        cout << "KEYWORD\t\t\t=\t\t" << w << endl;
                        out << "KEYWORD\t\t\t=\t\t" << w << endl;
                        count++;
                        flag = false;
                    }
                }

                // If not keyword, w is an identifier
                if(flag != false) {
                    cout << "IDENTIFIER\t\t=\t\t" << w << endl;
                    out << "IDENTIFIER\t\t=\t\t" << w << endl;
                    count++;
                }

                // Next 2 for loops checks to see if !isalpha(c) && !isdigit(c) && c != '$' && c != '_' 
                // is an operator or separator
                for(int i = 0; i < 8; i++) {
                    // Operator column
                    column = 2;
                    if(c == op[i]) {
                        // Changing states
                        state = fsm[state][column];
                        cout << "OPERATOR\t\t=\t\t" << c << endl;
                        out << "OPERATOR\t\t=\t\t" << c << endl;
                        count++;
                    }
                    // Revert back to state 0 after output
                    state = 0;          
                }

                for(int i = 0; i < 10; i++) {
                    // Separator column
                    column = 3;
                    if(c == sep[i]) {
                        // Changing states
                        state = fsm[state][column];
                        cout << "SEPARATOR\t\t=\t\t" << c << endl;
                        out << "SEPARATOR\t\t=\t\t" << c << endl;
                        count++;
                    }
                    // Revert back to state 0 after output
                    state = 0;
                }

                state = 0;
                w = "";
                flag = true;
            }

            // Integer check
            column = 1;
            if(isdigit(c) && state == 0) {
                state = fsm[state][column];
                // Concatonate char to num string
                num += c;
            }

            else if(isdigit(c) && state == 3) {
                // Concatonate char to string
                num += c;
            }

            else if(!isdigit(c) && c != '.' && state == 3) {
                cout << "INTEGER\t\t\t=\t\t" << num << endl;
                out << "INTEGER\t\t\t=\t\t" << num << endl;
                count++;

                // Next 2 for loops checks to see if !isdigit(c) && c != '.' is an operator or separator
                for(int i = 0; i < 8; i++) {
                    // Operator column
                    column = 2;
                    if(c == op[i]) {
                        // Changing states
                        state = fsm[state][column];
                        cout << "OPERATOR\t\t=\t\t" << c << endl;
                        out << "OPERATOR\t\t=\t\t" << c << endl;
                        count++;
                    }
                    // Revert back to state 0 after output
                    state = 0;          
                }

                for(int i = 0; i < 10; i++) {
                    // Separator column
                    column = 3;
                    if(c == sep[i]) {
                        // Changing states
                        state = fsm[state][column];
                        cout << "SEPARATOR\t\t=\t\t" << c << endl;
                        out << "SEPARATOR\t\t=\t\t" << c << endl;
                        count++;
                    }
                    // Revert back to state 0 after output
                    state = 0;
                }

                state = 0;
                num = "";
            }

            // Real number check
            else if(c == '.' && state == 3) {
                column = 6;
                state = fsm[state][column];
                num += c;
            }

            else if(isdigit(c) && state == 4) {
                num += c;
            }

            else if(!isdigit(c) && state == 4) {
                cout << "REAL NUMBER\t\t=\t\t" << num << endl;
                out << "REAL NUMBER\t\t=\t\t" << num << endl;
                count++;

                // Next 2 for loops checks to see if !isdigit(c) is an operator or separator
                for(int i = 0; i < 8; i++) {
                    // Operator column
                    column = 2;
                    if(c == op[i]) {
                        // Changing states
                        state = fsm[state][column];
                        cout << "OPERATOR\t\t=\t\t" << c << endl;
                        out << "OPERATOR\t\t=\t\t" << c << endl;
                        count++;
                    }
                    // Revert back to state 0 after output
                    state = 0;          
                }

                for(int i = 0; i < 10; i++) {
                    // Separator column
                    column = 3;
                    if(c == sep[i]) {
                        // Changing states
                        state = fsm[state][column];
                        cout << "SEPARATOR\t\t=\t\t" << c << endl;
                        out << "SEPARATOR\t\t=\t\t" << c << endl;
                        count++;
                    }
                    // Revert back to state 0 after output
                    state = 0;
                }

                state = 0;
                num = "";
            }
        }
    }

    return count;

    in.close();
    out.close();
}

#endif