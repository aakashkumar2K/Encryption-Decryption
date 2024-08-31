// C++ Program to print Magic square
// of Doubly even order
#include<bits/stdc++.h>
#include<windows.h>
#define n 16
#define borderline cout<<"-----------------------------------------------------------------\n";
using namespace std;

class MagicSquare
{
        int arr[n][n], i, j;
    public:
    MagicSquare( )
    {   


    // filling matrix with its count value
    // starting from 1;
    for ( i = 0; i < n; i++)
        for ( j = 0; j < n; j++)
            arr[i][j] = (n*i) + j + 1;
    
    // change value of Array elements
    // at fix location as per rule
    // (n*n+1)-arr[i][j]
    // Top Left corner of Matrix
    // (order (n/4)*(n/4))
    for ( i = 0; i < n/4; i++)
        for ( j = 0; j < n/4; j++)
            arr[i][j] = (n*n + 1) - arr[i][j];
    
    // Top Right corner of Matrix
    // (order (n/4)*(n/4))
    for ( i = 0; i < n/4; i++)
        for ( j = 3 * (n/4); j < n; j++)
            arr[i][j] = (n*n + 1) - arr[i][j];
    
    // Bottom Left corner of Matrix
    // (order (n/4)*(n/4))
    for ( i = 3 * n/4; i < n; i++)
        for ( j = 0; j < n/4; j++)
            arr[i][j] = (n*n+1) - arr[i][j];
    
    // Bottom Right corner of Matrix
    // (order (n/4)*(n/4))
    for ( i = 3 * n/4; i < n; i++)
        for ( j = 3 * n/4; j < n; j++)
            arr[i][j] = (n*n + 1) - arr[i][j];
    
    // Centre of Matrix (order (n/2)*(n/2))
    for ( i = n/4; i < 3 * n/4; i++)
        for ( j = n/4; j < 3 * n/4; j++)
            arr[i][j] = (n*n + 1) - arr[i][j];

 }
 void makeRandom(){
    for(int i=0;i<15;i++)
        randomise();
 }
 void swaprow(int x){
    int y=15-x;
    //cout<<"swapping "<<x<<" "<<y<<" row"<<endl;
    for(int i=0;i<16;i++){
        swap(arr[x][i],arr[y][i]);
    }
 }
  void swapcol(int x){
    int y=15-x;
    //cout<<"swapping "<<x<<" "<<y<<" col"<<endl;
    for(int i=0;i<16;i++){
        swap(arr[i][x],arr[i][y]);
    }
 }
 void randomise(){
    
    bool row=rand()%2;
    int line=rand()%9;
    if(row)
        swaprow(line);
    else
        swapcol(line);
 }
 int getposition(int i,int j){
    return arr[i][j];
 }
 void printSquare(){
       // Printing the magic-square
    for (i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
            cout<<"|"<<setfill('0')<<setw(3)<< arr[i][j];
        cout << "|\n";
        borderline
    }
 }
 void printChars(){
       // Printing the magic-square
    for (i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
            cout<<"|" <<setfill(' ')<<setw(2)<< (unsigned char)arr[i][j] << " ";
        cout << "|\n";
        borderline
    }

 }
};
class Encryptor{
    map <char,string> m;
    public:
    Encryptor(MagicSquare key){
        for(int i=0;i<16;i++){
            for(int j=0;j<16;j++){
                string s="";
                if(i<10)
                    s+="0";
                s+=to_string(i);
                if(j<10)
                    s+="0";
                s+=to_string(j);
                char c=key.getposition(i,j)%256;
                //cout<<(char)(key.getposition(i,j))<<" "<<s<<endl;
                m[c]=s;
            }
        }
    }
    string encrypt(string s){
        string newstring="";
        for(char i:s){
            newstring+=m[i];
        }
        return newstring;
    }
};
class Decryptor{
    map <string,char> m;
    public:
    Decryptor(MagicSquare key){
        for(int i=0;i<16;i++){
            for(int j=0;j<16;j++){
                string s="";
                if(i<10)
                    s+="0";
                s+=to_string(i);
                if(j<10)
                    s+="0";
                s+=to_string(j);
                char c=key.getposition(i,j)%256;
                //cout<<(char)(key.getposition(i,j))<<" "<<s<<endl;
                m[s]=c;
            }
        }
    }
    string decrypt(string s){
        string newstring="";
        for(int i=0;i<=s.size()-4;i+=4){
            string k=s.substr(i,4);
            
            newstring+=m[k];
        }
        return newstring;
    }
};

// driver program
int main()
{
    srand((unsigned) time(NULL)); 
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    MagicSquare key=MagicSquare();
    string message="",ciphertext,plaintext;
    cout<<" \n\n\n MESSAGE TO BE ENCRYPTED : ";
    getline(cin,message);
    key.printSquare();
    cout<<endl;
    key.makeRandom();    
                        
    key.printSquare();  
    cout<<endl<<endl;
    key.printChars();
    Encryptor e(key);
    ciphertext=e.encrypt(message);
    cout<<"\n\n CIPHER TEXT: "<<ciphertext<<endl;
    Decryptor d(key);
    plaintext=d.decrypt(ciphertext);
    cout<<"\n\n DECRYPTED TEXT:  "<<plaintext<<endl;
    return 0;
}
