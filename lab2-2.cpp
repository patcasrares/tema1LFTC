#include<bits/stdc++.h>
using namespace std;
const int DN = 1005;
int nrStari,n,nrConst,nrInd;
int finale[DN];
string s,A,B,C;
unordered_map<string,int>mp; /// Map pentru a normaliza
vector<pair<int,string> >v[DN]; /// List pentru a retine tranzitiile ca muchii
set<string>sett; /// Set pentru retinerea alfabetului
string a[DN]; /// array<string> starile
string ret;
vector<string>elemente;
vector<string>msg;
int cmd;


/**
<floating-point-constant> := <fractional-constant> <exponent-part>{0,1} <floating-suffix>{0, 1} |
                             <digit-sequence> <exponent-part> <floating-suffix>
<fractional-constant> := <digit-sequence>{0,1}. <digit-sequence> |
                         <digit-sequence>.
<exponent-part> := e <sign>{0,1} <digit-sequence>
                   E <sign>{0,1} <digit-sequence>

<sign> := + | -
<digit-sequence> := <digit>
                    <digit-sequence> <digit>

<floating-suffix> := f | l | F | L*/
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

void adaugConst(string s)
{
    ///verify the length

    if(cauta(1,s)==0)
    {
        nrConst++;
        adauga(1,s,nrConst);
    }
}

void adaugInden(string s)
{
    if(cauta(0,s)==0)
    {
        nrInd++;
        adauga(0,s,nrInd);
    }
}

bool incepe(string A,string B){ /// B este inclus in A
    if(B.size()>A.size())
        return false;
    for(int i=0;i<B.size();i++)
        if(A[i]!=B[i])
            return false;
    return true;
}

string cut(string s,int n){ ///a obtine prefixul
    string r="";
    for(int i=n;i<s.size();i++)
        r+=s[i];
    //cout<<r<<'\n';
    return r;
}

void bk(string s,string ans,int nod) { ///pt gasirea prefixului
    //cout<<"sss"<<'\n';
    if(ans.size()>ret.size() && finale[nod])
        ret=ans;
    // cout<<s<<' '<<ans<<' '<<nod<<'\n';
    for(auto i:v[nod])
    {
        //cout<<i.second<<'\n';
        if(incepe(s,i.second)){
            bk(cut(s,i.second.size()),ans+i.second,i.first);
        }
    }
}

string prefix(string s,int vf) { ///cel mai lung prefix corect
    ret="";
    bk(s,"",vf);
    return ret;
}
int stari = 0, vfReal,vfIndentificator,vfString;

void citireReal(){
    ifstream n1in("floatNumberC.txt");
    vfReal = stari + 1;
    n1in>>n;
    //cout<<n<<'\n';
    for(int i=1;i<=n;i++)
    {
        n1in>>a[i];
        //cout<<a[i]<<'\n';
        stari++;
        mp[a[i]]=stari;
        n1in>>finale[stari];
        //cout<<a[i]<<' '<<finale[stari]<<'\n';
    }
    while(n1in>>A){
        n1in>>B>>C;
        sett.insert(C);
        //cout<<A<<' '<<B<<' '<<C<<' '<<mp[A]<<' '<<mp[B]<<'\n';
        v[mp[A]].push_back({mp[B],C});
    }
    n1in.close();
}

void citireInden(){
    ifstream n1in("indentificator.txt");
    vfIndentificator = stari + 1;
    n1in>>n;
    //cout<<n<<'\n';
    for(int i=1;i<=n;i++)
    {
        n1in>>a[i];
        stari++;
        mp[a[i]]=stari;
        n1in>>finale[stari];
    }
    while(n1in>>A){
        n1in>>B>>C;
        sett.insert(C);
        v[mp[A]].push_back({mp[B],C});
    }
    n1in.close();
}

void citireString(){
    ifstream n1in("string.txt");
    vfString = stari + 1;
    n1in>>n;
    //cout<<n<<'\n';
    for(int i=1;i<=n;i++)
    {
        n1in>>a[i];
        stari++;
        mp[a[i]]=stari;
        n1in>>finale[stari];
    }
    while(n1in>>A){
        n1in>>B>>C;
        if (C=="-")
            C=" ";
        sett.insert(C);
        v[mp[A]].push_back({mp[B],C});
    }
    n1in.close();
}


string removeRezervat(string s)
{
    string aux;

    aux = "#include<iostream>";
    vector<string>z;

    if(incepe(s,aux)) {
        elemente.push_back(aux);
        return cut(s,aux.size());
    }

    aux = "void";
    if(incepe(s,aux)) {
        elemente.push_back(aux);
        return cut(s,aux.size());
    }

    aux = "int";
    if(incepe(s,aux)) {
        elemente.push_back(aux);
        return cut(s,aux.size());
    }

    aux = "double";
    if(incepe(s,aux)) {
        elemente.push_back(aux);
        return cut(s,aux.size());
    }

    aux = "float";
    if(incepe(s,aux)) {
        elemente.push_back(aux);
        return cut(s,aux.size());
    }

    aux = "using";
    if(incepe(s,aux)) {
        elemente.push_back(aux);
        return cut(s,aux.size());
    }

    aux = "namespace";
    if(incepe(s,aux)) {
        elemente.push_back(aux);
        return cut(s,aux.size());
    }

    aux = "std";
    if(incepe(s,aux)) {
        elemente.push_back(aux);
        return cut(s,aux.size());
    }

    aux = "cin";
    if(incepe(s,aux)) {
        elemente.push_back(aux);
        return cut(s,aux.size());
    }

    aux = "cout";
    if(incepe(s,aux)) {
        elemente.push_back(aux);
        return cut(s,aux.size());
    }

    aux = "return";
    if(incepe(s,aux)) {
        elemente.push_back(aux);
        return cut(s,aux.size());
    }

    return s;
}

void parsare(string s)
{
    string aux="";
    string initial = s;
    while(s.size()>0)
    {
        string aux;
        aux=removeRezervat(s);
        if(s!=aux) {
            s=aux;
            continue;
        }

        aux=prefix(s,vfReal);
       // cout<<vfReal<<' '<<s<<' '<<aux<<'\n';
        if(aux.size()>0) {
            elemente.push_back(aux);
            adaugConst(aux);
            s=cut(s,aux.size());
            continue;
        }

        aux=prefix(s,vfString);
        if(aux.size()>0) {
            elemente.push_back(aux);
            adaugConst(aux);
            s=cut(s,aux.size());
            continue;
        }

        aux=prefix(s,vfIndentificator);
        if(aux.size()>0) {
            elemente.push_back(aux);
            adaugInden(aux);
            s=cut(s,aux.size());
            continue;
        }

        if(s[0]==' '){
            s=cut(s,1);
            continue;
        }

        if(incepe(s,"==")||incepe(s,"!=")||incepe(s,"<<")||incepe(s,">>"))
        {
            string z="";
            z+=s[0];
            z+=s[1];
            elemente.push_back(z);
            s=cut(s,2);
            continue;
        }

        if(incepe(s,"=")||incepe(s,"+")||incepe(s,"-")||incepe(s,"*")||incepe(s,"/")||incepe(s,"%")||incepe(s,"<")||incepe(s,">") )
        {
            string z="";
            z+=s[0];
            elemente.push_back(z);
            s=cut(s,1);
            continue;
        }

        if(incepe(s,"{")||incepe(s,"}")||incepe(s,"(")||incepe(s,")")||incepe(s,",") || incepe(s,";"))
        {
            string z="";
            z+=s[0];
            elemente.push_back(z);
            s=cut(s,1);
            continue;
        }

        string gresit="";
        for(int i=0;i<s.size();i++)
        {
            if(s[i]==' ')
                break;
            gresit+=s[i];
        }
        msg.push_back(gresit + " nu respecta automatele pentru atomi si nu e rezervat sau operator sau separator");
        break;
    }
}

int main()
{
    citireReal();
    citireInden();
    citireString();
    //cout<<prefix("3",1);
    //cout<<prefix("3.14",1);
    ifstream fin("input.cpp");
    while(getline(fin,s))
    {
       parsare(s);
    }

    if(msg.size()>0)
    {
        for(auto i:msg)
            cout<<i<<'\n';
        return 0;
    }
    cout<<"FIP\n";
    int nrAtom = -1;
    for(auto i:elemente)
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
