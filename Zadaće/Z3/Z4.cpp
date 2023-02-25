//TP 2021/2022: Zadaæa 3, Zadatak 4
#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <set>
#include <vector>
#include <cctype>
typedef std::vector<std::set<std::string>> FormiraniTim;
typedef std::vector<std::string> Spisak;
typedef std::list<std::string> Lista;
typedef std::set<std::string> Skup;
bool BrojIliSlovo(char znak){
    if(isalpha(znak) || isdigit(znak)) return true;
    return false;
}
int BrojSlova(std::string stringic){
    int brojac(0);
    for(int i=0;i<stringic.length();i++){
        if(BrojIliSlovo(stringic.at(i))) brojac++;
    }
    return brojac;
}
FormiraniTim Razvrstavanje(Spisak imena, int broj_timova){
    if(broj_timova<=0 || broj_timova>imena.size()) throw std::logic_error("Razvrstavanje nemoguce");
    FormiraniTim Timovi(broj_timova);
    Lista lista_imena(imena.size());
    auto iterator=lista_imena.begin();
    int i=0;
    while(i<imena.size()){
        *iterator=imena.at(i);
        iterator++;
        i++;
    }
    int res=imena.size()%broj_timova;
    int broj_clanova=imena.size()/broj_timova;
    iterator=lista_imena.begin();
    for(int i=0;i<res;i++){
        for(int j=0;j<=broj_clanova;j++){
            bool zadnji_element=false;
            if(distance(iterator,lista_imena.end())==1) zadnji_element=true;
            Timovi.at(i).insert(*iterator);
            int broj_slova=BrojSlova(*iterator);
            iterator=lista_imena.erase(iterator);
            if(zadnji_element) iterator++;
            for(int k=0;k<broj_slova-1;k++){
                iterator++;
                if(iterator==lista_imena.end()) iterator=lista_imena.begin();
            }
        }
    }
    for(int i=res;i<broj_timova;i++){
        for(int j=0;j<broj_clanova;j++){
            bool zadnji_element=false;;
            if(distance(iterator,lista_imena.end())==1) zadnji_element=true;
            Timovi.at(i).insert(*iterator);
            int broj_slova=BrojSlova(*iterator);
            iterator=lista_imena.erase(iterator);
            if(zadnji_element) iterator++;
            for(int k=0;k<broj_slova-1;k++){
                iterator++;
                if(iterator==lista_imena.end()) iterator=lista_imena.begin();
            }
        }
    }
    return Timovi;
}
void IspisTimova(FormiraniTim Timovi){
    for(int i=0;i<Timovi.size();i++){
        Skup pomocni=Timovi.at(i);
        std::cout<<"Tim "<<i+1<<": ";
        for(auto iterator=pomocni.begin();iterator!=pomocni.end();iterator++){
            if(distance(iterator,pomocni.end())==1) std::cout<<*iterator<<std::endl;
            else std::cout<<*iterator<<", ";
        }
    }
}
int main ()
{
    int broj_djece;
    std::cout<<"Unesite broj djece: ";
    std::cin>>broj_djece;
    Spisak imena(broj_djece);
    std::cout<<std::endl<<"Unesite imena djece: ";
    std::cin.ignore(10000,'\n');
    for(int i=0;i<broj_djece;i++){
        std::getline(std::cin,imena.at(i));
    }
    std::cout<<std::endl<<"Unesite broj timova: "<<std::endl;
    int broj_timova;
    std::cin>>broj_timova;
    try{
        auto Timovi=Razvrstavanje(imena,broj_timova);
        IspisTimova(Timovi);
    }
    catch(std::logic_error izuzetak){
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
	return 0;
}

