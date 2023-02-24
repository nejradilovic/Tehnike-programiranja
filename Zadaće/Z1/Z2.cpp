//TP 2021/2022: Zadaæa 1, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <array>
#include <iomanip>

typedef std::vector<std::vector<double>> Matrica;
const double epsilon=0.0000000001;
Matrica KreirajMatricu(int br_redova, int br_kolona){
    return Matrica(br_redova, std::vector<double>(br_kolona));
}

int BrojRedova(Matrica m){
    return m.size();
}

int BrojKolona(Matrica m){
    if(m.size()!=0) return m.at(0).size();
    return 0;
}

Matrica UnesiMatricu(int br_redova, int br_kolona){
    auto m=KreirajMatricu(br_redova, br_kolona);
    for(int i=0;i<br_redova;i++){
        for(int j=0;j<br_kolona;j++){
            std::cin>>m.at(i).at(j);
        }
    }
    return m;
}

bool MoguSeMnoziti(Matrica m1, Matrica m2){
    return BrojKolona(m1)==BrojRedova(m2);
}

bool IspravnaStrukturaMatrice(Matrica m){
    if(m.size()==0) return true;
    int red=m.at(0).size();
    for(int i=0;i<BrojRedova(m);i++){
        if(red!=m.at(i).size()) return false;
    }
    return true;
}

Matrica MnozenjeMatrica(Matrica m1,Matrica m2){
    auto m3=KreirajMatricu(BrojRedova(m1),BrojKolona(m2));
    if(MoguSeMnoziti(m1, m2)==false){
        throw std::domain_error("Matrice nisu saglasne za mnozenje!");
    }
    if(IspravnaStrukturaMatrice(m1)==false || IspravnaStrukturaMatrice(m2)==false){
        throw std::domain_error("Neispravna matrica!");
    }
    for(int i=0;i<BrojRedova(m1);i++){
        for(int j=0;j<BrojKolona(m2);j++){
            double suma=0;
            for(int k=0;k<BrojRedova(m2);k++){ 
                suma+=m1.at(i).at(k)*m2.at(k).at(j);
            }
            m3.at(i).at(j)=suma;
        }
    }
    return m3;
}

std::array<Matrica,2> DoolittleLU(Matrica H){
    Matrica L(H.size(),std::vector<double> (H.size()));
    Matrica U(H.size(),std::vector<double> (H.size()));
    std::array<Matrica,2> LU;
    if(BrojKolona(H)!=BrojRedova(H)){
        throw std::domain_error("Matrica mora biti kvadratna!");
    }
    if(IspravnaStrukturaMatrice(H)==false){
        throw std::domain_error("Neispravna matrica!");
    }
    for(int i=0;i<L.size();i++){
        for(int j=i;j<L.size();j++){
            double suma=0;
            for(int k=0;k<i;k++){
                suma+=(L.at(i).at(k)*U.at(k).at(j));
            }
            U.at(i).at(j)=H.at(i).at(j)-suma;
            if(i==j){
                L.at(i).at(j)=1;
            }
            else{
                double suma=0;
                for(int k=0;k<i;k++){
                    suma+=L.at(j).at(k)*U.at(k).at(i);
                }
                L.at(j).at(i)=H.at(j).at(i)-suma;
                L.at(j).at(i)/=(U.at(i).at(i));
            }
            if(i==j && fabs(U.at(i).at(j))<epsilon){
                throw std::domain_error("Matrica je singularna!");
            }
        }
    }
    LU.at(0)=L;
    LU.at(1)=U;
    return LU;
}

bool ProvjeriFaktorizaciju(Matrica H,std::array<Matrica,2> LU){

    Matrica rezultat=MnozenjeMatrica(LU.at(0), LU.at(1));
    if(H.size()!=rezultat.size()){
        return false;
    }
    
    for (int i=0; i<H.size();i++){
        for(int j=0; j<H.at(i).size();j++){
            if(fabs(H.at(i).at(j)-rezultat.at(i).at(j))>epsilon) return false;
        }
    }

    if(!IspravnaStrukturaMatrice(LU.at(0)) || !IspravnaStrukturaMatrice(LU.at(1))){
        return false;
    } 

    return true;
}
int main ()
{
    int n=0;
    std::cout<<"Broj redova/kolona matrice: ";
    std::cin>>n;
    std::cout<<"Elementi matrice: "<<std::endl;
    auto matrix=UnesiMatricu(n,n);
    try{
        std::array<Matrica,2> LU;
        LU=DoolittleLU(matrix);
        std::cout<<"Matrica L: "<<std::endl;
        for(int i=0;i<LU.at(0).size();i++){
            for(int j=0;j<LU.at(0).at(0).size();j++){
                std::cout<<LU.at(0).at(i).at(j)<<" ";
            }
            std::cout<<std::endl;
        }

        std::cout<<"Matrica U: "<<std::endl;
        for(int i=0;i<LU.at(1).size();i++){
            for(int j=0;j<LU.at(1).at(0).size();j++){
                std::cout<<LU.at(1).at(i).at(j)<<" ";
            }
            std::cout<<std::endl;
        }
    }
    catch(...){
        std::cout<<"LU faktorizacija ne postoji, jer je matrica singularna!";
    } 
    return 0;
}

