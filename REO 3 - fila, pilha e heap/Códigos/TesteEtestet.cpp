#include <iostream>
using namespace std;

typedef int Dado;

class MinHeap
{
	private:
		Dado* fVetDados;
		Dado fTamanho;
	public:
		MinHeap(Dado capacidade, Dado* vet);
		~MinHeap();
		void CorrigeDescendo(Dado i);
        inline Dado filhoEsquerdo(Dado i);
        inline Dado filhoDireito(Dado i);
        void Troca(Dado* elementOne, Dado* elementTwo);
};
MinHeap::MinHeap(Dado capacidade, Dado* vetor){
    //Construtor Heap com metodo Corrige Descendo sendo chamado
	fVetDados = new Dado[capacidade];
	fTamanho = capacidade;
	for(Dado i = 0; i < fTamanho; i++){
		fVetDados[i] = vetor[i];
	}
    Dado moment = (fTamanho - 1) / 2;
	for(Dado i = moment; i >= 0; i--){
		CorrigeDescendo(i);
		cout << i << ": ";
		for ( int j = 0; j < capacidade; j++ ){
			cout << fVetDados[j] << " ";
		}
		cout << endl;
	}
}
MinHeap::~MinHeap(){
    //Destrutor
	delete[]fVetDados;
}

inline Dado MinHeap::filhoEsquerdo(Dado i){
    //Retorna Filho esquerdo
    return (2 * i) + 1;
}

inline Dado MinHeap::filhoDireito(Dado i){
    //Retorna Filho direito
    return (2 * i) + 2;
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
		Troca(&fVetDados[i], &fVetDados[menor]);
		CorrigeDescendo(menor);
	}
}

void MinHeap::Troca(Dado *elementOne, Dado *elementTwo){
    //Troca duas posições
    Dado temp = *elementOne; 
    *elementOne = *elementTwo; 
    *elementTwo = temp;
}
int main()
{
    int capacidade;
    cin >> capacidade;
    
    Dado* vet = new Dado[capacidade];
    for (Dado i = 0 ; i < capacidade; i++){
		cin >> vet[i];
	}
	MinHeap *MeuHeap = new MinHeap (capacidade,vet);
	delete(vet);
	delete(MeuHeap);
    return 0;
}
