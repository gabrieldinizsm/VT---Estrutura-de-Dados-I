#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <winsock2.h>
#include <locale.h>
#include "cliente.h"
#include "funcionario.h"
#include "produto.h"

	void menuInicial(){

		int opc;

        system("cls");
		printf("\tDigite 1 para se cadastrar(Clientes apenas)\n\n");
		printf("\tDigite 2 para efetuar login\n\n");
		printf("\tDigite 3 para sair \n\n");
		scanf("%d",&opc);

		switch (opc){

			case 1:
				cadastraCliente();
				menuInicial();
				break;

			case 2:

                system("cls");
                printf("\tDigite 1 para ir para tela de Login de Clientes\n\n");
                printf("\tDigite 2 para ir para tela de Login de Funcionários\n\n");
                scanf("%d",&opc);

                    switch(opc){

                        case 1:
                            loginCliente();
                            break;

                        case 2:
                            loginFuncionario();
                            break;

                        default:
                            printf("\tOperação inválida \n\n");
                            getch();
                            menuInicial();
                            break;
                    }

				break;

			default:
				exit(0);
				break;
		}
	}

		 main(){

            setlocale(LC_ALL, "Portuguese");
            system("color f0");

            menuInicial();


			system("pause>null");
		}

