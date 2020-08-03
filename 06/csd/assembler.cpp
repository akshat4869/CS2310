#include<bits/stdc++.h>
using namespace std;
int checkcomment=0;
map<string,int> symtab;

map<string,string>pass2;


present (string s,char c){
    for( int i=0;i<s.length();i++){
        if(s[i]==c)
            return i;
    }
    return -1;
}

long long decimalToBinary(int N) 
{ 
  
    // To store the binary number 
    long long  B_Number = 0; 
    int cnt = 0; 
    while (N != 0) { 
        int rem = N % 2; 
        long long  c = pow(10, cnt); 
        B_Number += rem * c; 
        N /= 2; 
  
        // Count used to store exponent value 
        cnt++; 
    } 
  
    return B_Number; 
} 

bool isNumber(string s) 
{ 
    for (int i = 0; i < s.length(); i++) 
        if (isdigit(s[i]) == false) 
            return false; 
  
    return true; 
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

int main(int argc, char* argv[]){
   fstream fi;
   fstream fo;
   fi.open(argv[1]);
   fo.open("pass1temp.txt",ios::out);
   

   while(fi){
       string line ;
       getline(fi,line);
       line.erase (remove(line.begin(), line.end(), ' '), line.end());
       line.erase (remove(line.begin(), line.end(), '\t'), line.end());
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
   fi.open("pass1.txt",ios::out);
   fo.open("pass1temp.txt");
   int i=16;
   int lineno=0;

   symtab.insert(pair<string,int>("SP",0));
   symtab.insert(pair<string,int>("LCL",1));
   symtab.insert(pair<string,int>("ARG",2));
   symtab.insert(pair<string,int>("THIS",3));
   symtab.insert(pair<string,int>("THAT",4));  
   symtab.insert(pair<string,int>("R0",0));
   symtab.insert(pair<string,int>("R1",1));
   symtab.insert(pair<string,int>("R2",2));
   symtab.insert(pair<string,int>("R3",3));
   symtab.insert(pair<string,int>("R4",4));
   symtab.insert(pair<string,int>("R5",5));
   symtab.insert(pair<string,int>("R6",6));
   symtab.insert(pair<string,int>("R7",7));
   symtab.insert(pair<string,int>("R8",8));
   symtab.insert(pair<string,int>("R9",9));
   symtab.insert(pair<string,int>("R10",10));
   symtab.insert(pair<string,int>("R11",11));
   symtab.insert(pair<string,int>("R12",12));
   symtab.insert(pair<string,int>("R13",13));
   symtab.insert(pair<string,int>("R14",14));
   symtab.insert(pair<string,int>("R15",15));
   symtab.insert(pair<string,int>("KBD",24576));
   symtab.insert(pair<string,int>("SCREEN",16384));
   string linex ;
    while(getline(fo,linex)){
        
        
        int x=present(linex,')');
        if(linex[0]=='(' && x<linex.size()-1){
            string temp=linex;
            linex.erase(x+1);
            fi<<linex<<endl;
            temp.erase(temp.begin(),temp.begin()+x+1);
            fi<<temp<<endl;
        }
        else
            fi<<linex<<endl;
    }
    fo.close();
    fi.close();
   //for labels
   fo.open("pass1.txt");
   while(fo){
       string line;
       getline(fo,line);
       if(line[0]=='(' ){
           int f=line.length();
               line.erase(line.begin(),line.begin()+1);
               line.erase(f-2);
               symtab[line]=lineno;         
               continue;
       }
       lineno++;
   }

   fo.close();
   fo.open("pass1.txt");

   //for @
   while(fo){
       string line;
       getline(fo,line);
       string temp;
       for(int i=1;i<line.length();i++){
           temp=temp+line[i];
       }
       if(line[0]=='@' && !isNumber(temp)){
           line.erase(line.begin(),line.begin()+1);
           auto itr=symtab.find(line);
           if(itr!=symtab.end()){
               continue;
           }
           else{
               symtab[line]=i;
               i++;
           }
       }
   }
    fo.close();
    fo.open("pass1.txt");
    
    //PASS 2 BEGINS HERE :
    pass2["JGT"]="001";
    pass2["JEQ"]="010";
    pass2["JGE"]="011";
    pass2["JLT"]="100";
    pass2["JNE"]="101";
    pass2["JLE"]="110";
    pass2["JMP"]="111";
    pass2["M"]="001";
    pass2["D"]="010";
    pass2["MD"]="011";
    pass2["DM"]="011";
    pass2["A"]="100";
    pass2["MA"]="101";
    pass2["AM"]="101";
    pass2["AD"]="110";
    pass2["DA"]="110";
    pass2["AMD"]="111";
    pass2["ADM"]="111";
    pass2["MAD"]="111";
    pass2["MDA"]="111";
    pass2["DAM"]="111";
    pass2["DMA"]="111";
    fstream ak;
    string line ;
    ak.open("pass2.hack",ios::out);
    while(getline(fo, line)){
        string out;
        //getline(fo,line);
        //jump instruction
        if(present(line,';')!=-1){
            out=out+"111";
            if(line[0]=='D'){
                out=out+"0";
                out=out+"001100";
            }
            else if(line[0]=='A'){
                out=out+"0";
                out=out+"110000";
            }
            else if(line[0]=='M'){
                out=out+"1";
                out=out+"110000";
            }
            else if(line[0]=='0'){
                out+="0";
                out+="101010";
            }
            out=out+"000";
            line.erase(line.begin(),line.begin()+2);
            if(line!="")
                out=out+pass2[line];
            else
                out=out+"000";
        }
        //C instruction non jump
        if(present(line,'=')!=-1){
            string temp=line;
            out=out+"111";
            temp.erase(temp.begin(),temp.begin()+present(line,'=')+1);
            if(present(temp,'M')!=-1)
                out+="1";
            else
                out+="0";
                if(temp=="0")
                    out+="101010";
                if(temp=="1")
                    out+="111111";
                if(temp=="-1")
                    out+="111010";
                if(temp=="D")
                    out+="001100";
                if(temp=="A")
                    out+="110000";
                if(temp=="!D")
                    out+="001101";
                if(temp=="!A")
                    out+="110001";
                if(temp=="-D")
                    out+="101010";
                if(temp=="-A")
                    out+="110011";
                if(temp=="D+1" || temp=="1+D")
                    out+="011111";
                if(temp=="A+1" || temp=="1+A")
                    out+="110111";
                if(temp=="D-1")
                    out+="001110";
                if(temp=="A-1")
                    out+="110010";
                if(temp=="D+A" || temp=="A+D")
                    out+="000010";
                if(temp=="D-A")
                    out+="010011";
                if(temp=="A-D")
                    out+="000111";
                if(temp=="D&A" || temp=="A&D")
                    out+="000000";
                if(temp=="D|A" || temp=="A|D")
                    out+="010101";
                if(temp=="M")
                    out+="110000";
                if(temp=="!M")
                    out+="110001";
                if(temp=="-M")
                    out+="110011";
                if(temp=="M-1")
                    out+="110010";
                if(temp=="D+M" || temp=="M+D")
                    out+="000010";
                if(temp=="D-M")
                    out+="010011";
                if(temp=="M-D")
                    out+="000111";
                if(temp=="D&M" || temp=="M&D")
                    out+="000000";
                if(temp=="D|M" || temp=="M|D")
                    out+="010101";
                if(temp=="M+1"||temp=="1+M")
                    out+="110111";
                line.erase(line.begin()+present(line,'='),line.end());
                out+=pass2[line];
                out=out+"000";
            }
    
    //A instructions
        string hha;
        for(int i=1;i<line.size();i++){
            hha=hha+line[i];
        }
        if(present(line,'@') !=-1 && !isNumber(hha)){
            out=out+"0";
            line.erase(line.begin(),line.begin()+1);
            long long x=symtab[line];
            x=decimalToBinary(x);
            string b=to_string(x);
            string a="";
            for(i=0;i<15-b.length();i++){
                a+="0";
            }
            a+=b;
            out+=a;
        }
        if(present(line,'@')!=-1 && isNumber(hha)){
            out+="0";
            line.erase(line.begin(),line.begin()+1);
            stringstream ec(line);
            long long x;
            ec>>x;
            x=decimalToBinary(x);
            string b=to_string(x);
            string a;
            for(i=0;i<15-b.length();i++){
                a+="0";
            }
            a+=b;
            out+=a;
        }

        if(present(line,'(')!=-1 && present(line,')')!=-1)
            continue;
        
        ak<<out<<endl;
    }
    ak.close();
    //    for (auto itr = symtab.begin(); itr != symtab.end(); itr++) 
    //     cout << itr->first 
    //          << '\t' << itr->second << '\n'; 
}
 

  
