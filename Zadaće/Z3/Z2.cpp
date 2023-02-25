//TP 2021/2022: Zadaæa 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
typedef std::map<std::string, std::set<int>> Mapa;
typedef std::set<int> Skup;
void PretvoriUMalaSlova(std::string &stringic){
    for(int i=0;i<stringic.length();i++){
        stringic.at(i)=tolower(stringic.at(i));
    }
}
bool SlovoIliBroj(char znak){
    if(isalpha(znak) || isdigit(znak)) return true;
    return false;
}
int BrojClanova(Mapa mapa){
    int brojac=0;
    auto iterator=mapa.begin();
    for(auto it=iterator->second.begin();it!=iterator->second.end();it++){
        brojac++;
    }
    return brojac;
}
Mapa KreirajIndeksPojmova(std:: string stringic){
    Mapa mapa;
    PretvoriUMalaSlova(stringic);
    for(int i=0;i<stringic.length();i++){
        if(stringic.at(i)!=stringic.length() && stringic.at(i)!=' ' && SlovoIliBroj(stringic.at(i))){
            int pocetak_elementa=i;
            while(i<stringic.length() && stringic.at(i)!=' ' && SlovoIliBroj(stringic.at(i))) i++;
            int duzina=i-pocetak_elementa;
            mapa[stringic.substr(pocetak_elementa,duzina)].insert(pocetak_elementa);
        }
    }
    return mapa;
}
void IspisiIndeksPojmova(Mapa mapa){
    for(auto iterator=mapa.begin(); iterator!=mapa.end();iterator++){
        std::cout<<iterator->first<<": ";
        int brojac=0;
        for(auto it=iterator->second.begin(); it!=iterator->second.end();it++){
            std::cout<<*it;
            brojac++;
            if(brojac!=iterator->second.size()) std::cout<<",";
        }
        std::cout<<std::endl;
    }
}
Skup PretraziIndeksPojmova(std::string pojam, Mapa mapa){
    PretvoriUMalaSlova(pojam);
    if(mapa.find(pojam)==mapa.end()) throw std::logic_error("Pojam nije nadjen");
    return mapa.find(pojam)->second;
}
int main ()
{
    std::string pojmovi;
    std::cout<<"Unesite tekst: ";
    std::getline(std::cin,pojmovi);
    Mapa mapa=KreirajIndeksPojmova(pojmovi);
    IspisiIndeksPojmova(mapa);
    std::string pojam;
    for(;;){
        std::cout<<std::endl;
        std::cout<<"Unesite rijec: ";
        std::getline(std::cin,pojam); 
        if(pojam==".") break;
        try{
        Skup skup=PretraziIndeksPojmova(pojam, mapa);
        for(auto element: skup) std::cout<<element<<" ";
        std::cout<<std::endl;
        }
    catch(...){
        std::cout<<"Unesena rijec nije nadjena!";
    }
        }
	return 0;
}

