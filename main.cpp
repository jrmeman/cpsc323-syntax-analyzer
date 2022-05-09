// Anthony Galustyan
// CS323 - Compilers and Languages
// Assignment 2

using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <istream>
#include <locale>
#include <array>
#include <stack>
#include <vector>

struct tokens {
	string lexeme;
	string token;
};

tokens id;
tokens num;
tokens equals;
tokens myplus;
tokens myminus;
tokens divide;
tokens multiply;
tokens l_paren;
tokens r_paren;
tokens dollarsign;


vector <tokens> lexered;

//converts string inputs to parsing table values
int To_Table(string input)
{
	if (input == "id" || input == "identifier")
	{
		return 0;
	}
	else if (input == "num" || input == "number")
	{
		return 1;
	}
	else if (input == "=")
	{
		return 2;
	}
	else if (input == "+")
	{
		return 3;
	}
	else if (input == "-")
	{
		return 4;
	}
	else if (input == "/")
	{
		return 5;
	}
	else if (input == "*")
	{
		return 6;
	}
	else if (input == "(")
	{
		return 7;
	}
	else if (input == ")")
	{
		return 8;
	}
	else if (input == "$")
	{
		return 9;
	}
	else if (input == "S")
	{
		return 0;
	}
	else if (input == "A")
	{
		return 1;
	}
	else if (input == "E")
	{
		return 2;
	}
	else if (input == "Q")
	{
		return 3;
	}
	else if (input == "T")
	{
		return 4;
	}
	else if (input == "P")
	{
		return 5;
	}
	else if (input == "F")
	{
		return 6;
	}
}

//Analyzes "lexered" vector if its correct with our defined grammar
void syntax_analyzer(vector <tokens> lexered)
{
	string table[7][10];

	table[0][0] = "rule1";
	table[1][0] = "rule2";
	table[2][0] = "rule3";
	table[2][1] = "rule3";
	table[2][7] = "rule3";
	table[3][3] = "rule4";
	table[3][4] = "rule5";
	table[3][8] = "rule6";
	table[3][9] = "rule6";
	table[4][0] = "rule7";
	table[4][1] = "rule7";
	table[4][7] = "rule7";
	table[5][0] = "rule10";
	table[5][1] = "rule10";
	table[5][3] = "rule11";
	table[5][4] = "rule11";
	table[5][5] = "rule9";
	table[5][6] = "rule8";
	table[5][7] = "rule10";
	table[5][8] = "rule11";
	table[5][9] = "rule11";
	table[6][0] = "rule13";
	table[6][1] = "rule14";
	table[6][7] = "rule12";

	int position = 0;
	int flag = 0;
	stack <string> mystack;
	lexered.push_back(dollarsign);
	mystack.push(dollarsign.lexeme);
	mystack.push("S");

	while (mystack.top() != "$")
	{
		string t = mystack.top();
		tokens i = lexered.at(position);
		
		if (flag == 0)
		{
			cout << "Token: " << i.token << "         " << "Lexeme: " << i.lexeme << endl;
			flag = 1;
		}

		//checks if top of stack is a terminal
		if (t == "id" || t == "num" || t == "=" || t == "+" || t == "-" || t == "/" || t == "*" || t == "(" || t == ")")
		{
			// if the top of stack is a terminal, checks if it matches the current position of the input
			if (t == i.lexeme || (t == "id" && i.token == "identifier") || (t == "num" && i.token == "number"))
			{
				mystack.pop();
				position++;
				flag = 0;
			}
			else
			{
				cout << "Error Found" << endl;
				return;
			}
		}
		
		//implementation for each rule, interacts with stack as needed.
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "rule1")
		{
			cout << "     <S> -> <A>" << endl;
			mystack.pop();
			mystack.push("A");
		}
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "rule2")
		{
			cout << "     <A> -> <id>" << endl;
			mystack.pop();
			mystack.push("E");
			mystack.push("=");
			mystack.push("id");
		}
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "rule3")
		{
			cout << "     <E> -> <T><Q>" << endl;
			mystack.pop();
			mystack.push("Q");
			mystack.push("T");
		}
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "rule4")
		{
			cout << "     <Q> -> +<T><Q>" << endl;
			mystack.pop();
			mystack.push("Q");
			mystack.push("T");
			mystack.push("+");
		}
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "rule5")
		{
			cout << "     <Q> -> -<T><Q>" << endl;
			mystack.pop();
			mystack.push("Q");
			mystack.push("T");
			mystack.push("-");
		}
		else if ((table[To_Table(t)][To_Table(i.lexeme)] == "rule6"))
		{
			cout << "     <Q> -> Epsilon" << endl;
			mystack.pop();
		}
		else if ((table[To_Table(t)][To_Table(i.lexeme)] == "rule7"))
		{
			cout << "     <T> -> <F><P>" << endl;
			mystack.pop();
			mystack.push("P");
			mystack.push("F");
		}
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "rule8")
		{
			cout << "     <P> -> *<F><P>" << endl;
			mystack.pop();
			mystack.push("P");
			mystack.push("F");
			mystack.push("*");
		}
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "rule9")
		{
			cout << "     <P> -> /<F><P>" << endl;
			mystack.pop();
			mystack.push("P");
			mystack.push("F");
			mystack.push("/");
		}
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "rule10")
		{
			cout << "     <P> -> <F><P>" << endl;
			mystack.pop();
			mystack.push("P");
			mystack.push("F");
		}
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "rule11")
		{
			cout << "     <P> -> Epsilon" << endl;
			mystack.pop();
		}
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "rule12")
		{
			cout << "     <F> -> ( <E> )" << endl;
			mystack.pop();
			mystack.push(")");
			mystack.push("E");
			mystack.push("(");
		}
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "rule13")
		{
			cout << "     <F> -> <id>" << endl;
			mystack.pop();
			mystack.push("id");
		}
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "rule14")
		{
			cout << "     <F> -> <num>" << endl;
			mystack.pop();
			mystack.push("num");
		}
		else
		{
		cout << "Error Found" << endl;
		return;
		}
		cout << endl;

	}

	cout << "Syntactically Correct" << endl;
}

//Pushes tokens/lexemes to vector "lexered", which is then used by function syntax_analyzer
void lexer_output(string token, string lexeme)
{

	if (token == "identifier")
	{
		lexered.push_back(id);
	}
	else if (token == "real" || token == "integer")
	{
		lexered.push_back(num);
	}
	else if (token == "operator"&& lexeme == "=")
	{
		lexered.push_back(equals);
	}
	else if (token == "operator" && lexeme == "+")
	{
		lexered.push_back(myplus);
	}
	else if (token == "operator" && lexeme == "-")
	{
		lexered.push_back(myminus);
	}
	else if (token == "operator" && lexeme == "/")
	{
		lexered.push_back(divide);
	}
	else if (token == "operator" && lexeme == "*")
	{
		lexered.push_back(multiply);
	}
	else if (token == "seperator" && lexeme == "(")
	{
		lexered.push_back(l_paren);
	}
	else if (token == "seperator" && lexeme == ")")
	{
		lexered.push_back(r_paren);
	}


}

//Lexer from assignment 1
void lexer()
{

	ifstream input;
	ofstream output;

	string line;
	string s;
	string word;
	string number;

	int state = 0;
	int flag = 0;

	int fsm[9][7] = { {1, 2, 3, 5, 0, 0, 2}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {4, 4, 3, 3, 3, 4, 4},
		{0, 0, 0, 0, 0, 0, 0}, {7, 7, 7, 5, 7, 7, 6}, {8, 8, 8, 6, 8, 8, 8}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0} };

	string keywords[18] = { "int", "float", "bool", "if", "else", "then", "endif", "while", "whileend", "do", "doend", "for", "forend", "input", "output", "and", "or", "function" };
	char operators[8] = { '*', '+', '-', '=', '/', '<', '>', '%' };
	char seperators[11] = { '\'', '(', ')', '{', '}', '[', ']', ',',':',';' };

	input.open("input.txt");
	output.open("output.txt");

	if (input.is_open())
	{
		cout << "TOKENS		    Lexemes" << endl << endl;
		output << "TOKENS		    Lexemes" << endl << endl;

		while (getline(input, s))
		{

			for (char c : s)
			{
				// checks if c is an operator at state 0
				for (int i = 0; i < 8; i++)
				{
					if ((c == operators[i] && state == 0))
					{
						//cout << "OPERATOR       =     " << c << endl;
						output << "OPERATOR       =     " << c << endl;
						string s(1, c);
						lexer_output("operator", s);
						s = "";
					}
				}
				// checks if c is a seperator at state 0
				for (int i = 0; i < 11; i++)
				{
					if (c == seperators[i] && state == 0)
					{
						//cout << "SEPERATOR      =     " << c << endl;
						output << "SEPERATOR      =     " << c << endl;
						string s(1, c);
						lexer_output("seperator", s);
						s = "";
					}
				}

				// handles comment blocks, there isn't actually a "state 9" in the current fsm, it's just using the logic
				// as if it was there. If the fsm was expanded that's where it would be defined. It was excluded to keep
				// the FSM simpler

				if (c == '!' && state == 0)
				{
					state = 9;
				}
				else if (c == '!' && state == 9)
				{
					state = 0;
				}


				// checks if c is a letter and current state is 0
				if (isalpha(c) && state == 0)
				{
					word += c;
					state = fsm[0][2];
				}

				// checks if we're in state 3 and have inputs from columns 2-4
				else if ((isalpha(c) || isdigit(c) || c == '$' ) && state == 3)
				{
					word += c;
				}
				
				// checks if we're in state 3 and have inputs from columns 0-1 and 5-6
				else if (state == 3 && !isalpha(c) && !isdigit(c) && c != '$')
				{
					for (int i = 0; i < 18; i++)
					{
						if (word == keywords[i])
						{
							//cout << "KEYWORD        =     " << word << endl;
							output << "KEYWORD        =     " << word << endl;
							lexer_output("keyword", word);
							flag = 1;
						}
					}
					if (flag != 1)
					{
						//cout << "IDENTIFIER     =     " << word << endl;
						output << "IDENTIFIER     =     " << word << endl;
						lexer_output("identifier", word);
					}

					for (int i = 0; i < 8; i++)
					{
						if (c == operators[i])
						{
							//cout << "OPERATOR     =     " << c << endl;
							output << "OPERATOR     =     " << c << endl;
							string s(1, c);
							lexer_output("operator", s);
							s = "";
						}
					}
					for (int j = 0; j < 11; j++)
					{
						if (c == seperators[j])
						{
							//cout << "SEPERATOR      =     " << c << endl;
							output << "SEPERATOR      =     " << c << endl;
							string s(1, c);
							lexer_output("seperator", s);
							s = "";
						}
					}


					word = "";
					state = 0;
					flag = 0;
				}
				// checks if we're in state 0 and c is a number
				if (isdigit(c) && state == 0)
				{
					number += c;
					state = fsm[0][3];
				}
				// checks if we're in state 5 and c is a number
				else if (isdigit(c) && state == 5)
				{
					number += c;
				}
				// checks if we're in state 5 and c has input from columns 0-2 and 4-5
				else if (!isdigit(c) && c != '.' && state == 5)
				{
					//cout << "INTEGER        =     " << number << endl;
					output << "INTEGER        =     " << number << endl;
					lexer_output("integer", number);

					for (int i = 0; i < 8; i++)
					{
						if (c == operators[i])
						{
							//cout << "OPERATOR       =     " << c << endl;
							output << "OPERATOR       =     " << c << endl;
							string s(1, c);
							lexer_output("operator", s);
							s = "";
						}
					}
					for (int j = 0; j < 11; j++)
					{
						if (c == seperators[j])
						{
							//cout << "SEPERATOR      =     " << c << endl;
							output << "SEPERATOR      =     " << c << endl;
							string s(1, c);
							lexer_output("seperator", s);
							s = "";
						}
					}
					state = 0;
					number = "";
				}

				// checks if we're in state 5 and c is a .
				else if (state == 5 && c == '.')
				{
					number += c;
					state = fsm[5][6];
				}
				// checks if we're in state 6 and c is a number
				else if (isdigit(c) && state == 6)
				{
					number += c;
				}

				// checks if we're in state 6 and c is not a number
				else if (!isdigit(c) && state == 6)
				{
					//cout << "REAL           =     " << number << endl;
					output << "REAL           =     " << number << endl;
					lexer_output("real", number);

					for (int i = 0; i < 8; i++)
					{
						if (c == operators[i])
						{
							//cout << "OPERATOR       =     " << c << endl;
							output << "OPERATOR       =     " << c << endl;
							string s(1, c);
							lexer_output("operator", s);
							s = "";
						}
					}
					for (int j = 0; j < 11; j++)
					{
						if (c == seperators[j])
						{
							//cout << "SEPERATOR      =     " << c << endl;
							output << "SEPERATOR      =     " << c << endl;
							string s(1, c);
							lexer_output("seperator", s);
							s = "";
						}
					}
					number = "";
					state = 0;
				}
			}
		}
	}
	input.close();
	output.close();
}


int main() {
	id.lexeme = "id";
	id.token = "identifier";
	num.lexeme = "num";
	num.token = "number";
	equals.lexeme = "=";
	equals.token = "operator";
	myplus.lexeme = "+";
	myplus.token = "operator";
	myminus.lexeme = "-";
	myminus.token = "operator";
	divide.lexeme = "/";
	divide.token = "operator";
	multiply.lexeme = "*";
	multiply.token = "operator";
	l_paren.lexeme = "(";
	l_paren.token = "seperator";
	r_paren.lexeme = ")";
	r_paren.token = "seperator";
	dollarsign.lexeme = "$";
	dollarsign.token = "endsymbol";

	lexer();
	syntax_analyzer(lexered);

}