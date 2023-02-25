//TP 2021/2022: Zadaæa 3, Zadatak 5
#include <iostream>
#include <cmath>
#include <cctype>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
typedef std::vector<std::set<std::string>> FormiraniTim;
typedef std::vector<std::string> Spisak;
typedef std::set<std::string> Skup;
struct Dijete{
    std::string ime;
    Dijete *sljedeci;
};
bool BrojIliSlovo(char znak){
    if(std::isalpha(znak) || isdigit(znak)) return true;
    return false;
}
int BrojSlova(std::string stringic){
    int brojac=0;
    for(int i=0;i<stringic.length();i++){
        if(BrojIliSlovo(stringic.at(i))){
            brojac++;
        }
    }
    return brojac;
}
bool JednoPreostaloDijete(int broj_djece){
    if(broj_djece==1) return true;
    return false;
}
FormiraniTim Razvrstavanje(Spisak Imena, int broj_timova){
    if(broj_timova<=0 || Imena.size()<broj_timova) throw std::logic_error("Razvrstavanje nemoguce");
    Dijete *pocetak=nullptr,*prethodni=nullptr;
    int i=0;
    while(i<Imena.size()){
        Dijete *novi_clan=new Dijete{Imena.at(i),nullptr};
        if(!pocetak) pocetak=novi_clan;
        else prethodni->sljedeci=novi_clan;
        prethodni=novi_clan;
        i++;
    }
    if(Imena.size()>0) prethodni->sljedeci=pocetak;
    FormiraniTim Timovi;
    int res=Imena.size()%broj_timova;
    int broj_clanova=Imena.size()/broj_timova;
    if(res!=0) broj_clanova++;
    int duzina_imena=0,broj_djece=Imena.size();
    Dijete *kopija=pocetak;
    for(int i=0;i<broj_timova;i++){
        Skup FTimovi;
        if(res!=0 && i==res) broj_clanova--;
        for(int j=0;j<broj_clanova;j++){
            if(JednoPreostaloDijete(broj_djece)){
                FTimovi.insert(kopija->ime);
                kopija->sljedeci=nullptr;
                delete kopija;
                break;
            }
            for(int k=0;k<duzina_imena-1;k++){
                kopija=kopija->sljedeci;
                prethodni=prethodni->sljedeci;
            }
            FTimovi.insert(kopija->ime);
            duzina_imena=BrojSlova(kopija->ime);
            prethodni->sljedeci=kopija->sljedeci;
            delete kopija;
            broj_djece--;
            kopija=prethodni->sljedeci;
        }
        Timovi.push_back(FTimovi);
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
{   int broj_djece;
    std::cout<<"Unesite broj djece: ";
    std::cin>>broj_djece;
    Spisak Imena(broj_djece);
    std::cout<<"Unesite imena djece: "<<std::endl;
    std::cin.ignore(10000,'\n');
    for(int i=0;i<broj_djece;i++){
        std::getline(std::cin,Imena.at(i));
    }
    std::cout<<"Unesite broj timova: "<<std::endl;
    int broj_timova=0;
    std::cin>>broj_timova;
    try{
        auto Timovi=Razvrstavanje(Imena, broj_timova);
        IspisTimova(Timovi);
    }
    catch(std::logic_error izuzetak){
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
	return 0;
}

