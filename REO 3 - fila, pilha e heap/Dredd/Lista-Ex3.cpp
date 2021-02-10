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
		void insereInicio(Dado dado);
		void insere(Dado dado, int pos);
		void inserePosAux(Dado dado, int pos);
		void insereVazio(Dado dado);
		void removePos(int pos);
		void removeInicio();
		void removeFim();
		void remove(int pos);
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

void lista :: insereVazio(Dado dado)
{
	if (primeiro == nullptr)
	{
	    noh* novoNoh = new noh(dado);

		primeiro = novoNoh;
		ultimo = novoNoh;

		tamanho++;
	}
}

void lista :: insereInicio(Dado dado)
{
	if (primeiro == nullptr)
	    insereVazio(dado);
	else
	{
	    noh* novoNoh = new noh(dado);

		novoNoh->proximo = primeiro;
		primeiro = novoNoh;

		tamanho++;
	}
}

void lista :: inserePosAux(Dado dado, int pos)
{
	if (primeiro == nullptr)
	    insereVazio(dado);
	else
	{
		noh* aux = primeiro;
		for (int i = 0; i < pos; i++)
		{
			if (i == pos - 1)
			{
			    noh* novoNoh = new noh(dado);

				novoNoh->proximo = aux->proximo;
				aux->proximo = novoNoh;
			}
	    	aux = aux->proximo;
		}
		tamanho++;
	}
}

// insere por padrão no final da lista
void lista::insere(Dado dado)
{
	if (primeiro == nullptr)
		insereVazio(dado);
	else
	{
		noh* novoNoh = new noh(dado);

		ultimo->proximo = novoNoh;
		ultimo = novoNoh;

		tamanho++;
	}
}

// insere um dado em uma determinada posição da lista
void lista::insere(Dado dado, int pos)
{
	if (pos < tamanho)
	{

		if (pos == 0)
		    insereInicio(dado);
		else if(pos == tamanho - 1)
			insere(dado);
		else
	    	inserePosAux(dado, pos);

	}
}


void lista :: removeInicio()
{
	noh* removido = primeiro;

	primeiro = removido->proximo;

	delete removido;
	tamanho--;

	if (vazia())
	{
		primeiro = nullptr;
	    ultimo = nullptr;
	}
}

void lista :: removeFim()
{
	noh* anterior = primeiro;
	noh* removido = primeiro;

	for (int i = 0; i < tamanho ; ++i)
	{
		if (i == tamanho - 1)
		{
			ultimo = anterior;
		   	anterior->proximo = nullptr;

			delete removido;
			tamanho--;
		}
		anterior = removido;
	    removido = removido->proximo;
	}
	if (vazia())
	{
	    primeiro = nullptr;
	}
}

void lista :: removePos(int pos)
{
	noh* anterior = primeiro;
	noh* removido = primeiro;

	for (int i = 0; i < pos; i++)
	{
		if (pos == 1)
		{
		    removido = primeiro->proximo;
			primeiro->proximo = removido->proximo;

			delete removido;
			tamanho--;
		}else if (i == pos - 1)
		{
		    anterior->proximo = removido->proximo;
			removido->proximo = nullptr;

			delete removido;
			tamanho--;
		}
		anterior = removido;
		removido = removido->proximo;
	}

	if (vazia())
	{
	    primeiro = nullptr;
		ultimo = nullptr;
	}
}

void lista::remove(int pos) //main
{
	if (pos < tamanho)
	{
	    if (pos == 0)
	        removeInicio();
		else if (pos == tamanho - 1)
			removeFim();
		else
			removePos(pos);
	}
}

// procura por um elemento e retorna a posição ou -1 se não encontrado
int lista::procura(Dado valor)
{
	noh* aux = primeiro;
	int pos = 0;
	int sentinela = 1;

	while (aux->dado != valor)
	{
		if (sentinela == tamanho)
		{
		    return -1;
		}

		aux = aux->proximo;
		pos++;
		sentinela++;
	}
	if (aux->dado == valor)
	{
	    return pos;
	}else
		return -1;
}

// verifica se a lista está vazia
inline bool lista :: vazia()
{
	if (primeiro == nullptr)
		return true;
	else
		return false;
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
				minhaLista.imprime();
				break;
			case 'W':
				cin >> valor;
				cin >> pos;
				minhaLista.insere(valor, pos);
				minhaLista.imprime();
				break;
			case 'P':
				cin >> valor;
				cout << minhaLista.procura(valor) << endl;
				minhaLista.imprime();
				break;
			case 'R':
				cin >> pos;
				minhaLista.remove(pos);
				minhaLista.imprime();
				break;
			case 'V':
				cout << minhaLista.vazia() << endl;
				minhaLista.imprime();
				break;
		}
		cin >> opcao;
	}
	minhaLista.imprime();
	return 0;
}
