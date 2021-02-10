#include <iostream>

typedef int Dado;

class MaxHeap
{
    private:
        Dado* fVetDados;
        Dado fCapacidade;
        Dado fTamanhoInicial;
        Dado fTamanho;
    public:
        MaxHeap(Dado* vetor1);
        ~MaxHeap();
        void Imprime();
        void CorrigeDescendo(Dado i);
        void CorrigeSubindo(Dado i);
        void Troca(Dado* elementOne, Dado* elementTwo);
        void InsereHeap(Dado valor);
        inline Dado pai(Dado i){ return (i - 1)/2; }
        inline Dado filhoEsquerdo(Dado i){ return 2 * i + 1; }
        inline Dado filhoDireito(Dado i){ return 2 * i + 2; }
        void Remove();
        void ImprimeDeTraz();
};

MaxHeap::MaxHeap(Dado* vetor1){
    //Costructor
    fCapacidade = 20;
    fTamanho = 15;
    fTamanhoInicial = 15;
    fVetDados = new Dado[fCapacidade];
    for (Dado i = 0; i < fTamanho; i++)
    {
        fVetDados[i] = vetor1[i];
    }
    
    for (Dado i = (fTamanho - 1) / 2; i >= 0 ; i--)
    {
        CorrigeDescendo(i);
    }
};

MaxHeap::~MaxHeap(){
    //Destructor
    delete []fVetDados;
};

using namespace std;

void MaxHeap::Imprime(){
    //Imprimir o codigo (debug);
    for (Dado i = 0; i < fTamanhoInicial; i++)
    {
        cout << fVetDados[i] << " ";
    }
}
void MaxHeap::CorrigeDescendo(Dado i){
    //Metodo Corrige descendo
    Dado esquerdo = filhoEsquerdo(i);
    Dado direito = filhoDireito(i);
    Dado maior = i;
    if(esquerdo < fTamanho and (fVetDados[esquerdo] > fVetDados[i])){
        maior = esquerdo;
    }
    if(direito < fTamanho and (fVetDados[direito] > fVetDados[maior])){
        maior = direito;
    }
    if(maior != i){
        Troca(&fVetDados[i], &fVetDados[maior]);
        CorrigeDescendo(maior);
    }
}

void MaxHeap::CorrigeSubindo(Dado i){
    //Metodo Corrige Subindo
    Dado p = pai(i);
    if(fVetDados[i] > fVetDados[p]){
        Troca(&fVetDados[i], &fVetDados[p]);
        CorrigeSubindo(p);
    }
}

void MaxHeap::Troca(Dado* x, Dado* y){
    //Troca Dois elementos
    Dado temp = *x;
    *x = *y;
    *y = temp;
}

void MaxHeap::InsereHeap(Dado valor){
    //Insere Valor
    if(fTamanho > fCapacidade){
        cout << "ERRO" << endl;
    } else {
        fVetDados[fTamanho] = valor;
        CorrigeSubindo(fTamanho);
        fTamanho++;
    }
    fTamanhoInicial = fTamanho;
}

void MaxHeap::Remove(){
    //Remove elementos
    Troca(&fVetDados[0], &fVetDados[fTamanho - 1]);
    fTamanho--;
    CorrigeDescendo(0);
}

void MaxHeap::ImprimeDeTraz(){
    //Imprime de Traz para frente
    for (Dado i = fCapacidade -1 ; i >= 0; i--)
    {
        cout << fVetDados[i] << " ";
    }
}

int main()
{
    Dado* vetor1 = new Dado[15];
    for (Dado i = 0; i < 15; i++)
    {
        cin >> vetor1[i];
    }
    
    MaxHeap *MeuHeap = new MaxHeap(vetor1);
    MeuHeap -> Imprime();
    delete[]vetor1;
    cout << endl;
    
    Dado valor;
    for (Dado i = 0; i < 5; i++)
    {
        cin >> valor;
        MeuHeap -> InsereHeap(valor);
    }
    
    MeuHeap -> Imprime();
    cout << endl;
    for (Dado i = 20; i > 0; i--)
    {
        MeuHeap -> Remove();
    }
    
    MeuHeap -> ImprimeDeTraz();
    
	return 0;
}

