#include <iostream>

using namespace std;

typedef float Dado;

class noh {
  friend class listadup;
  private:
    const Dado dado;
    noh* proximo;
    noh* anterior;
  public:
    noh(Dado d = 0) : dado(d) {
      proximo = NULL;
      anterior = NULL;
    }
};

// lista dinamicamente encadeada
class listadup {
  private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
  public:
    listadup() {
      // constrói uma lista inicialmente vazia
      tamanho = 0;
      primeiro = NULL;
      ultimo = NULL;
    };
    ~listadup() {
      // destroi a lista
      noh* atual = primeiro;
      while (atual != NULL) {
        noh* aux = atual;
        atual = atual->proximo;
        delete aux;
      }
    };
    inline void insere(Dado dado) {
        
        noh* novo = new noh(dado);
        
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
        else
        {
            cerr << "Noh nao foi criado" << endl;
        }
    };
    listadup* separa(int n) 
    {
      listadup* listaAux = new listadup;
        
      if(n < 0 or n >= tamanho or primeiro == NULL)
      {
          cerr << "erro!" << endl;
          return NULL;
      }
    
      noh* atual = primeiro;
      noh* ant = NULL;
      noh* deleta = NULL;
          
      int i = 0;

      if(primeiro != ultimo and n == 0)
      {
        while(atual != NULL)
        {
            listaAux -> insere(atual -> dado);
            deleta = atual;
            atual = atual -> proximo;
            delete deleta;
        }
        
        listaAux->primeiro->anterior = NULL;
        primeiro = NULL;
        ultimo = NULL;
        ultimo->proximo = NULL;
      }
      else if(primeiro != ultimo and n > 0)
      {
          i = 0;
          while(i < n) {
              atual = atual->proximo;
              i++;
          }
          ant = atual->anterior;
          while(atual != NULL)
          {
              listaAux -> insere(atual -> dado);
              deleta = atual;
              atual = atual -> proximo;
              delete deleta;
          }
      
      
          ultimo = ant;
          ultimo -> proximo = NULL;
          listaAux -> primeiro -> anterior = NULL;
      }     
      else if(primeiro == ultimo and n == 0)
      {
          listaAux -> insere(atual -> dado);
          delete atual;
          primeiro = NULL;
          ultimo = NULL;
          ultimo->proximo = NULL;
          listaAux->primeiro->anterior = NULL;
      }
      
      return listaAux;
    };
    
    void imprime() {
      // método básico que *percorre* uma lista, imprimindo seus elementos
      noh* aux = primeiro;
      
      if (aux == NULL) {
        cout << "vazio!";
      } else {
        while (aux != NULL) {
          cout << aux->dado << " ";
          aux = aux->proximo;
        }
      }
      
      cout << " <> ";
      
      // imprime reverso (para mostrar duplo encadeamento)
      aux = ultimo;
      if (aux == NULL) {
        cout << "vazio!";
      } else {
        while (aux != NULL) {
          cout << aux->dado << " ";
          aux = aux->anterior;
        }
      }
      
      cout << endl;
    };
};


// NÃO MODIFICAR
int main() {
  listadup* minhaLista = new listadup;
  
  char opcao;
  float valor;

  do {
    cin >> opcao;

    switch(opcao) {
      case 'I':
        cin >> valor;
        minhaLista->insere(valor);
        break;
      case 'S':
        cin >> valor;
        listadup* outraLista = minhaLista->separa(valor);
        if (outraLista != NULL) {
          outraLista->imprime();
          delete outraLista;
        } 
        break;
    }
  } while (opcao != 'Q');

  minhaLista->imprime();
  
  delete minhaLista;

  return 0;
}
