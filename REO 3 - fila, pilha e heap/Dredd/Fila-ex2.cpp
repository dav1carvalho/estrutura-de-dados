/* Classe fila, um fila (FIFO) implementada usando encadeamento
 * 
 * by Joukim, 2017, Estruturas de Dados
 * adaptada por Valéria, 2018
 */

#include <iostream>

using namespace std;

void ordenaVetor(int vet[], int tam)
{
	int posmenor, aux;
		for (int posind=0; posind < tam-1; posind++){
			posmenor = posind;
			for (int j=posind+1; j<tam; j++){
				if (vet[j] < vet[posmenor]){
					posmenor = j;
				}
			}
			aux = vet[posmenor];
			vet[posmenor] = vet[posind];
			vet [posind] = aux;
		}
}


class noh {
	friend class fila;
	private:
		int dado; // poderia ser outro tipo de variável
		noh* prox;
};

// fila dinamicamente encadeada
class fila {
	private:
		noh* primeiro;
		noh* ultimo;
		int tamanho;
    
	public:
		fila();
		fila(const fila& umaFila);
		~fila();
		void insere(int d) { enfileira(d); }
		void enfileira(int d); // insere no final da fila 
		int desenfileira(); // retorna o primeiro elemento da fila
		int espia(); // espia o primeiro elemento da fila
		bool vazia();
		void imprime();  
		fila operator+(const fila& umaFila) const;
                fila& operator=(const fila& umaFila);
};

fila::fila() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

fila::~fila() { 
    while (primeiro != NULL) {
        desenfileira();
    }
}

void fila::enfileira(int d) {
    // primeiro criamos o novo nó
    noh* temp = new noh;
    temp->dado = d;
    temp->prox = NULL;
    if (ultimo != NULL) {
        ultimo->prox = temp;
    }
    ultimo = temp;
    if (vazia()) {
        primeiro = temp;
    }    
    tamanho++; 
}

int fila::desenfileira() {
    int removido;
    noh* temp;
    removido = primeiro->dado;
    temp = primeiro;
    primeiro = primeiro->prox;
    if (vazia()){
        ultimo = NULL;
    }
    delete temp;
    tamanho--;
    return removido;    
}

int fila::espia(){
    return primeiro->dado;
}
    
bool fila::vazia() {
    return (primeiro == NULL);
}

void fila::imprime(){
    noh* temp = primeiro;
    while (temp != NULL) {
	cout << temp->dado << " ";
        temp = temp->prox;
    }
    cout << endl;
}

//mesclar filas
fila fila::operator+(const fila& umaFila) const {
	// IMPLEMENTAR
    fila resultante;
    noh* aPrimeiro = this->primeiro;
    noh* bPrimeiro = umaFila.primeiro;
    int contador = this->tamanho;
    int tam = this->tamanho + umaFila.tamanho;
        int vetor[tam]; // Vetor tem o tamanho das duas filas somadas

        for (int i = 0; contador > 0; i++)
        {
            vetor[i] = aPrimeiro->dado;
            aPrimeiro = aPrimeiro->prox;
            contador--;
        }
        contador = umaFila.tamanho;
        for (int i = this->tamanho; contador > 0; i++)
        {
            vetor[i] = bPrimeiro->dado;
            bPrimeiro = bPrimeiro->prox;
            contador--;
        }
        ordenaVetor(vetor, tam);

        for (int i = 0; i < tam; i++)
            resultante.enfileira(vetor[i]);
    
    return resultante;
}

// sobrecarga do operador de atribuição
fila& fila::operator=(const fila& umaFila){
	
	while (this->primeiro != NULL) 
        desenfileira();

    noh* aux = umaFila.primeiro;
    while (aux != NULL)
    {
        insere(aux->dado);
        aux = aux->prox;
    }
    
    return *this;
}

// construtor de cópia
fila::fila(const fila& umaFila) {
	this->primeiro = umaFila.primeiro;
    this->tamanho = umaFila.tamanho;
    this->ultimo = umaFila.ultimo;
}

int main() {
    fila filaA;
    fila filaB;
    string opcao;
    int dado;
    char idFila;
    do {
        cin >> opcao;
        if (opcao == "i") {
            cin >> idFila >> dado;
            if (idFila == 'a')
                filaA.enfileira(dado);
            else
                filaB.enfileira(dado);
        }
 	else if (opcao == "a=b") {
            filaA = filaB;
        }
        else if (opcao == "b=a") {
            filaB = filaA;
        }
        else if (opcao == "s") {
            fila filaM = filaA + filaB;
            filaM.imprime();
        }
        else if (opcao == "e") {
            cin >> idFila;
            if (idFila == 'a')
                filaA.imprime();
            else
                filaB.imprime();
        }
    } while (opcao != "t");
    return 0;
}
