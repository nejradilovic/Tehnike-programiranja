//TP 2021/2022: Zadaæa 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <type_traits>
#include <utility>
#include <vector>
#include <algorithm>
template <typename Tip, typename NekiTip>
int DuzinaKontejnera(Tip k, NekiTip pocetak, NekiTip kraj){
    int brojac=0;
    while(pocetak!=kraj){
        brojac++;
        pocetak++;
    }
    return brojac;
}
template <typename Tip1,typename Tip2>
auto ZbirKontejnera(Tip1 k1, Tip2 k2){
    int duzina=DuzinaKontejnera(k1,k1.begin(),k1.end());
    int velicina=DuzinaKontejnera(k2,k2.begin(),k2.end());
    auto pocetak=k1.begin();
    auto beginning=k2.begin();
    int duzina_zbira=0;
    if(duzina>velicina) duzina_zbira=duzina;
    else duzina_zbira=velicina;
    std::vector<decltype(*pocetak+*beginning)> zbir(duzina_zbira);
    int i=0;
    while(pocetak!=k1.end()){
        if(pocetak!=k1.end() && beginning==k2.end()){
            typename std::remove_reference<decltype(*k2.begin())>::type element={};
            while(pocetak!=k1.end()){
                zbir.at(i)=*pocetak+element;
                pocetak++;
                i++;
            }
            break;
        }
        zbir.at(i)=*pocetak+*beginning;
        pocetak++;
        beginning++;
        i++;
        if(pocetak==k1.end() && beginning!=k2.end()){
            typename std::remove_reference<decltype(*k1.begin())>::type element={};
            while(beginning!=k2.end()){
                zbir.at(i)=*beginning+element;
                beginning++;
                i++;
            }
            break;
        }
    }
    return zbir;
}
int main ()
{
    int duzina;
    std::cout<<"Duzina prvog kontejnera: ";
    std::cin>>duzina;
    std::cout<<"Elementi prvog kontejnera: ";
    std::vector<double> vektor;
    double element;
    for(int i=0;i<duzina;i++){
        std::cin>>element;
        vektor.push_back(element);
    }
    int velicina;
    std::cout<<"Duzina drugog kontejnera: ";
    std::cin>>velicina;
    std::vector<double> vektorcic;
    double clan;
    std::cout<<"Elementi drugog kontejnera: ";
    for(int i=0;i<velicina;i++){
        std::cin>>clan;
        vektorcic.push_back(clan);
    }
    std::cout<<"Zbir kontejnera: ";
    auto zbir=ZbirKontejnera(vektor, vektorcic);
    int duzina_zbira=DuzinaKontejnera(zbir,zbir.begin(),zbir.end());
    //std::cout<<duzina_zbira;
    for(int i=0;i<duzina_zbira;i++){
        std::cout<<zbir.at(i)<<" ";
    }
	return 0;
}

