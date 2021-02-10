#include <iostream>

using namespace std;

class noh
{
    friend class lista;
    private:
        noh* proximo;
        noh* anterior;
        string frase;
    public:
        noh(string comando);
};

noh::noh(string comando)
{
    proximo = NULL;
    anterior = NULL;
    frase = comando;
};

class lista
{
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        lista();
        ~lista();
        void insere(string d, int tam);
        int removefim(int tam);
        int removeInicio(int tam);
};

lista::lista()
{
    primeiro = NULL;
    ultimo = NULL;
};

lista::~lista()
{
    noh* atual = primeiro;
    noh* ant = NULL;
    
    while(atual != NULL)
    {
        ant = atual;
        atual = atual -> proximo;
        delete ant;
    }
    
    primeiro = NULL;
    ultimo = NULL;
};

void lista::insere(string d, int tam)
{
    noh* novo = new noh(d);
    
    if(novo)
    {
        if(primeiro == NULL)
        {
            primeiro = novo;
            ultimo = novo;
        }
        else
        {
            ultimo -> proximo = novo;
            novo -> anterior = ultimo;
            ultimo = novo;
        }
        tamanho++;
    }
}

int lista::removefim(int tam)
{
   int retorna;
   
   if(tamanho == 0)
   {
       cerr << "ERRO" << endl;
   }
   else
   {
       if(tamanho == 1)
       {
           retorna = primeiro -> frase;
           primeiro = NULL;
           ultimo = NULL;
           tamanho--;
       }
       else if(tamanho > 1)
       {
           noh* atual = ultimo;
           retorna = ultimo -> frase;
           ultimo = atual -> anterior;
           delete atual;
           ultimo -> proximo = NULL;
           tamanho--;
       }
   } 
   return retorna;   
}


void lista::removeInicio(int tam)
{
    int retorna;
    
    if(tamanho == 0)
    {
        cerr << "ERRO" << endl;
    }
    else
    {
        if(tamanho == 1)
        {
            noh* atual = primeiro;
            retirna = atual -> frase;
            delete atual;
            primeiro = NULL;
            ultimo = NULL;
            tamanho--;
        }
        else if(tamanho > 1)
        {
            noh* atual = primeiro;
            retorna = atual -> frase;
            primeiro = atual -> proximo;
            primeiro -> anterior = NULL;
            delete atual;
            tamanho--;
        }
    }
    return retorna;
}

int main()
{
    lista minhaLista;
    int tam;
    cin >> tam;
    string comando;
    cin.ignore();
    getline(cin, comando);
    int cont = 0;
    
    while(comando != "sair")
    {
        if(comando == "undo")
        {
            if(cont == 0)
            {
                cerr << "ERRO" << endl;
            }
            else if(cont > 0)
            {
                cout << "desfazer:" << " " << minhaLista.removefim(tam) << endl;
                cont--;
            }
        }
        else
        {
            if(cont < tam)
            {
                minhaLista.insere(comando, tam);
                cont++;
            }
            else if(cont == tam)
            {
                cout << "esqueci:" << " " << minhaLista.removeInicio(tam) << endl;
                minhaLista.insere(comando, tam);
            }
        }
        
        getline(cin , comando);
    }
	
	return 0;
}

