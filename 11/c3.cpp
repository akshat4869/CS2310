#include<bits/stdc++.h>
using namespace std;
string currsubroutinename;
string subroutinekind;
string subroutinetype;
string currclassname;
string nxt;
string filename;
int labelnum;
fstream fi,fo,ferr;
void compilestatements();
int compileexpressionlist();
void compileexpression();
struct node{
    string name;
    string kind;
    string type;
    int index;
};
class symboltable{
public:
    map<string,node>table;
    void startsubroutine(){
        table.clear();
    }
    int varcount(string ki){
        int i=0;
        for(auto itr=table.begin();itr!=table.end();itr++){
            if(itr->second.kind==ki)
                i++;
        }
        return i;
    }
    void define(string na,string ty,string ki){
        node temp;
        temp.name=na;
        temp.type=ty;
        temp.kind=ki;
        temp.index=varcount(ki);
        table[na]=temp;
    }
    string kindof(string na){
        auto itr=table.find(na);
        if (itr==table.end())
            return "NONE";
        else
            return itr->second.kind;
        
    }
    string TypeOf(string na){
        auto itr=table.find(na);
        if (itr==table.end())
            return "NONE";
        else
            return itr->second.type;
    }
    int indexof(string na){
        auto itr=table.find(na);
        if (itr==table.end())
            return -1;
        else
            return itr->second.index;
    }
}classsymboltable,subroutinesymboltable;
void gettoken(){
    getline(fi,nxt);
    int i;
    for(i=0;i<nxt.size();i++){
        if(nxt[i]!=' ')
            break;
    }
    nxt.erase(0,i);
    //cout<<nxt<<endl;
}
void split(){
    int i;
    for(i=0;i<nxt.size()-3;i++){
        if(nxt[i]=='>')
            break;
    }
    int j;
    for(j=nxt.length()-1;j>0;j--){
        if(nxt[j]=='<')
            break;
    }
    nxt=nxt.substr(i+2,j-i-3);
}
bool checkop(string s){
    if(s=="+"||s=="-"||s=="&amp;"||s=="|"||s=="&gt;"||s=="&lt;"||s=="="||s=="*"||s=="/")
        return 1;
    return 0;
}
bool checkunaryop(string s){
    if(s=="<symbol> - </symbol>"||s=="<symbol> ~ </symbol>")
        return 1;
    return 0;
}
void printop(string s){
    if(s=="+")
        fo<<"add"<<endl;
    if(s=="-")
        fo<<"sub"<<endl;
    if(s=="&amp;")
        fo<<"and"<<endl;
    if(s=="|")
        fo<<"or"<<endl;
    if(s=="&gt;")
        fo<<"gt"<<endl;
    if(s=="&lt;")
        fo<<"lt"<<endl;
    if(s=="=")
        fo<<"eq"<<endl;
    if(s=="*")
        fo<<"call Math.multiply 2"<<endl;
    if(s=="/")
        fo<<"call Math.divide 2"<<endl;    
}
bool checkintegerconstant(string s){
    if(s.substr(1,15)=="integerConstant")
        return 1;
    return 0;
}
bool checkkeyword(string s){
    if(s.substr(1,7)=="keyword")
        return 1;
    return 0;
}
bool checkkeywordconstant(string s){
    if(checkkeyword(s) && (s.find("true")!=string::npos || s.find("false")!=string::npos || s.find("null")!=string::npos || s.find("this")!=string::npos))
        return 1;
    return 0;
}
bool checkidentifier(string s){
    if(s.substr(1,10)=="identifier")
        return 1;
    return 0;
}
bool checkstringconstant(string s){
    if(s.substr(1,14)=="stringConstant")
        return 1;
    return 0;
}
void compilereturnstatement(){
    //cout<<nxt<<endl;
    gettoken();
    
    gettoken();
    //cout<<nxt<<endl;
    if(nxt=="<expression>"){
        compileexpression();
        fo<<"return"<<endl;
        gettoken();
        gettoken();
    }
    else{
        fo<<"push constant 0"<<endl;
        fo<<"return"<<endl;
        gettoken();
    }
   // gettoken();
    //cout<<nxt<<endl;
}
void compileterm(){
    gettoken();
    if(checkunaryop(nxt)){
        string op=nxt;
        gettoken();//nxt=<term>
        compileterm();
        gettoken();
        if(op=="<symbol> - </symbol>")
            fo<<"neg"<<endl;
        else if(op=="<symbol> ~ </symbol>")
            fo<<"not"<<endl;
    }
    else if(nxt=="<symbol> ( </symbol>"){
        gettoken();//nxt=<expr>
        compileexpression();
        gettoken();//nxt= )
        gettoken();//new addn
    }
    else if(checkintegerconstant(nxt)){
        
        split();
        fo<<"push constant "<<nxt<<endl;
        gettoken();
        
    }
    else if(checkkeywordconstant(nxt)){
        split();
        if(nxt=="true"){
            fo<<"push constant 0"<<endl;
            fo<<"not"<<endl;
        }
        else if(nxt=="false"){
            fo<<"push constant 0"<<endl;
        }
        else if(nxt=="null"){
            fo<<"push constant 0"<<endl;
        }
        else if(nxt=="this"){
            fo<<"push pointer 0"<<endl;
        }
        gettoken();
    }
    else if(checkidentifier(nxt)){
        split();
        string varname=nxt;
        gettoken();    split();//nxt= ( or [ or .
        
        auto itr1=classsymboltable.table.find(varname);
        auto itr2=subroutinesymboltable.table.find(varname);
        if(nxt!="(" && nxt!="[" && nxt!="."){//
            if(itr1==classsymboltable.table.end() && itr2==subroutinesymboltable.table.end()){
                ferr.open(filename+".err",ios::out);
                ferr<<"Declaration error: "<<varname<<" undeclared."<<endl;
                exit(-1);
            }
            else{
                if(itr2!=subroutinesymboltable.table.end()){
                    string kind=subroutinesymboltable.kindof(varname);
                    int index=subroutinesymboltable.indexof(varname);
                    if(kind=="field")
                        kind="this";
                    fo<<"push "<<kind<<" "<<index<<endl;
                }
                else if(itr1!=classsymboltable.table.end()){
                    string kind=classsymboltable.kindof(varname);
                    int index=classsymboltable.indexof(varname);
                    if(kind=="field")
                        kind="this";
                    fo<<"push "<<kind<<" "<<index<<endl;
                }
            } 
        }
        else {
            if(nxt=="["){//
                gettoken();
                compileexpression();
                gettoken();//nxt= ]
                if(itr1==classsymboltable.table.end() && itr2==subroutinesymboltable.table.end()){
                    ferr.open(filename+".err",ios::out);
                    ferr<<"Declaration error: "<<varname<<" undeclared."<<endl;
                    exit(-1);
                }
                if(itr2!=subroutinesymboltable.table.end()){
                    string kind=subroutinesymboltable.kindof(varname);
                    int index=subroutinesymboltable.indexof(varname);
                    if(kind=="field")
                        kind="this";
                    fo<<"push "<<kind<<" "<<index<<endl;
                }
                else if(itr1!=classsymboltable.table.end()){
                    string kind=classsymboltable.kindof(varname);
                    int index=classsymboltable.indexof(varname);
                    if(kind=="field")
                        kind="this";
                    fo<<"push "<<kind<<" "<<index<<endl;
                }
                fo<<"add\n";
                fo<<"pop pointer 1"<<endl;
                fo<<"push that 0"<<endl;
                gettoken();//new addn
            }
            //subroutine call
            else{
                string id1=varname;
                string id2;
                if(nxt=="."){
                    gettoken();     split();
                    id2=nxt;
                    if(itr1==classsymboltable.table.end() && itr2==subroutinesymboltable.table.end()){
                        //id1 is a classname
                    }
                    else{
                        if(itr2!=subroutinesymboltable.table.end()){
                            string kind=subroutinesymboltable.kindof(varname);
                            int index=subroutinesymboltable.indexof(varname);
                            if(kind=="field")
                                kind="this";
                            fo<<"push "<<kind<<" "<<index<<endl;
                        }
                        else if(itr1!=classsymboltable.table.end()){
                            string kind=classsymboltable.kindof(varname);
                            int index=classsymboltable.indexof(varname);
                            if(kind=="field")
                                kind="this";
                            fo<<"push "<<kind<<" "<<index<<endl;
                        }
                    }
                }
                else {
                    //id1 is a subroutine of current class
                    fo<<"push pointer 0"<<endl;
                }
                gettoken();
                gettoken();
                int np=compileexpressionlist();
                gettoken();
                gettoken();//nxt is ;
                //cout<<nxt<<endl;
                if(id2.size()!=0){
                    if(itr1==classsymboltable.table.end() && itr2==subroutinesymboltable.table.end()){
                        fo<<"call "<<id1<<"."<<id2<<" "<<np<<endl;
                    }
                    else{
                        string type;
                        if(itr2!=subroutinesymboltable.table.end()){
                            type=classsymboltable.TypeOf(id1);
                        }
                        else if(itr1!=classsymboltable.table.end()){
                            type=classsymboltable.TypeOf(id1);
                        }
                        fo<<"call "<<type<<"."<<id2<<" "<<np+1<<endl;
                    }
                }
                else{
                    fo<<"call "<<currclassname<<"."<<id1<<" "<<np+1<<endl;
                }  
                 
            }
            //cout<<nxt<<endl; 
        }
        //cout<<nxt<<endl; 
    }
    else if(checkstringconstant(nxt)){
        split();//nxt is thestring
        int strlen=nxt.length();
        fo<<"push constant "<<strlen<<endl;
        fo<<"call String.new 1"<<endl;
        for(int i=0;i<strlen;i++){
            fo<<"push constant "<<(int)nxt[i]<<endl;
            fo<<"call String.appendChar 2"<<endl;
        }
        gettoken();
    }
}
void compileexpression(){
    gettoken();//nxt may or may not be <term>
    if(nxt=="<term>"){
        compileterm();//nxt=</term>
        gettoken();     split();
        while(checkop(nxt)){
            string op=nxt;
            gettoken();//nxt=<term>
            compileterm();//nxt=</term>
            printop(op);
            gettoken();   split(); 
        }
        
    }

    
    //nxt should be </expr>
}
int compileexpressionlist(){
    int check=0;
    int np=0;
    gettoken();//nxt may or may not be <expr>
    if(nxt=="<expression>"){
        compileexpression();
        np++;
        gettoken();     split();
        while(nxt==","){
            check =1;
            gettoken();
            compileexpression();//nxt=</expr>
            np++;
            gettoken();    split();
        }
        
    }

    return np;
}
void compiledostatement(){
    gettoken();//nxt=do
    gettoken();     split();//nxt=<identifier>efhdb</id>
    string id1=nxt;
    string id2;
    gettoken();     split();
    if(nxt=="."){
        gettoken();      split();//nxt=<identifier>efhdb</id>
        id2=nxt;
        auto itr1=classsymboltable.table.find(id1);
        auto itr2=subroutinesymboltable.table.find(id1);
        if(itr1==classsymboltable.table.end() && itr2==subroutinesymboltable.table.end()){
            //id1 is a class name
            gettoken();
        }
        else {//
            //id1 is an object of a class
            string objectkind;
            int index;
            if(itr2!=subroutinesymboltable.table.end()){
                objectkind=subroutinesymboltable.kindof(id1);
                index=subroutinesymboltable.indexof(id1);
            }
            else if(itr1!=classsymboltable.table.end()){
                objectkind=classsymboltable.kindof(id1);
                index=classsymboltable.indexof(id1);
            }
            if(objectkind=="field")
                objectkind="this";
            fo<<"push "<<objectkind<<' '<<index<<endl;
            gettoken();
        }
    }
    else{
        //id1 is subroutine of current class
        fo<<"push pointer 0"<<endl;
    }
    //gettoken();
    gettoken();//nxt=<explist>
    int np=compileexpressionlist();
    //cout<<nxt<<endl; 
    gettoken();//nxt= )
    gettoken();
    if(id2.size()!=0){
        auto itr1=classsymboltable.table.find(id1);
        auto itr2=subroutinesymboltable.table.find(id1);
        if(itr1==classsymboltable.table.end() && itr2==subroutinesymboltable.table.end()){
            fo<<"call "<<id1<<"."<<id2<<" "<<np<<endl;
            fo<<"pop temp 0"<<endl;
        }
        else{
            string objectkind,objecttype;
            if(itr2!=subroutinesymboltable.table.end()){
                objectkind=subroutinesymboltable.kindof(id1);
                objecttype=subroutinesymboltable.TypeOf(id1);
            }
            else if(itr1!=classsymboltable.table.end()){
                objectkind=classsymboltable.kindof(id1);
                objecttype=classsymboltable.TypeOf(id1);
            }
            fo<<"call "<<objecttype<<"."<<id2<<" "<<np+1<<endl;
            fo<<"pop temp 0"<<endl;
        }
    }
    else{
        fo<<"call "<<currclassname<<"."<<id1<<" "<<np+1<<endl;
        fo<<"pop temp 0"<<endl;
    }
    gettoken();
    //cout<<nxt<<endl;
}
void compilewhilestatement(){
    gettoken();//nxt=while
    gettoken();//nxt=(
    gettoken();
    int tlabelnum=labelnum;
    labelnum+=2;
    fo<<"label "<<currclassname<<"."<<tlabelnum<<endl;
    compileexpression();//nxt=</expr>
    gettoken();//nxt= )
    fo<<"not\n";
    fo<<"if-goto "<<currclassname<<"."<<tlabelnum+1<<endl;
    gettoken();
    gettoken();//nxt=statements()
    compilestatements();
    gettoken();//nxt= }
    fo<<"goto "<<currclassname<<"."<<tlabelnum<<endl;
    fo<<"label "<<currclassname<<"."<<tlabelnum+1<<endl;
    gettoken();
}
void compileifstatement(){
    int tlabelnum=labelnum;
    labelnum+=2;
    gettoken();//nxt=if
    gettoken();//nxt=(
    gettoken();//nxt=<expr>
    compileexpression();//nxt=</expr>on return
    
    gettoken();
    gettoken();//nxt={
    
    fo<<"not"<<endl;
    fo<<"if-goto "<<currclassname<<"."<<tlabelnum<<endl;
    gettoken();
    compilestatements();
    gettoken();//nxt=}
    fo<<"goto "<<currclassname<<"."<<tlabelnum+1<<endl;
    fo<<"label "<<currclassname<<"."<<tlabelnum<<endl;
    gettoken();     split();//nxt=else or </if>
    if(nxt=="else"){
        gettoken();
        gettoken();
        compilestatements();
        gettoken();//nxt=}
        gettoken();//nxt=</if>
    }
    fo<<"label "<<currclassname<<"."<<tlabelnum+1<<endl;

}
void compileletstatement(){
    int check =0;
    gettoken();//nxt=let
    gettoken();     split();
    string varname=nxt;
    auto itr1=subroutinesymboltable.table.find(nxt);
    auto itr2=classsymboltable.table.find(nxt);
    if(itr1==subroutinesymboltable.table.end() && itr2==classsymboltable.table.end()){
        ferr.open(filename+".err",ios::out);
        ferr<<"Declaration error: "<<varname<<" undeclared."<<endl;
        exit(-1);
    }
    gettoken();     split();
    string kind;
    int index;
    if(itr1!=subroutinesymboltable.table.end()){
            kind=subroutinesymboltable.kindof(varname);
            index=subroutinesymboltable.indexof(varname);
        }
    else if(itr2!=classsymboltable.table.end()){
        kind=classsymboltable.kindof(varname);
        index=classsymboltable.indexof(varname);
    }
    if(nxt=="["){
        check=1;
        gettoken();//nxt=<expression>
        compileexpression();//nxt is </expression> on return
        gettoken();//nxt=]
        gettoken();//nxt= =
            //dump something//
        if(kind=="field")
            kind="this";
        fo<<"push "<<kind<<" "<<index<<endl;
        fo<<"add"<<endl;
    }
    //nxt is =
    gettoken();
    compileexpression();
    if(check==1){
        fo<<"pop temp 0"<<endl;
        fo<<"pop pointer 1"<<endl;
        fo<<"push temp 0"<<endl;
        fo<<"pop that 0"<<endl;
    }
    else{
        if(kind=="field")
            kind="this"; 
        fo<<"pop "<<kind<<" "<<index<<endl;
        //dump something//
    }
    gettoken();//nxt=;
    gettoken();

}
void compilestatements(){
    gettoken();
    while(nxt=="<letStatement>"||nxt=="<ifStatement>"||nxt=="<whileStatement>"||nxt=="<doStatement>"||nxt=="<returnStatement>"){
        if(nxt=="<letStatement>"){
            compileletstatement();
            gettoken();
        }
        if(nxt=="<ifStatement>"){
            compileifstatement();
            gettoken();
        }
        if(nxt=="<whileStatement>"){
            compilewhilestatement();
            gettoken();
        }
        if(nxt=="<doStatement>"){
            compiledostatement();
            gettoken();
        }
        if(nxt=="<returnStatement>"){
            compilereturnstatement();
            gettoken();
        }
    }

}
void compilevardec(){
    gettoken();
    gettoken();     split();
    string ty=nxt;
    gettoken();     split();
    string na=nxt;
    subroutinesymboltable.define(na,ty,"local");
    gettoken();     split();
    while(nxt==","){
        gettoken();     split();
        na=nxt;
        subroutinesymboltable.define(na,ty,"local");
        gettoken();     split();
    }
    //nxt=;
    gettoken();
}
void compilesubroutinebody(){
    gettoken();//nxt={
    gettoken();
    if(nxt=="<varDec>"){
        while(nxt=="<varDec>"){
            compilevardec();
            gettoken();
        }
    }
    int local_count=subroutinesymboltable.varcount("local");
    fo<<"function "<<currclassname<<'.'<<currsubroutinename<<' '<<local_count<<endl;
    if(subroutinekind=="constructor"){
        int field_count=classsymboltable.varcount("field");
        fo<<"push constant "<<field_count<<endl;
        fo<<"call Memory.alloc 1"<<endl;
        fo<<"pop pointer 0"<<endl;
    }
    else if(subroutinekind=="method"){
        fo<<"push argument 0"<<endl;
        fo<<"pop pointer 0"<<endl;
    }
    if(nxt=="<statements>"){
        compilestatements();//nxt=</statements>on return
    }
    gettoken();
    gettoken();
    //Ggettoken();
}
void compileparameterlist(){
    gettoken();
    if(nxt=="</parameterList>")
        return;
    string ty,na;
    //gettoken();     
    split();
    ty=nxt;
    gettoken();     split();
    na=nxt;
    subroutinesymboltable.define(na,ty,"argument");
    gettoken();     split();

    while(nxt==","){
        gettoken();     split();
        ty=nxt;
        gettoken();     split();
        na=nxt;
        subroutinesymboltable.define(na,ty,"argument");
        gettoken();     split();
    }
}
void compileclassvardec(){
    gettoken();    split();//nxt=static or field
    string ki=nxt;
    gettoken();    split();
    string ty=nxt;
    gettoken();    split();
    string na=nxt;
    auto itr=classsymboltable.table.find(na);
    if(itr!=classsymboltable.table.end()){
        ferr.open(filename+".err",ios::out);
        ferr<<"Declaration error: "<<na<<" already declared."<<endl;
        exit(-1);
    }
    classsymboltable.define(na,ty,ki);
    gettoken();     split();
    while(nxt==","){
        gettoken();    split();
        na=nxt;
        auto itr=classsymboltable.table.find(na);
        if(itr!=classsymboltable.table.end()){
            ferr.open(filename+".err",ios::out);
            ferr<<"Declaration error: "<<na<<" already declared."<<endl;
            exit(-1);
        }
        classsymboltable.define(na,ty,ki);
        gettoken();     split();
    }
    gettoken();
}
void compilesubroutinedec(){
    subroutinesymboltable.startsubroutine();
    gettoken();     split();
    subroutinekind=nxt;
    gettoken();     split();
    subroutinetype=nxt;
    gettoken();     split();
    currsubroutinename=nxt;
    if(subroutinekind=="method"){
        subroutinesymboltable.define("this",currclassname,"argument");
    }
    gettoken();
    gettoken();
    compileparameterlist();//nxt=</plist>on return
    //cout<<nxt<<endl;
    gettoken();gettoken();
    compilesubroutinebody();//nxt=</subroutinebody> on return
    gettoken();
    //cout<<nxt<<endl;
}
void compileclass(){
    gettoken();
    gettoken();
    gettoken();
    split();
    if(nxt!=filename){
        ferr.open(filename+".err",ios::out);
        ferr<<"filename does not match class name"<<endl;
        exit(-1);
    }
    currclassname=filename;
    gettoken();
    gettoken();
    if(nxt=="<classVarDec>"){
        //cout<<nxt<<endl;
        while(nxt=="<classVarDec>"){
            compileclassvardec();//on return nxt=</classVarDec>
            gettoken();
            //cout<<nxt<<endl;
        }
        // gettoken();
    }
    if(nxt=="<subroutineDec>"){
        while(nxt=="<subroutineDec>"){
            compilesubroutinedec();//on return nxt=</subroutineDec>
            
            gettoken();
        }
    }

}

int main(int argc,char**argv){
    for(int ii=2;ii<argc;ii++){
        filename=argv[ii];
        int x=filename.find(".");
        filename=filename.substr(0,x);
        labelnum=0;
        fi.open(filename+".xml");
        fo.open(filename+".vm",ios::out);        
        compileclass();
        currsubroutinename.clear();
        subroutinekind.clear();
        subroutinetype.clear();
        currclassname.clear();
        nxt.clear();
        filename.clear();
        fi.close();
        fo.close();
        ferr.close();
        classsymboltable.table.clear();
    }
    return 0;
}