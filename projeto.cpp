#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Cliente {
private:
    string nome; // Nome do cliente
    string cpf;  // CPF do cliente

public:
    // Construtor
    Cliente(string nome, string cpf) : nome(nome), cpf(cpf) {}

    // Métodos getter
    string getNome() const {
        return nome;
    }

    string getCpf() const {
        return cpf;
    }
};

class ContaBancaria {
private:
    int numero;          // Número da conta
    double saldo;       // Saldo da conta
    Cliente titular;    // Titular da conta

public:
    // Construtor
    ContaBancaria(int numero, Cliente titular, double saldo = 0.0)
        : numero(numero), titular(titular), saldo(saldo) {}

    // depositar
    void depositar(double valor) {
        saldo += valor;
    }

    // sacar
    void sacar(double valor) {
        if (valor > saldo) {
            cout << "Saldo insuficiente para saque de R$ " << valor << endl;
        } else {
            saldo -= valor;
        }
    }

    // Sobrecarga do método transferir
    void transferir(double valor, ContaBancaria &destino) {
        if (valor > saldo) {
            cout << "Saldo insuficiente para transferência de R$ " << valor << endl;
        } else {
            saldo -= valor;
            destino.depositar(valor);
            cout << "Transferido: R$ " << valor << " da conta " << numero 
                 << " para a conta " << destino.numero << endl;
        }
    }

    // Sobrecarga do método transferir para duas contas
    void transferir(double valor, ContaBancaria &destino1, ContaBancaria &destino2) {
        if (valor > saldo) {
            cout << "Saldo insuficiente para transferência de R$ " << valor << endl;
        } else {
            double valorPorConta = valor / 2; // Divide o valor entre as duas contas
            saldo -= valor;
            destino1.depositar(valorPorConta);
            destino2.depositar(valorPorConta);
            cout << "Transferido: R$ " << valorPorConta << " para cada conta ("
                 << destino1.numero << " e " << destino2.numero << ") da conta " 
                 << numero << endl;
        }
    }

    // exibir saldo
    void exibirSaldo() const {
        cout << "Saldo atual da conta " << numero << ": R$ " << fixed << setprecision(2) << saldo << endl;
    }

    // informações da conta
    void exibirInformacoes() const {
        cout << "Titular: " << titular.getNome() << ", CPF: " << titular.getCpf() << endl;
        cout << "Numero da Conta: " << numero << ", Saldo: R$ " << fixed << setprecision(2) << saldo << endl;
    }
};

int main() {
    // clientes
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    // Criação das contas bancárias com saldos iniciais
    ContaBancaria conta1(1001, cliente1, 1000.0);
    ContaBancaria conta2(1002, cliente2);
    ContaBancaria conta3(1003, cliente3);

    // Exibe o saldo inicial da conta de Ana
    conta1.exibirSaldo();

    // Ana transfere R$200 para Bruno
    conta1.transferir(200.0, conta2);

    // Ana transfere R$300 divididos entre Bruno e Carla
    conta1.transferir(300.0, conta2, conta3);

    // saldos finais
    cout << endl;
    conta1.exibirInformacoes();
    conta2.exibirInformacoes();
    conta3.exibirInformacoes();

    return 0;
}
