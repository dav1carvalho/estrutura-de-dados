#include <iostream>

using namespace std;

typedef int Dado;

class noh {
    friend class lista;
    private:
        const Dado dado;
        noh* proximo;
    public:
        noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d) {
    proximo = NULL;
}

class lista {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        lista();
        ~lista();
        void insere(Dado dado);
        void insere(Dado dado, int pos);
        void remove(int posicao);
        int procura(Dado valor);
        void imprime();
        inline bool vazia();
};

// constrói uma lista inicialmente vazia
lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

lista::~lista() {
    noh* iter = primeiro;
    noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->proximo;
        delete iter;
        iter = proximo;
    }
}

// método básico que *percorre* a lista, imprimindo seus elementos
void lista::imprime() {
    noh* aux = primeiro;
    while (aux != NULL) {
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

// insere por padrão no final da lista
void lista::insere(Dado dado) {
    
    noh* novo = new noh(dado);
    
    if(novo)
    {
        novo -> proximo = NULL;
        
        if(primeiro == NULL)
        {
           primeiro = novo;
           ultimo = novo;
       }
       else
       {
           ultimo -> proximo = novo;
           ultimo = novo;
       }
       tamanho++;
   }
}

// insere um dado em uma determinada posição da lista
void lista::insere(Dado dado, int posicao) {
    
    noh* novo = new noh(dado);
    
    if(novo)
    {
        if(posicao > tamanho or posicao < 0)
        {
            cerr << "Posicao muito grande desgraça" << endl;
        }
        else
        {
            if(primeiro == NULL)
            {
                insere(dado);
            }
            else
            {
                noh* ant = NULL;
                noh* atual = primeiro;
                
                for (int i = 0; i < posicao; i++)
                {
                    ant = atual;
                    atual = atual -> proximo;
                }

            ant -> proximo = novo;
            novo -> proximo = atual;
            }
            tamanho++;
        }
    }
}

// remove o item da posição passada por parâmetro
// Atenção - o código deve tratar de posição inválidas
void lista::remove(int posicao) {
    
    int cont = 0;
    noh* ant = NULL;
    noh* atual = primeiro;
    
    if(posicao < 0 or posicao > tamanho)
    {
        cerr << "posicao nao existe" << endl;
    }
    else
    {
        while(cont != posicao)
        {
            ant = atual;
            atual = atual -> proximo;
            cont++;
        }
        if(posicao > 0 and atual != ultimo)
        {
            ant -> proximo = atual -> proximo;
            delete atual;
        }
        else if(posicao > 0 and atual == ultimo)
        {
            ultimo = ant;
            ant -> proximo = NULL;
            delete atual;
        }
        else if(posicao == 0 and primeiro == ultimo) 
        {
            ant = atual;
            atual = atual->proximo;
            primeiro = NULL;
            ultimo = NULL;
            delete ant;
        }
        else if(posicao == 0 and primeiro != ultimo) 
        {
            ant = atual;
            atual = atual->proximo;
            primeiro = atual;
            delete ant;
        }
        tamanho--;
    }
}

// procura por um elemento e retorna a posição ou -1 se não encontrado
int lista::procura(Dado valor) {
    
    noh* aux;
    aux = primeiro;
    int cont = 0;
    
    while(aux != NULL)
    {
        if(aux -> dado == valor)
        {
            return cont;
        }
        else
        {
            aux = aux -> proximo;
        }
        cont++;
    }
    
    return -1;
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    // Implemente aqui
    if(primeiro == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main() { // NÃO MODIFIQUE!
    lista minhaLista;
    char opcao;
    int valor, pos;
    cin >> opcao;
    while (opcao != 'Q') {
        switch(opcao) {
            case 'I':
                cin >> valor;
                minhaLista.insere(valor);
                break;
            case 'W':
                cin >> valor;
                cin >> pos;
                minhaLista.insere(valor, pos);
                break;
            case 'P':
                cin >> valor;
                cout << minhaLista.procura(valor) << endl;
                break;
            case 'R':
                cin >> pos;
                minhaLista.remove(pos);
                break;
            case 'V':
                cout << minhaLista.vazia() << endl;
                break;
        }
        cin >> opcao;
    }
    minhaLista.imprime();
    return 0;
}
