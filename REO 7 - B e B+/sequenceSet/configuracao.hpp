/* Sequence Set - Arquivo de Configuração
 * (tipo de elemento armazenado, tamanho do pacote, etc.)
 *
 * by Joukim, Fevereiro de 2021 - Estrutura de Dados (GCC216)
 * Caracteristicas desta implementação - fevereiro de 2021:
 * -> usa chave/valor como dado de exemplo, mas que pode 
 * -> ser trocado com facilidade, usando typedef
 * -> 
 * -> tamanho máximo e mínimo do pacote definido por 
 * -> constantes (CAP_PACOTE e MIN_PACOTE)
 */

using namespace std;

struct pokemon {
    unsigned id;
    char nome[15];
    char tipo[15];
    int pontuacao;
    int vida;
    int ataque;
    int defesa;
    int ataqueEspecial;
    int defesaEspecial;
    int velocidade;
};

typedef pokemon dado; // a arvore guarda informacoes do tipo Dado
typedef char tipoChave[15]; // tipo da chave usada na comparação

// capacidade máxima e mínima do pacote
const unsigned CAP_PACOTE = 7;
const unsigned MIN_PACOTE = 3;

// posição do elemento do meio do pacote
const unsigned POS_MEIO = 3;

// posição inválida no disco
const int POS_INVALIDA = -1;