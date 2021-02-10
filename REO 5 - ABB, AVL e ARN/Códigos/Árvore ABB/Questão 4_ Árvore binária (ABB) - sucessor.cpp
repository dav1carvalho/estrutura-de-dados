#include <iostream>
#include <queue>

typedef int Dado;

enum Posicao {DIR, ESQ};

class Noh {
    friend class ABB;
    public:
        Noh (Dado d = Dado());
        ~Noh();
        // Verifica se um nó é filho da direita do pai.
        bool FilhoDaDireita();
        // Retorna a menor chave de uma sub-árvore.
        Dado MenorRecursivo();
        // Verifica se existe sucessor e retorna o valor sucessor, se existir.
        bool Sucessor(Dado* ptResultado);
    protected:
        Dado valor;
        Noh* esq;
        Noh* dir;
        Noh* pai;
};

class ABB {
    public:
        ABB() { raiz = NULL; }
        ~ABB();
        // Retorna um ponteiro para o nó de uma chave, ou NULL.
        Noh* Busca(Dado d);
        // Escreve uma árvore nível a nível.
        void EscreverNivelANivel(std::ostream& saida);
        // Insere um dado na árvore.
        void Inserir(Dado d);
        // Verifica se um dado tem sucessor e o retorna.
        bool Sucessor(Dado d, Dado* ptResultado);
    protected:
        Noh* raiz;
};

using namespace std;
// === Classe Noh ==============================================================
Noh::Noh(Dado d) // d tem valor default
    : valor(d), esq(NULL), dir(NULL), pai(NULL) {
}

Noh::~Noh() {
    // Destrutor recursivo!
    delete esq;
    delete dir;
}

bool Noh::FilhoDaDireita() {
    // implementar
    if(pai != NULL){
		if(pai -> dir == this){
			return true;
		}
	}
	return false;
}

Dado Noh::MenorRecursivo() {
    // implementar
    Noh* menor = esq;
    if(menor -> esq != NULL){
		return menor -> MenorRecursivo();
	}
	else{
		return menor -> valor;
	}
}

bool Noh::Sucessor(Dado* ptResultado) {
    // implementar
    if(FilhoDaDireita()){
		return true;
	}
	else{
		return false;
	}
}

// === Classe ABB ==============================================================
ABB::~ABB(){
    delete raiz;
}

void ABB::Inserir(Dado d) {
    Noh* novo = new Noh(d);
    if (raiz == NULL) {
        raiz = novo;
    } else {
        Posicao posInsercao;
        Noh* atual = raiz;
        Noh* anterior;
        while (atual != NULL) {
            anterior = atual;
            if (atual->valor > d) {
                atual = atual->esq;
                posInsercao = ESQ;
            } else {
                atual = atual->dir;
                posInsercao = DIR;
            }
        }
        novo->pai = anterior;
        if (posInsercao == DIR) {
            anterior->dir = novo;
        } else {
            anterior->esq = novo;
        }
    }
}

bool ABB::Sucessor(Dado d, Dado* ptResultado) {
    // implementar
    Noh* atual = Busca(d);
    if(atual != NULL){
		if(atual -> esq == NULL and atual -> dir == NULL){
            d = atual -> valor;
            *ptResultado = atual -> pai -> valor;
            Sucessor(d, ptResultado);
        }
        else if(atual -> dir == NULL and atual -> pai -> valor < atual -> valor){
            d = atual -> valor;
        }
        else if(atual -> esq == NULL and atual -> pai -> valor > atual -> valor){
            d = atual -> valor;
            *ptResultado = atual -> pai -> valor;
            Sucessor(d, ptResultado);
        }
	}
	else{
        return false;
    }
}

Noh* ABB::Busca(Dado d) {
    Noh* atual = raiz;
    while (atual != NULL) {
        if (atual->valor == d) {
            return atual;
        } else if (atual->valor > d) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    return atual;
}

void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh aux;
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

// === Programa ================================================================
int main() {
    ABB arvore;
    Dado chave;
    char operacao;
    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                cin >> chave;
                arvore.Inserir(chave);
                break;
            case 'e': // Escrever
                arvore.EscreverNivelANivel(cout);
                break;
            case 's': { // Sucessor
                cin >> chave;
                Dado sucessor;
                while (arvore.Sucessor(chave, &sucessor)) {
                    cout << sucessor << ' ';
                    chave = sucessor;
                }
                cout << endl;
                break;
            }
        }
    } while (operacao != 'f');
    return 0;
}

