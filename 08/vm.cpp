#include<bits/stdc++.h>
using namespace std;
int checkcomment=0;
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
int main(int argc,char* argv[]){
    fstream fi,fo;
    fi.open(argv[1]);
    fo.open("temp.txt",ios::out);
    
   while(fi){
       string line ;
       getline(fi,line);
       line = removecomment2(line);
       if(checkcomment==0)
        line= removecomment1(line);
       //cout<<line<<endl;
       if(line!=""){
            fo<<line<<endl;
       }   
   }
   fi.close();
   fo.close();
   fi.open("temp.txt");
   fo.open(argv[2],ios::out);
   int cnt=0;
   while(fi){
       string s;
       fi>>s;
        if(s=="add")
           fo<<"@SP\nAM=M-1\nD=M\nA=A-1\nM=D+M\n";
        else if(s=="sub")
           fo<<"@SP\nAM=M-1\nD=M\nA=A-1\nM=M-D\n";
        else if(s=="and")
           fo<<"@SP\nAM=M-1\nD=M\nA=A-1\nM=D&M\n";
        else if(s=="or")
           fo<<"@SP\nAM=M-1\nD=M\nA=A-1\nM=D|M\n";
        else if(s=="not")
           fo<<"@SP\nA=M-1\nM=!M\n";
        else if(s=="neg")
           fo<<"@SP\nA=M-1\nM=-M\n";       
        else if(s=="eq")
           fo<<"@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\n@"<<argv[1]<<cnt<<"\nD;JEQ\n@SP\nA=M-1\nM=0\n@"<<argv[1]<<cnt+1<<"\n0;JMP\n("<<argv[1]<<cnt<<")\n@SP\nA=M-1\nM=-1\n("<<argv[1]<<cnt+1<<")\n";
        else if(s=="gt")
           fo<<"@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\n@"<<argv[1]<<cnt<<"\nD;JGT\n@SP\nA=M-1\nM=0\n@"<<argv[1]<<cnt+1<<"\n0;JMP\n("<<argv[1]<<cnt<<")\n@SP\nA=M-1\nM=-1\n("<<argv[1]<<cnt+1<<")\n";
        else if(s=="lt")
           fo<<"@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\n@"<<argv[1]<<cnt<<"\nD;JLT\n@SP\nA=M-1\nM=0\n@"<<argv[1]<<cnt+1<<"\n0;JMP\n("<<argv[1]<<cnt<<")\n@SP\nA=M-1\nM=-1\n("<<argv[1]<<cnt+1<<")\n";
        //memory access
        else if(s=="push"){
            string s1,s2;
            fi>>s1>>s2;
            cout<<s1<<s2<<endl;
            if(s1=="local")
                fo<<"@LCL\nD=M\n@"<<s2<<"\nA=D+A\nD=A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
            if(s1=="argument")
                fo<<"@ARG\nD=M\n@"<<s2<<"\nA=D+A\nD=A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
            if(s1=="this")
                fo<<"@THIS\nD=M\n@"<<s2<<"\nA=D+A\nD=A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
            if(s1=="that")
                fo<<"@THAT\nD=M\n@"<<s2<<"\nA=D+A\nD=A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
            if(s1=="temp")
                fo<<"@5\nD=A\n@"<<s2<<"\nA=D+A\nD=A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
            if(s1=="constant")
                fo<<"@"<<s2<<"\nD=A\n@SP\nAM=M+1\nA=A-1\nM=D\n";
            if(s1=="pointer")
                fo<<"@3\nD=A\n@"<<s2<<"\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
            if(s1=="static")
                fo<<"@"<<argv[1]<<s2<<"\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
        }
        else if(s=="pop"){
            string s1,s2;
            fi>>s1>>s2;
            if(s1=="local")
                fo<<"@LCL\nD=M\n@"<<s2<<"\nD=A+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
            if(s1=="argument")
                fo<<"@ARG\nD=M\n@"<<s2<<"\nD=A+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
            if(s1=="this")
                fo<<"@THIS\nD=M\n@"<<s2<<"\nD=A+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
            if(s1=="that")
                fo<<"@THAT\nD=M\n@"<<s2<<"\nD=A+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
            if(s1=="temp")
                fo<<"@5\nD=A\n@"<<s2<<"\nD=A+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
            if(s1=="pointer")
                fo<<"@3\nD=A\n@"<<s2<<"\nD=A+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
            if(s1=="static")
                fo<<"@"<<argv[1]<<s2<<"\nD=M\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
        }
        //program flow
        else if(s=="label"){
            string s1;
            fi>>s1;
            fo<<"("<<argv[1]<<s1<<")\n";
        }
        else if(s=="goto"){
            string s1;
            fi>>s1;
            fo<<"@"<<argv[1]<<s1<<"\n0;JMP\n";
        }
        else if(s=="if-goto"){
            string s1;
            fi>>s1;
            fo<<"@SP\nAM=M-1\nD=M\n@"<<argv[1]<<s1<<"\nD;JNE\n";
        }
        //funcion calling
        else if(s=="function"){
            string s1,s2;
            fi>>s1>>s2;
            fo<<"("<<s1<<")\n@"<<s2<<"\nD=A\n("<<argv[1]<<s1<<cnt<<")\n@"<<argv[1]<<s1<<cnt+1<<"\nD;JEQ\n@SP\nA=M\nM=0\n@SP\nM=M+1\nD=D-1\n@"<<argv[1]<<s1<<cnt<<"\n0;JMP\n("<<argv[1]<<s1<<cnt+1<<")\n";
        }
        else if(s=="call"){
            string s1,s2;
            fi>>s1>>s2;
            fo<<"@"<<argv[1]<<s1<<cnt<<"RA\nD=A\n@SP\nAM=M+1\nA=A-1\nM=D\n";
            fo<<"@LCL\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
            fo<<"@ARG\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
            fo<<"@THIS\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
            fo<<"@THAT\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
            fo<<"@SP\nD=M\n@"<<s2<<"\nD=D-A\n@5\nD=D-A\n@ARG\nM=D\n";
            fo<<"@SP\nD=M\n@LCL\nM=D\n";
            fo<<"@"<<s1<<"\n0;JMP\n";
            fo<<"("<<argv[1]<<s1<<cnt<<"RA)\n";
        }
        else if(s=="return"){
            fo<<"@LCL\nD=M\n@FRAME\nM=D\n";
            fo<<"@FRAME\nD=M\n@5\nA=D-A\nD=M\n@RET\nM=D\n";
            fo<<"@SP\nA=M-1\nD=M\n@ARG\nA=M\nM=D\n";
            fo<<"@ARG\nD=M\n@1\nD=D+A\n@SP\nM=D\n";
            fo<<"@FRAME\nD=M\n@2\nA=D-A\nD=M\n@THIS\nM=D\n";
            fo<<"@FRAME\nD=M\n@1\nA=D-A\nD=M\n@THAT\nM=D\n";
            fo<<"@FRAME\nD=M\n@3\nA=D-A\nD=M\n@ARG\nM=D\n";
            fo<<"@FRAME\nD=M\n@4\nA=D-A\nD=M\n@LCL\nM=D\n";
            fo<<"@RET\nA=M\n0;JMP\n";
        }
        cnt+=2;
   }
}