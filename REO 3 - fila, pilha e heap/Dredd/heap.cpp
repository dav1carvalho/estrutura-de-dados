#include <iostream>
using namespace std;

typedef int Dado;


class Heap
{
private: //atributos
    unsigned mTam;
	unsigned mCap;
	Dado* mHeap;
public: //metodos
    Heap(unsigned _cap);
    ~Heap();
	void Troca(Dado* v1, Dado* v2);
	void CorrigeDescendo(unsigned _pos);
	void CorrigeSubindo(unsigned _pos);
	void ImprimirTudo();
	void Insere(Dado _valor);
	void Imprimir();
	Dado Remove();
    unsigned GetPai(unsigned _pos);
	unsigned GetFilhoDir(unsigned _pos);
	unsigned GetFilhoEsq(unsigned _pos);
};

Heap :: Heap(unsigned _cap)
{
	mCap = _cap;
	mHeap = new Dado[mCap];
	mTam = 0;
}

Heap :: ~Heap()
{
	delete [] mHeap;
}

void Heap :: Troca(TDado* v1, TDado* v2){
    //Troca Dois elementos
    TDado temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

void Heap :: CorrigeDescendo(unsigned _pos)
{
	unsigned esq = GetFilhoEsq(_pos);
	unsigned dir = GetFilhoDir(_pos);
	unsigned maior = _pos;

	if ((esq <= mTam - 1) and (mHeap[esq] > mHeap[maior]))
	    maior = esq;
	if ((dir <= mTam - 1) and (mHeap[dir] > mHeap[maior]))
	    maior = dir;
	if (maior != _pos)
	{
		swap(mHeap, _pos, maior);
		CorrigeDescendo(maior);
	}
}

void Heap :: CorrigeSubindo(unsigned _pos)
{
	unsigned p = GetPai(_pos);
	if ((p >= 0) and (mHeap[_pos] > mHeap[p]))
	{
	    swap(mHeap, _pos, p);
		CorrigeSubindo(p);
	}
}

void Heap :: Insere(Dado _valor)
{

	if (mTam < mCap)
	{
	    mHeap[mTam] = _valor;
		CorrigeSubindo(mTam);
		mTam++;
	}else if (mTam == 0)
	{
		mHeap[0] = _valor;
		mTam++;
	}
}

void Heap :: Imprimir()
{
	for (unsigned i = 0; i < mTam; ++i)
	{
	    cout << mHeap[i] << " ";
	}
	cout << endl;
}

void Heap :: ImprimirTudo()
{
	for (unsigned i = 0; i < mCap; ++i)
	{
	    cout << mHeap[i] << " ";
	}
	cout << endl;
}

Dado Heap :: Remove()
{
	Dado aux;
	if (mTam < 1)
	    return -1;
	aux = mHeap[0];
	swap(mHeap, 0, mTam - 1);
	mTam--;
	CorrigeDescendo(0);
	return aux;
}

unsigned Heap :: GetPai(unsigned _pos)
{
	return (_pos - 1)/2;
}

unsigned Heap :: GetFilhoDir(unsigned _pos)
{
	return (2 * _pos) + 1;
}

unsigned Heap :: GetFilhoEsq(unsigned _pos)
{
	return 2 * _pos;
}

int main ()
{
	Heap heap(10);
    Dado valor;
    char opcao;
    cin >> opcao;
    while (opcao != 'f') {
        switch(opcao) {
            case 'i': // Inserir
                cin >> valor;
                heap.Insere(valor);
                heap.Imprimir();
                break;
            case 'r': // item na Posicao
                cout << heap.Remove() << endl;
				heap.Imprimir();
                break;
			case 'p': // item na Posicao
	            heap.Imprimir();
	            break;
			case 'o': // item na Posicao
	            heap.ImprimirTudo();
	            break;
            default:
                cout << "Erro: opcao invalida!\n";
        }
        cin >> opcao;
    }
    return 0;
}
