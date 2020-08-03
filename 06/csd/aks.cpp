#include<iostream>
#include<cmath>
using namespace std;
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
int main(){
    int n;
    cin>>n;
    cout<<decimalToBinary(n)<<endl;
}