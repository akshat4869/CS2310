#include<bits/stdc++.h>
using namespace std;
fstream fi,fo,ferr;
string nxt;
int spaces=0;
int check=0;
string filename;
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
bool checkidentifier(string);
bool checkkeyword(string);
bool checkstringconstant(string);
bool checkintegerconstant(string);
bool checktype(string s){
    if(s=="<keyword> int </keyword>" || s=="<keyword> char </keyword>" || s=="<keyword> boolean </keyword>")
        return 1;
    return 0;
}
bool checktype2(string s){
    if(s=="<keyword> int </keyword>" || s=="<keyword> char </keyword>" || s=="<keyword> boolean </keyword>" || s=="<keyword> void </keyword>")
        return 1;
    return 0;
}
string split(string s){
    int i;
    for(i=0;i<s.size()-3;i++){
        if(s[i]=='>')
            break;
    }
    int j;
    for(j=s.length()-1;j>0;j--){
        if(s[j]=='<')
            break;
    }
    s=s.substr(i+2,j-i-3);
    return s;
}
void error(string type, string s){//s is actually middle thing
    if(type=="symbol" && !checksymbol(nxt)){
        ferr.open(filename+".err",ios::out);
        ferr<<"ERROR: Expecting <symbol> but "<<split(nxt)<<endl;
        exit(-1);
    }
    if(type=="identifier" && !checkidentifier(nxt)){
        
        ferr.open(filename+".err",ios::out);
        ferr<<"ERROR: Expecting <identifier> but "<<split(nxt)<<endl;
        exit(-1);
    }
    if(type=="keyword" && !checkkeyword(nxt)){
        
        ferr.open(filename+".err",ios::out);
        ferr<<"ERROR: Expecting <keyword> but "<<split(nxt)<<endl;
        exit(-1);
    }
    if(type=="stringconstant" && !checkstringconstant(nxt)){
        
        ferr.open(filename+".err",ios::out);
        ferr<<"ERROR: Expecting <stringconstant> but "<<split(nxt)<<endl;
        exit(-1);
    }
    if(type=="integerconstant" && !checkintegerconstant(nxt)){
        
        ferr.open(filename+".err",ios::out);
        ferr<<"ERROR: Expecting <integerconstant> but "<<split(nxt)<<endl;
        exit(-1);
    }
    //type mismatch ends here
    string s2=split(nxt);
    if(s2!=s){
        ferr.open(filename+".err",ios::out);
        ferr<<s2<<endl;
        exit(-1);
    }
}

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
        ferr.open(filename+".err",ios::out);
        ferr<<"ERROR: <TYPE> expected in class var dec" <<endl;
        exit(-1);
    }
    if(!checktype(nxt) && checkkeyword(nxt)){
        ferr.open(filename+".err",ios::out);
        ferr<<split(nxt)<<endl;
        exit(-1);
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    error("identifier",split(nxt));
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    while(nxt=="<symbol> , </symbol>"){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
        error("identifier",split(nxt));
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
    }
    if(nxt=="<symbol> ; </symbol>"){
        printspaces();
        fo<<nxt<<endl;
    }
    else{
        error("symbol",";");
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
    if(spaces>0){
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
        ferr.open(filename+".err",ios::out);
        ferr<<"ERROR: <TYPE> expected in subroutine dec" <<endl;
        exit(-1);
    }
    if(!checktype2(nxt) && checkkeyword(nxt)){
        ferr.open(filename+".err",ios::out);
        ferr<<split(nxt)<<endl;
        exit(-1);
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    error("identifier",split(nxt));
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    error("symbol","(");
    printspaces();
    fo<<nxt<<endl;// nxt='('
    printspaces();
    fo<<"<parameterList>"<<endl;
    spaces+=2;
    compileparameterlist(); //do getToken just before return nxt should be )
    spaces-=2;
    printspaces();
    fo<<"</parameterList>"<<endl;
    error("symbol",")");
    printspaces();
    fo<<nxt<<endl;//nxt=')
    printspaces();
    fo<<"<subroutineBody>"<<endl;
    spaces+=2;
    compilesubroutinebody();
    spaces-=2;
    printspaces();
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
        ferr.open(filename+".err",ios::out);
        ferr<<"ERROR: <TYPE> expected in parameter list" <<endl;
        exit(-1);
    }
    if(!checktype(nxt) && checkkeyword(nxt)){
        ferr.open(filename+".err",ios::out);
        ferr<<split(nxt)<<endl;
        exit(-1);
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    error("identifier",split(nxt));
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    while(nxt=="<symbol> , </symbol>"){
        printspaces();
        fo<<nxt<<endl;//nxt=,
        nxt=getToken();//nxt=type
        if(!checkkeyword(nxt) && !checkidentifier(nxt)){
            ferr.open(filename+".err",ios::out);
            ferr<<"ERROR: <TYPE> expected in parameter list" <<endl;
            exit(-1);
        }
        if(!checktype(nxt) && checkkeyword(nxt)){
            ferr.open(filename+".err",ios::out);
            ferr<<split(nxt)<<endl;
            exit(-1);
        }
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();//nxt=varname
        error("identifier",split(nxt));
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();//nxt==,or )
    }
    return; 
}    


void compilesubroutinebody(){
    nxt=getToken();//nxt={
    error("symbol","{");
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
    error("symbol","}");
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
        ferr.open(filename+".err",ios::out);
        ferr<<"ERROR: <TYPE> expected in var dec" <<endl;
        exit(-1);
    }
    if(!checktype(nxt) && checkkeyword(nxt)){
        ferr.open(filename+".err",ios::out);
        ferr<<split(nxt)<<endl;
        exit(-1);
    }
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();//nxt=var name
    error("identifier",split(nxt));
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();//nxt =,or ;
    while(nxt=="<symbol> , </symbol>"){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
        error("identifier",split(nxt));
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
    }
    if(nxt=="<symbol> ; </symbol>"){
        printspaces();
        fo<<nxt<<endl;
    }
    else{
        error("symbol",";");
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
    error("identifier",split(nxt));
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    if(nxt!="<symbol> = </symbol>" && nxt!="<symbol> [ </symbol>"){
        if(!checksymbol(nxt)){
            ferr.open(filename+".err",ios::out);
            ferr<<"ERROR: Expecting <symbol> but "<<split(nxt)<<endl;

            exit(-1);
        }
        if(split(nxt)!="=" && split(nxt)!="["){
            ferr.open(filename+".err",ios::out);
            ferr<<split(nxt)<<endl;
            exit(-1);
        }
    }
    // fo<<nxt<<endl;// nxt is = or [
    if(nxt=="<symbol> [ </symbol>"){
        printspaces();
        fo<<nxt<<endl;
        compileExpression();//function returns with nxt=]
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
    }
    error("symbol","=");
    printspaces();
    fo<<nxt<<endl;
    compileExpression();//functionreturns with nxt = ;
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
    error("symbol","(");
    printspaces();
    fo<<nxt<<endl;
    compileExpression();//nxt will be ) after return
    error("symbol",")");
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    error("symbol","{");
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
    error("symbol","(");
    printspaces();
    fo<<nxt<<endl;//nxt is (
    compileExpression();//nxt will be ) after return
    error("symbol",")");
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
    error("symbol","{");
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
    error("identifier",split(nxt));
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();
       
    
    if(nxt=="<symbol> ( </symbol>"){
        printspaces();
        fo<<nxt<<endl;
        compileExpressionList();//nxt is ) upon return;
        error("symbol",")");
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();//nxt is ;
    }
    else if(nxt=="<symbol> . </symbol>"){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
        error("identifier",split(nxt));
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
        error("symbol","(");
        printspaces();
        fo<<nxt<<endl;
        compileExpressionList();//nxt is ) upon return
        error("symbol",")");
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();//nxt is ;
    }
    error("symbol",";");
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
    nxt=getToken();
    if(nxt!="<symbol> ; </symbol>"){
        check=1;
    
    compileExpression();
    }
    error("symbol",";");
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
        return;
    }
    if(nxt!="<keyword> let </keyword>" && nxt!="<keyword> if </keyword>" && nxt!="<keyword> while </keyword>" && nxt!="<keyword> do </keyword>" && nxt!="<keyword> return </keyword>"){
        if(!checkkeyword(nxt)){
            ferr.open(filename+".err",ios::out);
            ferr<<"ERROR: Expecting <keyword> but "<<split(nxt)<<endl;
            exit(-1);
        }
        ferr.open(filename+".err",ios::out);
        ferr<<split(nxt)<<endl;
        exit(-1);
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
        compileTerm();
    }
    else if(checkintegerconstant(nxt)){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
    }
    else if(checkstringconstant(nxt)){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
    }
    else if(checkkeyword(nxt) && (nxt.find("true")!=string::npos || nxt.find("false")!=string::npos || nxt.find("null")!=string::npos || nxt.find("this")!=string::npos)){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();
    }
    else if(checkidentifier(nxt)){
        printspaces();
        fo<<nxt<<endl;
        nxt=getToken();

        if(nxt=="<symbol> [ </symbol>"){
            printspaces();
            fo<<nxt<<endl;
            compileExpression();//nxt is ] upon return
            printspaces();
            fo<<nxt<<endl;
            nxt=getToken();
        }
        else{    
            if(nxt=="<symbol> ( </symbol>"){
                printspaces();
                fo<<nxt<<endl;
                compileExpressionList();//nxt is ) upon return
                error("symbol",")");
                printspaces();
                fo<<nxt<<endl;
            }
            else if(nxt=="<symbol> . </symbol>"){
                printspaces();
                fo<<nxt<<endl;
                nxt=getToken();

                error("identifier",split(nxt));
                printspaces();
                fo<<nxt<<endl;
                nxt=getToken();

                error("symbol","(");
                printspaces();
                fo<<nxt<<endl;
                compileExpressionList();//nxt is ) upon return

                error("symbol",")");
                printspaces();
                fo<<nxt<<endl;
                nxt=getToken();
            }
            
        }
    }
    else if(nxt=="<symbol> ( </symbol>"){
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
    error("keyword","class");
    printspaces();
    fo<<"<class>\n";
    spaces+=2;
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();

    error("identifier",split(nxt));
    printspaces();
    fo<<nxt<<endl;
    nxt=getToken();

    error("symbol","{");
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

    error("symbol","}");
    fo<<nxt<<endl;
    spaces-=2;
    printspaces();
    fo<<"</class>";
}


int main(int argc, char**argv){
    for(int ii=2;ii<argc;ii++){
        filename=argv[ii];
        int x=filename.find(".");
        filename=filename.substr(0,x);
        fi.open(filename+"t.xml");
        fo.open(filename+".xml",ios::out);
        string line;
        getline(fi,line);
        if(line!="<tokens>"){
            ferr.open(filename+".err",ios::out);
            ferr<<"expected <tokens> not found"<<endl;
            exit(-1);
        }
        compileClass();
        spaces=0;check=0;
        filename.clear();
        fi.close();
        fo.close();
        ferr.close();
    }
    return 0;

}
