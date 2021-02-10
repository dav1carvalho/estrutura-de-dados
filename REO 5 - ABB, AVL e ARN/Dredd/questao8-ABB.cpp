#include <iostream>
#include <queue>
#include <stdexcept>

using namespace std;

typedef int Dado;

enum Posicao {DIR, ESQ};

class Noh {
    friend class ABB;
    public:
        Noh(Dado d);
        //~Noh();
        //unsigned NroDeFolhas() const;
    private:
        Dado valor;
        Noh* esq;
        Noh* dir;
        Noh* pai;
};

Noh::Noh(Dado d) {
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

/*unsigned Noh::NroDeFolhas() const {
    // implemente
}*/

class ABB {
    public:
        ABB();
        ~ABB();
        // Escreve uma Ã¡rvore nÃ­vel a nÃ­vel.
        // Pode ser Ãºtil para depurar o programa.
        void EscreverNivelANivel(std::ostream& saida);
        // Insere um dado na Ã¡rvore.
        void Inserir(Dado d);
        // Retorna o nro de folhas na Ã¡rvore.
        unsigned NroDeFolhas();
        //void percorre(Noh* atual);
    private:
        unsigned NroDeFolhasAux(Noh* atual);
        void destrutorRecursivo(Noh* atual);
        Noh* raiz;
};

ABB::~ABB(){
    destrutorRecursivo(raiz);
}

ABB::ABB(){
    raiz = NULL;
}

void ABB::destrutorRecursivo(Noh* atual){
    if(atual != NULL){
        destrutorRecursivo(atual->esq);
        destrutorRecursivo(atual->dir);
        delete atual;
    }
}

void ABB::Inserir(Dado d) {
    Noh* novoNoh = new Noh(d);
    if(raiz == NULL){
        raiz = novoNoh;
    }else{
        Noh* atual = raiz;
        Noh* anterior = NULL;

        while(atual != NULL){
            anterior = atual;
            if(atual->valor > d){
                atual = atual->esq;
            }else{
                atual = atual->dir;
            }
        }

        novoNoh->pai = anterior;

        if(anterior->valor > novoNoh->valor){
            anterior->esq = novoNoh;
        }else{
            anterior->dir = novoNoh;
        }
    }
}

/*void ABB::percorre(Noh* atual){
    int contador = 0;
    if(atual != NULL){
        percorre(atual->dir);
        cout << atual->valor << endl;
        percorre(atual->esq);
    }else{
        contador++;
        cout << "CONT" << contador << endl;
    }
}*/

unsigned ABB::NroDeFolhas(){
    return NroDeFolhasAux(raiz);
}

unsigned ABB::NroDeFolhasAux(Noh* atual){
    if(atual == NULL){
        return 0;
    }
    if((atual->esq == NULL) and (atual->dir == NULL)){
        return 1;
    }else{
        return (NroDeFolhasAux(atual->esq)) + (NroDeFolhasAux(atual->dir));
    }
}

void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh aux = Dado();
    Noh* fimDeNivel = &aux; // marcador especial para fim de nivel
    filhos.push(raiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        Noh* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << '[';
            if (ptNoh != NULL) {
                saida << ptNoh->valor;
                filhos.push(ptNoh->esq);
                filhos.push(ptNoh->dir);
            }
            saida << ']';
        }
    }
}

int main() {
    unsigned qtde;
    cin >> qtde;
    ABB arvore;
    Dado valor;
    for (unsigned i = 0; i < qtde; ++i) {
        cin >> valor;
        arvore.Inserir(valor);
    }
    cout << arvore.NroDeFolhas() << endl;
    return 0;
}