/******************************************************************************************************************
*** Name:       Jonathan Canfield, Ali Alrajhi																	***
*** Clase:      CPSC 323																						***
*** Professor:  Choi																							***
*** Assignment: #2																								***
*** Due:        11/4/2011																						***
*******************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>

using namespace std;
/******************************************************************************************************************
header file used for declarations, struct and class. 
*******************************************************************************************************************/
/******************************************************************************************************************
header file used for declarations, struct and class. 
*******************************************************************************************************************/
enum allowed_token {Identifier, Keyword, Integer,Real, Operator, Separator, Unknown};
const char * tokens [] = {"Identifier", "Keyword", "Integer", "Real",
								"Operator", "Separator", "Unknown"};
enum Asm_Data_T { INTEGER,BOOLS,EMPT };
const char * Keywords [] = {"function", "int", "Real", "boolean", "if","endif", "else", "while", 
								"return", "print", "scan", "true", "false","write"};
bool found_Keyword=false;
void Syntax_ana();
void Opt_Function_Definitions();
void Function_Definitions();
void Function();
void Opt_Parameter_List();
void Parameter_List();
void Parameter();
void Qualifier();
void Body();
void Opt_Declaration_List();
void Declaration_List();
void Declaration();
void IDs(Asm_Data_T Asm_Data_Typ = EMPT);
void FSM_STATment_List();
void FSM_STATment();
void Compound();
void Assign();
void If();
void Return();
void Write();
void Read();
void While();
void Condition();
void Relop();
void Expression(Asm_Data_T Asm_Data_Typ = EMPT);
void Expression_Prime(Asm_Data_T Asm_Data_Typ = EMPT);
void Term(Asm_Data_T Asm_Data_Typ = EMPT);
void Term_Prime(Asm_Data_T Asm_Data_Typ = EMPT);
void Factor(Asm_Data_T Asm_Data_Typ = EMPT);
void Primary(Asm_Data_T Asm_Data_Typ = EMPT);
void Empty();
void Term_Epsilon();
void Expression_Epsilon();
void output_new_token(const char * str);
void output_new_token(allowed_token token);
void output_production_rules(const char * str);
void check_end_file ();
void While_Jump(int );


struct Instruct_use {
	char Oper[8];
	int Oper_int;
};
class Instruct_Tab {	
public:
	vector <Instruct_use> table;
	int counter_index;
	Instruct_Tab() { 		
		Instruct_use i;
		counter_index = 1; 
		table.push_back(i);}


	void Send_Out(ostream & stream);
	void Create_Instruct(const char * Oper, int Oper_int);
};

struct Sym_Tab {
	char Id_counter[50];
	int Address_Sym_Tab;
	Asm_Data_T type;
};
class Symb_Table {
private:
	int Mem_Add_Locat_count;
	vector <Sym_Tab> table;
public:
	Symb_Table() { Mem_Add_Locat_count = 1000; }
	void Push(const char * Id_counter, Asm_Data_T & type);
	void Send_Out(ostream & stream);
	int Find_Identity(const char * Id_counter);
	int Addre_loc(const char * Id_counter);	
	bool Ident_loc(const char * Id_counter);};


struct Token {
	char lexeme[50];
	allowed_token token;
	int line_int;
	bool Lexeme_comp(const char * str)
	{ 
		return (strcmp(str,lexeme) == 0); 
	}
};

class Lexical {
private:
	ifstream input;
public:
	int b;
	Lexical(const char * filename) { 
		input.open(filename);
		b = 1;
	}
	~Lexical() { input.close(); }
	

	bool check_Keyword( const char * Id_counter ){
		found_Keyword=false;
		for (int counter=0;counter<14;counter++)
			if (strcmp(Keywords[counter],Id_counter) == 0)
				found_Keyword = true;
		return found_Keyword;
	}
	Token nextToken();
};

Lexical *get_lexical;
Token token;
ofstream output_file;
Instruct_Tab Push_Table;
Symb_Table Push_Sym_Table;
stack <int> Pop_Stk;
bool Push_Decs;
Asm_Data_T Get_typ;