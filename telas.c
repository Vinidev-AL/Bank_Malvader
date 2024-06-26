#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "destinador.h"
#include <locale.h>


void tela_login_funcionario(){
	verificar_conta_funcionario();
}

void tela_login_cliente(){
	setlocale(LC_ALL, "portuguese");
	int opc;
	limpar_tela();
	style_bank();
	printf("DIGITE A OPCAO DESEJADA: \n\n");
	tabela_style();
	printf("1 - CONTA CORRENTE: \n");
	tabela_style();
	printf("2 - CONTA POUPANCA: \n\n");
	tabela_style();
	printf("3 - VOLTAR\n");
	tabela_style();
	printf("OPCAO: ");
	scanf("%d", &opc);
	
	switch(opc){
	case 1:
		verificar_conta_corrente();
		break;
	case 2:
		verificar_conta_poupanca();
		break;
	case 3:
		return;
		break;
	default:
		printf("OPCAO INVALIDA");
		system("pause");
		break;
	}
};

void menu_principal() {
	int opc;
	setlocale(LC_ALL, "portuguese");
	while(1){
		limpar_tela();
		malvader();
        printf("MENU PRINCIPAL\n\n\n");
        tabela_style();
        printf("Digite a opcao desejada\n\n");
        tabela_style();
        printf("[1] - FUNCIONARIO\n");
        tabela_style();
        printf("[2] - CLIENTE\n");
        tabela_style();
        printf("[3] - SAIR DO PROGRAMA\n");
        tabela_style();
        printf("OPCAO: ");
        scanf("%d", &opc);
        limpar_buffer();

		delay();
        switch(opc){
            case 1:
                tela_login_funcionario();
                break;
            case 2:
                tela_login_cliente();
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("OPCAO INVALIDA");
                break;
        }
	}
}

void menu_cliente_corrente(int contan){
	
	while(1)
	
	{
		limpar_tela();
		style_bank();
		setlocale(LC_ALL, "portuguese");
	
		FILE *file = fopen("contas_corrente.bin", "r+b");
	    if (file == NULL) {
	        printf("ERRO, ARQUIVO NAO EXISTE\n");
	        return;
	    }
	    Cliente conta;   
	    fseek(file, (contan - 1) * sizeof(Cliente), SEEK_SET);
	
	    if (fread(&conta, sizeof(Cliente), 1, file) != 1) {
	        if (feof(file)) {
	            printf("ERRO, CONTA NAO ENCONTRADA\n");
	        } else {
	            printf("ERRO AO LER A CONTA\n");
	        }
	        fclose(file);
	        return;
	    }
	
		int opc;
		printf("MENU CLIENTE\n\n");
		tabela_style();
		printf("[1] - SALDO\n");
		tabela_style();
		printf("[2] - DEPOSITO\n");
		tabela_style();
		printf("[3] - SAQUE\n");
		tabela_style();
		printf("[4] - EXTRATO\n");
		tabela_style();
		printf("[5] - CONSULTAR LIMITE\n");
		tabela_style();
		printf("[6] - SAIR\n\n");
		tabela_style();
		printf("OPCAO: ");
		scanf("%d", &opc);
		
		float deposito;
		float saque;
		
		char nome_arquivo[100];
		sprintf(nome_arquivo, "extrato_conta_corrente%d.csv", contan);
		
		FILE *arqui;
		arqui = fopen(nome_arquivo, "a");
		
		FILE *arqui_geral;
		arqui_geral = fopen("extratos.csv", "a");
	
		switch(opc){
		case 1:
			tabela_style();
			printf("O saldo da conta e: R$%.2f\n", conta.saldo);
			fclose(file);
			tabela_style();
			system("pause");
			break;
		case 2:
			tabela_style();
			printf("Digite quando deseja depositar: ");
			scanf("%f", &deposito);
			
 	 		
 	 		conta.saldo += deposito;
 	 		tabela_style();
 	 		fprintf(arqui, "Depositado R$%.2f na conta de %s %s\n", deposito, conta.nome.nome, conta.nome.sobrenome);
 	 		fprintf(arqui_geral, "Depositado R$%.2f na conta de %s %s\n", deposito, conta.nome.nome, conta.nome.sobrenome);
			fclose(arqui);
			fclose(arqui_geral);
 	 		
 	 		fseek(file, -sizeof(Cliente), SEEK_CUR);
 	 		
 	 		fwrite(&conta, sizeof(Cliente), 1, file);
			fclose(file);
			break;
			
		case 3:
			tabela_style();
			printf("Digite quanto deseja sacar: ");
			scanf("%f", &saque);
			
			if(saque > conta.saldo)
			
			{
				tabela_style();
				printf("Saldo insuficiente, seu saldo atual e: %.2f\n\n", conta.saldo);
				tabela_style();
				system("pause");
			} 
			
			else
			{
				tabela_style();
				fprintf(arqui, "Sacados R$%.2f da conta do cliente %s %s\n", saque, conta.nome.nome, conta.nome.sobrenome);
				fprintf(arqui_geral, "Sacados R$%.2f da conta do cliente %s %s\n", saque, conta.nome.nome, conta.nome.sobrenome);
				fclose(arqui);
				fclose(arqui_geral);
				conta.saldo -= saque;
				fseek(file, -sizeof(Cliente), SEEK_CUR);
 	 		
 	 			fwrite(&conta, sizeof(Cliente), 1, file);
				fclose(file);
				tabela_style();
				printf("Sacados R$%.2f da conta\n\n", saque);	
				tabela_style();
				system("pause");
			}
			
			break;
			
		case 4: {
			fclose(arqui);
			fclose(arqui_geral);
			 char excel[100] = "";
			 strcat(excel, nome_arquivo);
			system(excel);
			fclose(arqui);
			fclose(arqui_geral);
			tabela_style();
			system("pause");
			break;
		}
		case 5:
			
			tabela_style();
			printf("Seu limite atual e: R$%.2f\n\n", conta.limite);
			tabela_style();
			system("pause");
			fclose(file);
			break;
			
		case 6:
	 		 fclose(arqui);
			fclose(arqui_geral);
			tabela_style();
			printf("Saindo...");
			fclose(file);
			return;
			break;
		dafault:
			tabela_style();
			printf("OPCAO INVALIDA");
			tabela_style();
			system("pause");
		}
		
	}
}

void menu_cliente_poupanca(int contan){
	
	while(1)
	
	{
		limpar_tela();
		style_bank();
		setlocale(LC_ALL, "portuguese");
	
		FILE *file = fopen("contas_poupanca.bin", "r+b");
	    if (file == NULL) {
	        printf("ERRO, ARQUIVO N�O EXISTE\n");
	        return;
	    }
	    Cliente conta;   
	    fseek(file, (contan - 1) * sizeof(Cliente), SEEK_SET);
	
	    if (fread(&conta, sizeof(Cliente), 1, file) != 1) {
	        if (feof(file)) {
	            printf("ERRO, CONTA N�O ENCONTRADA\n");
	        } else {
	            printf("ERRO AO LER A CONTA\n");
	        }
	        fclose(file);
	        return;
	    }
	
		int opc;
		printf("MENU CLIENTE\n\n");
		tabela_style();
		printf("[1] - SALDO\n");
		tabela_style();
		printf("[2] - DEPOSITO\n");
		tabela_style();
		printf("[3] - SAQUE\n");
		tabela_style();
		printf("[4] - EXTRATO\n");
		tabela_style();
		printf("[5] - SAIR\n\n");
		tabela_style();
		printf("OPCAO: ");
		scanf("%d", &opc);
		
		float deposito;
		float saque;
		
		char nome_arquivo[100];
		sprintf(nome_arquivo, "extrato_conta_poupanca%d.csv", contan);
		
		FILE *arqui;
		arqui = fopen(nome_arquivo, "a");
		
		FILE *arqui_geral;
		arqui_geral = fopen("extratos.csv", "a");
		
	
		switch(opc){
		case 1:
			printf("O saldo da conta e: R$%.2f\n", conta.saldo);
			fclose(file);
			system("pause");
			break;
		case 2:
			printf("Digite quando deseja depositar: ");
			scanf("%f", &deposito);
			
 	 		
 	 		conta.saldo += deposito;
 	 		
			fprintf(arqui, "Depositado R$%.2f na conta de %s %s\n", deposito, conta.nome.nome, conta.nome.sobrenome);
			fprintf(arqui_geral, "Depositado R$%.2f na conta de %s %s\n", deposito, conta.nome.nome, conta.nome.sobrenome);
			fclose(arqui);
			fclose(arqui_geral);
 	 		
 	 		fseek(file, -sizeof(Cliente), SEEK_CUR);
 	 		
 	 		fwrite(&conta, sizeof(Cliente), 1, file);
			fclose(file);
			break;
			
		case 3:
			printf("Digite quanto deseja sacar: ");
			scanf("%f", &saque);
			
			if(saque > conta.saldo)
			
			{
				printf("Saldo insuficiente, seu saldo atual e: %.2f\n\n", conta.saldo);
				
				system("pause");
			} 
			
			else
			{
				
				fprintf(arqui, "Sacados R$%.2f da conta do cliente %s %s\n", saque, conta.nome.nome, conta.nome.sobrenome);
				fprintf(arqui_geral, "Sacados R$%.2f da conta do cliente %s %s\n", saque, conta.nome.nome, conta.nome.sobrenome);
				fclose(arqui);
				fclose(arqui_geral);
				conta.saldo -= saque;
				fseek(file, -sizeof(Cliente), SEEK_CUR);
 	 		
 	 			fwrite(&conta, sizeof(Cliente), 1, file);
				fclose(file);
				
				printf("Sacados R$%.2f da conta\n\n", saque);	
				
				system("pause");
			}
			
			break;
			
		case 4:
				fclose(arqui);
	 			char excel[100] = "";
	 			strcat(excel, nome_arquivo);
			system(excel);
			fclose(arqui);
			tabela_style();
			system("pause");
			break;

		case 5:
			 fclose(arqui);
			fclose(arqui_geral);
			printf("Saindo...");
			fclose(file);
			return;
			break;
		dafault:
				fclose(arqui);
			fclose(arqui_geral);
			printf("OPCAO INVALIDA");
			system("pause");
		}
		
	}
}


void menu_funcionario(){
	while(1){
 			 FILE *arqui_geral_dois;
		arqui_geral_dois = fopen("extratos.csv", "a");
		int opc;
		int op;
		int opc_encerrar;
		int pass;
		int adm = 123456;
		int opc_case3;
		int opc_case4;
		int opc_case3_switch;

		setlocale(LC_ALL, "portuguese");
		limpar_tela();
		style_bank();
		printf("[1] - Abertura de conta\n");
		tabela_style();
		printf("[2] - Encerramento de conta\n");
		tabela_style();
		printf("[3] - Consultar dados\n");
		tabela_style();
		printf("[4] - Alterar dados\n");
		tabela_style();
		printf("[5] - Cadastro de funcionarios\n");
		tabela_style();
		printf("[6] - Gerar relatorios\n");
		tabela_style();
		printf("[7] - Sair\n");
		tabela_style();
		printf("OPCAO: ");
		scanf("%d", &opc);

		switch(opc){
			case 1:
				limpar_tela("cls");
				style_bank();
				printf("[1] - CONTA CORRENTE\n");
				tabela_style();
				printf("[2] - CONTA POUPANCA\n");
				tabela_style();
				printf("[3] - VOLTAR\n");
				tabela_style();
				printf("OPCAO: ");
				scanf("%d", &op);
				
				switch(op){
					case 1:
						criar_conta_cliente_corrente();	
						break;
					case 2:
						criar_conta_cliente_poupanca();
						break;
					case 3:
						return;
						break;
					default:
						printf("OPCAO INVALIDA!");
						break;
				}

				break;
			case 2:
				tabela_style();
				printf("DIGITE A SENHA DE ADMINISTRADOR: ");
				scanf("%d", &pass);

				if(pass == adm){
					tabela_style();
					printf("DIGITE A OPCAO DESEJADA: \n");
					tabela_style();
					printf("1 - ENCERRAR CONTA DE FUNCIONARIO\n");
					tabela_style();
					printf("2 - ENCERRAR CONTA CORRENTE\n");
					tabela_style();
					printf("3 - ENCERRAR CONTA POUPANCA\n");
					tabela_style();
					printf("4 - VOLTAR\n\n");
					tabela_style();
					printf("OPCAO: ");
					scanf("%d", &opc_encerrar);

						switch(opc_encerrar){
					case 1:
						encerrar_conta_funcionario();
						break;
					case 2:
						encerrar_conta_corrente();
						break;
					case 3:
						encerrar_conta_poupanca();
						break;
					case 4:
						return;
						break;
					default:
						tabela_style();
						printf("OPCAO INVALIDA\n");
						tabela_style();
						system("pause");
					}
				} else {
					tabela_style();
					printf("Senha incorreta!\n\n");
					tabela_style();
					system("pause");
				}

				break;
			case 3:
				limpar_tela();
				style_bank();
				printf("DIGITE A OPCAO DESEJADA\n\n");
				tabela_style();
				printf("1 - CONSULTAR CONTA\n");
				tabela_style();
				printf("2 - CONSULTAR CLIENTE\n");
				tabela_style();
				printf("3 - CONSULTAR FUNCIONARIO\n");
				tabela_style();
				printf("4 - VOLTAR\n");
				tabela_style();
			
				printf("OPCAO: ");
				scanf("%d", &opc_case3);

				switch(opc_case3){
				case 1:
					quebrar_linha();
					tabela_style();
					printf("QUAL O TIPO DE CONTA?\n\n");
					tabela_style();
					printf("[1] - CORRENTE\n");
					tabela_style();
					printf("[2] - POUPANCA\n");
					tabela_style();
					printf("[3] - VOLTAR\n");
					tabela_style();
					printf("OPCAO: ");
					scanf("%d", &opc_case3_switch);

					switch(opc_case3_switch){
					case 1:
						consultar_conta_corrente();
						break;
					case 2:
						consultar_conta_poupanca();
						break;
					case 3:
						tabela_style();
						printf("Voltando...\n");
						tabela_style();
						system("pause");
						break;
					default:
						tabela_style();
						printf("Opcao invalida!\n");
						tabela_style();
						system("pause");
						break;
					}
					break;
				case 2:
					consultar_cliente();
					break;
				case 3:
					consultar_funcionario();
					break;
				case 4:
					tabela_style();
					printf("Voltando...\n");
					tabela_style();
					system("pause");
					break;
				default:
					tabela_style();
					printf("OPCAO INVALIDA\n");
					tabela_style();
					system("pause");
					break;
				}

				break;
			case 4:
				limpar_tela();
				style_bank();
				printf("DIGITE A OPCAO DESEJADA\n\n");
				tabela_style();
				printf("1 - CONTA CORRENTE\n");
				tabela_style();
				printf("2 - CONTA POUPANCA\n");
				tabela_style();
				printf("3 - ALTERAR FUNCIONARIO\n");
				tabela_style();
				printf("4 - VOLTAR\n");
				tabela_style();
			
				printf("OPCAO: ");
				scanf("%d", &opc_case4);
				
				switch(opc_case4){
					case 1:
						alterar_conta_corrente();
						break;
					case 2:
						alterar_conta_poupanca();
						break;
					case 3:
						alterar_dados_funcionario();
						break;
					case 4:
						tabela_style();
						printf("Voltando...");
						tabela_style();
						system("pause");
						break;
					default:
						tabela_style();
						printf("Opcao invalida!\n");
						tabela_style();
						system("pause");
						break;
				}
				
				break;
			case 5:
				criar_conta_funcionario();
				break;
			case 6:
				tabela_style();
				fclose(arqui_geral_dois);
				printf("Gerando relatorios...");
				sleep(1);
				system("extratos.csv");
				break;
			case 7:
				return;
				break;
			default:
				tabela_style();
				printf("OPCAO INVALIDA!\n");
				tabela_style();
				system("pause");
		}
	}	
}



