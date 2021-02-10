#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Dado;

class MinHeap
{
	private:
		Dado* fVetDados;
		Dado fTamanho;
		bool troca;
	public:
		MinHeap(Dado capacidade, Dado* vet);
		~MinHeap();
		void CorrigeDescendo(Dado i);
		inline Dado pai(Dado i){ return (i - 1) / 2;}
        inline Dado filhoEsquerdo(Dado i){ return 2 * i + 1;}
        inline Dado filhoDireito(Dado i){ return 2 * i + 2; }
};
MinHeap::MinHeap(Dado capacidade, Dado* vetor){
    //Construtor Heap com metodo Corrige Descendo sendo chamado
	fVetDados = new Dado[capacidade];
	fTamanho = capacidade;
	for(Dado i = 0; i < fTamanho; i++){
		fVetDados[i] = vetor[i];
	}
    Dado moment = pai(fTamanho);
	for(Dado i = moment; i >= 0; i--){
		troca = false;
		CorrigeDescendo(i);
		if(troca){
			cout << i << ": ";
			for ( int j = 0; j < capacidade; j++ ){
				cout << fVetDados[j] << " ";
			}
			cout << endl;
		}
	}
}
MinHeap::~MinHeap(){
    //Destrutor
	delete[]fVetDados;
}

void MinHeap::CorrigeDescendo(Dado i){
    //Metodo corrige descendo (Heapipy)
	Dado esquerdo = filhoEsquerdo(i);
	Dado direito = filhoDireito(i);
	Dado menor = i;
	if (esquerdo < fTamanho and fVetDados[esquerdo] < fVetDados[i]){
		menor = esquerdo;
	}
	if (direito < fTamanho and fVetDados[direito] < fVetDados[menor]){
		menor = direito;
	}
	if (menor != i){
		swap(fVetDados[i], fVetDados[menor]);
		troca = true;
		CorrigeDescendo(menor);
	}
}

int main()
{
    int capacidade;
    cin >> capacidade;
    
    Dado* vet = new Dado[capacidade];
    for (Dado i = 0 ; i < capacidade; i++){
		cin >> vet[i];
	}
	MinHeap MeuHeap(capacidade, vet);
	delete[] vet;
    return 0;
}
