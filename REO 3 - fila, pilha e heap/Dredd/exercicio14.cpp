#include <iostream> // Pode usar varias coisas prontas
#include <vector>   // mas e' preciso completar a classe
#include <limits>   // classe Heap. E' permitido fazer
#include <string>   // alteracoes na classe Heap.
#include <stdexcept>

class Atividade
{
public:
    int nota;
    int tentativas;
};

class Aluno
{
public:
    Aluno();
    Aluno(unsigned matr, const std::string &n);
    ~Aluno();
    void InserirAtividade(const Atividade &a);
    std::string Nome() const { return nome; }
    unsigned Matricula() { return matricula; }
    float Media() const;
    int Tentativas() const;
    bool ordemAlfabetica(const Aluno &aluno);

protected:
    unsigned matricula;
    std::string nome;
    std::vector<Atividade> vetAtividades;
};

Aluno::Aluno()
    : matricula(0), nome(), vetAtividades()
{
}

Aluno::Aluno(unsigned matr, const std::string &n)
    : matricula(matr), nome(n), vetAtividades()
{
}

Aluno::~Aluno()
{
}

void Aluno::InserirAtividade(const Atividade &a)
{
    vetAtividades.push_back(a);
}

float Aluno::Media() const
{
    float soma = 0.0f;
    unsigned nroAtividades = unsigned(vetAtividades.size());
    for (unsigned i = 0; i < nroAtividades; ++i)
        soma += float(vetAtividades.at(i).nota);
    return soma / float(nroAtividades);
}

int Aluno::Tentativas() const
{
    int tentativas = 0;
    unsigned nroAtividades = unsigned(vetAtividades.size());
    for (unsigned i = 0; i < nroAtividades; ++i)
        tentativas += vetAtividades[i].tentativas;
    return tentativas;
}
bool Aluno::ordemAlfabetica(const Aluno &aluno)
{
    if (aluno.nome > nome)
    {
        return true;
    }
    return false;
}

//bool operator>(const Aluno &a1, const Aluno &a2)
//{
//}

typedef Aluno TDado;

class Heap
{
    // classe Heap (max-heap, o maior fica na raiz/inicio)
public:
    // Criar heap sem dados e com capacidade informada
    Heap(int cap);
    // Destruttor
    ~Heap();
    // Inserir um dado na heap
    void Troca(TDado *v1, TDado *v2);
    void Inserir(const TDado &d);
    // Consulta a raiz
    TDado Raiz();
    // Retira e retorna a raiz
    TDado Retirar();
    // Verifica se a heap está vazia
    bool Vazia();

protected:
    void ArrumarDescendo(int i);
    void ArrumarSubindo(int i);
    inline int Direito(int i);
    inline int Esquerdo(int i);
    inline int Pai(int i);
    int mCapacidade;
    int mTamanho;
    TDado *mVetDados;
};

using namespace std;

Heap::Heap(int cap)
{
    mTamanho = 0;
    mCapacidade = cap;
    mVetDados = new TDado[mCapacidade];
}

Heap::~Heap()
{
    delete[] mVetDados;
}

void Heap ::Troca(TDado *v1, TDado *v2)
{
    TDado temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}
void Heap::ArrumarDescendo(int i)
{
    unsigned esq = Esquerdo(i);
    unsigned dir = Direito(i);
    unsigned maior = i;

    if ((esq <= mTamanho - 1) and (mVetDados[esq].Media() > mVetDados[maior].Media()))
        maior = esq;
    if ((dir <= mTamanho - 1) and (mVetDados[dir].Media() > mVetDados[maior].Media()))
        maior = dir;
    if (maior != i)
    {
        Troca(&mVetDados[i], &mVetDados[maior]);
        ArrumarDescendo(maior);
    }
}

void Heap::ArrumarSubindo(int i)
{

    unsigned p = Pai(i);
    if ((mVetDados[i].Media() > mVetDados[p].Media()))
    {
        Troca(&mVetDados[i], &mVetDados[p]);
        ArrumarSubindo(p);
    }
    else
    {
        if (mVetDados[i].Media() == mVetDados[p].Media())
        {
            if (mVetDados[i].Tentativas() < mVetDados[p].Tentativas())
            {
                Troca(&mVetDados[i], &mVetDados[p]);
                ArrumarSubindo(p);
            }
            else
            {
                if (mVetDados[i].Tentativas() == mVetDados[p].Tentativas())
                {
                    if (mVetDados[i].ordemAlfabetica(mVetDados[p]) == true)
                    {
                        Troca(&mVetDados[i], &mVetDados[p]);
                        ArrumarSubindo(p);
                    }
                }
            }
        }
    }
}

int Heap::Pai(int i)
{
    return (i - 1) / 2;
}

int Heap::Esquerdo(int i)
{
    return 2 * i + 1;
}

int Heap::Direito(int i)
{
    return 2 * i + 2;
}

TDado Heap::Raiz()
{
    if (mTamanho == 0)
    {
        cerr << "Heap vazia nao tem raiz." << endl;
        return TDado();
    }
    TDado aux = mVetDados[0];
    Troca(&mVetDados[0], &mVetDados[mTamanho - 1]);
    mTamanho--;
    ArrumarDescendo(0);
    return aux;
}

TDado Heap::Retirar()
{
    if (mTamanho == 0)
    {
        cerr << "Impossivel retirar de heap vazia." << endl;
        return TDado();
    }
    if (mTamanho < 1)
    {
        return TDado();
    }
    TDado aux;
    aux = mVetDados[0];
    Troca(&mVetDados[0], &mVetDados[mTamanho - 1]);
    mTamanho--;
    ArrumarDescendo(0);
    return aux;
}

bool Heap::Vazia()
{
    return (mTamanho == 0);
}

void Heap::Inserir(const TDado &d)
{
    if (mTamanho == mCapacidade)
    {
        cerr << "Impossivel inserir em heap cheio.\n";
        return;
    }

    else
    {
        mVetDados[mTamanho] = d;
        ArrumarSubindo(mTamanho);
        mTamanho++;
    }
}

int main()
{
    unsigned qtdeAlunos;
    cin >> qtdeAlunos;
    unsigned qtdeAtividades;
    cin >> qtdeAtividades;
    Heap heap(qtdeAlunos);
    Atividade atividade;
    string nome;
    unsigned matricula;
    for (unsigned i = 0; i < qtdeAlunos; ++i)
    {
        cin >> matricula >> nome;
        Aluno aluno(matricula, nome);
        for (unsigned i = 0; i < qtdeAtividades; ++i)
        {
            cin >> atividade.nota >> atividade.tentativas;
            aluno.InserirAtividade(atividade);
        }
        heap.Inserir(aluno);
    }
    Aluno alunoDestaque(heap.Retirar());
    cout << '[' << alunoDestaque.Matricula() << "] " << alunoDestaque.Nome() << endl;
    return 0;
}