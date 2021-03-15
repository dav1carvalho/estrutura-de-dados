#include <iostream>
#include <stdexcept>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef int dado; // tipo da chave usada na comparação

class noh {
    friend class avl;
    friend unsigned informarAltura(noh* umNoh);
    friend void atualizaAltura(noh* umNoh);
    
    private:
        dado elemento;
        noh* esq;
        noh* dir;
        unsigned altura;
    public:
        noh(const dado& umDado):
            elemento(umDado),  esq(NULL), dir(NULL), altura(1) { }
        ~noh() { }
        int fatorBalanceamento();
};

unsigned informarAltura(noh* umNoh) { 
    if (umNoh == NULL){
        return 0;   
    }
    else{
        return umNoh->altura;
    }
}

void atualizaAltura(noh* umNoh) {
    unsigned altArvEsq = informarAltura(umNoh->esq);
    unsigned altArvDir = informarAltura(umNoh->dir);
    umNoh->altura = 1 + max(altArvEsq, altArvDir);
}

int noh::fatorBalanceamento() {
    int alturaEsq, alturaDir;

    if(esq != NULL){
        alturaEsq = esq->altura;
    }else{
        alturaEsq = 0;
    }

    if(dir != NULL){
        alturaDir = dir->altura;
    }else{
        alturaDir = 0;
    }
    
    return alturaEsq - alturaDir;
}


class avl {
    private:
        noh* raiz;
        int contador;
        // funções auxiliares para remoção
        noh* encontraMenor(noh* raizSub);
        noh* removeMenor(noh* raizSub);
        // funções auxiliares para inserção e remoção usando método recursivo
        // retorna o nó para ajustar o pai ou o raiz
        noh* insereAux(noh* umNoh, const dado& umDado);
        noh* removeAux(noh* umNoh, dado chave);
        // métodos para manutenção do balanceamento
        noh* rotacaoEsquerda(noh* umNoh);
        noh* rotacaoDireita(noh* umNoh);
        noh* arrumaBalanceamento(noh* umNoh);
        // busca, método iterativo
        noh* buscaAux(dado chave);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);
        void imprimirDir(const std::string& prefixo, const noh* meuNoh);
        void imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao);
    public:
        avl() { raiz = NULL; }
        ~avl();
        void imprimir();
        // inserção e remoção são recursivos
        void insere(const dado& umDado);
        void remove(dado chave);
        // inserção e remoção, métodos recursivos
        // busca retorna uma cópia do objeto armazenado
        dado busca(dado chave);
        // efetua levantamento de quantas motos existem de uma dada marca 
        // fabricadas a partir de um dado ano
};

// destrutor
avl::~avl() {
    destruirRecursivamente(raiz);
}

// destrutor é recursivo, fazendo percorrimento pós-ordem
void avl::destruirRecursivamente(noh* umNoh) {
    if(umNoh != NULL){
        destruirRecursivamente(umNoh->esq);
        destruirRecursivamente(umNoh->dir);
        delete umNoh;
    }
}


void avl::insere(const dado& umDado) {
    contador = 0;
    raiz = insereAux(raiz, umDado);
    if(raiz->elemento == umDado){
        contador++;
    }
    cout << "Nos Acessados: " << contador << endl;
    cout << endl << "-----------------" << endl << endl;
}

// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh* avl::insereAux(noh* umNoh, const dado& umDado) {
   
    noh* novoNoh;
    if(umNoh == NULL){
        novoNoh = new noh(umDado);
        return novoNoh;
    }else{
        if(umDado < umNoh->elemento){
            contador++;
            umNoh->esq = insereAux(umNoh->esq, umDado);
        }else{
            contador++;
            umNoh->dir = insereAux(umNoh->dir, umDado);
        }
    }
    return arrumaBalanceamento(umNoh);
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários
noh* avl::arrumaBalanceamento(noh* umNoh) {
    if(umNoh == NULL){
        return umNoh;
    }

    atualizaAltura(umNoh);  
    contador ++;

    int FB = umNoh->fatorBalanceamento();

    if((FB >= -1) and (FB <= 1)){
        return umNoh;
    }
    //caso1
    else if((FB>1) and (umNoh->esq->fatorBalanceamento() >= 0)){
        return rotacaoDireita(umNoh);
    }
    //caso2
    else if((FB>1) and (umNoh->esq->fatorBalanceamento() < 0)){
        umNoh->esq = rotacaoEsquerda(umNoh->esq);
        return rotacaoDireita(umNoh);
    }
    //caso3
    else if((FB<-1) and (umNoh->dir->fatorBalanceamento() <= 0)){
        return rotacaoEsquerda(umNoh);
    }
    //caso4
    else if((FB<-1) and (umNoh->dir->fatorBalanceamento() > 0)){
        umNoh->dir = rotacaoDireita(umNoh->dir);
        return rotacaoEsquerda(umNoh);
    }

    return umNoh;
}


// rotação à esquerda na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoEsquerda(noh* umNoh) {
    noh* aux = umNoh->dir;
    umNoh->dir = aux->esq;
    aux->esq = umNoh;
    atualizaAltura(umNoh);
    atualizaAltura(aux);
    contador += 2;

    return aux;
}

// rotação à direita na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoDireita(noh* umNoh) {
    noh* aux = umNoh->esq;
    umNoh->esq = aux->dir;
    aux->dir = umNoh;
   
    atualizaAltura(umNoh);
    atualizaAltura(aux);
    contador += 2;


    return aux;
}

// método de busca auxiliar (retorna o nó), iterativo
noh* avl::buscaAux(dado chave) {
    noh* atual = raiz;

    while(atual != NULL){
        if(atual->elemento == chave){
            contador++;
            return atual;
        }else if(atual->elemento > chave){
            atual = atual->esq;
            contador++;
        }else{
            atual = atual->dir;
            contador++;
        }
    }
    return atual;
}

// busca elemento com uma dada chave na árvore e retorna o registro completo
dado avl::busca(dado chave) {
    contador = 0;
    noh* resultado = buscaAux(chave);
    cout << "Nos Acessados: " << contador << endl;
    cout << endl << "-----------------" << endl << endl;
    if (resultado != NULL)
        return resultado->elemento;
    else{
        return 0;
    }
}

// nó mínimo (sucessor) de subárvore com raiz em raizSub (folha mais à esquerda)
noh* avl::encontraMenor(noh* raizSub) {
    if (raizSub->esq != NULL){
        contador++;
        raizSub = encontraMenor(raizSub->esq);
    }
    return raizSub;
}

// procedimento auxiliar para remover o sucessor substituíndo-o pelo
// seu filho à direita
noh* avl::removeMenor(noh* raizSub) {
    if(raizSub->esq == NULL){
        return raizSub->dir;
    }else{
        contador++;
        raizSub->esq = removeMenor(raizSub->esq);
        return arrumaBalanceamento(raizSub);
    }
}

// remoção recursiva
void avl::remove(dado chave) {
    contador = 0;
    raiz = removeAux(raiz, chave);
    cout << "Nos Acessados: " << contador << endl;
    cout << endl << "-----------------" << endl << endl;
}

noh* avl::removeAux(noh* umNoh, dado chave) {
    if(umNoh == NULL){
        return NULL;
    }

    noh* novaRaiz = umNoh;

    if(chave < umNoh->elemento){
        umNoh->esq = removeAux(umNoh->esq, chave);
        contador++;
    }else if(chave > umNoh->elemento){
        umNoh->dir = removeAux(umNoh->dir, chave);
        contador++;
    }else{
        if(umNoh->esq == NULL){
            novaRaiz = umNoh->dir;
            contador ++;
            if(novaRaiz != NULL){
                if((novaRaiz->esq == NULL) and (novaRaiz->dir == NULL)){
                    contador++;
                }
            }
        }else if(umNoh->dir == NULL){
            novaRaiz = umNoh->esq;
            contador ++;
            if(novaRaiz != NULL){
                if((novaRaiz->esq == NULL) and (novaRaiz->dir == NULL)){
                    contador++;
                }
            }
        }else{
            if((umNoh->dir->esq == NULL) and (umNoh->dir->dir == NULL)){
                contador++;
            }
            novaRaiz = encontraMenor(umNoh->dir);
            novaRaiz->dir = removeMenor(umNoh->dir);
            novaRaiz->esq = umNoh->esq;
            contador ++;
        }
        delete umNoh;
    }
    return arrumaBalanceamento(novaRaiz);
}

int main() {
    avl arvore;
    dado valor;

    auto start = high_resolution_clock::now();
    //insere 30 objetos
    
    for (unsigned i = 0; i < 30; ++i)
    {
        cout << "Insercao de: ";
        cin >> valor;
        arvore.insere(valor);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << "milliseconds" << endl;

    cout << endl << "##################################################################" << endl << endl;
    //remove 20 objetos
    
    start = high_resolution_clock::now();
    for (unsigned i = 0; i < 20; ++i) {
        cout << "Remocao de: ";
        cin >> valor;
        arvore.remove(valor);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << "milliseconds" << endl;

    cout << endl << "##################################################################" << endl << endl;

    
    start = high_resolution_clock::now();
    //busca 30 objetos
    for (unsigned i = 0; i < 30; ++i) {
        cout << "Busca de: ";
        cin >> valor;
        arvore.busca(valor);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << "milliseconds" << endl;
    return 0;
}