#include<iostream>
#include<bits/stdc++.h>
#include <sstream>
using namespace std;
//TO DO:
// ADD SUPPORT FOR STRING and COMMENTS
class Lexer{
    set<string> keywords_list;
    set<char> operator_list;
    public:
    Lexer(){
        cout << " Building " << endl;
        string keywords_list_[] = {"auto",
                         "break",
                         "case",
                         "char",
                         "const",
                         "continue",
                         "default",
                         "do",
                         "double",
                         "else",
                         "enum",
                         "extern",
                         "float",
                         "for",
                         "goto",
                         "if",
                         "int",
                         "long",
                         "register",
                         "return",
                         "short",
                         "signed",
                         "sizeof",
                         "static",
                         "struct",
                         "switch",
                         "typedef",
                         "union",
                         "unsigned",
                         "void",
                         "volatile",
                         "while",
                         "print"
                         "\0"};

        char operator_list_[] = {'+',
                         '-',
                         '*',
                         '/',
                         '%',
                         '=',
                         '\0'};
    for(int i=0;keywords_list_[i]!="\0";i++) keywords_list.insert(keywords_list_[i]);
    for (int i = 0; operator_list_[i] != '\0'; i++)
        operator_list.insert(operator_list_[i]);

    cout << " Lexer Built " << endl;
    }
    
    bool isKeyword(string word){
        return keywords_list.count(word);
    }

    bool isOperator(char read){
        return operator_list.count(read);
    }
    void isIdentifier(string buffer,int line_no){
        if(buffer.length()==0) return;
        if(isKeyword(buffer)){
            cout << "{ " << line_no << " { " << buffer << " {Keyword}}}" << endl;
            return;
        }
        if(isLetters(buffer)){
            if (isFloat(buffer))
                cout << "{ "<<line_no<<" { "<<buffer << " {Float}}}" << endl;
            else if (isInt(buffer))
                cout << "{ " << line_no << " { "<< buffer << " {Int}}}" << endl;
            return ;
        }
        
        else{
            cout << "{ " << line_no << " { " << buffer << " {Identifier}}}" << endl;
        }
        
    }
    bool isFloat(string buffer)
    {
        istringstream iss(buffer);
        float f;
        iss >> noskipws >> f; 
        // Check the entire string was consumed and if either failbit or badbit is set
        return iss.eof() && !iss.fail();
    }

    bool isInt(string buffer){
        istringstream iss(buffer);
        int i;
        iss >> noskipws >> i;
        return iss.eof() && !iss.fail();
    }
    bool isLetters(string input)
    {
        for (int i = 0; i < input.size(); i++)
        {
            
            if (isalpha(input[i])) //If character is not A-Z
            {
                return false;
            }
        }
        //At this point, we have gone through every character and checked it.
        return true; //Return true since every character had to be A-Z
    }
};

int readFile(string filename){
    try{
        
    
        ifstream file(filename);
        if(!file.is_open()) throw -1;
        char read_char;
        string buffer="";
        Lexer lex_identifier;
        int line_no=1;
        while (!file.eof())
        {
            read_char=file.get();
            if(lex_identifier.isOperator(read_char)){
                cout << "{ " << line_no << " { " << read_char << " {Operator}}}" << endl;
                lex_identifier.isIdentifier(buffer,line_no);
                buffer="";
            }
            else if (isalnum(read_char)){
                buffer+=string(1,read_char);
            }
            else if(read_char==' ' || read_char=='\n'){
                lex_identifier.isIdentifier(buffer,line_no);
                buffer="";
            }
            if(read_char=='\n') line_no++;
        }
    }
    catch(int x){
        cout<<"File Not Opened"<<endl;
        return -1;
    }
    return 0;
}

int main(){
    string file_path="../Lexer/";
    string filename="test_lexer.txt";
    int test=readFile(file_path+filename);
    if(test){
        cout<<"An Error Occurred"<<endl;
    }
    return 0;
}
