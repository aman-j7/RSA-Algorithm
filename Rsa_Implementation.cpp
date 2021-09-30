#include<bits/stdc++.h>
#include<iostream>
using namespace std;
int prime(int n)
{
    for(int i=2; i<=sqrt(n); i++)
        if(n%i==0)
            return 1;
    return 0;

}
int gcd(int a, int b)
{
    if(a==0)
        return b ;
    else
        gcd(b%a,a);
}
void extendedEuc(long a,long b, int &x, int &y)
{
    if(a==1)
    {
        x=1;
        y=0;
        return;
    }
    int x1,y1;
    extendedEuc(b%a,a,x1,y1);
    x= y1- (b/a)*x1;
    y=x1;
}
int modInverse(long a, long m)
{
    int x,y;
    extendedEuc(a,m,x,y);
    x = (x%m+m)%m;
    return x;
}
long long binpow(long long a,long b, long c)
{
    a%=c;
    long long res=1;
    while(b>0)
    {
        if(b&1)
            res=(res*a)%c;
        a=(a*a)%c;
        b>>=1;
    }
    return res;
}
class Rsa
{
    vector<long long>cipher;
    pair<long,long> public_key,private_key;
    long p,q,n,phi;
    long long d,e;
protected:
    void genPrime(long &,long &);
    void pubk();
    void prvk();
    void encrypt(string,pair<long,long> );
    void decrypt();
public:
    Rsa();
    vector<long long> send(string,pair<long,long>);
    void received(vector<long long>);
    pair<long,long> getPk()
    {
        return public_key;
    }
};
Rsa::Rsa()
{
    genPrime(p,q);
    n=p*q;
    phi=(p-1)*(q-1);
    public_key.second=private_key.second=n;
    pubk();
    prvk();
}
void Rsa::genPrime(long &p,long &q)
{
    q=rand()%99;
    if(q%2==0)
        ++q;
    while(prime(q))
        q+=2;
    p=(255-q)/2;
    if(p%2==0)
        ++p;
    while(prime(p))
        p+=2;
}
void Rsa::pubk()
{
    int i,f;
    for(i=2; i<phi; i++)
    {
        f=gcd(i,phi);
        if(f==1)
        {
            e=i;
            break;
        }
    }
    public_key.first=e;
}
void Rsa::prvk()
{
    d=modInverse(e,phi);
    private_key.first=d;
}
void Rsa::encrypt(string s,pair<long,long> pk)
{
    int i;
    long k;
    vector<char> c;
    for(i=0; i<s.length(); i++)
    {
        k=s.at(i);
        k= binpow(k,pk.first,pk.second);
        cipher.push_back(k);
        c.push_back(k);
    }
    cout<<" Encryted Message : ";
    for(i=0; i<c.size(); i++)
    {
        cout<<c[i];
    }
    cout<<endl;
}
void Rsa::decrypt()
{
    int i;
    long long k;
    vector<char> c(cipher.size());
    for(i=0; i<cipher.size(); ++i)
    {
        k= binpow(cipher[i],private_key.first,private_key.second);
        c[i]=k;
    }
    cout<<" Decrypted Message : ";
    for(i=0; i<c.size(); i++)
        cout<<c[i];
    cout<<endl;
}
vector<long long> Rsa::send(string msg,pair<long,long>pk)
{
    encrypt(msg,pk);
    return cipher;
}
void Rsa::received(vector<long long> v)
{
    cipher=v;
    decrypt();
}
int main()
{
    srand(time(NULL));
    string s;
    vector<long long >v;
    Rsa a,b;
    cout<<" Enter Message : ";
    getline(cin,s);
    v=a.send(s,b.getPk());
    b.received(v);
    return 0;
}
