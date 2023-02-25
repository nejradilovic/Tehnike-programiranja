//TP 2021/2022: Zadaæa 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include <algorithm>
#include <iomanip>
typedef std::pair<double,double> Par;
typedef std::vector<std::pair<double,double>> Vektor;
typedef std::function<double(double)> Funkcija;
double TezinskiKoeficijenti(int i, int duzina, int red_interpolacije, Vektor vektor){
    int donja_granica=std::max(1,i+1-red_interpolacije);
    int gornja_granica=std::min(i+1,duzina-red_interpolacije);
    double suma(0),xi(0),xj(0);
    for(int j=donja_granica;j<=gornja_granica;j++){
        double proizvod=1;
        xi=vektor.at(i).first;
        for(int k=j-1;k<j+red_interpolacije;k++){
            if(k==i) continue;
            xj=vektor.at(k).first;
            proizvod*=1/(xi-xj);
        }
        int predznak=pow(-1,j-1);
        suma+=predznak*proizvod;
    }
    return suma;
}
bool Kriterij(Par p1,Par p2){
    return p1.first<p2.first;
}
Funkcija BaricentricnaInterpolacija(Vektor vektor, int d){
    if(d<0 || d>=vektor.size()) throw std::domain_error("Nedozvoljen red");
    sort(vektor.begin(),vektor.end());
    for(int i=0;i<vektor.size()-1;i++){
        if(vektor.at(i).first==vektor.at(i+1).first) throw std::domain_error("Neispravni cvorovi");
    }
return [=](double x){
    double nazivnik(0),brojnik(0),x1(0),y1(0),w(0),f(0);
    int i=0;
    while(i<vektor.size()){
        x1=vektor.at(i).first;
        y1=vektor.at(i).second;
        if(x==x1) return y1;
        w=TezinskiKoeficijenti(i,vektor.size(),d,vektor);
        brojnik+=(w/(x-x1))*y1;
        nazivnik+=(w/(x-x1));
        i++;
    }
    f=brojnik/nazivnik;
    return f;
    };
}
Funkcija BaricentricnaInterpolacija(Funkcija f,double xmin,double xmax,double deltax,int d){
    Vektor vektor;
    if(xmin>xmax || deltax<=0) throw std::domain_error("Nekorektni parametri");
    for(auto i=xmin;i<=xmax;i+=deltax){
        double y=f(i);
        Par par={i,y};
        vektor.push_back(par);
    }
    try{
        auto F=BaricentricnaInterpolacija(vektor,d);
        return F;
    }
    catch(...){
        throw;
    }
}
double Fja(double x){
    return x*x+sin(x);
}
int main ()
{
    try{
    int opcija;
    std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    std::cin>>opcija;
    if(opcija==1){
        int broj_cvorova=0;
        std::cout<<"Unesite broj cvorova: ";
        std::cin>>broj_cvorova;
        Vektor vektor(broj_cvorova);
        std::cout<<"Unesite cvorove kao parove x y: ";
        for(int i=0;i<broj_cvorova;i++){
            std::cin>>vektor.at(i).first>>vektor.at(i).second;
        }
        int d;
        std::cout<<"Unesite red interpolacije: ";
        std::cin>>d;
        auto Fun=BaricentricnaInterpolacija(vektor,d);
        double broj;
        for(;;){
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
            std::cin>>broj;
            if(!std::cin) return 0;
            std::cout<<"f("<<broj<<") = "<<Fun(broj)<<std::endl;
        }
    }
    else if(opcija==2){
        double xmin,xmax,deltax;
        std::cout<<"Unesite krajeve intervala i korak: ";
        std::cin>>xmin>>xmax>>deltax;
        int d;
        std::cout<<"Unesite red interpolacije: ";
        std::cin>>d;
        auto Fun=BaricentricnaInterpolacija(Fja,xmin,xmax,deltax,d);
        double broj;
        for(;;){
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
            std::cin>>broj;
            if(!std::cin) return 0;
            std::cout<<"f("<<broj<<") = "<<Fja(broj)<<" "<<"fapprox("<<broj<<") = "<<Fun(broj)<<std::endl;
        }
    }
    }
    catch(std::domain_error e){
        std::cout<<e.what();
    }
    catch(std::range_error e){
        std::cout<<e.what();
    }
	return 0;
}

