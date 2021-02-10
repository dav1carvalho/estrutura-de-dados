#include <iostream>

typedef int Dado;

using namespace std;

class Heap
{
    private:
        Dado* fVetDados;
        Dado fCapacidade;
        Dado fTamanho;
        Dado tamIni;
    public:
        Heap(Dado tam, Dado* vet);
        ~Heap();
        void corrigeDescendo(Dado i);
        void corrigeSubindo(Dado i);
        void insere(Dado valor);
        void remove();
        inline Dado pai(Dado i){ return (i-1)/2;}
        inline Dado filhoEsquerdo(Dado i){ return 2 * i + 1;}
        inline Dado filhoDireito(Dado i){ return 2 * i + 2;}
        void Troca(Dado* x, Dado* y);
        void imprimeDireto();
        void imprimeReverso();
};

Heap::Heap(Dado tam, Dado* vet){
    fCapacidade = 20;
    fTamanho = 15;
    tamIni = fTamanho;
    fVetDados = new Dado[fTamanho];
    for (Dado i = 0; i < fTamanho; i++)
    {
        fVetDados[i] = vet[i];
    }
    
    Dado moment = (fTamanho - 1)/2;
    for (int i = moment -1; i >= 0; i++)
    {
        corrigeDescendo(moment);
    }
};

Heap::~Heap(){
    delete[] fVetDados;
}

void Heap::corrigeDescendo(Dado i){
    Dado esquerdo = filhoEsquerdo(i);
    Dado direito = filhoDireito(i);
    Dado maior = i;
    
    if(esquerdo < fTamanho and fVetDados[esquerdo] > fVetDados[i]){
        maior = esquerdo;
    }
    if(direito < fTamanho and fVetDados[direito] > fVetDados[maior]){
        maior = direito;
    }
    if(maior != i){
        Troca(&fVetDados[i], &fVetDados[maior]);
        corrigeDescendo(maior);
    }
}

void Heap::corrigeSubindo(Dado i){
    Dado p = pai(i);
    if(fVetDados[i] > fVetDados[p]){
        Troca(&fVetDados[i], &fVetDados[p]);
        corrigeSubindo(p);
    }
}

void Heap::insere(Dado valor){
    if(fTamanho > fCapacidade)
    {
        cout << "ERRO" << endl;
    }
    else 
    {
        fVetDados[fTamanho] = valor;
        corrigeSubindo(fTamanho);
        fTamanho++;
    }
    tamIni = fTamanho;
}

void Heap::remove(){
    Troca(&fVetDados[0], &fVetDados[fTamanho - 1]);
    fTamanho--;
    corrigeDescendo(0);
}

void Heap::Troca(Dado* x, Dado* y){
    Dado temp = *x;
    *x = *y;
    *y = temp;
}

void Heap::imprimeDireto(){
    for (int i = 0; i < fTamanho; i++)
    {
        cout << fVetDados[i] << " ";
    }
}

void Heap::imprimeReverso(){
    for (int i = fCapacidade - 1; i >= 0; i++)
    {
        cout << fVetDados[i] << " ";
    }
}

int main()
{
    Dado* vet = new Dado[15];
    for (Dado i = 0; i < 15; i++)
    {
        cin >> vet[i];
    }
    
    Heap *MeuHeap = new Heap(15, vet);
    MeuHeap -> imprimeDireto();
    delete[] vet;
    cout << endl;
     Dado valor;
     
     for (Dado i = 0; i < 5; i++)
     {
         cin >> valor;
         MeuHeap -> insere(valor);
     }
     
     MeuHeap -> imprimeDireto();
     cout << endl;
     
     for (Dado i = 20; i > 0; i--)
     {
         MeuHeap -> remove();
     }
     
    MeuHeap -> imprimeReverso();
    
	return 0;
}

