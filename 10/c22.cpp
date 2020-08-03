#include<bits/stdc++.h>
using namespace std;
fstream fi,fo;
string nxt;
int spaces=0;
int check=0;

void compileclassVarDec();
void compilesubroutineDec();
void compileparameterlist();
void compilesubroutinebody();
void compilevarDec();
void compileIf();
void compileWhile();
void compileDo();
void compileLet();
void compileReturn();
void compileStatements();
void compileExpression();
void compileExpressionList();
void compileTerm();
void compileClass();
bool checksymbol(string);


string getToken(){
    string s;
    getline(fi,s);
    return s;
}

bool checkop(string s){
    if(checksymbol(s)){
        if(s.find("+")!=string::npos || s.find("-")!=string::npos || s.find("*")!=string::npos || s=="<symbol> / </symbol>" || s=="<symbol> &amp; </symbol>"||s.find("|")!=string::npos||s=="<symbol> &lt; </symbol>" ||s=="<symbol> &gt; </symbol>"||s.find("=")!=string::npos){
            return 1;
        }
    }
    return 0;
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


void compileclassVarDec(){
    printspaces();
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
        printspaces();
        fo<<"</classVarDec>\n";
        compileclassVarDec();
    }
    spaces-=2;
    if(spaces){
        printspaces();
        fo<<"</classVarDec>\n";
    }
    return;
}


void compilesubroutineDec(){
    if(nxt=="<symbol> } </symbol>")       //after arraytest
        return;
    printspaces();
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
    fo<<"</parameterList>"<<endl;
    if(nxt!="<symbol> ) </symbol>"){
        cout<<") not found"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;//nxt=')
    printspaces();
    fo<<"<subroutineBody>"<<endl;
    spaces+=2;
    compilesubroutinebody();
    spaces-=2;
    printspaces();
    //cout<<"aaaaaaaaaaaa"<<nxt<<endl;
    fo<<"</subroutineBody>"<<endl;
    spaces-=2;
    fo<<"</subroutineDec>\n";
    nxt=getToken();
    if(nxt=="<symbol> } </symbol>")
        return;
    compilesubroutineDec();
}


void compileparameterlist(){
    nxt=getToken();
    if(nxt=="<symbol> ) </symbol>")
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
    if(nxt!="<symbol> { </symbol>"){
        cout<<"{ not found in subroutine body"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;//nxt={
    compilevarDec();//do gettoken just after entering
    //nxt=let while if }
    printspaces();
    fo<<"<statements>\n";
    spaces+=2; 
    compileStatements();//do getToken just before return
    spaces-=2;
    printspaces();
    fo<<"</statements>\n";
   // cout<<"qqqqqqqqqqqqqqqqqqqq"<<nxt<<endl;
    if(nxt!="<symbol> } </symbol>"){
        cout<<"} not found "<<endl;
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
    spaces+=2;
    printspaces();
    fo<<"<letStatement>\n";
    spaces+=2;
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(!checkidentifier(nxt)){
        cout<<"wrong let statement"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt!="<symbol> = </symbol>" && nxt!="<symbol> [ </symbol>"){
        cout<<"= or [ not found in let statement"<<endl;
        return;
    }
    // printspaces();
    // fo<<nxt<<endl;// nxt is = or [
    if(nxt=="<symbol> [ </symbol>"){
        printspaces();
        fo<<nxt<<endl;
        compileExpression();//function returns with nxt=]
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
    compileExpression();//functionreturns with nxt = ;
    // spaces-=2;
    // printspaces();
    // fo<<"</expression>\n";
    cout<<"qqqqqqqqqqq"<<nxt<<endl;
    printspaces();
    fo<<nxt<<endl;///nxt is ;
    nxt=getToken();
    spaces-=2;
    printspaces();
    fo<<"</letStatement>"<<endl;
    spaces-=2;
    compileStatements();
}


void compileIf(){
    spaces+=2;
    printspaces();
    fo<<"<ifStatement>\n";
    spaces+=2;
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt!="<symbol> ( </symbol>"){
        cout<<"( not found in if "<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    compileExpression();//nxt will be ) after return
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
    if(nxt=="<keyword> else </keyword>"){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
        printspaces();
        fo<<nxt<<endl;
        printspaces();
        fo<<"<statements>"<<endl;
        spaces+=2;
        nxt=getToken();
        compileStatements();
        spaces-=2;
        printspaces();
        fo<<"</statements>"<<endl;
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
    }
    spaces-=2;
    printspaces();
    fo<<"</ifStatement>"<<endl;
    spaces-=2;
    compileStatements();
}


void compileWhile(){
    spaces+=2;
    printspaces();
    fo<<"<whileStatement>\n";
    spaces+=2;
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt!="<symbol> ( </symbol>"){
        cout<<"( not found in while\n";
        return;
    }
    printspaces();
    fo<<nxt<<endl;//nxt is (
    
    compileExpression();//nxt will be ) after return

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
    fo<<"</statements>\n";
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    spaces-=2;
        printspaces();
        fo<<"</whileStatement>"<<endl;
        spaces-=2;
    compileStatements();   
}


void compileDo(){
    spaces+=2;
    printspaces();
    fo<<"<doStatement>\n";
    spaces+=2;
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
        compileExpressionList();//nxt is ) upon return;
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
        //nxt=getToken();////new addition
        compileExpressionList();//nxt is ) upon return
        if(nxt!="<symbol> ) </symbol>"){
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
    spaces-=2;
    printspaces();
    fo<<"</doStatement>"<<endl;
    spaces-=2;
    compileStatements();
}


void compileReturn(){
    spaces+=2;
    printspaces();
    fo<<"<returnStatement>\n";
    spaces+=2;
    printspaces();
    fo<<nxt<<endl;
    //nxt=getToken();
    // if(nxt=="<symbol> ; </symbol>"){
    //     printspaces();
    //     fo<<nxt<<endl;
    //     spaces-=2;
    //     printspaces();
    //     fo<<"</returnStatement>"<<endl;
    //     nxt=getToken();
    //     return;
    // }
    nxt=getToken();
    if(nxt!="<symbol> ; </symbol>"){
        check=1;
    
    compileExpression();
    }
    if(nxt!="<symbol> ; </symbol>"){
        cout<<"; not found in return"<<endl;
        return;
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    spaces-=2;
    printspaces();
    fo<<"</returnStatement>"<<endl;
    spaces-=2;
    compileStatements();
}


void compileStatements(){
    if(nxt=="<symbol> } </symbol>"){
        //nxt=getToken();
        return;
    }
    if(nxt!="<keyword> let </keyword>" && nxt!="<keyword> if </keyword>" && nxt!="<keyword> while </keyword>" && nxt!="<keyword> do </keyword>" && nxt!="<keyword> return </keyword>"){
        cout<<"wrong satements"<<endl;
        return;
    }
    if(nxt=="<keyword> let </keyword>"){
        compileLet();
        
    }
    if(nxt=="<keyword> if </keyword>"){
        
        compileIf();
        
    }
    if(nxt=="<keyword> while </keyword>"){
        
        
        compileWhile();
        
    }
    if(nxt=="<keyword> do </keyword>"){
        
        compileDo();
        
    }
    if(nxt=="<keyword> return </keyword>"){
        
        compileReturn();
        
    }
    // gettoken just before return in each and call compile statements
}


void compileExpression(){
    printspaces();
    fo<<"<expression>\n";
    compileTerm();
    if(checkop(nxt)){
        printspaces();
        fo<<nxt<<endl;
        compileTerm();
    }
    spaces-=2;
    printspaces();
    fo<<"</expression>\n";

}


void compileExpressionList(){
    printspaces();
    fo<<"<expressionList>\n";
    spaces+=2;
    nxt=getToken();
    if(nxt=="<symbol> ) </symbol>"){
        spaces-=2;
        printspaces();
        fo<<"</expressionList>\n";
        return;
    }
    check=1;
    compileExpression();
    while(nxt=="<symbol> , </symbol>"){
        printspaces();
        fo<<nxt<<endl;
        compileExpression();
    }
    spaces-=2;
    printspaces();
    fo<<"</expressionList>\n";
    return;

    
}


void compileTerm(){
    if(check==0)
        nxt=getToken();
    else if(check==1)
        check=0;
    printspaces();
    fo<<"<term>\n";
    spaces+=2;
    if(nxt.find("-")!=string::npos || nxt.find("~")!=string::npos){
        printspaces();
        fo<<nxt<<endl;
        // spaces-=2;
        // printspaces();
        // fo<<"</term>\n";
        compileTerm();
    }
    else if(checkintegerconstant(nxt)){
        printspaces();
        cout<<nxt<<endl;
        fo<<nxt<<endl;
        nxt=getToken();
        // spaces-=2;
        // printspaces();
        // fo<<"</term>\n";
        //compileTerm();
    }
    else if(checkstringconstant(nxt)){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
        // spaces-=2;
        // printspaces();
        // fo<<"</term>\n";
        //compileTerm();
    }
    else if(checkkeyword(nxt) && (nxt.find("true")!=string::npos || nxt.find("false")!=string::npos || nxt.find("null")!=string::npos || nxt.find("this")!=string::npos)){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
        // spaces-=2;
        // printspaces();
        // fo<<"</term>\n";
        //compileTerm();
    }
    else if(checkidentifier(nxt)){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
        // if(checkop(nxt)){
        //     printspaces();
        //     fo<<nxt<<endl;
        //     compileTerm();
        // }
        if(nxt=="<symbol> [ </symbol>"){
            printspaces();
            fo<<nxt<<endl;
            compileExpression();//nxt is ] upon return
            printspaces();
            fo<<nxt<<endl;
            nxt=getToken();
            // spaces-=2;
            // printspaces();
            // fo<<"</term>\n";
            //compileTerm();
        }
        else{
            if(nxt=="<symbol> ( </symbol>"){
                printspaces();
                fo<<nxt<<endl;
                compileExpressionList();//nxt is ) upon return
                if(nxt!="<symbol> ) </symbol>"){
                    cout<<") not found in subroutine of statement\n";
                    return;
                }
                printspaces();
                fo<<nxt<<endl;
                //nxt=getToken();//nxt is ;
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
                compileExpressionList();//nxt is ) upon return
                if(nxt!="<symbol> ) </symbol>"){
                    cout<<") not found in subroutine of do statement\n";
                    return;
                }
                printspaces();
                fo<<nxt<<endl;
                nxt=getToken();
            }
        }
    }
    else if(nxt=="<symbol> ( </symbol>"){//jkjjkghjgfd
        printspaces();
        fo<<nxt<<endl;
        compileExpression();//nxt is ) upon return
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
    }
    spaces-=2;
    printspaces();
    fo<<"</term>\n";    
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
    if(nxt.find("static")!=string::npos || nxt.find("field")!=string::npos){
        //dont change spaces in compileclassvar dec and finally do gettoken just beofre return in it
        compileclassVarDec();
    }
    if(nxt.find("constructor")!=string::npos || nxt.find("function")!=string::npos||nxt.find("method")!=string::npos){//gettoke just before return and dont change spaces
        compilesubroutineDec();
    }
    if(nxt!="<symbol> } </symbol>"){
        cout<<"} not found  "<<endl;
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
