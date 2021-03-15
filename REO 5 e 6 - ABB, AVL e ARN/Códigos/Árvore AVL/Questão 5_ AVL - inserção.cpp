#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>

class NohAVL; // declaração avançada

typedef std::string TChave; // chave da árvore
typedef float TValor; // valor da árvore

// Declarações das classes ===================================================

class NohAVL {
    friend class AVL;
    friend std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh);
    private:
        NohAVL (TChave c, const TValor& v);
        ~NohAVL();
        NohAVL* ArrumarBalanceamento();
        void AtualizarAltura();
        void DesalocarFilhosRecursivo();
        int FatorBalanceamento();
        NohAVL* InserirRecursivo(NohAVL* ptNoh);
        NohAVL* RotacionarEsquerda();
        NohAVL* RotacionarDireita();
        TChave mChave;
        TValor mValor;
        NohAVL* mPtEsq;
        NohAVL* mPtDir;
        NohAVL* mPtPai;
        unsigned int mAltura; // folhas têm altura 1
};

class AVL {
    public:
        AVL();
        ~AVL();
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(TChave chave, const TValor& valor);
    private:
        NohAVL* mPtRaiz;
};

// === Classe NohAVL ==============================================================================

using namespace std;

NohAVL::NohAVL(TChave c, const TValor& v) : mChave(c), mValor(v) {
    mPtEsq = NULL;
    mPtDir = NULL;
    mPtPai = NULL;
    mAltura = 1;
}

NohAVL::~NohAVL() {
    DesalocarFilhosRecursivo();
}

NohAVL* NohAVL::ArrumarBalanceamento() {
    AtualizarAltura();
    int fator_balanceamento = FatorBalanceamento();
    if(fator_balanceamento > 1 && mPtEsq->FatorBalanceamento() >= 0){
        return RotacionarDireita();
    }
    if(fator_balanceamento > 1 && mPtEsq->FatorBalanceamento() < 0){
        mPtEsq = mPtEsq->RotacionarEsquerda();
        return RotacionarDireita();
    }
    if(fator_balanceamento < -1 && mPtDir->FatorBalanceamento() <= 0){
        return RotacionarEsquerda();
    }
    if(fator_balanceamento < -1 && mPtDir->FatorBalanceamento() > 0){
        mPtDir = mPtDir->RotacionarDireita();
        return RotacionarEsquerda();
    }
    return this;
}

// Calcula e atualiza a altura de um nó.
void NohAVL::AtualizarAltura() {
    int altArvEsq;
    int altArvDir;
    if(mPtEsq != NULL){
        altArvEsq = mPtEsq->mAltura;
    } else {
        altArvEsq = 0;
    }
    if(mPtDir != NULL){
        altArvDir = mPtDir->mAltura;
    } else {
        altArvDir = 0;
    }
    if(altArvEsq >= altArvDir){
        mAltura = altArvEsq + 1;
    } else { 
        mAltura = altArvDir + 1;
    }
}

// Desaloca todos os descendentes.
void NohAVL::DesalocarFilhosRecursivo() {
    if(mPtEsq != NULL){
        delete mPtEsq;
    }
    if(mPtDir != NULL){
        delete mPtDir;
    }
}

// Calcula e retorna o fator de balanceamento do nó.
int NohAVL::FatorBalanceamento() {
    int altArvEsq;
    int altArvDir;
    if(mPtEsq != NULL){
        altArvEsq = mPtEsq->mAltura;
    } else {
        altArvEsq = 0;
    }
    if(mPtDir != NULL){
        altArvDir = mPtDir->mAltura;
    } else {
        altArvDir = 0;
    }
    int fator_balanceamento = altArvEsq - altArvDir;
    return fator_balanceamento;
}

// Insere um nó numa subárvore.
NohAVL* NohAVL::InserirRecursivo(NohAVL* ptNoh) {
    if(ptNoh->mChave < mChave){
        if(mPtEsq == NULL){
            mPtEsq = ptNoh;
            ptNoh->mPtPai = this;
        }else{
            mPtEsq = mPtEsq->InserirRecursivo(ptNoh);
        }
    }else{
        if(mPtDir == NULL){
            mPtDir = ptNoh;
            ptNoh->mPtPai = this;
        }else{
            mPtDir = mPtDir->InserirRecursivo(ptNoh);
        }
    }
    return ArrumarBalanceamento();
}

// Rotaciona a subárvore à direita. Retorna a nova raiz da subárvore.
NohAVL* NohAVL::RotacionarDireita() {
    NohAVL* aux = mPtEsq;
    this->mPtEsq = aux->mPtDir;
    if(aux->mPtDir != NULL){
        aux->mPtDir->mPtPai = this;
    }
    aux->mPtDir = this;
    this->mPtPai = aux;
    
    this->AtualizarAltura();
    aux->AtualizarAltura();

    return aux;
}

// Rotaciona a subárvore à esquerda. Retorna a nova raiz da subárvore.
NohAVL* NohAVL::RotacionarEsquerda() {
    NohAVL* aux = this->mPtDir;
    this->mPtDir =  aux->mPtEsq;
    if(aux->mPtEsq != NULL){
        aux->mPtEsq->mPtPai = this;
    }
    aux->mPtPai = this->mPtPai;
    aux->mPtEsq = this;
    this->mPtPai = aux;
    
    this->AtualizarAltura();
    aux->AtualizarAltura();
    
    return aux;
}

std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh) {
    if (ptNoh == NULL)
        saida << "[]";
    else
        saida << '[' << ptNoh->mAltura << ':' << ptNoh->mChave << '/' << ptNoh->mValor << ']';
    return saida;
}

// === Classe AVL =================================================================================
AVL::AVL() {
    mPtRaiz = NULL;
}

AVL::~AVL() {
    delete mPtRaiz;
}

// Escreve o conteúdo da árvore nível a nível, na saída de dados informada.
// Usado para conferir se a estrutra da árvore está correta.
void AVL::EscreverNivelANivel(ostream& saida) {
    queue<NohAVL*> filhos;
    NohAVL* fimDeNivel = new NohAVL(TChave(), TValor()); // nó especial para marcar fim de um nível
    filhos.push(mPtRaiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        NohAVL* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << ptNoh << ' ';
            if (ptNoh != NULL) {
                filhos.push(ptNoh->mPtEsq);
                filhos.push(ptNoh->mPtDir);
            }
        }
    }
    delete fimDeNivel;
}

// Insere um par chave/valor na árvore.
void AVL::Inserir(TChave chave, const TValor& valor) {
    NohAVL* novo = new NohAVL(chave, valor);
    if(mPtRaiz == NULL){
        mPtRaiz = novo;
    }else{
        mPtRaiz = mPtRaiz->InserirRecursivo(novo);
    }
}

// === Programa ===================================================================================
int main() {
    AVL minhaArvore;
    char opcao;
    TChave chave;
    TValor valor;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave >> valor;
                minhaArvore.Inserir(chave, valor);
                break;
            case 'e': // Escrever nós nível a nível
                minhaArvore.EscreverNivelANivel(cout);
                break;
            case 'f': // Finalizar o programa
                // vai verificar depois
                break;
            default:
                cerr << "Opção inválida\n";
        }
    } while (opcao != 'f');
    return 0;
}
