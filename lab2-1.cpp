#include<bits/stdc++.h>
using namespace std;
ifstream fin("lab.txt");
const int DN = 1005;
int nrStari,n;
int finale[DN];
string s,A,B,C;
unordered_map<string,int>mp; /// Map pentru a normaliza
vector<pair<int,string> >v[DN]; /// List pentru a retine tranzitiile ca muchii
set<string>sett; /// Set pentru retinerea alfabetului
string a[DN]; /// array<string> starile
string ret;
int cmd;

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
    //cout<<s<<' '<<ans<<' '<<nod<<'\n';
    for(auto i:v[nod])
    {
        if(incepe(s,i.second)){
            bk(cut(s,i.second.size()),ans+i.second,i.first);
        }
    }
}

string prefix(string s) { ///cel mai lung prefix corect
    ret="";
    bk(s,"",1);
    return ret;
}

int main()
{
    fin>>n;
    for(int i=1;i<=n;i++)
    {
        fin>>a[i];
        mp[a[i]]=i;
        fin>>finale[i];
    }
    while(fin>>A){
        fin>>B>>C;
        sett.insert(C);
        v[mp[A]].push_back({mp[B],C});
    }
    cmd=1;
    while(cmd){
        cout<<"introdu 0 pt a iesi\n";
        cout<<"introdu 1 pt a arata starile\n";
        cout<<"intordu 2 pt a arata alfabetul\n";
        cout<<"intordu 3 pt a arata tranzitiile\n";
        cout<<"intordu 4 pt a arata starile finale\n";
        cout<<"intordu 5 pt a verifica daca o secventa e acceptata\n";
        cout<<"intordu 6 pt a obtine cel mai lung prefix acceptat\n";
        cin>>cmd;
        if(cmd==0){
            break;
        }
        if(cmd==1){
            for(auto i:mp)
                cout<<i.first<<'\n';
            continue;
        }
        if(cmd==2) {
            for(auto i:sett){
                cout<<i<<'\n';
            }
            continue;
        }
        if(cmd==3) {
            for(int i=1;i<=n;i++)
            {
                for(auto j:v[i])
                    cout<<a[i]<<' '<<a[j.first]<<' '<<j.second<<'\n';
            }
            continue;
        }
        if(cmd==4) {
            for(int i=1;i<=n;i++)
            {
                if(finale[i])
                    cout<<a[i]<<'\n';
            }
            continue;
        }
        if(cmd==5)
        {
            cout<<"Introdu secventa ";
            cin>>s;
            cout<<(prefix(s)==s)<<'\n';
            continue;
        }
        if(cmd!=6)
            continue;
        cout<<"Introdu secventa ";
        cin>>s;
        cout<<prefix(s)<<'\n';
    }
}
