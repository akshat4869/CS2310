#include<bits/stdc++.h>
using namespace std;
fstream fi,fo;
string nxt;
int spaces=0;

string getToken(){
    string s;
    getline(fi,s);
    return s;
}


void printspaces(){
    for(int i=0;i<spaces;i++){
        fo<<' ';
    }
    return;
}


bool checkidentifier(string s){
    if(s.substr(1,10)=="identifier")
        return 1;
    return 0;
}


bool checkkeyword(string s){
    if(s.substr(1,7)=="keyword")
        return 1;
    return 0;
}


bool checkintegerconstant(string s){
    if(s.substr(1,15)=="integerConstant")
        return 1;
    return 0;
}


bool checkstringconstant(string s){
    if(s.substr(1,14)=="stringConstant")
        return 1;
    return 0;
}


bool checksymbol(string s){
    if(s.substr(1,6)=="symbol")
        return 1;
    return 0;
}



bool checkintegerconstant(string s){
    if(s.substr(1,10)=="integerConstant")
        return 1;
    return 0;
}



void compileclassVarDec(){
    fo<<"<classVarDec>\n";
    spaces+=2;
    printspaces();
    fo<<nxt<<endl;//nxt=static or field
    nxt=getToken();
    if(!checkidentifier(nxt) && !checkkeyword(nxt)){
        cout<<"class variable type not found"<<endl;
        return ;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(!checkidentifier(nxt)){
        cout<<"varname not found"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt=="<symbol> , </symbol>"){
        while(nxt=="<symbol> , </symbol>"){
            printspaces();
            fo<<nxt<<endl;
            nxt=getToken();
            if(!checkidentifier(nxt)){
                cout<<"varname not found"<<endl;
                return;
            }
            printspaces();
            fo<<nxt<<endl;
            nxt=getToken();
        }
    }
    if(nxt=="<symbol> ; </symbol>"){
        printspaces();
        fo<<nxt<<endl;
    }
    else{
        cout<<"; is missing"<<endl;
        return;
    }
    nxt=getToken();
    if(nxt.find("static")!=string::npos || nxt.find("field")!=string::npos){
        spaces-=2;
        fo<<"</classVarDec>\n";
        compileclassVarDec();
    }
    spaces-=2;
    fo<<"</classVarDec>\n";
    return;
}


void compilesubroutinDec(){
    
    if(nxt=="<symbol> } </symbol>")
        return;
    fo<<"<subroutineDec>\n";
    spaces+=2;
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(!checkidentifier(nxt) && !checkkeyword(nxt)){
        cout<<" subroutine type not found"<<endl;
        return ;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(!checkidentifier(nxt)){
        cout<<"subroutine name not found"<<endl;
        return ;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt!="<symbol> ( </symbol>"){
        cout<<"( not found"<<endl;
        return ;
    }
    printspaces();
    fo<<nxt<<endl;// nxt='('
    printspaces();
    fo<<"<parameterList>"<<endl;
    spaces+=2;
    compileparameterlist(); //do getToken just before return nxt should be )
    spaces-=2;
    printspaces();
    fo<<"<parameterList>"<<endl;
    if(nxt!="<symbol> ) </symbol>"){
        cout<<") not found"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;//nxt=')
    printspaces();
    fo<<"<subroutineBody>"<<endl;
    spaces+=2;
    compilesubroutineBody();
    spaces-=2;
    printspaces();
    fo<<"</subroutineBody>"<<endl;
    nxt=getToken();
    spaces-=2;
    fo<<"</subroutineDec>\n";
    compilesubroutineDec();
}


void compileparameterist(){
    nxt=getToken();
    if(nxt==')')
        return;
    if(!checkkeyword(nxt) && !checkidentifier(nxt)){
        cout<<"var type not found in parameter list"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(!checkidentifier(nxt)){
        cout<<"var name not found in parameter list"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    while(nxt=="<symbol> , </symbol>"){
        printspaces();
        fo<<nxt<<endl;//nxt=,
        nxt=getToken();//nxt=type
        if(!checkkeyword(nxt) && !checkidentifier(nxt)){
            cout<<"var type not found in parameter list"<<endl;
            return;
        }
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();//nxt=varname
        if(!checkidentifier(nxt)){
            cout<<"var name not found in parameter list"<<endl;
            return;
        }
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();//nxt==,or )
    }
    return; 
}    


void compilesubroutinebody(){
    nxt=getToken();//nxt={
    if(nxt!='{'){
        cout<<"{ not found in subroutine body"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;//nxt={
    compileVarDec();//do gettoken just after entering
    //nxt=let while if }
    printspaces();
    fo<<"<statements>\n";
    spaces+=2; 
    compileStatements();//do getToken just before return
    spaces-=2;
    fo<<"</statements>\n";
    if(nxt!='}'){
        cout<<"} not found"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    return;
}


void compilevarDec(){
    nxt=getToken();
    if(nxt!="<keyword> var </keyword>")
        return;
    printspaces();
    fo<<"<varDec>"<<endl;
    spaces+=2;
    printspaces();
    fo<<nxt<<endl;//nxt=var
    nxt=getToken();
    if(!checkidentifier(nxt) && !checkkeyword(nxt)){
        cout<<"subroutine var dec type not found"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();//nxt=var name
    if(!checkidentifier(nxt)){
        cout<<"varname not found"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();//nxt =,or ;
    if(nxt=="<symbol> , </symbol>"){
        while(nxt=="<symbol> , </symbol>"){
            printspaces();
            fo<<nxt<<endl;
            nxt=getToken();
            if(!checkidentifier(nxt)){
                cout<<"varname not found"<<endl;
                return;
            }
            printspaces();
            fo<<nxt<<endl;
            nxt=getToken();
        }
    }
    if(nxt=="<symbol> ; </symbol>"){
        printspaces();
        fo<<nxt<<endl;
    }
    else{
        cout<<"; is missing"<<endl;
        return;
    }
    spaces-=2;
    printspaces();
    fo<<"</varDec>\n";
    compilevarDec();
}


void compileLet(){
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(!chekidentifier(nxt)){
        cout<<"wrong let statement"<<endl;
        return;
    }
    printspaces();
    fo<nxt<<endl;
    nxt=getToken();
    if(nxt!="<symbol> = </symbol>" && nxt!="<symbol> [ </symbol>"){
        cout<<"= or [ not found in let statement"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;// nxt is = or [
    if(nxt=="<symbol> [ </symbol>"){
        printspaces();
        fo<<"<expression>\n";
        spaces+=2;
        compileExpression();//function returns with nxt=]
        spaces-=2;
        printspaces();
        fo<<"</expression>\n";
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
    }
    if(nxt!="<symbol> = </symbol>"){
        cout<<"= not found in let statement"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    printspaces();
    fo<<"<expression>\n";
    spaces+=2;
    compileExpression();//functionreturns with nxt=;
    spaces-=2;
    printspaces();
    fo<<"</expression>\n";
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    compileStatements();
}


void compileIf(){
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt!="<symbol> ( </symbol>"){
        cout<<"( not found in if "<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    printspaces();
    fo<<"<expression>"<<endl;
    spaces+=2;
    compileExpression();//nxt will be ) after return
    spaces-=2;
    printspaces();
    fo<<"</expression>"<<endl;
    if(nxt!="<symbol> ) </symbol>"){
        cout<<") not found in if "<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt!="<symbol> { </symbol>"){
        cout<<"{ not found in if\n";
        return;
    }   
    printspaces();
    fo<<nxt<<endl;//nxt is {
    printspaces();
    fo<<"<statements>\n";
    spaces+=2;
    nxt=getToken();
    compileStatements();
    spaces-=2;
    printspaces();
    fo<<"</statements>\n";
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    compileStatements();
}


void commpileWhile(){
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt!="<symbol> ( </symbol>"){
        cout<<"( not found in while\n";
        return;
    }
    printspaces();
    fo<<nxt<<endl;//nxt is (
    printspaces();
    fo<<"<expression>"<<endl;
    spaces+=2;
    compileExpression();//nxt will be ) after return
    spaces-=2;
    printspaces();
    fo<<"</expression>"<<endl;
    if(nxt!="<symbol> ) </symbol>"){
        cout<<") not found in while"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt!="<symbol> { </symbol>"){
        cout<<"{ not found in while\n";
        return;
    }   
    printspaces();
    fo<<nxt<<endl;//nxt is {
    printspaces();
    fo<<"<statements>\n";
    spaces+=2;
    nxt=getToken();
    compileStatements();
    spaces-=2;
    printspaces();
    fo<<"<statements>\n";
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    compileStatements();   
}


void compileDo(){
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();////////////
    if(!checkidentifier(nxt)){
        cout<<"subroutine name not found in do\n";
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt=="<symbol> ( </symbol>"){
        printspaces();
        fo<<nxt<<endl;
        printspaces();
        fo<<"<expressionList>\n";
        spaces+=2;
        compileExpressionList();//nxt is ) upon return
        spaces-=2;
        printspaces();
        fo<<"</expressionList>\n";
        if(nxt!="<symbol> ) </symbol>"){
            cout<<") not found in subroutine of do statement\n";
            return;
        }
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();//nxt is ;
    }
    else if(nxt=="<symbol> . </symbol>"){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
        if(!checkidentifier(nxt)){
            cout<<"subroutine name not foound in do subroutine call\n";
            return;
        }
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
        if(nxt!="<symbol> ( </symbol>"){
            cout<<"( not found in do \n";
            return;
        }
        printspaces();
        fo<<nxt<<endl;
        printspaces();
        fo<<"<expressionList>\n";
        spaces+=2;
        compileExpressionList();//nxt is ) upon return
        spaces-=2;
        printspaces();
        fo<<"</expressionList>\n";
        if(nxt!="<symbol> ( </symbol>"){
            cout<<") not found in subroutine of do statement\n";
            return;
        }
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();//nxt is ;
    }
    if(nxt!="<symbol> ; </symbol>"){
        cout<<"; not found in do"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    compileStatements();
}


void compileReturn(){
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt=="<symbol> ; </symbol>")
        return;
    printspaces();
    fo<<"<expression>\n";
    spaces+=2;
    compileExpression();
    spaces-=2;
    printspaces();
    fo<<"</expression>"<<endl;
    if(nxt!="<symbol> ; </symbol>"){
        cout<<"; not found in return"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    compileStatements();
}


void compileStatements(){
    if(nxt=="<symbol> } </symbol>")
        return;
    if(nxt!="<keyword> let </keyword>" && nxt!="<keyword> if </keyword>" && nxt!="<keyword> while </keyword>" && nxt!="<keyword> do </keyword>" && nxt!="<keyword> return </keyword>"){
        cout<<"wrong satements"<,endl;
        return;
    }
    if(nxt=="<keyword> let </keyword>"){
        space+=2;
        printspaces();
        fo<<"<letstatement>\n";
        spaces+=2;
        compileLet();
        spaces-=2;
        printspaces();
        fo<<"</letstatements>"<<endl;
        spaces-=2;
    }
    if(nxt=="<keyword> if </keyword>"){
        space+=2;
        printspaces();
        fo<<"<ifstatement>\n";
        spaces+=2;
        compileIf();
        spaces-=2;
        printspaces();
        fo<<"</ifstatements>"<<endl;
        spaces-=2;
    }
    if(nxt=="<keyword> while </keyword>"){
        space+=2;
        printspaces();
        fo<<"<whilestatement>\n";
        spaces+=2;
        compileWhile();
        spaces-=2;
        printspaces();
        fo<<"</whilestatements>"<<endl;
        spaces-=2;
    }
    if(nxt=="<keyword> do </keyword>"){
        space+=2;
        printspaces();
        fo<<"<dostatement>\n";
        spaces+=2;
        compileDo();
        spaces-=2;
        printspaces();
        fo<<"</dostatements>"<<endl;
        spaces-=2;
    }
    if(nxt=="<keyword> return </keyword>"){
        space+=2;
        printspaces();
        fo<<"<returnstatement>\n";
        spaces+=2;
        compileReturn();
        spaces-=2;
        printspaces();
        fo<<"</statements>"<<endl;
        spaces-=2;
    }
    // gettoken just before return in each and call compile statements
}


void compileExpression(){
    if(checkop(nxt)){
        printspaces();
        fo<<nxt<<endl;
    }
    spaces+=2;
    compileTerm();
    spaces-=2;
}


void compileExpressionList(){
    nxt=getToken();
    if(nxt=="<symbol> ) </symbol>"){
        return;
    }
    printspaces();
    fo<<"<expression>\n";
    spaces+=2;
    compileExpression();
    spaces-=2;
    printspaces();
    fo<<"<expression>\n";
}


void compileTerm(){
    nxt=getToken();
    if(nxt=="<symbol> ) </symbol>" || nxt=="<symbol> ] </symbol>" || nxt=="<symbol> ; </symbol>" || nxt=="<symbol> , </symbol>" ){
        spaces-=2;
        printspaces();
        fo<<"</term>\n";
        if(nxt=="<symbol> , </symbol>" ){
            spaces-=2;
            printspaces();
            fo<<"</expression>\n";
            compileExpressionList();
        }
        return;
    }
    else if(checkop(nxt)){
        compileExpression();
    }
    printspaces();
    fo<<"<term>\n";
    spaces+=2;
    if(nxt.find("-")!=string::npos || nxt.find("~")!=string::npos){
        printspaces();
        fo<<nxt<<endl;
        spaces-=2;
        printspaces();
        fo<<"</term>\n";
        compileTerm();
    }
    if(checkintegerconstant(nxt)){
        printspaces();
        fo<<nxt<<endl;
        spaces-=2;
        printspaces();
        fo<<"</term>\n";
        compileTerm();
    }
    if(checkstringconstant(nxt)){
        printspaces();
        fo<<nxt<<endl;
        spaces-=2;
        printspaces();
        fo<<"</term>\n";
        compileTerm();
    }
    if(checkkeyword(nxt) && (nxt.find("true")!=string::npos || nxt.find("false")!=string::npos || nxt.find("null")!=string::npos || nxt.find("this")!=string::npos)){
        printspaces();
        fo<<nxt<<endl;
        spaces-=2;
        printspaces();
        fo<<"</term>\n";
        compileTerm()
    }
    if(checkidentifier(nxt)){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
        if(nxt=="<symbol> [ </symbol>"){
            printspaces();
            fo<<nxt<<endl;
            printspaces();
            fo<<"<expression>\n";
            spaces+=2;
            compileExpression();//nxt is ] upon return
            spaces-=2;
            printspaces();
            fo<<"<expression>\n";
            printspaces();
            fo<<nxt<<endl;
            spaces-=2;
            printspaces();
            fo<<"</term>\n";
            compileterm();
        }
        else{
            if(nxt=="<symbol> ( </symbol>"){
                printspaces();
                fo<<nxt<<endl;
                printspaces();
                fo<<"<expressionList>\n";
                spaces+=2;
                compileExpressionList();//nxt is ) upon return
                spaces-=2;
                printspaces();
                fo<<"</expressionList>\n";
                if(nxt!="<symbol> ( </symbol>"){
                    cout<<") not found in subroutine of do statement\n";
                    return;
                }
                printspaces();
                fo<<nxt<<endl;
                nxt=getToken();//nxt is ;
            }
            else if(nxt=="<symbol> . </symbol>"){
                printspaces();
                fo<<nxt<<endl;
                nxt=getToken();
                if(!checkidentifier(nxt)){
                    cout<<"subroutine name not foound in do subroutine call\n";
                    return;
                }
                printspaces();
                fo<<nxt<<endl;
                nxt=getToken();
                if(nxt!="<symbol> ( </symbol>"){
                    cout<<"( not found in do \n";
                    return;
                }
                printspaces();
                fo<<nxt<<endl;
                printspaces();
                fo<<"<expressionList>\n";
                spaces+=2;
                compileExpressionList();//nxt is ) upon return
                spaces-=2;
                printspaces();
                fo<<"</expressionList>\n";
                if(nxt!="<symbol> ( </symbol>"){
                    cout<<") not found in subroutine of do statement\n";
                    return;
                }
                printspaces();
                fo<<nxt<<endl;
            }
            spaces-=2;
            printspaces();
            fo<<"</term>\n";
            compileTerm();
        }
    }
    if(nxt=="<symbol> ( </symbol>"){//jkjjkghjgfd
        printspaces();
        fo<<nxt<<endl;
        printspaces();
        fo<<"<expression>\n";
        spaces+=2;
        compileExpression();//nxt is ) upon return
        spaces-=2;
        printspaces();
        fo<<"</expression>\n";
        printspaces();
        fo<<nxt<<endl;
    }


    
}


void compileClass(){
    nxt=getToken();
    if(nxt!="<keyword> class </keyword>"){
        cout<<"keyword class not found"<<endl;
        return;
    }
    printspaces();
    fo<<"<class>\n";
    spaces+=2;
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(!checkidentifier(nxt)){
        cout<<"classname not found"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt!="<symbol> { </symbol>"){
        cout<<"{ not found"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt.find("static")!=string::npos || nxt.find("field")!=string::npos){//dont change spaces in compileclassvar dec and finally do gettoken just beofre return in it
        compileclassVarDec();
    }
    if(nxt.find("constructor")!=string::npos || nxt.find("function")!=string::npos||nxt.find("method")!=string::npos){//gettoke just before return and dont change spaces
        compilesubroutineDec();
    }
    if(nxt!="<symbol> } </symbol>"){
        cout<<"} not found "<<endl;
        return ;
    }
    fo<<nxt<<endl;
    spaces-=2;
    printspaces();
    fo<<"</class>";
}


int main(int argc, char**argv){
    fi.open(argv[1]);
    fo.open(argv[2],ios::out);
    string line;
    getline(fi,line);
    if(line!="<tokens>"){
        cout<<"expected <tokens> not found"<<endl;
        return 0;
    }
    compileClass();

    

    return 0;

}
