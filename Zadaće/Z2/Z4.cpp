//TP 2021/2022: Zadaæa 2, Zadatak 4
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
template <typename NekiTip>
bool Kriterij(std::vector<NekiTip> vektor, std::vector<NekiTip> vektorcic){
    auto suma_vektor=NekiTip();
    auto suma_vektorcic=NekiTip();
    for(int i=0;i<vektor.size();i++){
        suma_vektor=suma_vektor+vektor.at(i);
    }
    for(int i=0;i<vektorcic.size();i++){
        suma_vektorcic=suma_vektorcic+vektorcic.at(i);
    }
    if(suma_vektor==suma_vektorcic) return vektor>vektorcic;
    return suma_vektor>suma_vektorcic;
}
template<typename NekiTip>
void SortirajPoSumiRedova(std::vector<std::vector<NekiTip>> &matrica){
    sort(matrica.begin(),matrica.end(),Kriterij<NekiTip>); 
}
template<typename NekiTip>
void UnosMatrice(std::vector<std::vector<NekiTip>> &matrica){
    NekiTip element;
    int i=0; 
    for(;;){
        matrica.resize(i+1);
        for(;;){
            std::cin>>element;
            if(!std::cin){
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                break;
            }
            matrica.at(i).push_back(element);
        }
        if(matrica.at(i).size()==0) break;
        i++;
    }
}
template<typename NekiTip>
void IspisiMatricu(std::vector<std::vector<NekiTip>> matrica){
    for(int i=0;i<matrica.size();i++){
        for(int j=0;j<matrica.at(i).size();j++){
            std::cout<<std::setw(10)<<matrica.at(i).at(j);
        }
        std::cout<<std::endl;
    }
}
int main ()
{
    std::cout<<"Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa): ";
    std::vector<std::vector<int>> Matrica;
    UnosMatrice(Matrica);
    std::cout<<"Matrica nakon sortiranja: "<<std::endl;
    SortirajPoSumiRedova(Matrica);
    IspisiMatricu(Matrica);
    return 0;
}

