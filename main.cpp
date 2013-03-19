/******************************************************************************************************************
*** Name:       Jonathan Canfield																	***
*** Clase:      CPSC 323																						***
*** Professor:  Choi																							***
*** Assignment: #3																								***
*** Due:        12/9/2011																						***
*******************************************************************************************************************/
#include "header.h";


/******************************************************************************************************************
For this homework assignment I soon Realized our lexical analyzer would not meet the requirements for grabbing one 
token at a time when need.  I guess I could have ran the lexical analyzer stored everything into a text file then 
from that text file the Syntax analyzer would read the tokens from there.  I knew this would work but it�s a very
amateur way of going about it. So much to our dismay I completely revamped the first assignment to use a proper 
table for the tokens and FSM FSM_STAT. I think I got a few grey hairs from this but I wanted to do the assignment 
as correct as I possibly could. 
The main is very simple. I are now using pointers to get tokens from the lexical ana. It�s check to see if the 
file is empty or not and calls the Syntax analyzer. If I didn't modify the first assignment The lex. would read 
the entire source code from the user and output the results Then the syntax analyzer would use that text file for
its process. Now the syntax analyzer calls the lex when it needs a new token. I feel this is a much more professional
approach. Sadly I didn't ran out of time so I was unable to add error checking, if the code is not 100% correct 
the program crashes. 
*******************************************************************************************************************
I now added the the creation of the the generation of Assembly language to the code. I ran out of time and had
trouble with error handling such as an identifier being declared more than once. my error handling attemps only 
lead to the error message being sent every time the identifier was used. I'm sure with more time I could have 
resolved it. Also I had some trouble with the PUSHI PUSHM and POPM I placed them where I felt they were needed
but comapairing the results to yours they seem to be wrong but I feel they are in the right location. 
*******************************************************************************************************************/

int main(){	
	system("Color F");
	string File_name;	
	cout<<"What input file would you like to use today?  ";
	getline (cin, File_name);
	const char* Run_file = File_name.c_str ();
	get_lexical = new Lexical(Run_file);
	output_file.open("output.txt");	
	token = get_lexical->nextToken();	
	check_end_file ();
	Syntax_ana();	
	Push_Table.Send_Out(output_file);
	output_file << endl;	
	Push_Sym_Table.Send_Out(output_file);	
	output_file.close();
	system("pause");
	return 0;
}

/******************************************************************************************************************
This is the main part of the syntax analyzer. It first checks to see if the users program will have functions. If
it does the process for functions will be called. If it does not have any functions this part is ignored. 
************************************************************************************************************
There is now the edition of symbol table and proper assembly code creation the the functions, not all 
but some
*******************************************************************************************************************/

/*<Rat11F>::=  # <Opt Function Definition> # <Opt Declaration List> <FSM_STATment List> # */
void Syntax_ana(){
		
	if (token.Lexeme_comp("#")){
		output_new_token("");
		output_production_rules("<Syntax_ana>::=  # <Opt Function Definition> # <Opt Declaration List> <FSM_STATment List> #");		
		token = get_lexical->nextToken();
		Opt_Function_Definitions();
		token = get_lexical->nextToken();		
		Opt_Declaration_List();		
	}
		output_new_token("");
		FSM_STATment_List();			
	
	
}
/******************************************************************************************************************
Now there are a lot of functions for this program. instead is commenting on everyone; this would be some what
reduendent since most just output results. We did however comment above each function the syntax rule which is 
outputted. 
*******************************************************************************************************************/
//<Opt Function Definition>::=  <Function Definition> | <Empty>
void Opt_Function_Definitions() {
	output_production_rules("<Opt Function Definition>::=  <Function Definition> | <Empty>");
	
	if (token.Lexeme_comp("function")){		
	   Function_Definitions();}	
}

/*<Function Definition>::=  <Function> | <Function> <Function Definition>*/
void Function_Definitions(){
	output_production_rules("<Function Definition>::=  <Function> | <Function> <Function Definition>");
	Function();
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	if (token.Lexeme_comp("function"))
		Function_Definitions();
}

/*<Function>::=  function <Identifier> (<Opt Parameter List>) <Opt Declaration List> <Body>*/
void Function() {
	output_production_rules("<Function>::=  function <Identifier> (<Opt Parameter List>) <Opt Declaration List> <Body>");
	output_new_token("function");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(Identifier);
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	Opt_Parameter_List();	
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	Opt_Declaration_List();
	Body();
}

/*<Opt Parameter List>::=  <Parameter List> | <Empty>*/
void Opt_Parameter_List() {
	output_production_rules("<Opt Parameter List>::=  <Parameter List> | <Empty>");
	if (token.token == Identifier)
		Parameter_List();
	else
		Empty();
}

/*<Parameter List>::=  <Parameter> | <Parameter> , <Parameter List>*/
void Parameter_List() {
	output_production_rules("<Parameter List>::=  <Parameter> | <Parameter> , <Parameter List> ");
	Parameter();
	token = get_lexical->nextToken();
	check_end_file ();
	if (token.Lexeme_comp(",")) {
		output_new_token("");
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token(" ");
		Parameter_List();
	}
}
/*<Parameter>::=  <IDs> : <Qualifier>*/
void Parameter() {
	output_production_rules("<Parameter>::=  <IDs> : <Qualifier>");
	IDs();	
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	Qualifier();
	
}
/*<Qualifier>::=  int | boolean | Real*/
void Qualifier() {	
	if (token.Lexeme_comp("int")) {
		output_production_rules("<Qualifier>::=  int");		
		Get_typ = INTEGER;
		
	}
	else if (token.Lexeme_comp("boolean")) {
		output_production_rules("<Qualifier>::=  boolean");
		Get_typ = BOOLS;
	}
	else if (token.Lexeme_comp("Real")) {
		output_production_rules("<Qualifier>::=  Real");
				
	}
	
}

/*<Body>::=  { <FSM_STATment List> }*/
void Body() {
	output_production_rules("<Body>::=  { <FSM_STATment List> }");	
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	if (token.Lexeme_comp("}")){
		Push_Table.Create_Instruct("JUMPZ", -999);}
	FSM_STATment_List();	
}

/*<Opt Declaration List>::=  <Declaration List> | <Empty>*/
void Opt_Declaration_List() {
	output_production_rules("<Opt Declaration List>::=  <Declaration List> | <Empty>");
	Push_Decs=true;
	if (token.Lexeme_comp("int") || token.Lexeme_comp("boolean") || token.Lexeme_comp("Real")){
		Declaration_List();
		Push_Decs=true;}
	else
		Empty();
}

/*<Declarations List> ::=  <Declaration>; | <Declaration>; < Declaration List>*/
void Declaration_List() {
	output_production_rules("<Declarations List> ::=  <Declaration>; | <Declaration>; < Declaration List>");
	Declaration();	
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	if (token.Lexeme_comp("int") || token.Lexeme_comp("boolean") ) 
		Declaration_List();
}
/*"<Declaration>::=  <Qualifier> <IDs>"*/
void Declaration() {
	output_production_rules("<Declaration>::=  <Qualifier> <IDs>");
	Qualifier();
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	IDs();	
}

/*<IDs>::=  <Identifier> | <Identifier>, <IDs>*/
void IDs(Asm_Data_T Asm_Data_Typ) {
	
	output_production_rules("<IDs>::=  <Identifier> | <Identifier>, <IDs>");
	if (Push_Decs){
		Push_Sym_Table.Push(token.lexeme, Get_typ);}
	else {
		int addr = Push_Sym_Table.Addre_loc(token.lexeme);
		Push_Table.Create_Instruct("PUSHM", addr);}
	token = get_lexical->nextToken();
	check_end_file ();	
	if (token.Lexeme_comp(",")){
		output_new_token(" ");
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token(" ");
		IDs();

	}

	if (token.Lexeme_comp("]")){
		output_new_token(" ");
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token(" ");
		IDs();

	}

}

/*<FSM_STATment List>::=  <FSM_STATment> | <FSM_STATment> <FSM_STATment List>*/
void FSM_STATment_List() {
	FSM_STATment();	
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	if (token.Lexeme_comp("{") || token.token == Identifier || token.Lexeme_comp("if")|| token.Lexeme_comp("write")
		|| token.Lexeme_comp("while")  || token.Lexeme_comp("return")
		|| token.Lexeme_comp("print") || token.Lexeme_comp("scan"))
	{
		FSM_STATment_List();
	}
}
/*I added print I noticed print is used in <Write> ::= print<Expression>);*/
/*<FSM_STATment List> ::= <FSM_STATment> | <Assign> | <If> | <Return> | <Write> | <Read> | <While>*/
void FSM_STATment() {
	if (token.Lexeme_comp("{")) {
		output_production_rules("<FSM_STATment>::=  <Compound>");
		Compound();
	}
	else if (token.token == Identifier) {

		output_production_rules("<FSM_STATment>::=  <Assign>");
		Assign();
	}
	else if (token.Lexeme_comp("if")) {
		output_production_rules("<FSM_STATment>::=  <If>");
		If();
	}
	else if (token.Lexeme_comp("while")) { 
		output_production_rules("<FSM_STATment>::=  <While>");
		While();
	}
	else if (token.Lexeme_comp("return")) {
		output_production_rules("<FSM_STATment>::=  <Return>");
		Return();
	}
	else if (token.Lexeme_comp("write")) {
		output_production_rules("<FSM_STATment>::=  <write>");
		Write();
	}
	else if (token.Lexeme_comp("print")) {
		output_production_rules("<FSM_STATment>::=  <Write>");
		Write();
	}
	else if (token.Lexeme_comp("scan")) {
		output_production_rules("<FSM_STATment>::=  <Read>");
		Read();
	}
	
}


/*<Compound>::=  { <FSM_STATment List> }*/
void Compound() {
	output_production_rules("<Compound>::=  { <FSM_STATment List> }");

	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	FSM_STATment_List();
	output_new_token("");
}

/*<Assign>::=  <Identifier> := <Expression>;*/
void Assign() {	
	Token temp = token;
	Token tmp = token;
	bool Check = true;
	
	output_production_rules("<Assign>::=  <Identifier> := <Expression>;");
	if (token.token == Identifier) {
		Push_Sym_Table.Push(token.lexeme, Get_typ);
		int addr = Push_Sym_Table.Addre_loc(token.lexeme);
	
	}
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(":=");
	Push_Table.Create_Instruct("", -999);
		Pop_Stk.push(Push_Table.counter_index);
	token = get_lexical->nextToken();
	check_end_file ();
	Expression();	

	
	if (Push_Sym_Table.Find_Identity(temp.lexeme)==1) {
		if (tmp.Lexeme_comp("true") || tmp.Lexeme_comp("false") || Push_Sym_Table.Find_Identity(tmp.lexeme)==1) {
			Check = true;}
		else
			Check = false;
	}
	else if (Push_Sym_Table.Find_Identity(temp.lexeme)==0) {
		if (tmp.token == Integer || Push_Sym_Table.Find_Identity(tmp.lexeme)==0){
			Check = true;}
		else
			Check = false;}		
	int addr = Push_Sym_Table.Addre_loc(temp.lexeme);
	Push_Table.Create_Instruct("PUSHM", addr);
}

/*<If>::=  if ( <Condition> ) <FSM_STATment> endif | if ( <Condition> ) <FSM_STATment> else <FSM_STATment> endif*/
void If() {
	output_production_rules("<If>::=  if ( <Condition> ) <FSM_STATment> endif | if ( <Condition> ) <FSM_STATment> else <FSM_STATment> endif");
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	Condition();

	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	FSM_STATment();
	token = get_lexical->nextToken();
	check_end_file ();
	if (token.Lexeme_comp("endif")) {
		
		output_new_token("");
	}
	else if (token.Lexeme_comp("else")) {
		output_new_token("");
		token = get_lexical->nextToken();
		check_end_file ();
		FSM_STATment();
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
	}
	
	

}

/*<While>::=  while ( <Condition> ) <FSM_STATment>*/
void While() {
	int addr = Push_Table.counter_index;
	output_production_rules("<While>::=  while ( <Condition> ) <FSM_STATment>");
	output_new_token("");
	Push_Table.Create_Instruct("LABEL", -999);
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	Condition();
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	FSM_STATment();
	Push_Table.Create_Instruct("JUMP", addr);
	While_Jump(Push_Table.counter_index);		
}

/*<Return>::=  return ; | return <Expression>;*/
void Return() {
	
	output_production_rules("<Return>::=  return ; | return <Expression>;");
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	if (token.Lexeme_comp(""))
		output_new_token("");
	else {
		Expression();
		output_new_token("");
	}
}

/*<Write>::=  print ( <Expression> );*/
void Write() {
	
	output_production_rules("<Write>::=  print ( <Expression> );");	
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	Expression();
	Push_Table.Create_Instruct("STDOUT", -999);

	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
}

/*<Read>::=  read ( <IDs> );*/
void Read() {
	output_production_rules("<Read>::=  scan ( <IDs> );");		
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
	token = get_lexical->nextToken();
	Push_Table.Create_Instruct("STDIN", -999);
	output_new_token("");	
	IDs();	
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
}

/*<Condition>::=  <Expression> <Relop> <Expression>*/
void Condition() {
	Token op = token;
	output_production_rules("<Condition>::=  <Expression> <Relop> <Expression>");
	Expression();
	Relop();
	Expression();
		
}

/*<Relop>::=  = | /= | > | < | <= | =>*/
void Relop() {
	output_production_rules("<Relop>::=  = | /= | > | < | <= | =>");
	if (token.Lexeme_comp("=")) {
		output_production_rules("<Relop>::=  =");
		output_new_token("=");
	}
	else if (token.Lexeme_comp("/=")){
		output_production_rules("<Relop>::=  /=");
		output_new_token("");
	}
	else if (token.Lexeme_comp(">")) {
		output_production_rules("<Relop>::=  >");
		output_new_token("");
	}
	else if (token.Lexeme_comp("<")) {
		output_production_rules("<Relop>::=  <");
		Push_Table.Create_Instruct("LES", -999);		
		Pop_Stk.push(Push_Table.counter_index);
		Push_Table.Create_Instruct("JUMPZ", -999);
		output_new_token("");
	}
	else if (token.Lexeme_comp("<=")) { 
		output_production_rules("<Relop>::=  <=");
		Push_Table.Create_Instruct("LEQ", -999);
		Pop_Stk.push(Push_Table.counter_index);
		Push_Table.Create_Instruct("JUMPZ", -999);
		output_new_token("");
	}
	else if (token.Lexeme_comp("=>")) {
		output_production_rules("<Relop>::=  =>");
		Push_Table.Create_Instruct("GEQ", -999);
		Pop_Stk.push(Push_Table.counter_index);
		Push_Table.Create_Instruct("JUMPZ", -999);
		output_new_token("");
	}
	
	token = get_lexical->nextToken();	
	
}

/*<Expression>::=  <Term><Expression_Prime>*/
void Expression(Asm_Data_T Asm_Data_Typ) {
	output_new_token("");
	output_production_rules("<Expression>::=  <Term> <Expression_Prime>");	
	Term();	
	Expression_Prime();
}

/*<Expression_Prime>::=  +<Term><Expression_Prime> | -<Term><Exression_Prime>*/
void Expression_Prime(Asm_Data_T Asm_Data_Typ) {
	if (token.Lexeme_comp("+")) {
		output_production_rules("<Expression_Prime>::=  +<Term><Expression_Prime>");				
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
		Term();
		Push_Table.Create_Instruct("ADD", -999);
		Expression_Prime();}

	if (token.Lexeme_comp("-")) {
		output_production_rules("<Expression_Prime>::=  -<Term><Expression_Prime>");		
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
		Term();
		Push_Table.Create_Instruct("SUB", -999);
		Expression_Prime();}
	else
		Expression_Epsilon();
}

/*<Term>::=  <Factor> <Term_Prime>*/
void Term(Asm_Data_T Asm_Data_Typ) {
	output_production_rules("<Term>::=  <Factor> <Term_Prime>");	
	Factor();
	Term_Prime();
}

//<Term_Prime>::=  *<Factor><Term_Prime> | /<Factor><Term_Prime>
void Term_Prime(Asm_Data_T Asm_Data_Typ) {
	if (token.Lexeme_comp("*")) {
		output_production_rules("<Term_Prime>::=  *<Factor><Term_Prime>");		
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
		Factor();
		Push_Table.Create_Instruct("MUL", -999);
		Term_Prime();}
	if (token.Lexeme_comp("/")) {
		output_production_rules("<Term_Prime>::=  /<Factor><Term_Prime>");		
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
		Factor();
		Push_Table.Create_Instruct("DIV", -999);
		Term_Prime();}
	else
		Term_Epsilon();
}

/*<Factor>::=  -<Primary> | <Primary>*/
void Factor(Asm_Data_T Asm_Data_Typ) {
	if (token.Lexeme_comp("-")) {
		output_production_rules("<Factor>::=  -<Primary>");		
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
		Primary();}
	else {		
		output_production_rules("<Factor>::=  <Identifier>");
		Primary();}
}

/*<Primary>::=  <Integer> | <Real> | <Expression> | true | false | <Identifier> | <Identifier> [<IDs>]*/
void Primary(Asm_Data_T Asm_Data_Typ) {

	if (token.token == Integer) {
		output_production_rules("<Primary>::=  <Integer>");
		Push_Table.Create_Instruct("PUSHI", atoi(token.lexeme));
		token = get_lexical->nextToken();
		check_end_file ();}
	if (token.token == Real) {
		output_production_rules("<Primary>::=  <Real>");	
		token = get_lexical->nextToken();
		check_end_file ();}
	if (token.Lexeme_comp("(")) {
		output_production_rules("<Primary>::=  ( <Expression> )");				
		token = get_lexical->nextToken();
		check_end_file ();		
		Expression();
		output_new_token("");
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");}
	if (token.Lexeme_comp("true")) {
		output_production_rules("<Primary>::=  true");		
		Push_Table.Create_Instruct("PUSHI", 1);
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");}
	if (token.Lexeme_comp("false")) {
		output_production_rules("<Primary>::=  false");		
		Push_Table.Create_Instruct("PUSHI", 0);
		token = get_lexical->nextToken();
		check_end_file ();}
	if (token.token == Identifier) {
		output_production_rules("<Primary>::=  <Identifier>");		
		Push_Sym_Table.Push(token.lexeme, Get_typ);
		int addr = Push_Sym_Table.Addre_loc(token.lexeme);
		Push_Table.Create_Instruct("POPM", addr);
		token = get_lexical->nextToken();	
		output_new_token(" ");
		if (token.Lexeme_comp("[")) {
			output_production_rules("<Primary>::=  <Identifier> [<IDs>]");	
			token = get_lexical->nextToken();
			check_end_file ();
			output_new_token(" ");
			IDs();				
			token = get_lexical->nextToken();
			check_end_file ();
			output_new_token("");}}
	
}

/* <Empty>::=  epsilon*/
void Empty() {
		output_production_rules("<Empty>::=  epsilon");
}

/*<Term Prime>::=  epsilon*/
void Term_Epsilon() {	
	output_production_rules("<Term Prime>::=  epsilon");	
}

/*<Expression Prime>::=  epsilon*/
void Expression_Epsilon() {
	output_production_rules("<Expression Prime>::=  epsilon");
	
	
}

void check_end_file (){	
	if (token.Lexeme_comp("")){
		cout<<"its over ";
		//system ("pause");
	   //  exit(1);
	}
}
/************************************************************************************
The following set of functions are used to output results from the assignemt 2 
and assignment 3. the second assignemt has been turned off because its not needed
for this assignemt 
*************************************************************************************/

void output_new_token(const char * str) {
	
	//cout << "TOKEN: " << tokens[token.token] << setw (10)<< ", Lexeme: " << token.lexeme << "\n";
	//output_file << "Token: " << tokens[token.token] << ", Lexeme: " << token.lexeme << "\n";
}

void output_new_token(allowed_token allowed_token) {
	
	//cout << "Token: " << tokens[token.token] << setw (10)<< ", Lexeme: " << token.lexeme << "\n";
	//output_file << "Token: " << tokens[token.token] << ", Lexeme: " << token.lexeme << "\n";
}

void output_production_rules(const char * str) {
	//cout << "	" << str << "\n";
	//output_file << "	" << str << "\n";
}

void Symb_Table::Send_Out(ostream & stream) {
		cout << endl;
		cout << "Identifier		Memory Location		Type\n";
		output_file << "Identifier		Memory Location		Type\n";
	for ( int count = 0; count < table.size(); count++) 
		if (table[count].type == 0) {
			cout << table[count].Id_counter << "			" << table[count].Address_Sym_Tab << "			" << "Integer" << endl;
			output_file << table[count].Id_counter << "				" << table[count].Address_Sym_Tab << "				" << "Integer" << endl;
		}
		else if (table[count].type == 1) {
			cout << table[count].Id_counter << "			" << table[count].Address_Sym_Tab << "			" << "Boolean" << endl;
			output_file << table[count].Id_counter << "	    		" << table[count].Address_Sym_Tab << "		  		" << "Boolean" << endl;

		}
}
	
void Instruct_Tab::Send_Out(ostream & stream) {
	for (int count = 1; count < table.size(); count++) {
		if (table[count].Oper_int == -999) {
			cout << count << "	" << table[count].Oper << "	" << endl;
			output_file << count << "	" << table[count].Oper << "	" << endl;
		}
		else {
			cout << count << "	" << table[count].Oper << "	" << table[count].Oper_int << endl;
			output_file << count << "	" << table[count].Oper << "	" << table[count].Oper_int << endl;
		}
	}
}


void Instruct_Tab::Create_Instruct(const char *Oper, int Oper_int) {
	
	Instruct_use i;
	i.Oper_int = Oper_int;
	strcpy_s(i.Oper,Oper);
	table.push_back(i);
	counter_index++;}

void While_Jump(int jump_addr) {
   
	int addr = Pop_Stk.top();
	Push_Table.table[addr].Oper_int = jump_addr;
	 Pop_Stk.pop();
}



bool Symb_Table::Ident_loc(const char * Id_counter)
{
	bool found = false;

	for ( int count = 0; count < table.size(); count++)
		if (strcmp(table[count].Id_counter,Id_counter) == 0)
			found = true;
	return found;
}
/***************************************************************
This function get the adress from the table
******************************************************************/
int Symb_Table::Addre_loc(const char * Id_counter)
{
	int addr = -999;

	
	for ( int count = 0; count < table.size(); count++ ) 
		if (strcmp(table[count].Id_counter, Id_counter) == 0)
			addr = table[count].Address_Sym_Tab;

	return addr;
}

/***************************************************************
This function will put the identifier into the symbol tabel for
later usage
******************************************************************/
void Symb_Table::Push(const char * Id_counter, Asm_Data_T & type) {
	if (Ident_loc(Id_counter)) {
		//cout << "The identifier " << Id_counter << "\" has already been declared" << endl;
	}
	else {
		Sym_Tab s;
		s.Address_Sym_Tab = Mem_Add_Locat_count++;
		strcpy_s(s.Id_counter, Id_counter);
		s.type = type;
		table.push_back(s);}
	}
/***************************************************************
This function will finds the identifier from the symbol tabel for
usage
******************************************************************/
int Symb_Table::Find_Identity(const char *Id_counter) {
	int type = 0;
	for ( unsigned int i = 0; i < table.size(); i++ ) {
		if (strcmp(table[i].Id_counter, Id_counter) == 0)
			type = table[i].type;
	}
	return type;
	
}


Token Lexical::nextToken()
{
	bool check_stab = false;
	int running = 0, cols = 0, FSM_STAT = 0;
	char c;

	Token ptr;
	ptr.lexeme[0] = '\0';
	ptr.token = Unknown;


	const unsigned int table_stat[18][22] = 

	{1,  2,  7,  11, 11, 11, 8,  12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 13, 0,
	1,  1,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
	5,  2,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  14, 5,
	1,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	6,  6,  6,  6,  6,  9,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
	9,  9,  9,  9,  9,  10, 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 
	9,  9,  9,  9,  9,  9,  0,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
	6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6, 
	6,  6,  6,  6,  6,  6,  6,  11, 6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  11, 6,  6,  6,
	7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
	15, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
	
	while ( !input.eof() && !check_stab && running < 1000) {
		c = input.get();
		
		if (isalpha(c))
			cols = 0;
		else if (isdigit(c))
			cols = 1;
		else if (c == '_')
			cols = 2;
		else if (c == '+')
			cols = 3;
		else if (c == '-')
			cols = 4;
		else if (c == '*')
			cols = 5;
		else if (c == '/')
			cols = 6;
		else if (c == '=')
			cols = 7;
		else if (c == '>')
			cols = 8;
		else if (c == '<')
			cols = 9;
		else if (c == '(')
			cols = 10;
		else if (c == ')')
			cols = 11;
		else if (c == '{')
			cols = 12;
		else if (c == '}')
			cols = 13;
		else if (c == '[')
			cols = 14;
		else if (c == ']')
			cols = 15;
		else if (c == ';')
			cols = 16;
		else if (c == ',')
			cols = 17;
		else if (c == '#')
			cols = 18;
		else if (c == ':')
			cols = 19;
		else if (c == '.')
			cols = 20;
		else 
			cols = 21;


		FSM_STAT = table_stat[FSM_STAT][cols];		
		
		switch (FSM_STAT) {
			case 0:
				running = 0;
				break;
			case 4:
				ptr.lexeme[running] = '\0';
				ptr.token = Identifier;
				if (check_Keyword(ptr.lexeme))
					ptr.token = Keyword;

				if (c != '\n')
					input.unget();
				check_stab = true;
				break;
			case 5:
				ptr.token = Integer;

				if (c != '\n')
					input.unget();
				check_stab = true;
				break;
			case 6:
				ptr.token = Operator;

				if (c != '\n')
					input.unget();
				check_stab = true;
				break;
			case 7:
				ptr.token = Separator;

				if (c != '\n')
					input.unget();
				check_stab = true;
				break;
			case 15:
				ptr.token = Real;

				if (c != '\n')
					input.unget();
				check_stab = true;
				break;
			default:
				ptr.lexeme[running++] = c;
		}
	}

	ptr.line_int = b;
	if (c == '\n')
		b++;
	
	ptr.lexeme[running] = '\0';

	return ptr;

}



