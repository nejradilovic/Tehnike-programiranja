//TP 2021/2022: Zadaæa 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

typedef std::vector<std::vector<bool>> Matrica;
typedef std::vector<int> vektor;
bool DaLiSeDameNapadaju(Matrica sahovska_ploca){
    int broj_redova=sahovska_ploca.size();
    int najveci_red=0;
    for(int i=0;i<sahovska_ploca.size();i++){
        if(sahovska_ploca.at(i).size()>najveci_red) najveci_red=sahovska_ploca.at(i).size();
    }
    for(int i=0;i<sahovska_ploca.size();i++){
        sahovska_ploca.at(i).resize(najveci_red,false);
    }
    for(int i=0;i<broj_redova;i++){
        for(int j=0;j<najveci_red;j++){
            if(sahovska_ploca.at(i).at(j)==true){
                for(int k=j+1;k<najveci_red;k++){
                    if(sahovska_ploca.at(i).at(j)==sahovska_ploca.at(i).at(k)) return true;   //horizontalni napad
                }
                for(int k=i+1;k<broj_redova;k++){                                            
                    if(sahovska_ploca.at(i).at(j)==sahovska_ploca.at(k).at(j)) return true;  //vertikalni napad
                }
                for(int k=1,l=1;(l+j)<najveci_red && (k+i)<broj_redova;k++,l++){
                    if(sahovska_ploca.at(i).at(j)==sahovska_ploca.at(i+k).at(j+l)) return true; //kretanje po glavnoj dijagonali
                }
                for(int k=1,l=1;(k+i)<broj_redova && (j-l)>=0;k++,l++){
                    if(sahovska_ploca.at(i).at(j)==sahovska_ploca.at(i+k).at(j-l)) return true; //kretanje po sporednoj dijagonali
                }
            }
        }
    }
    return false;
}
int main ()
{
    std::cout<<"Unesite opis sahovske ploce:"<<std::endl;
    std::cout<<"(Q za kraljicu, bilo sta drugo za prazno polje, ENTER naprazno za kraj unosa):"<<std::endl;
    Matrica sahovska_ploca;
    int max_duzina=0,i=0;
    for(;;){
        std::string red_matrice;
        std::getline(std::cin,red_matrice);
        if(red_matrice.length()==0) break;
        if(max_duzina<red_matrice.length()) max_duzina=red_matrice.length();

        sahovska_ploca.resize(i+1,std::vector<bool>(max_duzina,false));
        for(int j=0;j<red_matrice.length();j++){
            if(red_matrice.at(j)=='Q') sahovska_ploca.at(i).at(j)=true;
            else sahovska_ploca.at(i).at(j)=false;
        }
        i++;
    }
    if(DaLiSeDameNapadaju(sahovska_ploca)){
        std::cout<<"Dame se medjusobno napadaju."<<std::endl;
    }
    else{
        std::cout<<"Dame se medjusobno ne napadaju."<<std::endl;
    }
	return 0;
}

