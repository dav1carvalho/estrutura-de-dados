#include <iostream>

using namespace std;

int funcaoHash(string c){
    int h = (c.size() % 23);
	return h;
}

class noh
{
    friend class dicionario;
    private:
        std::string chave;
        string significado;  
        noh* proximo;  
    public:
        noh(string c, string s);
};

noh::noh(string c, string s){
    chave = c;
    significado = s;
    proximo = NULL;
};

class dicionario
{
    private:
        noh** palavras;
        int capacidade;
    public:
        dicionario(int tam = 100);
        ~dicionario();
        void insere(string c, string s);
        void consulta(string c);
};

dicionario::dicionario(int tam){
    capacidade = tam;
    palavras = new noh*[capacidade];
    for (int i = 0; i < tam; i++)
    {
        palavras[i] = NULL;
    }
};

dicionario::~dicionario(){
    for (int i = 0; i < capacidade; i++)
    {
        noh* atual = palavras[i];
        while(atual != NULL){
            noh* aux = atual;
            atual = atual -> proximo;
            delete aux;
        }
    }
    
    delete[] palavras;
}

void dicionario::insere(string c, string s){
    
    int h = funcaoHash(c);
    noh* novo = new noh(c,s);
    
    if(palavras[h] == NULL){
        novo -> proximo = NULL;
        palavras[h] = novo;
    }
    else{
        noh* atual = palavras[h];
        while(atual -> proximo != NULL){
            atual = atual -> proximo;
        }
        atual -> proximo = novo;
        novo -> proximo = NULL;
    }
}

void dicionario::consulta(string c){
    
    int h = funcaoHash(c);
    if(palavras[h] == NULL){
        cout << "[" << c << "]" << " " << "=>" << " " << "NULL" << std::endl;
    }
    else if(palavras[h] -> chave != c and palavras[h] -> proximo == NULL){
        cout << "[" << c << "]" << " " << "=>" << " " << "NULL" << std::endl;
    }
    else{
        noh* atual = palavras[h];
        bool achou = false;
        while(atual != NULL and achou == false){
            if(atual -> chave == c){
                cout << "[" << atual -> chave << "]" << " " << "=>" << " " << atual -> significado << endl;
                achou = true;
            }
            else{
                atual = atual -> proximo;
            }
        }
        if(achou == false){
            cout << "[" << atual -> chave << "]" << " " << "=>" << " " << "NULL" << endl;
        }
    }
}

int main()
{
    dicionario minhaTabela(23);
	int quantElem;
	string chave;
	string valor;
	cin >> quantElem;
	
	for (int i = 0; i < quantElem; i++)
	{
		cin >> chave;
        cin.ignore();
		getline(cin, valor);
		
		minhaTabela.insere(chave, valor);
	}
	
	string chaveAux = "NULL";
	
	while(chaveAux != "-1")
	{
		cin >> chaveAux;
        if (chaveAux != "-1")
        {
            minhaTabela.consulta(chaveAux);
        }
	}
	cout << endl;
	
	return 0;
}

