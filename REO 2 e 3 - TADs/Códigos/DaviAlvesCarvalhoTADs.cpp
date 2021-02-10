/* 
* Nome: Davi Alves Carvalho
* TADs - Enunciado 2
* 
* Decisões de Projeto:
* Vale destacar que houve mudanças em relação ao planejamento inicial enviado, inclusive para satisfazer as exigências da correção.
* Justificativa: Durante a implementação do código tive algumas dificuldades utilizando apenas duas classes
* e portanto resolvi criar dois structs (especies e fornecedor) e uma classe administradora que
* corresponde a Morgana do exercício. Nessa classe administradora contém todos os métodos utilizados durante o programa.
* Além disso, foi incluido o atributo tipoCultivo na struct especies, referente aos tipos de cultivares. 
* Dessa forma acredito que o programa atendeu todos os requisitos do enunciado de forma correta e eficaz.
*
* Observações:
* Utilizei um menu básico para facilitar a visualização e implementação do código.
* A alocação de "especiesCadastradas" e "fornecedorCadastrado" foi feita com o valor 50 apenas para efeito de exemplificação.
*/

#include <iostream>
#include <string>

using namespace std;


struct especies
{
    string tipoCultivo;
    string nomeEspecie;
    string periodoPlantio;
    string tempoProducao;

};

struct fornecedor
{
    string nomeFornecedor;
    string produto;
    string telefone;

};

class administrador
{
	private:
		especies *especiesCadastradas;
		fornecedor *fornecedorCadastrado;
		int qtdEspecie;
		int qtdFornecedor;

	public:
		administrador();
		~administrador();
		void cadastrarEspecie();
		void registrarFornecedor();
		void buscaFornecedor(string produtoDesejado);


};

administrador::administrador()
{
    qtdEspecie = 0;
    qtdFornecedor = 0;
    especiesCadastradas = new especies[50];
    fornecedorCadastrado = new fornecedor[50];
}

administrador::~administrador()
{
	cout << "Invocando o destrutor..." <<endl;
    qtdEspecie = 0;
    qtdFornecedor = 0;
    delete[] especiesCadastradas;
    delete[] fornecedorCadastrado;
    cout << "Morri " <<endl;
}

void administrador::cadastrarEspecie()
{

    if (qtdEspecie < 49)
    {
        cout << "Tipo de cultivo (flor,hortalica ou fruta): ";
        getline(cin,especiesCadastradas[qtdEspecie].tipoCultivo);
        cout << "Nome da especie: ";
        getline(cin,especiesCadastradas[qtdEspecie].nomeEspecie);
        cout << "Periodo de plantio: ";
        getline(cin,especiesCadastradas[qtdEspecie].periodoPlantio);
        cout << "Tempo de producao: ";
        getline(cin,especiesCadastradas[qtdEspecie].tempoProducao);
        cout << "Especie cadastrada com sucesso" << endl << endl;
        qtdEspecie++;

    }

}


void administrador::registrarFornecedor()
{
    if (qtdFornecedor < 49)
    {
        cout << "Nome do fornecedor: ";
        getline(cin,fornecedorCadastrado[qtdFornecedor].nomeFornecedor);
        cout << "Produto: ";
        getline(cin,fornecedorCadastrado[qtdFornecedor].produto);
        cout << "Telefone: ";
        getline(cin,fornecedorCadastrado[qtdFornecedor].telefone);
        cout << "Fornecedor registrado com sucesso" << endl <<endl;
        qtdFornecedor++;
    }

}
void administrador::buscaFornecedor(string produtoDesejado)
{
    int cont = 0;
    cout << "Os fornecedores do produto escolhido sao:" << endl <<endl;
    for (int i=0; i<qtdFornecedor; i++)
    {
        if(fornecedorCadastrado[i].produto == produtoDesejado)
        {
            cout << "Nome do Fornecedor: " << fornecedorCadastrado[i].nomeFornecedor <<endl;
            cout << "Produto: " << fornecedorCadastrado[i].produto <<endl;
            cout << "Telefone: " << fornecedorCadastrado[i].telefone << endl << endl;

            cont++;
        }
    }
    if (cont == 0)
    {
        cout <<"Nao temos fornecedores para esse tipo de produto no momento " << endl;
    }
}

int main()
{

    int qtdEspecies, qtdFornecedor;
    administrador admin;

    cout << "Quantidade de especies que voce deseja cadastrar: ";
    cin >> qtdEspecies;
    cin.ignore();
    for (int i=0; i <qtdEspecies; i++)
    {
        admin.cadastrarEspecie();
    }

    cout << "Quantidade de fornecedores que voce deseja registrar: ";
    cin >> qtdFornecedor;
    cin.ignore();
    for (int i=0; i <qtdFornecedor; i++)
    {
        admin.registrarFornecedor();
    }


    bool menu = true;
    while (menu)
    {

        cout << endl << " Ola Morgana " << endl << endl;
        cout << "O que deseja fazer?" << endl;
        cout << "(1)Cadastrar nova especie de cultivo" << endl;
        cout << "(2)Registrar novo fornecedor" << endl;
        cout << "(3)Buscar por fornecedores de um determinado produto" << endl;
        cout << "(4)Sair" << endl;

        int opcao;
        cout << "Opcao: ";
        cin>>opcao;
        cin.ignore();
        string produto;
        switch (opcao)
        {
        case 1:
            admin.cadastrarEspecie();
            break;
        case 2:
            admin.registrarFornecedor();
            break;
        case 3:
            cout <<"Digite o nome do produto e veja quais sao os seus fornecedores: ";
            cin >> produto;
            admin.buscaFornecedor(produto);
            break;
        case 4:
            cout << "Programa encerrado" << endl;
            menu = false;
            break;
        default:
            cout << "Opcao invalida. Tente novamente" <<endl;
            break;
        }
    }
    
    return 0;
}
