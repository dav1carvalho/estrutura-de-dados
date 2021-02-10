#include <iostream>

using namespace std;

class noh
{
	friend class pilha;

private:
	char mValor;
	noh *mProximo;

public:
	noh(char valor);
};

noh::noh(char valor)
{
	mValor = valor;
	mProximo = NULL;
}

class pilha
{
private:
	noh *mTopo;
	unsigned mTamanho;

public:
	pilha();
	~pilha();
	unsigned tamanho();
	void empilha(char valor);
	void desempilha();
	void limpaPilha();
	bool vazia();
};

pilha::pilha()
{
	mTopo = NULL;
	mTamanho = 0;
}

pilha::~pilha()
{
	limpaPilha();
}

void pilha::limpaPilha()
{
	while (mTamanho > 0)
	{
		desempilha();
	};
}

unsigned pilha::tamanho()
{
	return mTamanho;
}

bool pilha::vazia()
{
	return (mTamanho == 0);
}
void pilha::empilha(char valor)
{
	noh *novo = new noh(valor);
	if (novo)
	{
		novo->mValor = valor;
		novo->mProximo = NULL;
		if (mTopo == NULL)
		{
			mTopo = novo;
		}
		else
		{
			novo->mProximo = mTopo;
			mTopo = novo;
		}
		mTamanho++;
	}
}

void pilha::desempilha()
{
	noh *temp = mTopo;
	mTopo = mTopo->mProximo;
	delete temp;
	mTamanho--;
}
int main()
{
	pilha pA;
	pilha pC;
	unsigned contB = 0;
	char letra;

	cin >> letra;

	while (letra != 'X')
	{
		switch (letra)
		{
		case 'A':
			pA.empilha(letra);

			break;

		case 'B':
			contB++;

			break;

		case 'C':
			pC.empilha(letra);

		default:
			break;
		}
		cin >> letra;
	}
	unsigned auxC = 0;
	if (contB == 1)
	{
		while (not pA.vazia() and not pC.vazia())
		{
			if (not pC.vazia())
			{
				pA.desempilha();
				if (not pC.vazia())
				{
					pC.desempilha();
					if (not pC.vazia())
					{
						pC.desempilha();
					}
					else
					{
						auxC++;
					}
				}
			}
		}
	}

	if (pA.vazia() and pC.vazia() and auxC == 0)
	{
		cout << "sim"
			 << " " << pA.tamanho() << " " << pC.tamanho() << endl;
	}
	else
	{
		cout << "nao"
			 << " " << pA.tamanho() << " " << pC.tamanho() << endl;
	}
	return 0;
}