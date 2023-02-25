// TP 2021/2022: Zadaæa 5, Zadatak 3
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// pravimo virtualnu baznu klasu
class Spremnik {
protected:
  double tezina_sanduka;
  std::string naziv_predmeta;

public:
  Spremnik(double tezina, std::string naziv) {
    tezina_sanduka = tezina;
    naziv_predmeta = naziv;
  }
  virtual ~Spremnik() = default;
  virtual double DajUkupnuTezinu() const = 0;
  double DajTezinu() const { return tezina_sanduka; }
  virtual void Ispisi() const = 0;
  virtual Spremnik *DajKopiju() const = 0;
};
// sada pravimo klase nasljedjivanja
class Sanduk : public Spremnik {
  // jer ove gore atribute iz skladista mogu koristiti jer su protected pa ne
  // moram ih opet deklarisati
  std::vector<double> tezine_predmeta;

public:
  Sanduk(double weight, std::string name, std::vector<double> weights)
      : Spremnik(weight, name), tezine_predmeta(weights) {}
  double DajUkupnuTezinu() const {
    double tezina_sanduka = DajTezinu();
    int i = 0;
    while (i < tezine_predmeta.size()) {
      tezina_sanduka = tezina_sanduka + tezine_predmeta.at(i);
      i++;
    }
    return tezina_sanduka;
  }
  void Ispisi() const {
    std::cout << "Vrsta spremnika: Sanduk" << std::endl
              << "Sadrzaj: " << naziv_predmeta << std::endl
              << "Tezine predmeta: ";
    for (auto x : tezine_predmeta)
      std::cout << x << " ";
    std::cout << " (kg)" << std::endl
              << "Vlastita tezina: " << DajTezinu() << " (kg)" << std::endl
              << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)" << std::endl;
  }
  Sanduk *DajKopiju() const { return new Sanduk(*this); }
};
class Vreca : public Spremnik {
  double tezina_materije;

public:
  Vreca(double weight, std::string name, double matter_weight)
      : Spremnik(weight, name), tezina_materije(matter_weight) {}
  double DajUkupnuTezinu() const { return DajTezinu() + tezina_materije; }
  void Ispisi() const {
    std::cout << "Vrsta spremnika: Vreca" << std::endl
              << "Sadrzaj: " << naziv_predmeta << std::endl
              << "Vlastita tezina: " << DajTezinu() << " (kg)" << std::endl
              << "Tezina pohranjene materije: " << tezina_materije << " (kg)"
              << std::endl
              << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)" << std::endl;
  }
  Vreca *DajKopiju() const { return new Vreca(*this); }
};
class Bure : public Spremnik {
  double specificna_tezina_tecnosti, zapremina_tecnosti;

public:
  Bure(double weight, std::string name, double stt, double volume)
      : Spremnik(weight, name), specificna_tezina_tecnosti(stt),
        zapremina_tecnosti(volume) {}
  void Ispisi() const {
    std::cout << "Vrsta spremnika: Bure" << std::endl
              << "Sadrzaj: " << naziv_predmeta << std::endl
              << "Vlastita tezina: " << DajTezinu() << " (kg) " << std::endl
              << "Specificna tezina tecnosti: " << specificna_tezina_tecnosti
              << " (kg/m^3)" << std::endl
              << "Zapremina tecnosti: " << zapremina_tecnosti << " (l)"
              << std::endl
              << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)" << std::endl;
  }
  double x = specificna_tezina_tecnosti * zapremina_tecnosti / 1000;
  double DajUkupnuTezinu() const { return DajTezinu() + x; }
  Bure *DajKopiju() const { return new Bure(*this); }
};
typedef std::vector<std::shared_ptr<Spremnik>> S;
typedef std::shared_ptr<Spremnik> pametni;
class Skladiste {
  S spremnik;

public:
  explicit Skladiste() {}
  Skladiste(const Skladiste &skladiste) {
    for(auto element: skladiste.spremnik)
        spremnik.push_back(std::shared_ptr<Spremnik>(element->DajKopiju()));
    
  }
  Skladiste(Skladiste &&skladiste) {
    spremnik = std::move(skladiste.spremnik);
    skladiste.spremnik.resize(0);
  }
  Skladiste &operator=(const Skladiste &skladiste) {
    for (auto x : spremnik)
      x = nullptr;
    spremnik.resize(0);
    for (auto x : skladiste.spremnik)
      spremnik.push_back(std::shared_ptr<Spremnik>(x->DajKopiju()));
    return *this;
  }
  Skladiste &operator=(Skladiste &&skladiste) {
    if (&skladiste != this)
      spremnik = std::move(skladiste.spremnik);
    return *this;
  }
  Spremnik *DodajVrecu(double weight, std::string name, double dust_weight) {
    Vreca *temp = new Vreca(weight, name, dust_weight);
    spremnik.push_back(std::shared_ptr<Spremnik>(temp));
    return temp;
  }
  Spremnik *DodajBure(double weight, std::string name, double st, double v) {
    Bure *temp = new Bure(weight, name, st, v);
    spremnik.push_back(std::shared_ptr<Spremnik>(temp));
    return temp;
  }
  Spremnik *DodajSanduk(double weight, std::string name,
                        std::vector<double> weights) {
    Sanduk *temp = new Sanduk(weight, name, weights);
    spremnik.push_back(std::shared_ptr<Spremnik>(temp));
    return temp;
  }
  Spremnik *DodajSpremnik(Spremnik *p, bool DaLiDa) {
    if (DaLiDa) {
      Spremnik *temp = p->DajKopiju();
      delete p;
      spremnik.push_back(std::shared_ptr<Spremnik>(temp));
      return temp;
    } else {
      Spremnik *temp = p->DajKopiju();
      spremnik.push_back(std::shared_ptr<Spremnik>(temp));
      return temp;
    }
  }
  Spremnik &DajNajlaksi() {
    if (spremnik.size() == 0) throw std::range_error("Skladiste je prazno");
    return **std::min_element(spremnik.begin(), spremnik.end(),
                              [](pametni temp, pametni pom) {
                                return (temp->DajTezinu() < pom->DajTezinu());
                              });
  }
  Spremnik &DajNajtezi() {
    if (spremnik.size() == 0) throw std::range_error("Skladiste je prazno");
    return **std::max_element(spremnik.begin(), spremnik.end(),
                              [](pametni pom, pametni temp) {
                                return (pom->DajTezinu() < temp->DajTezinu());
                              });
  }
  int BrojPreteskih(double x) const {
      int brojac(0);
      pametni pok;
      for(int i=0;i<spremnik.size();i++){
          if(spremnik[i]->DajUkupnuTezinu()>x) brojac++;
          }
      return brojac;
  }
  void IzlistajSkladiste() const {
    auto fejkic = spremnik;
    std::sort(fejkic.begin(), fejkic.end(), [](pametni pom, pametni temp) {
      return pom->DajUkupnuTezinu() > temp->DajUkupnuTezinu();
    });
    for (auto x : fejkic)
      x->Ispisi();
  }
  void UcitajIzDatoteke(std::string name) {
    spremnik.clear();
    std::ifstream d(name);
    if (!d)
      throw std::logic_error("Trazena datoteka ne postoji");
    std::string Name;
    char sign;
    double weight;
    for (;;) {
      d >> sign;
      if (!d)
        break;
      std::getline(d, Name);
      if (sign == 'S') {
        int x;
        std::vector<double> weights;
        d >> weight >> x;
        for (int i = 0; i < x; i++) {
          double y;
          d >> y;
          weights.push_back(y);
        }
        if (!d)
          break;
        DodajSanduk(weight, Name, weights);
      } else if (sign == 'B') {
        double st, v;
        d >> weight >> st >> v;
        if (!d)
          break;
        DodajBure(weight, Name, st, v);
      } else if (sign == 'V') {
        double dust_weight;
        d >> weight >> dust_weight;
        if (!d)
          break;
        DodajVrecu(weight, Name, dust_weight);
      }
    }
    if (d.bad())
      throw std::logic_error("Problemi pri citanju datoteke");
    else if (!d.eof() && !d)
      throw std::logic_error("Datoteka sadrzi besmislene podatke");
  }
  void BrisiSpremnik(Spremnik *kanta) {
    for (int i = 0; i < spremnik.size(); i++) {
      if (kanta == spremnik.at(i).get()) { 
          for(int j=i;j<spremnik.size()-1;j++){
              spremnik[j]=spremnik[j+1];
          }
          spremnik.resize(spremnik.size()-1);
      }
    }
  }
};
int main() {
  Skladiste ETF;
  ETF.DodajSanduk(2, "RioMare", {4, 5, 3});
  ETF.DodajBure(6, "Vino", 1200, 100);
  ETF.DodajVrecu(0.5,"Kukuruzno brasno",23.6);
  ETF.UcitajIzDatoteke("ROBA.TXT");
  ETF.IzlistajSkladiste();
  return 0;
}

