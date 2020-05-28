#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

int ne;///nr de neterminale
int te;///nr de terminale
int pro;///productiile
set<char> neTerminale;
set<char> terminale;
unordered_map<char,vector<string>> productii;//in ce se pot transforma nodurile terminale
int i,n;
char elem;
string line;
string startSymbol;

void inputReader(){
        fin>>ne;
        for(i=0;i<ne;i++)
        {
            fin>>elem;
            neTerminale.insert(elem);
        }
        fin>>te;
        for(i=0;i<te;i++)
        {
            fin>>elem;
            terminale.insert(elem);
        }
        fin>>pro;
        cout<<pro;
        for(int j=0;j<pro;j++)
        {
            fin>>line;
            string aux="";
            for(i=3;i<line.size();i++){
               if(line[i]=='|'){productii[line[0]].push_back(aux); aux="";}
               else {aux+=line[i];}
            }
            productii[line[0]].push_back(aux);
        }
        fin>>n;///limita de lungime
        fin>>startSymbol;
}

int main()
{
    set<string> vizitate;
    queue<string> coada;
    set<string> solutii;
    inputReader();
    cout<<productii['S'][0]<<" ";
    cout<<productii['S'][1]<<" ";
    cout<<productii['A'][0]<<" ";
    cout<<productii['A'][1]<<" ";
    coada.push(startSymbol);
    while(!coada.empty()){
        string prim = coada.front();
        coada.pop();
        ne=0;
        te=0;
        for(i=0;i<prim.size();i++){
            if(neTerminale.find(prim[i])!=neTerminale.end()) ne++;
            if(terminale.find(prim[i])!=terminale.end()) te++;
        }
        if(te<=n && ne==0) solutii.insert(prim);
        if(te<=n) {
            for(i=0;i<prim.size();i++){
            if(neTerminale.find(prim[i])!=neTerminale.end())
            {
                for(auto str:productii[prim[i]]){
                    string noulSir="";
                    for(int j=0;j<i;j++)
                        noulSir+=prim[j];
                    if(str!="~")
                    noulSir+=str;
                    for(int j=i+1;j<prim.size();j++)
                        noulSir+=prim[j];
                    if(vizitate.find(noulSir)==vizitate.end()) {vizitate.insert(noulSir); coada.push(noulSir);}
                }
            }
        }
    }
    }
    for(auto sol:solutii){
        if(sol=="") fout<<"~"<<endl;
        else fout<<sol<<endl;
    }

    return 0;
}
