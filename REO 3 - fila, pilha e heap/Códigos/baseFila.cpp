
#include <iostream>

using namespace std;

class noh
{
    friend class fila;

private:
    int mValor;
    noh *mProximo;

public:
    noh(int valor);
};

noh::noh(int valor)
{
    mValor = valor;
    mProximo = NULL;
}

class fila
{
private:
    noh *mInicio;
    noh *mFim;
    unsigned mTamanho;

public:
    fila();
    ~fila();
    unsigned tamanho();
    void enfileira(int valor);
    int desenfileira();
    void limpaFila();
    bool vazia();
};

fila::fila()
{
    mTamanho = 0;
    mInicio = NULL;
    mFim = NULL;
}

fila::~fila()
{
    limpaFila();
}

void fila::limpaFila()
{
    while (mTamanho > 0)
    {
        desenfileira();
    };
}

unsigned fila::tamanho()
{
    return mTamanho;
}

bool fila::vazia()
{
    return (mTamanho == 0);
}

void fila::enfileira(int valor)
{
    // primeiro criamos o novo nó
    noh *novo = new noh(valor);
    if (mTamanho == 0)
    {
        mInicio = novo;
    }
    else
    {
        mFim->mProximo = novo;
    }
    mFim = novo;
    mTamanho++;
}

int fila::desenfileira()
{
    int valor = mInicio->mValor;
    noh *temp = mInicio;
    mInicio = mInicio->mProximo;
    delete temp;
    mTamanho--;
    if (mTamanho == 0)
    {
        mFim = NULL;
    }
    return valor;
}


int main()
{
    fila f1;
    int num;
    cin >> num;

    while (num > 0)
    {
        f1.enfileira(num);
        cin >> num;
    }

    cout << "tamanho: " << f1.tamanho() << endl;
    cout << "elementos: ";

    while (not f1.vazia())
    {
        cout << f1.desenfileira() << " ";
    }
    cout << endl;

    return 0;
}