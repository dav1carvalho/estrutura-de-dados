
#include <iostream>
#include <queue>
#include <stdexcept>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef int Dado;

enum Posicao
{
    DIR,
    ESQ
};

class Noh
{
    friend class ABB;

public:
    Noh(Dado d);
    //~Noh();
    //unsigned NroDeFolhas() const;
private:
    Dado valor;
    Noh *esq;
    Noh *dir;
    Noh *pai;
};

Noh::Noh(Dado d)
{
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

class ABB
{
public:
    ABB();
    ~ABB();

    // Escreve uma Ã¡rvore nÃ­vel a nÃ­vel.// Pode ser Ãºtil para depurar o programa.
    void EscreverNivelANivel(std::ostream &saida);

    // Insere um dado na Ã¡rvore.
    void Inserir(Dado d);

    // Retorna o nro de folhas na Ã¡rvore.
    //unsigned NroDeFolhas();
    //void percorre(Noh* atual);

    //Busca um elemento na arvore
    Dado busca(Dado valor);

    //Remove um elemento da arvore
    void remove(Dado d);
    void ImprimeQtde();

private:
    Noh *buscaAux(Dado chave);
    int ContarNohs(Noh *noh);
    void transplanta(Noh *antigo, Noh *novo);
    Noh *minimoAux(Noh *atual);

    int contador;
    //unsigned NroDeFolhasAux(Noh* atual);
    void destrutorRecursivo(Noh *atual);
    Noh *raiz;
};

ABB::~ABB()
{
    destrutorRecursivo(raiz);
}

ABB::ABB()
{
    raiz = NULL;
    contador = 0;
}

void ABB::destrutorRecursivo(Noh *atual)
{
    if (atual != NULL)
    {
        destrutorRecursivo(atual->esq);
        destrutorRecursivo(atual->dir);
        delete atual;
    }
}

void ABB::Inserir(Dado d)
{
    Noh *novoNoh = new Noh(d);
    contador = 0;
    if (raiz == NULL)
    {
        raiz = novoNoh;
        contador++;
    }
    else
    {
        Noh *atual = raiz;
        Noh *anterior = NULL;

        while (atual != NULL)
        {
            anterior = atual;
            if (atual->valor > d)
            {
                atual = atual->esq;
            }
            else
            {
                atual = atual->dir;
            }
            contador++;
        }

        novoNoh->pai = anterior;

        if (anterior->valor > novoNoh->valor)
        {
            anterior->esq = novoNoh;
        }
        else
        {
            anterior->dir = novoNoh;
        }
    }
    cout << "Nos Acessados: " << contador << endl;
    cout << endl
         << "-----------------" << endl
         << endl;
}

void ABB::EscreverNivelANivel(ostream &saida)
{
    queue<Noh *> filhos;
    Noh aux = Dado();
    Noh *fimDeNivel = &aux; // marcador especial para fim de nivel
    filhos.push(raiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty())
    {
        Noh *ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel)
        {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else
        {
            saida << '[';
            if (ptNoh != NULL)
            {
                saida << ptNoh->valor;
                filhos.push(ptNoh->esq);
                filhos.push(ptNoh->dir);
            }
            saida << ']';
        }
    }
}

Dado ABB::busca(Dado valor)
{
    contador = 0;
    Noh *resultado = buscaAux(valor);
    if (resultado != NULL)
    {
        cout << endl;
        cout << "Nos Acessados: " << contador << endl;
        cout << endl
             << "-----------------" << endl
             << endl;

        return resultado->valor;
    }
    else
    {
        cerr << "Elemento não encontrado davi, como q faz?" << endl;
        cout << endl;
        cout << "Nos Acessados: " << contador << endl;
        cout << endl
             << "-----------------" << endl
             << endl;

        return 0;
    }
}

Noh *ABB::buscaAux(Dado chave)
{
    //Faz a busca na estrutura e retorna
    Noh *atual = raiz;

    while (atual != NULL)
    {
        if (atual->valor == chave)
        {
            contador++;
            return atual;
        }
        else if (atual->valor > chave)
        {
            atual = atual->esq;
            contador++;
        }
        else
        {
            atual = atual->dir;
            contador++;
        }
    }
    return atual;
}

void ABB::remove(Dado d)
{
    //Remove um elemento (noh) da arvore
    //Noh* aux = new Noh(d);
    contador = 0;
    Noh *remover = buscaAux(d);

    if (remover == NULL)
    {
        cout << "ERRO" << endl;
    }
    else
    {
        if ((remover->esq == NULL) and (remover->dir == NULL))
        {
            contador--;
        }
        if (remover->esq == NULL)
        {
            transplanta(remover, remover->dir);
            contador++;
        }
        else if (remover->dir == NULL)
        {
            transplanta(remover, remover->esq);
            contador++;
        }
        else
        {
            Noh *sucessor = minimoAux(remover->dir);

            if (sucessor->pai != remover)
            {
                transplanta(sucessor, sucessor->dir);
                sucessor->dir = remover->dir;
                sucessor->dir->pai = sucessor;
            }
            transplanta(remover, sucessor);
            sucessor->esq = remover->esq;
            sucessor->esq->pai = sucessor;
            contador++;
        }
        delete remover;
    }
    cout << "Nos Acessados: " << contador << endl;
    cout << endl
         << "-----------------" << endl
         << endl;
}

void ABB::transplanta(Noh *antigo, Noh *novo)
{
    //Troca dois nos
    if (raiz == antigo)
    {
        raiz = novo;
    }
    else if (antigo == antigo->pai->esq)
    {
        antigo->pai->esq = novo;
    }
    else
    {
        antigo->pai->dir = novo;
    }
    if (novo != NULL)
    {
        novo->pai = antigo->pai;
    }
}

Noh *ABB::minimoAux(Noh *atual)
{
    //Retorna o minimo da arvore
    while (atual->esq != NULL)
    {
        contador++;
        atual = atual->esq;
    }
    return atual;
}

int ABB::ContarNohs(Noh *noh)
{
    if (noh == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + ContarNohs(noh->esq) + ContarNohs(noh->dir);
    }
}

void ABB::ImprimeQtde()
{
    cout << ContarNohs(raiz) << endl;
    cout << ContarNohs(raiz->esq) - ContarNohs(raiz->dir) << endl;
}

int main()
{
    ABB arvore;
    Dado valor;
    string a;

    auto start = high_resolution_clock::now();
    //insere 30 objetos
    
    for (unsigned i = 0; i < 30; ++i)
    {
        cout << "Insercao de: ";
        cin >> valor;
        arvore.Inserir(valor);
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
