#include <iostream>

using namespace std;

typedef int Dado; // para facilitar a troca de int para outro tipo
 
// pilha implementada em arranjo 
class pilhav {
private:
	int capacidade;
	Dado *dados;
	int tamanho;
	int posTopo;
public:
	pilhav(int cap = 100);
    ~pilhav();
	void empilha(Dado valor);
	Dado desempilha();
	Dado espia(); // acessa elemento do topo, mas não retira
	void depura(); // imprime os dados do vetor da pilha sem removê-los (desempilhar)
	void info();  // imprime informações da pilha (tamanho e  posição do topo)
};

pilhav::pilhav(int cap) {
    
    capacidade = cap;
    dados = new Dado[capacidade];
    
    for (int i = 0; i < capacidade; i++)
    {
        dados[i] = 0;
    }
    
    tamanho = 0;
    posTopo = 0;
}

pilhav::~pilhav()
{
    delete[] dados;
}

void pilhav::empilha(Dado valor)
{
    if(tamanho > capacidade)
    {
        cerr << "erro" << endl;
    }
    else
    {
        dados[tamanho] = valor;
        posTopo = tamanho;
        ++tamanho;
    }
}

Dado pilhav::desempilha()
{
    if(tamanho == 0)
    {
        cout << "nao tem elementos para desempilhar" << endl;
        return 0;
    }
    
    Dado i = tamanho - 1;
    Dado element = dados[i];
    posTopo = i - 1;
    tamanho--;
    
    return element;    
}

Dado pilhav::espia()
{
    Dado temp = dados[posTopo];
    
    return temp;
}

void pilhav::depura()
{
    for (Dado i = 0; i < tamanho; i++)
    {
        cout << dados[i] << " ";
    }
    
    cout << endl;
}
    
void pilhav::info()
{
    cout << tamanho << " " << posTopo << endl;
}

int main()
{
    Dado cap = 20;
    pilhav* vetorPilha = new pilhav(cap);
    
    Dado valor;
    Dado i = 0;
    
    while(i < 5)
    {
        cin >> valor;
        
        vetorPilha->empilha(valor);
        i++;
    }
    
    cout << endl;
    i = 0;
    
    while(i < 3)
    {
        cout << vetorPilha->desempilha() << " ";
        i++;
    }
   
   cout << endl;
   i = 0;
   
    while(i < 4)
    {
        cin >> valor;
        
        vetorPilha->empilha(valor);
        i++;
    }
    
    i = 0;
    
    while(i < 3)
    {
        cout << vetorPilha->desempilha() << " ";
        i++;
    }
    
    cout << endl;
    
    cout << vetorPilha->espia() << endl;
    
    vetorPilha->depura();
    
    vetorPilha->info();

    return 0;
}
