//TP 2021/2022: Zadaæa 4, Zadatak 1
#include <iostream>
#include <cmath>
#include <tuple>
#include <memory>
#include <vector>
#include <algorithm>
const double pi=4*atan(1);
long double epsilon=0.0000000001;
bool presijecanje=false;
class Kugla{
    double x,y,z,r;
    public:
        explicit Kugla(double r = 0){
            PostaviPoluprecnik(r);
            PostaviX(0);
            PostaviY(0);
            PostaviZ(0);
        };
        Kugla(double x, double y, double z, double r = 0){
            PostaviX(x);
            PostaviY(y);
            PostaviZ(z);
            PostaviPoluprecnik(r);
        };
        explicit Kugla(const std::tuple<double, double, double> &centar, double r = 0){
            x=std::get<0>(centar);
            y=std::get<1>(centar);
            z=std::get<2>(centar);
            Kugla::r=r;
        };
        double DajX() const{return x;}
        double DajY() const{return y;}
        double DajZ() const{return z;}
        std::tuple<double, double, double> DajCentar() const{
            std::tuple<double,double,double> centar;
            std::get<0>(centar)=x;
            std::get<1>(centar)=y;
            std::get<2>(centar)=z;
            return centar;
        };
        double DajPoluprecnik() const{return r;}
        double DajPovrsinu() const{return 4*r*r*pi;}
        double DajZapreminu() const{return (4/3.)*r*r*r*pi;}
        Kugla &PostaviX(double x){
            Kugla::x=x;
            return *this;
        };
        Kugla &PostaviY(double y){
            Kugla::y=y;
            return *this;
        };
        Kugla &PostaviZ(double z){
            Kugla::z=z;
            return *this;
        };
        Kugla &PostaviCentar(double x, double y, double z){
            PostaviX(x);
            PostaviY(y);
            PostaviZ(z);
            return *this;
        }
        Kugla &PostaviCentar(const std::tuple<double, double, double> &centar){
            PostaviX(std::get<0>(centar));
            PostaviY(std::get<1>(centar));
            PostaviZ(std::get<2>(centar));
            return *this;
        };
        Kugla &PostaviPoluprecnik(double r){
            if(r<0) throw std::domain_error("Ilegalan poluprecnik\n");
            Kugla::r=r;
            return *this;
        };
        void Ispisi() const{std::cout<<"{("<<x<<","<<y<<","<<z<<")"<<","<<r<<"}"<<std::endl;};
        void Transliraj(double delta_x, double delta_y, double delta_z){
            x+=delta_x;
            y+=delta_y;
            z+=delta_z;
        };
        friend bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2);
        friend bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2);
        friend bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2);
        friend bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2);
        friend bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2);
        friend bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2);
        friend bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2);
        bool DaLiSadrzi(const Kugla &k) const{
            double udaljenost_dvije_tacke=sqrt(pow(Kugla::x-k.x,2)+pow(Kugla::y-k.y,2)+pow(Kugla::z-k.z,2));
            if((Kugla::r-k.r)<udaljenost_dvije_tacke) return false;
            return true;
        }
        friend double RastojanjeCentara(const Kugla &k1, const Kugla &k2);
};
bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2){
    if(std::fabs(k1.r-k2.r)>epsilon*(std::fabs(k1.r)+std::fabs(k2.r)) ||
    std::fabs(k1.x-k2.x)>epsilon*(std::fabs(k1.x)+std::fabs(k2.x)) ||
    std::fabs(k1.y-k2.y)>epsilon*(std::fabs(k1.y)+std::fabs(k2.y)) ||
    std::fabs(k1.z-k2.z)>epsilon*(std::fabs(k1.z)+std::fabs(k2.z))) return false;
    return true;
}
bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2){
    if(std::fabs(k1.r-k2.r)<epsilon*(std::fabs(k1.r)+std::fabs(k2.r))) return true;
    return false;
}
bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2){
    if(std::fabs(k1.x-k2.x)>epsilon*(std::fabs(k1.x)+std::fabs(k2.x)) ||
    std::fabs(k1.y-k2.y)>epsilon*(std::fabs(k1.y)+std::fabs(k2.y)) ||
    std::fabs(k1.z-k2.z)>epsilon*(std::fabs(k1.z)+std::fabs(k2.z))) return false;
    return true;
}
double UdaljenostDvijeTacke(double x1, double y1, double z1, double x2, double y2, double z2){
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2)+pow(z2-z1,2));
}
bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2){
    double udaljenost_dvije_tacke=UdaljenostDvijeTacke(k1.x, k1.y, k1.z, k2.x, k2.y, k2.z);
    if(fabs(udaljenost_dvije_tacke-(k1.r+k2.r))<epsilon*(fabs(udaljenost_dvije_tacke)+fabs(k1.r+k2.r))) return true;
    return false;
}
bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2){
    double udaljenost_dvije_tacke=UdaljenostDvijeTacke(k1.x,k1.y,k1.z,k2.x,k2.y,k2.z);
    if(fabs(udaljenost_dvije_tacke-(k1.r-k2.r))<epsilon*(fabs(udaljenost_dvije_tacke)+fabs(k1.r-k2.r))) return true;
    return false;
}
bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2){
    if(DaLiSeSijeku(k1,k2) || DaLiSeDodirujuIznutra(k1, k2) || DaLiSuIdenticne(k1, k2) || k1.DaLiSadrzi(k2) || k2.DaLiSadrzi(k1) || DaLiSuKoncentricne(k1,k2)) return true;
    return false;
}
bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2){
    /*
    double udaljenost_dvije_tacke=UdaljenostDvijeTacke(k1.x, k1.y, k1.z, k2.x , k2.y, k2.z);
    if(udaljenost_dvije_tacke>fabs(k1.r-k2.r) && udaljenost_dvije_tacke<k1.r+k2.r) return true;
    return false;
    */
    if(RastojanjeCentara(k1,k2)<(k1.r+k2.r) && !DaLiSeDodirujuIznutra(k1, k2) && !DaLiSeDodirujuIzvana(k1, k2) && !k2.DaLiSadrzi(k1) && !k1.DaLiSadrzi(k2)) return true;
    return false;
}
double RastojanjeCentara(const Kugla &k1, const Kugla &k2){
    return sqrt(pow(k2.x-k1.x,2)+pow(k2.y-k1.y,2)+pow(k2.z-k1.z,2));
}
typedef std::shared_ptr<Kugla> pp;
typedef std::vector<std::pair<pp,pp>> Par;
Par Kugle;
void OcistiTok(){
    std::cin.clear();
    std::cin.ignore(10000,'\0');
}
int main ()
{
    int n;
    std::cout<<"Unesite broj kugla: ";
    std::cin>>n;
    std::vector<pp> vektor(n);
    double x,y,z,r;
    for(int i=0;i<n;i++){
        std::cout<<"Unesite centar "<<i+1<<". kugle: ";
        std::cin>>x>>y>>z;
        if(!std::cin){
            i--;
            OcistiTok();
            continue;
        }
        std::cout<<"Unesite poluprecnik "<<i+1<<". kugle: ";
        std::cin>>r;
        if(!std::cin){
            i--;
            OcistiTok();
            continue;
        }
        try{
            vektor[i]=std::make_shared<Kugla>(x,y,z,r);
        }
        catch(std::domain_error izuzetak){
            std::cout<<izuzetak.what();
            i--;
        }
    }
    std::cout<<"Unesite parametre translacije (delta_x,delta_y,delta_z): ";
    double dx,dy,dz;
    std::cin>>dx>>dy>>dz;
    std::transform(vektor.begin(),vektor.end(),vektor.begin(),[=](pp temp){temp->Transliraj(dx,dy,dz); return temp;});
    std::sort(vektor.begin(),vektor.end(),[](pp prva, pp druga){return prva->DajZapreminu()<druga->DajZapreminu();});
    std::cout<<"Kugle nakon obavljenje transformacije imaju sljedece vrijednosti:"<<std::endl;
    std::for_each(vektor.begin(),vektor.end(),[](pp temp){temp->Ispisi();});
    std::cout<<"Kugla sa najvecom povrsinom je: ";
    auto maksimalna_povrsina=std::max_element(vektor.begin(),vektor.end(),[](pp prva, pp druga){return prva->DajPovrsinu()<druga->DajPovrsinu();});
    (*maksimalna_povrsina)->Ispisi();
    std::for_each(vektor.begin(),vektor.end(),[=](pp temp){
        std::for_each(vektor.begin(), vektor.end(), [=](pp pom){
            if(DaLiSeSijeku(*temp, *pom)){
                auto tempp=std::make_pair(temp,pom);
                auto pomp=std::make_pair(pom,temp);
                auto pronasao=std::find(Kugle.begin(),Kugle.end(),tempp);
                if(pronasao==Kugle.end()){
                    presijecanje=true;
                    Kugle.push_back(pomp);
                    std::cout<<"Presjecaju se kugle: ";
                    temp->Ispisi();
                    pom->Ispisi();
                }
            }
        });
    });
    if(presijecanje==false) std::cout<<"Ne postoje kugle koje se presjecaju!";
	return 0;
}

