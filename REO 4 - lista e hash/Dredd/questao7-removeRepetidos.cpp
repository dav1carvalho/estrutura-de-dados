#include <iostream>

using namespace std;

typedef int Dado;

class noh
{
    friend class listadup;

private:
    const Dado dado;
    noh *proximo;
    noh *anterior;

public:
    noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d)
{
    proximo = NULL;
    anterior = NULL;
}

class listadup
{
private:
    noh *primeiro;
    noh *ultimo;
    int tamanho;
    void removeTodos();

public:
    listadup();
    listadup(const listadup &umaLista);
    ~listadup();
    inline void insere(Dado dado);
    void insereNoFim(Dado dado);
    void imprime();
    inline bool vazia();
    void removeRepetidos();
};

listadup::listadup()
{
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

listadup::listadup(const listadup &umaLista)
{
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;

    noh *aux = umaLista.primeiro;
    while (aux != NULL)
    {
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
}

listadup::~listadup()
{
    removeTodos();
}

void listadup::removeTodos()
{
    noh *aux = primeiro;
    noh *temp;
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

void listadup::insere(Dado dado)
{
    insereNoFim(dado);
}

void listadup::insereNoFim(Dado dado)
{
    noh *novo = new noh(dado);

    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
    }
    else
    {
        ultimo->proximo = novo;
        novo->anterior = ultimo;
        ultimo = novo;
    }
    tamanho++;
}
void listadup::imprime()
{
    noh *aux = primeiro;
    while (aux != NULL)
    {
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
    aux = ultimo;
    while (aux != NULL)
    {
        cout << aux->dado << " ";
        aux = aux->anterior;
    }
    cout << endl;
}

inline bool listadup::vazia()
{
    return (tamanho == 0);
}
void listadup::removeRepetidos()
{
    if (vazia())
    {
        return;
    }
    noh *atual = primeiro;
    noh *aux = atual->proximo;
    while (atual->proximo != NULL)
    {
        while (aux != NULL)
        {

            if (aux->dado == atual->dado)
            {
                noh *mAnterior = aux->anterior;
                noh *mProximo = aux->proximo;

                mAnterior->proximo = mProximo;
                if (mProximo != NULL)
                {
                    mProximo->anterior = mAnterior;
                }
                else
                {
                    ultimo = aux->anterior;
                }
                delete aux;
                tamanho--;
                aux = mAnterior;
            }
            aux = aux->proximo;
        }
        if (atual->proximo != NULL)
        {
            atual = atual->proximo;
            aux = atual->proximo;
        }
        else
        {
            if (tamanho == 1)
            {
                primeiro = atual;
            }
        }
    }
}

int main()
{
    listadup l1;
    int qtd;
    cin >> qtd;
    int valor;
    for (int i = 0; i < qtd; i++)
    {
        cin >> valor;
        l1.insere(valor);
    }
    l1.removeRepetidos();
    l1.imprime();
    return 0;
}