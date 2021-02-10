#include <iostream>

using namespace std;

typedef string Texto;

class noh {
    friend class lista;
    private:
        const Texto palavra;
        noh* proximo;
    public:
        noh(Texto p);
};

noh::noh(Texto p) : palavra(p) {
    proximo = NULL;
}

class lista {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        lista();
        lista(const lista& umaLista);
        lista& operator=(const lista& umaLista);
        lista operator+(const lista& umaLista) const;
        ~lista();
        void insere(Texto palavra);
        void imprime() const;
        void LimpaTudo();
        void InserenoFim(Texto palavra);
};

// constrÃ³i uma lista inicialmente vazia
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

// insere no inicio da lista
void lista::insere(Texto palavra) {
    
    noh* novo = new noh(palavra);
    novo->proximo = primeiro;
    primeiro = novo;
    if (tamanho == 0)
        ultimo = novo;
    ++tamanho;
}

// mÃ©todo bÃ¡sico que *percorre* a lista, imprimindo seus elementos
void lista::imprime() const {
    
    noh* iter = primeiro;
    while (iter != NULL) {
        cout << iter->palavra << " ";
        iter = iter->proximo;
    }
    cout << endl;
}

// construtor de cÃ³pia
lista::lista(const lista& umaLista) {
    
    tamanho = 0;
    ultimo = NULL;
    primeiro = NULL;
    
    noh* aux = umaLista.primeiro;
    
    while(aux != NULL)
    {
        insere(aux -> palavra);
        aux = aux -> proximo;
    }
}

// sobrecarga do operador de atribuiÃ§Ã£o - retorna a prÃ³pria lista
lista& lista::operator=(const lista& umaLista) {
    
    LimpaTudo();
    
    noh* aux = umaLista.primeiro;
    
    while(aux != NULL)
    {
        insere(aux -> palavra);
        aux = aux -> proximo;
    }
    
    return *this;
}

// concatenacao de listas
lista lista::operator+(const lista& umaLista) const {
    
   lista lista3;
    noh* aux = primeiro;
    
    while(aux!=NULL)
    {
        lista3.InserenoFim(aux -> palavra);
        aux = aux -> proximo;
    }
    
    aux = umaLista.primeiro;
    
    while(aux != NULL)
    {
        lista3.InserenoFim(aux -> palavra);
        aux = aux -> proximo;
    }
    return lista3;
}

void lista::LimpaTudo()
{
    noh* atual = primeiro;
    noh* ant = NULL;
    
    while(atual != NULL)
    {
        ant = atual -> proximo;
        delete atual;
        atual = ant;
    }
    
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

void lista::InserenoFim(Texto palavra)
{
    noh* novo = new noh(palavra);
    
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
    }
    ++tamanho;
}

int main() { // NÃƒO MODIFIQUE!
    lista listaA;
    lista listaB;
    string opcao;
    string palavra;
    char idLista;
    do {
        cin >> opcao;
        if (opcao == "i") {
            cin >> idLista >> palavra;
            if (idLista == 'a')
                listaA.insere(palavra);
            else
                listaB.insere(palavra);
        }
        else if (opcao == "a=b") {
            listaA = listaB;
        }
        else if (opcao == "b=a") {
            listaB = listaA;
        }
        else if (opcao == "s") {
            lista soma = listaA + listaB;
            soma.imprime();
        }
        else if (opcao == "e") {
            // escreve _uma copia_ da lista indicada
            cin >> idLista;
            lista* ptLista = (idLista == 'a') ? &listaA : &listaB;
            lista copiaDaLista(*ptLista);
            copiaDaLista.imprime();
        }
    } while (opcao != "t");
    return 0;
}
