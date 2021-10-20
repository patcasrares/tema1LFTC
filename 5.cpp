
#include<iostream>
#include<fstream>
#include<map>
#include<vector>

using namespace std;
ifstream fin("2.cpp");
string s;
int poz,nrInd,nrConst,nrAtom;
bool vf=true;
//map<string,int>mp[3];
vector<string>v;
vector<string>msg;

struct nod {
    string s;
    int val = 0;
    nod* dr=nullptr;
};

nod* sursa[3] = {new nod(),new nod(),new nod()};

int cauta(int dict,string s)
{
    nod* z = sursa[dict];
    int ret = 0;
    while(z!=nullptr){
        if(z->s==s)
        {
            ret=z->val;
            break;
        }
        z=z->dr;
    }
    return ret;
}

void adauga(int dict,string s,int valoare)
{
    nod* z = sursa[dict];
    int ret = 0;
    while(z!=nullptr){
        if (z->dr==nullptr|| (s<z->dr->s))
        {
            nod* nd = new nod();
            nd->dr=z->dr;
            nd->s=s;
            z->dr=nd;
            nd->val=valoare;
            break;
        }
        z=z->dr;
    }
}


void adaugInden(string s)
{
    if (s=="void" || s=="int" || s=="double" || s=="float" || s=="using" || s=="namespace" || s=="std"||s=="cin"||s=="cout")
        return;
    ///verify length
    if (s.size()>250)
    {
        vf=false;
        msg.push_back(s+" len <=250");
        return;
    }

    ///must have lower case letters
    for(int i=0;i<s.size();i++)
    {
        if(!('a'<=s[i]<='z'))
        {
            vf=false;
            msg.push_back(s+" characters are letters");
            return;
        }
    }

    if(cauta(0,s)==0)
    {
        nrInd++;
        adauga(0,s,nrInd);
    }
}

void adaugConst(string s)
{
    ///verify the length

    if(cauta(1,s)==0)
    {
        nrConst++;
        adauga(1,s,nrConst);
    }
}

///scoate biblioteca de la inceput
void removeBiblioteca(string s)
{
    if(poz>=s.size())
        return;
    if(s[poz]=='#')
    {
        poz=s.size();
        if(s!="#include<iostream>")
            msg.push_back(s+" must be a library");
        v.push_back(s);
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
    if(aux!="") {
        adaugInden(aux);
        v.push_back(aux);
    }
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
            adaugConst(aux);
            v.push_back(aux);
            return;
        }
        while(isdigit(s[poz]) || s[poz]=='.')
        {
            aux+=s[poz];
            poz++;
        }
        adaugConst(aux);
        v.push_back(aux);
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
        adaugConst(aux);
        v.push_back(aux);
    }

}


void parsare(string s)
{
    poz=0;
    string aux="";
    while(poz<s.size())
    {
        if(s[poz]==' '||s[poz]=='\n')
        {
            poz++;
            continue;
        }
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
        string aux="";
        if(s[poz]==s[poz+1]||((s[poz]=='<'||s[poz]=='>')&&s[poz+1]=='='))
        {
            poz++;
            aux+=s[poz];
        }
        aux+=s[poz];
        v.push_back(aux);
        poz++;
    }
}

int main()
{
    while(getline(fin,s))
    {
       parsare(s);
    }
    //return 0;
    if(msg.size()>0)
    {
        for(auto i:msg)
            cout<<i<<'\n';
        return 0;
    }
    cout<<"FIP\n";
    for(auto i:v)
    {
        cout<<i<<' ';
        int codAtom = -1;
        if(cauta(0,i)==0 && cauta(1,i)==0)
        {
            if(cauta(2,i)==0)
            {
                nrAtom++;
                adauga(2,i,nrAtom);
            }
            codAtom = cauta(2,i);
        }
        if(cauta(1,i))
        {
            codAtom=0;
        }
        codAtom++;
        cout<<codAtom<<' ';
        if (codAtom ==0 )
        {
            if(cauta(0,i))
                cout<<cauta(0,i)<<'\n';
            else
                cout<<cauta(1,i)<<'\n';
            continue;
        }
        cout<<"-\n";
    }
    cout<<"\nTabele simboluri\n";
    for(int pz=0;pz<2;pz++){
        if(pz==0)
            cout<<"Indentificatori\n";
        else
            cout<<"Constante\n";
        nod* z=sursa[pz];
        z=z->dr;
        while(z) {
            cout<<z->s<<' '<<z->val-1<<'\n';
            z=z->dr;
        }
        cout<<'\n';
    }
}
