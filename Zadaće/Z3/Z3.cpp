// TP 2021/2022: Zadaæa 3, Zadatak 3
#include <cmath>
#include <iomanip>
#include <iostream>
#include <new>
#include <vector>

template <typename TipElemenata> struct Matrica {
  int broj_redova, broj_kolona;
  TipElemenata **elementi = nullptr;
  char ime_matrice;
};
template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat) {
  if (!mat.elementi)
    return;
  for (int i = 0; i < mat.broj_redova; i++)
    delete[] mat.elementi[i];
  delete[] mat.elementi;
  mat.elementi = nullptr;
}
template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int broj_redova, int broj_kolona,
                                    char ime = 0) {
  Matrica<TipElemenata> mat;
  mat.broj_redova = broj_redova;
  mat.broj_kolona = broj_kolona;
  mat.ime_matrice = ime;
  mat.elementi = new TipElemenata *[broj_redova] {};
  try {
    for (int i = 0; i < broj_redova; i++) {
      mat.elementi[i] = new TipElemenata[broj_kolona];
    }
  } catch (...) {
    UnistiMatricu(mat);
    throw;
  }
  return mat;
}
template <typename TipElemenata>
void UnesiMatricu(char ime, Matrica<TipElemenata> &mat) {
  for (int i = 0; i < mat.broj_redova; i++) {
    for (int j = 0; j < mat.broj_kolona; j++) {
      std::cout << ime << "(" << i + 1 << "," << j + 1 << ") = ";
      std::cin >> mat.elementi[i][j];
    }
  }
}
template <typename TipElemenata>
void IspisiMatricu(Matrica<TipElemenata> &mat, int sirina_ispisa,
                   int preciznost = 6, bool treba_brisati = false) {
  for (int i = 0; i < mat.broj_redova; i++) {
    for (int j = 0; j < mat.broj_kolona; j++)
      std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost)
                << mat.elementi[i][j];
    std::cout << std::endl;
  }
  if (treba_brisati)
    UnistiMatricu(mat);
}
template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
                                  const Matrica<TipElemenata> &m2) {
  if (m1.broj_redova != m2.broj_redova || m1.broj_kolona != m2.broj_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  auto m3 = StvoriMatricu<TipElemenata>(m1.broj_redova, m1.broj_kolona);
  for (int i = 0; i < m1.broj_redova; i++)
    for (int j = 0; j < m1.broj_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m3;
}
template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1,
                                     const Matrica<TipElemenata> &m2) {
  if (m1.broj_kolona != m2.broj_redova)
    throw std::domain_error("Matrice nisu saglasne za mnozenje");
  auto m3 = StvoriMatricu<TipElemenata>(m1.broj_redova, m2.broj_kolona);
  for (int i = 0; i < m1.broj_redova; i++){
    for (int j = 0; j < m2.broj_kolona; j++){
        TipElemenata suma=0;
        for (int k = 0; k < m1.broj_kolona; k++) suma+= m1.elementi[i][k] * m2.elementi[k][j];
        m3.elementi[i][j]=suma;
    }
  }
  return m3;
}
template <typename TipElemenata>
bool PrazanVektor(std::vector<TipElemenata> vektor) {
  if (vektor.size() == 0)
    return true;
  return false;
}
template <typename TipElemenata>
Matrica<TipElemenata> SkalarniProizvod(const Matrica<TipElemenata> &M, double skalar) {
    Matrica<TipElemenata> pomnozena;
    try{
    pomnozena=StvoriMatricu<TipElemenata>(M.broj_redova,M.broj_kolona);
    }
    catch(...){
        throw;
    }
  for (int i = 0; i < M.broj_redova; i++){
    for (int j = 0; j < M.broj_kolona; j++){
      pomnozena.elementi[i][j] =M.elementi[i][j]*skalar;
    }
  }
  
      return pomnozena;
}
template <typename TipElemenata>
void IzjednaciMatrice(const Matrica<TipElemenata> &m1,
                      const Matrica<TipElemenata> &m2) {
  for (int i = 0; i < m1.broj_redova; i++)
    for (int j = 0; j < m1.broj_kolona; j++)
      m1.elementi[i][j] = m2.elementi[i][j];
}
template <typename TipElemenata>
Matrica<TipElemenata> MatricniPolinom(const Matrica<TipElemenata> &A,
                                      std::vector<double> p) {
  if (A.broj_redova != A.broj_kolona)
    throw std::domain_error("Matrica mora biti kvadratna");
  Matrica<TipElemenata> matricnipolinom;
  matricnipolinom = StvoriMatricu<TipElemenata>(A.broj_redova, A.broj_kolona);
  if (PrazanVektor(p)) {
    for (int i = 0; i < A.broj_redova; i++) {
      for (int j = 0; j < A.broj_kolona; j++) {
        matricnipolinom.elementi[i][j] = 0;
      }
    }
    return matricnipolinom;
  }
  int n = p.size();
  for (int k = 0; k < n; k++) {
    if (k == 0) {
      for (int i = 0; i < A.broj_redova; i++) {
        for (int j = 0; j < A.broj_kolona; j++) {
          if (i == j)
            matricnipolinom.elementi[i][j] = p.at(0);
          else
            matricnipolinom.elementi[i][j] = 0;
        }
      }
    } else if (k == 1) {
      Matrica<TipElemenata> temp;
      try {
        temp = StvoriMatricu<TipElemenata>(A.broj_redova, A.broj_kolona);
      } catch (...) {
        throw;
      }
      //temp=SkalarniProizvod(A, p.at(1));
      for(int i=0;i<A.broj_redova;i++){
          for(int j=0;j<A.broj_kolona;j++){
              temp.elementi[i][j]=A.elementi[i][j]*p.at(1);
          }
      }
      Matrica<TipElemenata> pom;
      pom = ZbirMatrica(matricnipolinom, temp);
      IzjednaciMatrice(matricnipolinom, pom);
      UnistiMatricu(temp);
      UnistiMatricu(pom);
    } else {
      Matrica<TipElemenata> m;
      try {
        m = StvoriMatricu<TipElemenata>(A.broj_redova, A.broj_kolona);
      } catch (...) {
        UnistiMatricu(matricnipolinom);
        throw;
      }
      for (int i = 0; i < A.broj_redova; i++) {
        for (int j = 0; j < A.broj_kolona; j++) {
          IzjednaciMatrice(m, A);
        }
      }
      int b = k - 1;
      while (b != 0) {
        Matrica<TipElemenata> temp;
        temp = ProduktMatrica(m, A);
        for (int i = 0; i < A.broj_redova; i++) {
          for (int j = 0; j < A.broj_kolona; j++) {
            IzjednaciMatrice(m, temp);
          }
        }
        b--;
        UnistiMatricu(temp);
      }
      Matrica<TipElemenata> temporary;
      try {
        temporary = StvoriMatricu<TipElemenata>(A.broj_redova, A.broj_kolona);
      } catch (...) {
        UnistiMatricu(matricnipolinom);
        UnistiMatricu(m);
        throw;
      }
      for (int i = 0; i < A.broj_redova; i++) {
        for (int j = 0; j < A.broj_kolona; j++) {
          temporary.elementi[i][j] = m.elementi[i][j] * p.at(k);
        }
      }
      Matrica<TipElemenata> temp;
      temp = ZbirMatrica(matricnipolinom, temporary);
      for (int i = 0; i < A.broj_redova; i++) {
        for (int j = 0; j < A.broj_kolona; j++) {
          IzjednaciMatrice(matricnipolinom, temp);
        }
      }
      UnistiMatricu(temporary);
      UnistiMatricu(m);
      UnistiMatricu(temp);
    }
  }
  return matricnipolinom;
}
int main() {
  std::cout << "Unesite dimenziju kvadratne matrice: ";
  int n(0);
  std::cin >> n;
  std::cout << "Unesite elemente matrice A: " << std::endl;
  Matrica<double> A;
  try {
    A = StvoriMatricu<double>(n, n, 'A');
  } catch (...) {
    std::cout << "Greska";
  }
  UnesiMatricu('A', A);
  std::cout << "Unesite red polinoma: ";
  int red_polinoma = 0;
  std::cin >> red_polinoma;
  std::cout << "Unesite koeficijente polinoma: ";
  std::vector<double> koeficijenti_polinoma;
  for (int i = 0; i < red_polinoma + 1; i++) {
    double koeficijent;
    std::cin >> koeficijent;
    koeficijenti_polinoma.push_back(koeficijent);
  }
  //for(auto x:koeficijenti_polinoma) std::cout<<x<<" ";
  Matrica<double> polinom;
  try {
    polinom = MatricniPolinom(A, koeficijenti_polinoma);
  } catch (...) {
    std::cout << "Greska";
  }
  IspisiMatricu(polinom, 10, 6, true);
  UnistiMatricu(A);
  UnistiMatricu(polinom);
  return 0;
}

