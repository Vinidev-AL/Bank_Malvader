#ifndef OPERACOES_H
#define OPERACOES_H

// fun��es

void menu_principal();
void criar_conta_funcionario();
void criar_conta_cliente_corrente();
void criar_conta_cliente_poupanca();
void limpar_tela();
void limpar_buffer();
void verificar_conta_corrente();
void verificar_conta_poupanca();
void remover_nova_linha(char *str);
void tabela_style();
void menu_funcionario();
void menu_cliente_corrente(int contan);
void menu_cliente_poupanca(int contan);
void style_icon();
void delay();
void carregar();
void malvader();
void encerrar_conta_funcionario();
void encerrar_conta_corrente();
void encerrar_conta_poupanca();
void consultar_funcionario();
void consultar_conta_corrente();
void consultar_conta_poupanca();
void alterar_conta_corrente();
void alterar_conta_poupanca();
void salvar_contador_conta_poupanca_alt();
void carregar_contador_conta_poupanca_alt();
void quebrar_linha();
void consultar_cliente();
void removeEspacos(char *str);



// structs

typedef struct {
	int dia;
	int mes;
	int ano;
} Data;

typedef struct {
	char cep[10];
	char logradouro[100];
	int n_casa;
	char bairro[100];
	char cidade[100];
	char estado[100];

} Endereco;

typedef struct{
	char DDD[4];
	char numero[10];

} Telefone;

typedef struct{
	char nome[32];
	char sobrenome[100];
} Nome;

typedef struct{
	char agencia[5];
	int n_conta;
	float saldo;
	float limite;
	Data vencimento;
	Nome nome;
	char cpf[12];
	Data nascimento;
	Telefone telefone;
	Endereco endereco;
	char senha[32];
} Cliente;


typedef struct{
	int codigo;
	char cargo[100];
	Nome nome;
	char cpf[12];
	Data nascimento;
	Telefone telefone;
	Endereco endereco;
	char senha[32];
} Funcionario;

#endif

