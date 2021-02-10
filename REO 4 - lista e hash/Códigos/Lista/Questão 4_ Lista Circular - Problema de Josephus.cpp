#include <iostream>

using namespace std;

typedef int Dado;

class Noh
{
    friend class listaCircle;
    private:
        Noh* proximo;
        Dado dado;
    public:
        Noh(Dado Numero);
};

Noh::Noh(Dado Numero)
{
    dado = Numero;
    proximo = NULL;
};

class listaCircle
{
    private:
        Noh* primeiro;
        Noh* ultimo;
        int tamanho;
    public:
        listaCircle(Dado size);
        ~listaCircle();
        void criaNoh(Dado Numero);
        void Remove(Dado chave);
};

listaCircle::listaCircle(Dado size)
{
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
    
    for (Dado i = 1; i <= size; i++)
    {
        criaNoh(i);
    }
};

listaCircle::~listaCircle()
{
    Noh* atual = primeiro;
    
    if(tamanho == 0)
    {
        delete atual;
    }
}

void listaCircle::criaNoh(Dado Numero)
{
    Noh* novo = new Noh(Numero);
    
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
            ultimo -> proximo = primeiro;
        }
        ++tamanho;
    }
    else
    {
        cerr << "Noh nao foi criado" << endl;
    }
}

void listaCircle::Remove(Dado chave)
{
    if(tamanho < chave)
    {
        cerr << "Chave maior que tamanho" << endl;
    }
    else if(tamanho == chave)
    {
        cerr << "tamanho igual a chave" << endl;
    }
    else if(chave < tamanho)
    {
        Noh* atual = primeiro;
        Noh* ant = NULL;
        int i = 1;
    
        while(tamanho != 1)
        {
            while(i <= chave)
            {
                ant = atual;
                atual = atual -> proximo;
                i++;
            }
  
            ant -> proximo = atual -> proximo;
            delete atual;
            atual = ant;
            tamanho--;
            i = 0;
        }
        cout << atual -> dado << endl;
    }
}

int main()
{
    Dado N;
    cin >> N;
    listaCircle minhaLista(N);
    
    Dado M;
	
    cin >> M;
    
    minhaLista.Remove(M);
    
    
	return 0;
}

