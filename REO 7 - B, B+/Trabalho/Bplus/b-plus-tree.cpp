/*Árvore B+ - Arquivo da árvore
 * Utiliza a configuração do arquivo configuracao.hpp
 *
 * Davi Alves Carvalho | Ewerton Keiji Onga | José Victor Amorim Morais, Março de 2021 - Estrutura de Dados (GCC216)
 * Caracteristicas desta implementação - Março de 2021:
 * 
 * Inserção e Busca em uma árvore B+ com encadeamente entre as folhas
 * A busca é feita de maneira sequencial
*/

#include <iostream>
#include <string.h>
#include "configuracao.hpp"
using namespace std;

class Pagina {
    // declarando a árvore como classe amiga para acessar as propriedades privadas da página
    friend class Bplustree;

    private:
        bool folha;
        dado *chave;
        unsigned tamanho;
        // declarando um ponteiro que aponta para outro ponteiro pokemon
        Pagina **ponteiroPagina;
    public:
        Pagina();
};

Pagina::Pagina() {
    chave = new dado[CAP_PACOTE];
    ponteiroPagina = new Pagina *[CAP_PACOTE + 1];
    tamanho = 0;
}

class Bplustree {
    private:
        Pagina *raiz;
        Pagina *encontrarPai(Pagina* umaPagina, Pagina* outraPagina);
        void inserirInternamente(dado umDado, Pagina* umaPagina, Pagina* outraPagina);
    public:
        Bplustree();
        void inserir(dado umDado);
        dado busca(tipoChave umaChave, int &contador);
        void depuracao(Pagina* umaPagina);
        void imprime(Pagina* umaPagina);
        Pagina *raizArvore();
};
// constructor
Bplustree::Bplustree() {
    raiz = NULL;
}

void Bplustree::inserir(dado umDado) {
    // ÁRVORE VAZIA
    if (raiz == NULL) {
        raiz = new Pagina;
        raiz->chave[0] = umDado;
        raiz->folha = true;
        raiz->tamanho++;
    } else {
        Pagina *auxiliar = raiz;
        Pagina *pai;
        while (auxiliar->folha != true) {
            pai = auxiliar;
            bool sair = false;
            unsigned i = 0;
            while (i < auxiliar->tamanho and sair == false) {
                if (strcmp(umDado.nome, auxiliar->chave[i].nome) < 0) {
                    auxiliar = auxiliar->ponteiroPagina[i];
                    sair = true;
                }
                if (i == auxiliar->tamanho - 1 and sair == false) {
                    auxiliar = auxiliar->ponteiroPagina[i + 1];
                    sair = true;
                }
                i++;
            }
        }
        if (auxiliar->tamanho < CAP_PACOTE) {
            unsigned i = 0;
            while (strcmp(umDado.nome, auxiliar->chave[i].nome) > 0 and i < auxiliar->tamanho) {
                i++;
            }
            for (unsigned j = auxiliar->tamanho; j > i; j--) {
                auxiliar->chave[j] = auxiliar->chave[j - 1];
            }
            auxiliar->chave[i] = umDado;
            auxiliar->tamanho++;
            auxiliar->ponteiroPagina[auxiliar->tamanho] = auxiliar->ponteiroPagina[auxiliar->tamanho-1];
            auxiliar->ponteiroPagina[auxiliar->tamanho - 1] = NULL;
        } else {
            Pagina *novaFolha = new Pagina;
            dado paginaProvisoria[CAP_PACOTE + 2];
            for (unsigned i = 0; i < CAP_PACOTE; i++) {
                paginaProvisoria[i] = auxiliar->chave[i];
            }
            unsigned i = 0, j;
            while (strcmp(umDado.nome, paginaProvisoria[i].nome) > 0 and i < CAP_PACOTE)
            {
                i++;
            }
            for (unsigned j = CAP_PACOTE + 1; j > i; j--) {
                paginaProvisoria[j] = paginaProvisoria[j - 1];
            }
            paginaProvisoria[i] = umDado;
            novaFolha->folha = true;
            auxiliar->tamanho = CAP_PACOTE/2;
            novaFolha->tamanho = CAP_PACOTE - (CAP_PACOTE/2);
            auxiliar->ponteiroPagina[auxiliar->tamanho] = novaFolha;
            novaFolha->ponteiroPagina[novaFolha->tamanho] = auxiliar->ponteiroPagina[CAP_PACOTE];
            auxiliar->ponteiroPagina[CAP_PACOTE] = NULL;
            for (i = 0; i < auxiliar->tamanho; i++) {
                auxiliar->chave[i] = paginaProvisoria[i];
            }
            for (i = 0, j = auxiliar->tamanho; i < novaFolha->tamanho; i++, j++) {
                novaFolha->chave[i] = paginaProvisoria[j];
            }
            if (auxiliar == raiz) {
                Pagina *novaRaiz = new Pagina;
                novaRaiz->chave[0] = novaFolha->chave[0];
                novaRaiz->ponteiroPagina[0] = auxiliar;
                novaRaiz->ponteiroPagina[1] = novaFolha;
                novaRaiz->folha = false;
                novaRaiz->tamanho = 1;
                raiz = novaRaiz;
            } else {
                inserirInternamente(novaFolha->chave[0], pai, novaFolha);
            }
        }
    }
}

void Bplustree::inserirInternamente(dado umDado, Pagina *umaPagina, Pagina *outraPagina) {
    if (umaPagina->tamanho < CAP_PACOTE) {
        unsigned i = 0;
        while (strcmp(umDado.nome, umaPagina->chave->nome) > 0 and i < umaPagina->tamanho) {
            i++;
        }
        for (unsigned j = umaPagina->tamanho; j > i; j--) {
            umaPagina->chave[j] = umaPagina->chave[j - 1];
        }
        for (unsigned j = umaPagina->tamanho + 1; j > i + 1; j--) {
            umaPagina->ponteiroPagina[j] = umaPagina->ponteiroPagina[j - 1];
        }
        umaPagina->chave[i] = umDado;
        umaPagina->tamanho++;
        umaPagina->ponteiroPagina[i + 1] = outraPagina;
    } else {
        Pagina *novaPaginaInterna = new Pagina;
        dado listaProvisoria[CAP_PACOTE + 2];
        Pagina *paginaProvisoria[CAP_PACOTE + 3];
        for (unsigned i = 0; i < CAP_PACOTE; i++) {
            listaProvisoria[i] = umaPagina->chave[i];
        }
        for (unsigned i = 0; i < CAP_PACOTE + 1; i++) {
            paginaProvisoria[i] = umaPagina->ponteiroPagina[i];
        }
        unsigned i = 0;
        while (strcmp(umDado.nome, listaProvisoria[i].nome) > 0 and i < CAP_PACOTE)
        {
            i++;
        }
        for (unsigned j = CAP_PACOTE + 1; j > i; j--) {
            listaProvisoria[j] = listaProvisoria[j - 1];
        }
        listaProvisoria[i] = umDado;
        for (unsigned j = CAP_PACOTE + 2; j > i + 1; j--) {
            paginaProvisoria[j] = paginaProvisoria[j - 1];
        }
        paginaProvisoria[i + 1] = outraPagina;
        novaPaginaInterna->folha = false;
        umaPagina->tamanho = CAP_PACOTE/2;
        novaPaginaInterna->tamanho = CAP_PACOTE - (CAP_PACOTE/2);
        unsigned j;
        for (i = 0, j = umaPagina->tamanho + 1; i < novaPaginaInterna->tamanho; i++, j++) {
            novaPaginaInterna->chave[i] = listaProvisoria[j];
        }      
        for (i = 0, j = umaPagina->tamanho + 1; i < novaPaginaInterna->tamanho + 1; i++, j++) {
            novaPaginaInterna->ponteiroPagina[i] = paginaProvisoria[j];
        }
        if (umaPagina == raiz) {
            Pagina *novaRaiz = new Pagina;
            novaRaiz->chave[0] = umaPagina->chave[umaPagina->tamanho];
            novaRaiz->ponteiroPagina[0] = umaPagina;
            novaRaiz->ponteiroPagina[1] = novaPaginaInterna;
            novaRaiz->folha = false;
            novaRaiz->tamanho = 1;
            raiz = novaRaiz;
        } else {
            inserirInternamente(umaPagina->chave[umaPagina->tamanho], encontrarPai(raiz, umaPagina), novaPaginaInterna);
        }
    }
}

Pagina* Bplustree::encontrarPai(Pagina* umaPagina, Pagina* outraPagina) {
    Pagina *pai;
    if (umaPagina->folha == true or umaPagina->ponteiroPagina[0]->folha == true) {
        return NULL;
    }
    bool sair = false;
    unsigned i = 0;
    while (sair == false and i < umaPagina->tamanho + 1) {
        if (umaPagina->ponteiroPagina[i] == outraPagina) {
            pai = umaPagina;
            sair = true;
        } else {
            pai = encontrarPai(umaPagina->ponteiroPagina[i], outraPagina);
            if (pai != NULL) {
                sair = true;
            }
        }
        i++;
    }
    return pai;
}

dado Bplustree::busca(tipoChave umaChave, int &contador) {
    if (raiz == NULL) {
        cout << "Árvore vazia" << endl;
    } else {
        Pagina *auxiliar = raiz;
        while (auxiliar->folha != true) {
            unsigned i = 0;
            bool sair = false;
            while (i < auxiliar->tamanho and sair == false) {
                if (strcmp(umaChave, auxiliar->chave[i].nome) < 0) {
                    auxiliar = auxiliar->ponteiroPagina[i];
                    sair = true;
                }
                if (i == auxiliar->tamanho - 1 and sair == false) {
                    auxiliar = auxiliar->ponteiroPagina[i + 1];
                    sair = true;
                }
                i++;
                contador++;
            }
            contador++;
        }
        for (unsigned i = 0; i < auxiliar->tamanho; i++) {
            contador++;
            if (strcmp(auxiliar->chave[i].nome,umaChave) == 0) {
                return auxiliar->chave[i];
            }
        }
        // Não retornou nada então não encontrou
    }
    throw runtime_error("Busca: elemento não encontrado.");
}

void Bplustree::depuracao(Pagina *umaPagina) {
    if (umaPagina != NULL) {
        for (unsigned i = 0; i < umaPagina->tamanho; i++) {
            cout << umaPagina->chave[i].nome << " ";
        }
        cout << endl;
        if (umaPagina->folha != true) {
            for (unsigned i = 0; i < umaPagina->tamanho + 1; i++) {
                depuracao(umaPagina->ponteiroPagina[i]);
            }
        }
    }
}

void Bplustree::imprime(Pagina *umaPagina) {
    if (umaPagina != NULL) {
        if (umaPagina->folha == true) {
            for (unsigned i = 0; i < umaPagina->tamanho; i++) {
                cout << umaPagina->chave[i].nome << " ";
            }
            cout << " -> ";
        }
        if (umaPagina->folha != true) {
            for (unsigned i = 0; i < umaPagina->tamanho + 1; i++) {
                imprime(umaPagina->ponteiroPagina[i]);
            }
        }
    }
}

Pagina *Bplustree::raizArvore() {
    return raiz;
}

int main() {
    dado umDado;
    Bplustree minhaArvore;
    tipoChave umaChave;
    int contador;
    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // inserir
                    cin >> umDado.id >> umDado.nome 
                    >> umDado.tipo >> umDado.pontuacao >> umDado.vida >> umDado.ataque
                    >> umDado.defesa >> umDado.ataqueEspecial >> umDado.defesaEspecial >> umDado.velocidade;
                    minhaArvore.inserir(umDado);
                    break;
                case 'b': // buscar
                    contador = 0;
                    cin >> umaChave;
                    umDado = minhaArvore.busca(umaChave, contador);
                    cout << "Contador: " << contador << endl;
                    cout << "Busca Pokemon: " << endl;
                    cout << "Id: " << umDado.id << endl;
                    cout << "Nome: " << umDado.nome << endl;
                    cout << "Tipo: " << umDado.tipo << endl;
                    cout << "Pontuacao: " << umDado.pontuacao << endl;
                    cout << "Vida: " << umDado.vida << endl;
                    cout << "Ataque: " << umDado.ataque << endl;
                    cout << "Defesa: " << umDado.defesa << endl;
                    cout << "Ataque Especial: " << umDado.ataqueEspecial << endl;
                    cout << "Defesa Especial: " << umDado.defesaEspecial << endl;
                    cout << "Velocidade: " << umDado.velocidade << endl;
                    break;
                case 'p': // mostrar estrutura
                    minhaArvore.imprime(minhaArvore.raizArvore());
                    cout << endl;
                    break;
                case 'd': // mostrar estrutura
                    minhaArvore.depuracao(minhaArvore.raizArvore());
                    break;
                case 's': // sair
                    // será tratado no while
                    break;
                default:
                    cout << "Opção inválida!" << endl;
            }
        } catch (runtime_error& e) {
            cerr << e.what() << endl;
        }
    } while (operacao != 's');

    return 0;
}