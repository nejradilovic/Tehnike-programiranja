//TP 2021/2022: Zadaæa 2, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
//globalne promjenjive
bool aktivnost=true;
bool svemulijepomdodjekraj=false;
enum class Pravci {Sjever, Sjeveroistok, Istok, Jugoistok, Jug, Jugozapad, Zapad, Sjeverozapad};
enum class Smjer {Nalijevo, Nadesno};
enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar, NeispravanParametar};
enum class Komande {Aktiviraj, Deaktiviraj, Nalijevo, Nadesno, Idi, Kraj};
Pravci orijentacija=Pravci::Sjever;
//funkcije 
void  AktivirajRobota(){
    aktivnost=true;
}
void DeaktivirajRobota(){
    aktivnost=false;
}
void PrijaviGresku(KodoviGresaka kod_greske){
    if(int(kod_greske)==0) std::cout<<"Nerazumljiva komanda!\n";
    if(int(kod_greske)==1) std::cout<<"Komanda trazi parametar koji nije naveden!\n";
    if(int(kod_greske)==2) std::cout<<"Zadan je suvisan parametar nakon komande!\n";
    if(int(kod_greske)==3) std::cout<<"Parametar komande nije ispravan!\n";
}
void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu){
    //nalijevo kretanje
    if(na_koju_stranu==Smjer::Nalijevo && orijentacija==Pravci::Sjever) orijentacija=Pravci::Sjeverozapad;
    else if(na_koju_stranu==Smjer::Nalijevo && orijentacija==Pravci::Sjeverozapad) orijentacija=Pravci::Zapad;
    else if(na_koju_stranu==Smjer::Nalijevo && orijentacija==Pravci::Zapad) orijentacija=Pravci::Jugozapad;
    else if(na_koju_stranu==Smjer::Nalijevo && orijentacija==Pravci::Jugozapad) orijentacija=Pravci::Jug;
    else if(na_koju_stranu==Smjer::Nalijevo && orijentacija==Pravci::Jug) orijentacija=Pravci::Jugoistok;
    else if(na_koju_stranu==Smjer::Nalijevo && orijentacija==Pravci::Jugoistok) orijentacija=Pravci::Istok;
    else if(na_koju_stranu==Smjer::Nalijevo && orijentacija==Pravci::Istok) orijentacija=Pravci::Sjeveroistok;
    else if(na_koju_stranu==Smjer::Nalijevo && orijentacija==Pravci::Sjeveroistok) orijentacija=Pravci::Sjever;
    //nadesno kretanje
    if(na_koju_stranu==Smjer::Nadesno && orijentacija==Pravci::Sjever) orijentacija=Pravci::Sjeveroistok;
    else if(na_koju_stranu==Smjer::Nadesno && orijentacija==Pravci::Sjeveroistok) orijentacija=Pravci::Istok;
    else if(na_koju_stranu==Smjer::Nadesno && orijentacija==Pravci::Istok) orijentacija=Pravci::Jugoistok;
    else if(na_koju_stranu==Smjer::Nadesno && orijentacija==Pravci::Jugoistok) orijentacija=Pravci::Jug;
    else if(na_koju_stranu==Smjer::Nadesno && orijentacija==Pravci::Jug) orijentacija=Pravci::Jugozapad;
    else if(na_koju_stranu==Smjer::Nadesno && orijentacija==Pravci::Jugozapad) orijentacija=Pravci::Zapad;
    else if(na_koju_stranu==Smjer::Nadesno && orijentacija==Pravci::Zapad) orijentacija=Pravci::Sjeverozapad;
    else if(na_koju_stranu==Smjer::Nadesno && orijentacija==Pravci::Sjeverozapad) orijentacija=Pravci::Sjever;
}
void Idi(int &x, int &y, Pravci orijentacija, int korak){
    if(aktivnost==true){
    if(orijentacija==Pravci::Sjever){
        y=y+korak;
    }
    else if(orijentacija==Pravci::Jug){
        y=y-korak;
    }
    else if(orijentacija==Pravci::Zapad){
        x=x-korak;
    }
    else if(orijentacija==Pravci::Istok){
        x=x+korak;
    }
    else if(orijentacija==Pravci::Sjeveroistok){
        x=x+korak;
        y=y+korak;
    }
    else if(orijentacija==Pravci::Sjeverozapad){
        y=y+korak;
        x=x-korak;
    }
    else if(orijentacija==Pravci::Jugoistok){
        x=x+korak;
        y=y-korak;
    }
    else if(orijentacija==Pravci::Jugozapad){
        x=x-korak;
        y=y-korak;
    }
    }
}
void IspisiPoziciju(int x, int y, Pravci orijentacija){
        if(orijentacija==Pravci::Sjever) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever.\n";
        else if(orijentacija==Pravci::Jug) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na jug.\n";
        else if(orijentacija==Pravci::Istok) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na istok.\n";
        else if(orijentacija==Pravci::Zapad) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na zapad.\n";
        else if(orijentacija==Pravci::Sjeveroistok) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjeveroistok.\n";
        else if(orijentacija==Pravci::Sjeverozapad) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjeverozapad.\n";
        else if(orijentacija==Pravci::Jugoistok) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na jugoistok.\n";
        else if(orijentacija==Pravci::Jugozapad) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na jugozapad.\n";
    else if (aktivnost==false){
        if(orijentacija==Pravci::Sjever) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever.\n";
        else if(orijentacija==Pravci::Jug) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever.\n";
        else if(orijentacija==Pravci::Istok) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever.\n";
        else if(orijentacija==Pravci::Zapad) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever.\n";
        else if(orijentacija==Pravci::Sjeveroistok) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever.\n";
        else if(orijentacija==Pravci::Sjeverozapad) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever.\n";
        else if(orijentacija==Pravci::Jugoistok) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever.\n";
        else if(orijentacija==Pravci::Jugozapad) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever.\n";
    }
}
void GutajPraznine(){
    while(std::cin.peek()==' '){
        std::cin.get();
    }
}

bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske){
    std::cin>>std::ws;
    if(std::cin.peek()=='A'){
        std::cin.get();
        if(std::cin.peek()=='+'){
            komanda=Komande::Aktiviraj;
            std::cin.get();
            bool temp=true;
            while(std::cin.peek()!='\n'){
                if(std::cin.get()!=' '){
                    temp=false;
                    kod_greske=KodoviGresaka::SuvisanParametar;
                }
            }
            return temp;
        }
        else if(std::cin.peek()=='-'){
            komanda=Komande::Deaktiviraj;
            std::cin.get();
            bool temp=true;
            while(std::cin.peek()!='\n'){
                if(std::cin.get()!=' '){
                    temp=false;
                    kod_greske=KodoviGresaka::SuvisanParametar;
                }
            }
            return temp;
        }
        else{
            kod_greske=KodoviGresaka::PogresnaKomanda;
            return false;
        }
    }
        else if(std::cin.peek()=='I'){
            std::cin.get();
            GutajPraznine();
            if(std::cin.peek()=='\n'){
                kod_greske=KodoviGresaka::NedostajeParametar;
                return false;
            }
            int brojic;
            std::cin>>brojic;
            if(!std::cin){
                kod_greske=KodoviGresaka::NeispravanParametar;
                return false;
            }
            else if(std::cin.peek()!='\n' && std::cin.peek()!=' '){
                kod_greske=KodoviGresaka::NeispravanParametar;
                return false;
            }
            GutajPraznine();
            if(std::cin.peek()!='\n'){
                kod_greske=KodoviGresaka::SuvisanParametar;
                return false;
            }
            else{
                komanda=Komande::Idi;
                parametar=brojic;
                return true;
            }
        }
        else if(std::cin.peek()=='L'){
                komanda=Komande::Nalijevo;
                std::cin.get();
                bool temp=true;
                while(std::cin.peek()!='\n'){
                if(std::cin.get()!=' '){
                    temp=false;
                    kod_greske=KodoviGresaka::SuvisanParametar;
                }
            }
            return temp;
            }
        else if(std::cin.peek()=='D'){
                komanda=Komande::Nadesno; 
                std::cin.get();
                bool temp=true;
                while(std::cin.peek()!='\n'){
                if(std::cin.get()!=' '){
                    temp=false;
                    kod_greske=KodoviGresaka::SuvisanParametar;
                }
            }
            return temp;
            }
        else if(std::cin.peek()=='K'){
                komanda=Komande::Kraj;
                std::cin.get();
                bool temp=true;
                while(std::cin.peek()!='\n'){
                if(std::cin.get()!=' '){
                    temp=false;
                    kod_greske=KodoviGresaka::SuvisanParametar;
                }
            }
            return temp;
            }
            else{
                kod_greske=KodoviGresaka::PogresnaKomanda;
                return false;
            }
        return true;
}
void IzvrsiKomandu(Komande komanda,int parametar, int &x, int &y, Pravci &orijentacija){
    if(komanda==Komande::Aktiviraj) AktivirajRobota();
    else if(komanda==Komande::Deaktiviraj) DeaktivirajRobota();
    else if(komanda==Komande::Nalijevo) Rotiraj(orijentacija,Smjer::Nalijevo);
    else if(komanda==Komande::Nadesno) Rotiraj(orijentacija,Smjer::Nadesno);
    else if(komanda==Komande::Kraj){
        svemulijepomdodjekraj=true; 
        return ;
    }
    else if(komanda==Komande::Idi) Idi(x,y,orijentacija,parametar);
}
void Ciscenje(){
    std::cin.clear();
    std::cin.ignore(10000,'\n');
}
int main ()
{
    AktivirajRobota();
    int x=0,y=0;
    Pravci orijentacija=Pravci::Sjever;
    IspisiPoziciju(x,y,orijentacija);
    while(1){
        int parametar;
        Komande komanda;
        KodoviGresaka kod_greske;
        std::cout<<"Unesi komandu: "<<std::endl;
        if(UnosKomande(komanda,parametar,kod_greske)){
            IzvrsiKomandu(komanda,parametar,x,y,orijentacija);
            if(komanda==Komande::Kraj) break;
            IspisiPoziciju(x,y,orijentacija);
        }
        else{
            PrijaviGresku(kod_greske); 
        }
        Ciscenje();
    }
    std::cout<<"Dovidjenja!"; 
	return 0;
}

