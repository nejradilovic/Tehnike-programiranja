//TP 2021/2022: Zadaæa 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>

typedef std::vector<int> vektor;
int CiklickaPermutacija(vektor a,vektor b){
    if(a.size()!=b.size()) return -1;
    vektor dupli=a;
    if(a==b) return 0;
    for(int i=0;i<a.size();i++){
        dupli.push_back(a.at(i));
    }
    int pamti=-1;
    int p=1;
    for(int i=0;i<b.size();i++){
        for(int j=0;j<dupli.size();j++){
            p=1;
            if(b.at(i)==dupli.at(j)){
                for(int k=i+1,l=j+1;k<b.size() && l<dupli.size();k++,l++ ){
                    if(dupli.at(l)!=b.at(k)){
                        p=0;
                        break;
                    }
                }
                if(p==1){ 
                    pamti=j;
                    break;
                }
            }
        }
      break;
    }
    return pamti;
}
int main ()
{
    std::cout<<"Prva sekvenca: ";
    vektor v1;
    int broj;
    do{
        std::cin>>broj;
        if(!(std::cin)){
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            break;
        }
        v1.push_back(broj);
    }while(std::cin);

    vektor v2;
    std::cout<<"Druga sekvenca: ";
    do{
        std::cin>>broj;
        if(!(std::cin)){
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            break;
        }
        v2.push_back(broj);
    }while(std::cin);
    
    int pomak=CiklickaPermutacija(v1, v2);
    if(pomak!=-1){
        std::cout<<"Druga sekvenca je ciklicka permutacija prve s pomakom "<<pomak<<".";
    }
    else{
        std::cout<<"Druga sekvenca nije ciklicka permutacija prve.";
    }
	return 0;
}
