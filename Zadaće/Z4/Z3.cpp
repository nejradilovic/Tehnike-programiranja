//TP 2021/2022: Zadaæa 4, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <algorithm>
typedef std::pair<int,int> vrijeme;
class Polazak{
    std::string odrediste;
    int broj_perona,broj_voza,sat_polaska,minute_polaska,trajanje_voznje,kasnjenje;
    bool brzi_voz;
    static bool ProvjeraVremena(int h, int m, int duration){
        if(h<0 || h>23 || m<0 || m>59 || duration<0) return false;
        return true;
    }
    public:
    Polazak(std::string odrediste, int broj_voza, int broj_perona, bool brzi_voz, int sat_polaska, int minute_polaska, int trajanje_voznje);
    void PostaviKasnjenje(int kasnjenje){
        Polazak::kasnjenje=kasnjenje;
    };
    bool DaLiKasni() const{return kasnjenje!=0;};
    int DajTrajanjeVoznje() const{return trajanje_voznje;};
    std::pair<int, int> DajOcekivanoVrijemePolaska() const{
        vrijeme ocekivano;
        ocekivano.first=sat_polaska;
        ocekivano.second=minute_polaska;
        if(DaLiKasni()){
            ocekivano.second+=kasnjenje;
            while(ocekivano.second>59){
                ocekivano.first++;
                ocekivano.second-=60;
            }
            while(ocekivano.first>23) ocekivano.first-=24;
        }
        return ocekivano;
    }
    std::pair<int, int> DajOcekivanoVrijemeDolaska() const{
        vrijeme ocekivano;
        ocekivano.first=sat_polaska+trajanje_voznje/60+kasnjenje/60;
        ocekivano.second=minute_polaska+trajanje_voznje%60+kasnjenje%60;
        while(ocekivano.second>59){
            ocekivano.first++;
            ocekivano.second-=60;
        }
        while(ocekivano.first>23) ocekivano.first-=24;
        return ocekivano;
    };
    void Ispisi() const{
        vrijeme vrijeme_polaska=DajOcekivanoVrijemePolaska(),vrijeme_dolaska=DajOcekivanoVrijemeDolaska();
        if(brzi_voz) std::cout<<"Brzi voz ";
        else std::cout<<"Lokalni voz ";
        if(!DaLiKasni()){
            std::cout<<"broj "<<broj_voza<<", odrediste "<<odrediste<<", polazi sa perona "<<broj_perona<<" u ";
            if(sat_polaska>9) std::cout<<sat_polaska;
            else std::cout<<"0"<<sat_polaska;
            std::cout<<":";
            if(minute_polaska>9) std::cout<<minute_polaska;
            else std::cout<<"0"<<minute_polaska;
            std::cout<<", a na odrediste stize u ";
            if(vrijeme_dolaska.first>9) std::cout<<vrijeme_dolaska.first;
            else std::cout<<"0"<<vrijeme_dolaska.first;
            std::cout<<":";
            if(vrijeme_dolaska.second>9) std::cout<<vrijeme_dolaska.second;
            else std::cout<<"0"<<vrijeme_dolaska.second;
            std::cout<<". Putnicima i voznom osoblju zelimo ugodno putovanje."<<std::endl;
        }
        else{
            std::cout<<"broj "<<broj_voza<<", odrediste "<<odrediste<<", sa predvidjenim vremenom polaska u ";
            if(sat_polaska>9) std::cout<<sat_polaska;
            else std::cout<<"0"<<sat_polaska;
            std::cout<<":";
            if(minute_polaska>9) std::cout<<minute_polaska;
            else std::cout<<"0"<<minute_polaska;
            std::cout<<", kasni oko "<<kasnjenje<<" minuta, te ce poci oko ";
            if(vrijeme_polaska.first>9) std::cout<<vrijeme_polaska.first;
            else std::cout<<"0"<<vrijeme_polaska.first;
            std::cout<<":";
            if(vrijeme_polaska.second>9) std::cout<<vrijeme_polaska.second;
            else std::cout<<"0"<<vrijeme_polaska.second;
            std::cout<<". Ocekuje se da voz stigne na odrediste oko ";
            if(vrijeme_dolaska.first>9) std::cout<<vrijeme_dolaska.first;
            else std::cout<<"0"<<vrijeme_dolaska.first;
            std::cout<<":";
            if(vrijeme_dolaska.second>9) std::cout<<vrijeme_dolaska.second;
            else std::cout<<"0"<<vrijeme_dolaska.second;
            std::cout<<". Izvinjavamo se putnicima zbog eventualnih neugodnosti."<<std::endl;
        }
    };
};
Polazak::Polazak(std::string odrediste, int broj_voza, int broj_perona, bool brzi_voz, int sat_polaska, int minute_polaska, int trajanje_voznje): kasnjenje(0){
    if(broj_voza>99999) throw std::domain_error("Neispravan broj voza");
    if(broj_perona<1 || broj_perona>6) throw std::domain_error("Neispravan broj perona"); 
    if(!ProvjeraVremena(sat_polaska,minute_polaska, trajanje_voznje)) throw std::domain_error("Neispravno vrijeme");
    Polazak::odrediste=odrediste;
    Polazak::broj_voza=broj_voza;
    Polazak::broj_perona=broj_perona;
    Polazak::brzi_voz=brzi_voz;
    Polazak::sat_polaska=sat_polaska;
    Polazak::minute_polaska=minute_polaska;
    Polazak::trajanje_voznje=trajanje_voznje;
}

class RedVoznje{
    Polazak **Polasci{};
    int broj_polazaka;
    int max_br_polazaka;
    public:
    explicit RedVoznje(int max_broj_polazaka): broj_polazaka(0), max_br_polazaka(max_broj_polazaka){
        Polasci=new Polazak*[max_broj_polazaka]{};
    }
    RedVoznje(std::initializer_list<Polazak> lista_polazaka): broj_polazaka(lista_polazaka.size()), max_br_polazaka(lista_polazaka.size()),Polasci(new Polazak*[lista_polazaka.size()]{}){
        auto iterator=lista_polazaka.begin();
        for(int i=0;i<lista_polazaka.size();i++){
            try{
                Polasci[i]=new Polazak(*iterator);
                iterator++;
            }
            catch(...){
                for(int i=0;i<lista_polazaka.size();i++){
                    delete Polasci[i];
                    Polasci[i]=nullptr;
                }
                throw;
            }
        }
    }
    ~RedVoznje(){
        for(int i=0;i<broj_polazaka;i++) delete Polasci[i];
        delete [] Polasci;
        broj_polazaka=0;
    }
    RedVoznje(const RedVoznje &red_voznje):broj_polazaka(red_voznje.broj_polazaka),max_br_polazaka(red_voznje.max_br_polazaka){
        Polasci=new Polazak*[red_voznje.max_br_polazaka]{};
        try{
            for(int i=0;i<red_voznje.broj_polazaka;i++) Polasci[i]=new Polazak(*red_voznje.Polasci[i]);
        }
        catch(...){
            for(int i=0;i<broj_polazaka;i++) delete Polasci[i];
            delete [] Polasci;
            throw;
        }
    }
    RedVoznje(RedVoznje &&red_voznje):broj_polazaka(red_voznje.broj_polazaka), max_br_polazaka(red_voznje.max_br_polazaka),Polasci(red_voznje.Polasci){
        red_voznje.Polasci=nullptr;
        red_voznje.broj_polazaka=0;
    }
    RedVoznje &operator =(const RedVoznje &red_voznje){
        if(&red_voznje!=this){
        if(broj_polazaka<red_voznje.broj_polazaka){
            for(int i=0;i<broj_polazaka;i++) delete Polasci[i];
            delete[] Polasci;
            Polasci=new Polazak*[red_voznje.max_br_polazaka]{};
            try{
                for(int i=broj_polazaka;i<red_voznje.broj_polazaka;i++) Polasci[i]=new Polazak(*red_voznje.Polasci[i]);
            }
            
            catch(...){
                for(int i=broj_polazaka;i<red_voznje.broj_polazaka;i++){
                    delete Polasci[i];
                    Polasci[i]=nullptr;
                }
                throw;
            }
        }
        else{
            for(int i=red_voznje.broj_polazaka;i<broj_polazaka;i++){
                delete Polasci[i];
                Polasci[i]=nullptr;
            }
        }
        broj_polazaka=red_voznje.broj_polazaka;
        for(int i=0;i<broj_polazaka;i++) *Polasci[i]=*red_voznje.Polasci[i];
        }
        return *this;
    }
    RedVoznje &operator =(RedVoznje &&red_voznje){
        if(&red_voznje!=this){
        std::swap(broj_polazaka,red_voznje.broj_polazaka);
        std::swap(Polasci,red_voznje.Polasci);
        }
        return *this;
    }
    void RegistrirajPolazak(std::string odrediste, int broj_voza, bool brzi_voz,
    int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje){
        if(broj_polazaka==max_br_polazaka) throw std::range_error("Dostignut maksimalni broj polazaka");
        Polasci[broj_polazaka++]=new Polazak(odrediste,broj_voza,broj_perona,brzi_voz,sat_polaska,minute_polaska,trajanje_voznje);
    }
    void RegistrirajPolazak(Polazak *polazak){
        if(broj_polazaka==max_br_polazaka) throw std::range_error("Dostignut maksimalni broj polazaka");
        Polasci[broj_polazaka]=polazak;
        broj_polazaka++;
    }
    int DajBrojPolazaka() const{return broj_polazaka;}
    int DajBrojPolazakaKojiKasne() const{
        int zakasnjeli(0);
        for(int i=0;i<broj_polazaka;i++) 
        if(Polasci[i]->DaLiKasni()) zakasnjeli++;
        return zakasnjeli;
    }
    int DajProsjecnoTrajanjeVoznji() const{
        double zakasnjeli(0);
        for(int i=0;i<broj_polazaka;i++) zakasnjeli+=Polasci[i]->DajTrajanjeVoznje();
        return zakasnjeli/double(broj_polazaka);
    }
    Polazak &DajPrviPolazak() const{
        if(broj_polazaka==0) throw std::domain_error("Nema registriranih polazaka");
        return **std::min_element(Polasci,Polasci+broj_polazaka,[](Polazak *pom, Polazak *temp){
            int min1,min2,h1,h2;
            pom->DajOcekivanoVrijemePolaska();
            temp->DajOcekivanoVrijemePolaska();
            min1+=h1*60;
            min2+=h2*60;
            return(min1<min2);
        });
    }
    Polazak &DajPosljednjiPolazak() const{
        if(broj_polazaka==0) throw std::domain_error("Nema registriranih polazaka");
        return **std::min_element(Polasci,Polasci+broj_polazaka,[](Polazak *pom, Polazak *temp){
            int min1,min2,h1,h2;
            pom->DajOcekivanoVrijemePolaska();
            temp->DajOcekivanoVrijemePolaska();
            min1+=h1*60;
            min2+=h2*60;
            return(min1>min2);
        });
    }
    void IsprazniRedVoznje(){
        std::for_each(Polasci,Polasci+broj_polazaka,[](Polazak *pom){delete pom;});
        broj_polazaka=0;
    }
    void Ispisi(int sati, int minute) const{
        std::sort(Polasci,Polasci+broj_polazaka,[](Polazak *pom, Polazak *temp){
            int s=pom->DajOcekivanoVrijemePolaska().first;
            int h=temp->DajOcekivanoVrijemePolaska().first;
            int m=pom->DajOcekivanoVrijemePolaska().second;
            int mm=temp->DajOcekivanoVrijemePolaska().second;
            if(h>s) return true;
            else if(h==s){
                if(mm>m) return true;
            }
            return false;
        });
        for(int i=0;i<broj_polazaka;i++)
            if(Polasci[i]->DajOcekivanoVrijemePolaska().first>sati || (Polasci[i]->DajOcekivanoVrijemePolaska().second>=minute && Polasci[i]->DajOcekivanoVrijemePolaska().first==sati))
            Polasci[i]->Ispisi();
    }
};
int main ()
{
    RedVoznje rd(3);
    rd.RegistrirajPolazak("Srebrenik",144,false,2,18,30,230);
    rd.RegistrirajPolazak("Sjenica",104,false,1,14,8,400);
    rd.RegistrirajPolazak("Pocitelj",907,true,1,20,20,120);
    Polazak *p=new Polazak("Prijepolje",1010,1,true,10,10,150);
    rd.RegistrirajPolazak(p);
    RedVoznje novi(std::move(rd));
    std::cout<<"Broj kasnjenja: "<<novi.DajBrojPolazakaKojiKasne();
    std::cout<<novi.DajBrojPolazaka();
	return 0;
}

