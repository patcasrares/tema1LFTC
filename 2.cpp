#include<iostream>
using namespace std;

void calculCerc(float R)
{
    float pi=3.14;
    cout<<"Perimetru ";
    cout<<2*pi*R<<'\n';
    cout<<"Aria ";
    cout<<pi*R*R<<'\n';
}

int cmmdc(int a, int b)
{
    while(b)
    {
        int c = a%b;
        a=b;
        b=c;
    }
    return a;
}

int suma()
{
    cout<<"introdu nr n ";
    int n,sum;
    sum=0;
    cin>>n;
    while(n>0)
    {
        n=n-1;
        int a;
        cout<<"introdu un nr ";
        cin>>a;
        sum=sum+a;
    }
    return sum;
}

int main()
{
    calculCerc(3);
    cout<<"cmmdc 12 so 18 ";
    cout<<cmmdc(12,18)<<'\n';
    cout<<"suma n citite ";
    cout<<suma()<<'\n';
}
