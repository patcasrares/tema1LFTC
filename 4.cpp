#include<iostream>
#include<fstream>

using namespace std;
ifstream fin("2.cpp");
string s;
int poz;

///scoate biblioteca de la inceput
void removeBiblioteca(string s)
{
    if(poz>=s.size())
        return;
    if(s[poz]=='#')
    {
        poz=s.size();
        cout<<s<<'\n';
    }
}

///scoate cuvantul cheie sau nume de variabila
void removeWord(string s)
{
    if(poz>=s.size())
        return;
    string aux="";
    while((s[poz]>='a'&&s[poz]<='z')||(s[poz]>='A'&&s[poz]<='Z'))
    {
        aux+=s[poz];
        poz++;
    }
    if(aux!="")
        cout<<aux<<'\n';
}

///scoate numarul de la inceputul sirului
void removeNumber(string s)
{
    if(poz>=s.size())
        return;
    string aux="";
    if ((s[poz]=='-' && isdigit(s[poz+1]))|| isdigit(s[poz]))
    {
        aux+=s[poz];
        poz++;
        if(poz==s.size())
        {
            cout<<aux<<'\n';
            return;
        }
        while(isdigit(s[poz]) || s[poz]=='.')
        {
            aux+=s[poz];
            poz++;
        }
        cout<<aux<<'\n';
    }

}

///scoate variabile de tip string
void removeString(string s)
{
    if(poz>=s.size())
        return;
    string aux="";
    if (s[poz]=='"' || s[poz]=='\'')
    {
        aux+=s[poz];
        poz++;
        while(!(s[poz]=='"' || s[poz]=='\''))
        {
            aux+=s[poz];
            poz++;
        }
        aux+=s[poz];
        poz++;
        cout<<aux<<'\n';
    }

}


void parsare(string s)
{
    poz=0;
    string aux="";
    while(poz<s.size())
    {
        removeBiblioteca(s);
        removeWord(s);
        removeNumber(s);
        removeString(s);
        //removeConsOperator(s);
        if(poz>=s.size())
            continue;
        if(s[poz]==' '||s[poz]=='\n')
        {
            poz++;
            continue;
        }
        ///scoate operatorii
        if(s[poz]==s[poz+1]||((s[poz]=='<'||s[poz]=='>')&&s[poz+1]=='='))
        {
            poz++;
            cout<<s[poz];
        }
        cout<<s[poz]<<'\n';
        poz++;
    }
}

int main()
{
    while(getline(fin,s))
    {
       parsare(s);
    }
}
