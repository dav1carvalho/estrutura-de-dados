#include <iostream>
#include <fstream>

using namespace std;

typedef string Dado;

//========================= Classe Lista ===============================

class NohList
{
    friend class Lista;
    private:
        NohList* proximo;
        int valor;
    public:
        NohList(int d);
};

class Lista
{
    friend class Noh;
    private:
       NohList* primeiro;
    public:
       Lista();
       ~Lista();
       void InsereLista(int d);
       void imprimeList();
};

//======================= Metodos da Lista =============================
Lista::Lista(){
    //Construtor da Lista presente no Nó
    primeiro = NULL;
}

Lista::~Lista(){
    NohList* atual = primeiro;
    NohList* ant = NULL;
    while(atual != NULL) {
        ant = atual;
        atual = atual -> proximo;
        delete ant;
    }
}

NohList::NohList(int d){
    valor = d;
    proximo = NULL;
}

void Lista::InsereLista(int d){
    //Insere na lista
    NohList* novo = new NohList(d);
    if(primeiro == NULL){
        primeiro = novo;
    } else {
        NohList* atual = primeiro;
        NohList* ant = NULL;
        while(atual != NULL) {
            ant = atual;
            atual = atual -> proximo;
        }
        ant -> proximo = novo;
    }
}

void Lista::imprimeList(){
    //Imprime a lista
    NohList* atual = primeiro;
    while(atual != NULL) {
        cout << atual -> valor << " ";
        atual = atual -> proximo;
    }
}
//================== Classes Noh e ArvoreABB =========================== 
class Noh
{
    friend class ArvoreABB;
	private:
	    Noh* pai;
	    Noh* dir;
	    Noh* esq;
	    Dado palavra;
        Lista posicoes;
	public:
	    Noh(Dado p);
};

class ArvoreABB
{
	private:
        Noh* fRaiz;
	public:
	    ArvoreABB();
	    ~ArvoreABB();
	    void insere(Dado p);
        void busca(Dado procura);
        //void BuscaInsere(Dado p, int posi);
        void EmOrdem(){ EmOrdemImp(fRaiz); }
        void EmOrdemImp(Noh* atual);
        void posOrdem(){ posOrdem(fRaiz);}
        void posOrdem(Noh* atual);
};
//===================== Contrutores e Destrutores ======================

Noh::Noh(Dado p){
	//Contrutor do Nó
	palavra = p;
	pai = NULL;
	dir = NULL;
	esq = NULL;
}
ArvoreABB::ArvoreABB(){
	//Construtor da Arvore
	fRaiz = NULL;
}

ArvoreABB::~ArvoreABB(){
    //Destrutor da Arvore
   posOrdem();
}
//=================== Métodos da Classe ARVOREPALAVRAS =================

void ArvoreABB::insere(Dado d){
	//Insere um novo Nó na Arvore
    Noh* novo = new Noh(d);
    if(fRaiz == NULL){
        fRaiz = novo;
    } else {
        Noh* atual = fRaiz;
        Noh* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(atual -> palavra > d){
                atual = atual -> esq;
            } else {
                atual = atual -> dir;
            }
        }
        novo -> pai = ant;
        if(ant -> palavra > novo -> palavra){
            ant -> esq = novo;
        } else {
            ant -> dir = novo;
        }
    }
}

void ArvoreABB::busca(Dado procura){
    //Procura na arvore a palavra desejada
    Noh* atual = fRaiz;
    bool achou = false;
    while (atual != NULL and achou == false) {
        if (atual -> palavra == procura) {
            achou = true;
            atual -> posicoes.imprimeList();
        } else if (atual -> palavra > procura) {
            atual = atual -> esq;
        } else {
            atual = atual -> dir;
        }
    }
    if(achou == false) {
        cout << -1 << endl;
    }
}

void ArvoreABB::EmOrdemImp(Noh* atual){
    //Imprime os Dados em Ordem
    if(atual != NULL){
        EmOrdemImp(atual -> esq);
        cout << atual -> palavra << " ";
        EmOrdemImp(atual -> dir);
    }
}

void ArvoreABB::posOrdem(Noh* atual){
    if(atual != NULL){
        posOrdem(atual->esq);
        posOrdem(atual->dir);
        delete atual;
    }
}

/*void ArvoreABB::BuscaInsere(Dado p, int posi) {
    Noh* atual = fRaiz;
    while (atual != NULL and achou == false) {
        if (atual -> palavra == p) {
            atual -> posicoes.InsereLista(posi);
        } else if (atual -> palavra > p) {
            atual = atual -> esq;
        } else {
            atual = atual -> dir;
        }
    }
}*/

int main()
{
	ArvoreABB MyTree;
    ifstream ArquivoEnt("entrada.txt");
    int cont = 0;
    string palavra[100];
    while(ArquivoEnt >> palavra[cont++]){}
    
    int teste[cont];
    for (int i = 0; i < cont; i++){
        teste[i] = 1;
    }
    
    int i = 0;
    while(i < cont){
        int j = i + 1;
        while(j < cont){
            if(palavra[j] == palavra[i]){
                teste[j] = 0;
            }
            j++;
        }
        i++;
    }
    
    for (int i = 0; i < cont; i++)
    {
        if(teste[i] == 1){
            cout << palavra[i] << " ";
            MyTree.insere(palavra[i]);
        }
    }
    
	
	return 0;
}
