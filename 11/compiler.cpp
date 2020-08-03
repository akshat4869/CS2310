#include<bits/stdc++.h>
using namespace std;
fstream ferr;
int checkcomment=0;
map<string,string> table;
void error(){
    ferr<<"Lexical Error"<<endl;
    exit(-1);
}
string removecomment2(string str){
    string ans;
    size_t flag1=str.find("/*");
    size_t flag2=str.find("*/");
    if(flag1!=string::npos && flag2!=string::npos){
        str.erase(str.begin()+flag1,str.begin()+flag2+2);
        ans=str;
    }
    if(flag1!=string::npos && flag2==string::npos){
        str.erase(flag1);
        ans=str;
        checkcomment=1;
    }
    if(flag1==string::npos && flag2!=string::npos){
        str.erase(str.begin(),str.begin()+flag2+2);
        ans=str;
        checkcomment=0;
    }
    if(flag1==string::npos && flag2==string::npos && checkcomment==1){
        ans="";
    }
    if(flag1==string::npos && flag2==string::npos && checkcomment==0){
        ans=str;
    }
    return ans;

}

string removecomment1(string str){
   size_t flag=str.find("//");
    if(flag!=std::string::npos){
        str.erase(flag);
    }
    return str;
}

void declaretable(){
    table.insert({"class","keyword"}); table.insert({"constructor","keyword"}); table.insert({"function","keyword"}); table.insert({"method","keyword"});
    table.insert({"field","keyword"}); table.insert({"static","keyword"}); table.insert({"var","keyword"}); table.insert({"int","keyword"});
    table.insert({"char","keyword"}); table.insert({"boolean","keyword"}); table.insert({"void","keyword"}); table.insert({"true","keyword"});
    table.insert({"false","keyword"}); table.insert({"null","keyword"}); table.insert({"this","keyword"}); table.insert({"let","keyword"});
    table.insert({"do","keyword"}); table.insert({"if","keyword"}); table.insert({"else","keyword"}); table.insert({"while","keyword"});
    table.insert({"return","keyword"});
    table.insert({"{","symbol"}); table.insert({"}","symbol"}); table.insert({"(","symbol"}); table.insert({")","symbol"});
    table.insert({"[","symbol"}); table.insert({"]","symbol"}); table.insert({".","symbol"}); table.insert({",","symbol"});
    table.insert({";","symbol"}); table.insert({"+","symbol"}); table.insert({"-","symbol"}); table.insert({"*","symbol"});
    table.insert({"/","symbol"}); table.insert({"&","symbol"}); table.insert({"|","symbol"}); table.insert({"<","symbol"});
    table.insert({">","symbol"}); table.insert({"=","symbol"}); table.insert({"~","symbol"});
    return;
}


string check1(string st){
    if(table[st]=="keyword")
        return "keyword";
    else
        return "identifier";
    
}

string check2(string x){
    if(table[x]=="symbol")
        return "symbol";
    else
        return "unidentified";
    
}
bool checkvar(char c){
    if((c>='a' && c<='z') || c=='_' || (c>='A' && c<='Z'))
        return 1;
    return 0;
}
int main(int argc, char* argv[]){
    for(int ii=2; ii<argc; ii++){
        declaretable();
        fstream fi;
        fstream fo;
        fi.open(argv[ii]);
        fo.open("pass1temp.txt",ios::out);
        string filename=argv[ii];
        int x=filename.find(".");
        filename=filename.substr(0,x);
        ferr.open(filename+".err",ios::out);
        while(fi){
            string line ;
            getline(fi,line);
            line = removecomment2(line);
            if(checkcomment==0)
                line= removecomment1(line);
            if(line!=""){
                    fo<<line<<endl;
            }   
        }
        fi.close();
        fo.close();
        fo.open(filename+"t.xml",ios::out);
        fi.open("pass1temp.txt");
        fo<<"<tokens>\n";
        while(fi){
            char c;
            string s;
            string s2;
            int ec=0;
            fi.get(c);
            
            if(checkvar(c)){
                s=s+c;
                while(1){
                    fi.get(c);
                    if(c==' ' || c=='\n' || c=='\t')
                        break;
                    
                    string s3;
                    s3=s3+c;
                    if(check2(s3)=="symbol"){
                        ec=1;
                        s2=s3;
                        break;
                    }
                    if(!checkvar(c)){
                        cout<<'a'<<endl;
                        error();
                    }
                    s=s+c;  
                }
                string tkn=check1(s);
                fo<<"<"<<tkn<<"> "<<s<<" </"<<tkn<<">\n";
                if(ec==1){
                    fo<<"<symbol> "<<s2<<" </symbol>\n";
                }
            }
            else{
                if(c=='"'){
                    while(1){
                        if(fi.eof()){
                            cout<<'b'<<endl;
                            error();
                        }
                        fi.get(c);
                        if(c=='"')
                            break;
                        s=s+c;
                    }
                    fo<<"<stringConstant> "<<s<<" </stringConstant>\n";
                }
                else if(c>='0' && c<='9'){
                    s=s+c;
                    while(1){
                        fi.get(c);
                        string s3;
                        s3=s3+c;
                        if(c==' ')
                            break;
                        if(check2(s3)=="symbol"){
                            ec=1;
                            s2=s3;
                            break;
                        }
                        if(!(c>='0' && c<='9')){
                            cout<<'c'<<endl;
                            error();
                        }
                        s=s+c;
                    }
                    fo<<"<integerConstant> "<<s<<" </integerConstant>\n";
                    if(ec==1){
                        fo<<"<symbol> "<<s2<<" </symbol>\n";
                    }
                    
                }
                else if(c==' '|| c=='\n' || c=='\t'){
                    continue;
                }
                else{ 
                    s=s+c;
                    string tkn=check2(s);
                    if(tkn=="unidentified"){
                        cout<<'d'<<endl;
                        error();
                    }
                    if(s=="<")s="&lt;";
                    if(s==">")s="&gt;";
                    if(s=="&")s="&amp;";
                    fo<<"<"<<tkn<<"> "<<s<<" </"<<tkn<<">\n";
                }
            }
        }
        fo<<"</tokens>";
        checkcomment=0;
    }
    return 0;
}