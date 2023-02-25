//TP 2021/2022: Zadaæa 2, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
bool DaLiJeProst(int n){
    if(n<=1) return false;
    for(int i=2;i<=sqrt(n);i++){
        if(n%i==0) return false;
    }
    return true;
}
void Goldbach(int n, int &p, int &q){
    if(n<=2) throw std::logic_error("Rastava ne postoji");
    if(n>2){
    for(int i=2;i<n;i++){
        p=i;
        q=n-i;
        if(DaLiJeProst(p) && p>1 && DaLiJeProst(q) && q>1) break;
    }
    if(!DaLiJeProst(p) || !DaLiJeProst(q) || p==1 || q==1) throw std::logic_error("Rastava ne postoji");
    }
}
int main ()
{
    int n,p,q;
    try{
        std::cout<<"Unesi broj: "<<std::endl;
        std::cin>>n;
        Goldbach(n, p, q);
        std::cout<<n<<" je zbir prostih brojeva "<<p<<" i "<<q<<std::endl;
    }
    catch(std::logic_error izuzetak){
        std::cout<<n<<" nije zbir dva prosta broja!";
    }
	return 0;
}

