//TP 2021/2022: Zadaæa 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>
#include <cctype>
#include <array>

typedef  std::vector<std::string> vektor;
typedef  std::array<vektor,100> m_niz;

bool SlovoIliBroj(char recenica){
    if(isdigit(recenica) || isalpha(recenica)) return true; //provjera da li je rijec 
    return false;
}

m_niz RazvrstajRijeciPoDuzini(std::string recenica){
    m_niz niz_rijeci;
    if(recenica.size()==1){
        niz_rijeci.at(1).resize(1);
        niz_rijeci.at(1).at(0).push_back(recenica.at(0));
    }
    else{
        for(int i=0;i<recenica.length();i++){
            if(SlovoIliBroj(recenica.at(i))){
                int prva=i,brojac=0;
                while(SlovoIliBroj(recenica.at(i))){
                    brojac++;
                    i++;
                    if(i==recenica.length()) break;
                }
                if(brojac>=100){
                    throw std::range_error("Predugacka rijec!");
                    return niz_rijeci;
                }
                int zadnja=i;
                i=prva;
                int max_br=niz_rijeci.at(brojac).size();
                niz_rijeci.at(brojac).resize(max_br+1);
                while(SlovoIliBroj(recenica.at(i))){
                    niz_rijeci.at(brojac).at(max_br).push_back(toupper(recenica.at(i)));
                    i++;
                    if(i==recenica.length()) break;
                }
                i=zadnja;
                if(i==recenica.length()) return niz_rijeci;
            }
        }
    }
    return niz_rijeci;
}
int main ()
{
    std::cout<<"Unesite recenicu: ";
    std::string recenica;
    std::getline(std::cin,recenica);
    m_niz niz_rijeci;
    try{
        niz_rijeci=RazvrstajRijeciPoDuzini(recenica);
    }
    catch(std::range_error prekoracenje){
        std::cout<<"Greska: Recenica sadrzi predugacku rijec!"<<std::endl;
        return 0;
    }
    for(int i=0;i<100;i++){
        if(niz_rijeci.at(i).size()>0){
        std::cout<<"Duzina "<<i<<": ";
        for(int j=0;j<niz_rijeci.at(i).size();j++){
            for(int k=0;k<niz_rijeci.at(i).at(j).length();k++){
                std::cout<<niz_rijeci.at(i).at(j).at(k);
            }
            std::cout<<" ";
        }
        std::cout<<std::endl;
        }
    }
	return 0;
}

