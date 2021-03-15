#include <iostream>
#include "sequenceset.hpp"

using namespace std;

int main() {
    sequenceset meuSeqSet("teste.dat");
    dado umDado;
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
                    meuSeqSet.inserirDado(umDado);
                    break;
                case 'b': // buscar
                    contador = 0;
                    cin >> umaChave;
                    umDado = meuSeqSet.buscar(umaChave, contador);
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
                    meuSeqSet.imprimir();
                    break;
                case 'd': // mostrar estrutura
                    meuSeqSet.depurar();
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
