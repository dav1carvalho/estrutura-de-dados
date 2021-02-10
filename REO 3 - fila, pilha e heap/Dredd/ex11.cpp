#include <iostream>

using namespace std;

class noh
{
	friend class Fila;

private:
	int mValor;
	noh(int valor);
	noh *mProximo;
};

noh::noh(int valor)
{
	mValor = valor;
	mProximo = NULL;
}

class Fila
{
private:
	noh *mInicio;
	noh *mFim;
	unsigned mTamanho;

public:
	void enfileira(int valor);
	int desenfileira();
	int espia();
	bool vazia();
	Fila();
};

Fila::Fila()
{
	mInicio = NULL;
	mFim = NULL;
	mTamanho = 0;
}

void Fila::enfileira(int valor)
{
	noh *novo = new noh(valor);

	if (mTamanho == 0)
	{
		mInicio = novo;
		mFim = novo;
	}
	else
	{
		mFim->mProximo = novo;
		mFim = novo;
	}
	mTamanho++;
}

int Fila::desenfileira()
{

	noh *aux = mInicio;
	int valor = aux->mValor;

	if (mInicio == NULL)
		return 0;
	else
	{
		mInicio = mInicio->mProximo;
		mTamanho--;
		delete aux;
		return valor;
	}
}

int Fila::espia()
{
	return mInicio->mValor;
}

bool Fila::vazia()
{
	if (mInicio == NULL)
		return true;
	return false;
}

int main()
{

	Fila fila1, fila2;
	int valor, qtd1, qtd2;

	cin >> qtd1;

	for (int i = 0; i < qtd1; i++)
	{
		cin >> valor;
		fila1.enfileira(valor);
	}

	cin >> qtd2;

	for (int i = 0; i < qtd2; i++)
	{
		cin >> valor;
		fila2.enfileira(valor);
	}

	Fila fila3;
	int guardaElemento;
	while (!fila1.vazia() or !fila2.vazia())
	{
		if (!fila1.vazia())
		{
			if (!fila2.vazia())
			{
				if (fila2.espia() < fila1.espia())
				{
					guardaElemento = fila2.desenfileira();
				}

				else
				{
					guardaElemento = fila1.desenfileira();
				}
			}
			else
			{
				guardaElemento = fila1.desenfileira();
			}
		}
		else
		{
			guardaElemento = fila2.desenfileira();
		}
		while (!fila1.vazia() and fila1.espia() == guardaElemento)
		{
			fila1.desenfileira();
		}
		while (!fila2.vazia() and fila2.espia() == guardaElemento)
		{
			fila2.desenfileira();
		}

		fila3.enfileira(guardaElemento);
	}

	while (!fila3.vazia())
	{
		cout << fila3.desenfileira() << " ";
	}
	return 0;
}
