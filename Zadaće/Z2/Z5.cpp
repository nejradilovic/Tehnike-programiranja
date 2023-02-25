//TP 2021/2022: Zadaæa 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <deque>
#include <iomanip>
template <typename Tip1, typename Tip2, typename Funkcija>
auto GeneraliziraniSpoljasnjiProizvod(Tip1 a, Tip1 b, Tip2 c, Tip2 d, Funkcija f){
    int duzina_tip1=0,duzina_tip2=0;
    Tip1 pocetak=a,kraj=b;
    Tip2 beginning=c,end=d;
    while(pocetak++!=kraj) duzina_tip1++;
    while(beginning++!=end) duzina_tip2++;
    decltype(f(*a,*c)) **matrica=nullptr;
    try{
        matrica=new decltype(f(*a,*c))*[duzina_tip1]{};
        try{
            for(int i=0;i<duzina_tip1;i++){
                matrica[i]=new decltype(f(*a,*c))[duzina_tip2];
            }
            Tip1 pocetak=a,kraj=b;
            Tip2 beginning=c,end=d;
            for(int i=0;i<duzina_tip1;i++){
                beginning=c;
                for(int j=0;j<duzina_tip2;j++){
                    matrica[i][j]=f(*pocetak,*beginning);
                    beginning++;
                }
                pocetak++;
            }
        }
    catch(...){
        for(int i=0;i<duzina_tip1;i++) delete [] matrica[i];
        delete [] matrica;
        throw;
    }
    }
    catch(...){
        throw std::range_error("Nema dovoljno memorije!");
    }
    return matrica;
}
int main ()
{
    try{
    int duzina_vektora;
    std::cout<<"Duzina prve sekvence: ";
    std::vector<double> vektor;
    std::cin>>duzina_vektora;
    double element_vektora;
    std::cout<<"Elementi prve sekvence: ";
    for(int i=0;i<duzina_vektora;i++){
        std::cin>>element_vektora;
        vektor.push_back(element_vektora);
    }
    int duzina_deka;
    std::cout<<"Duzina druge sekvence: ";
    std::deque<double> dek;
    std::cin>>duzina_deka;
    double element_deka;
    std::cout<<"Elementi druge sekvence: ";
    for(int i=0;i<duzina_deka;i++){
        std::cin>>element_deka;
        dek.push_back(element_deka);
    }
    std::cout<<"Generalizirani spoljasnji proizvod uz f(x,y)=x+2y: ";
    auto Matrica=GeneraliziraniSpoljasnjiProizvod(vektor.begin(),vektor.end(),dek.begin(),dek.end(),[](double x, double y){return x+2*y;});
	for(int i=0;i<duzina_vektora;i++){
        for(int j=0;j<duzina_deka;j++){
            std::cout<<std::setw(10)<<Matrica[i][j];
        }
        std::cout<<std::endl;
    }
    for(int i=0;i<duzina_vektora;i++) delete [] Matrica[i];
    delete [] Matrica;
    }
    catch(std::range_error izuzetak){
        std::cout<<izuzetak.what();
    }
    return 0;
}

