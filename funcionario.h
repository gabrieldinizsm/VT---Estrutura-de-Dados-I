struct  funcionario_loja{
		char *nome;
		char *login;
		char *senha;
		char *cpf;
    }; struct funcionario_loja funcionario;

	void cadastraFuncionario(){
	    system("cls");
	    fflush(stdin);
	    funcionario.nome = malloc(sizeof(20));
        printf("\tInsira o nome do Funcionário\n\n");
        gets(funcionario.nome);
        fflush(stdin);
        funcionario.login = malloc(sizeof(15));
        printf("\tInsira o Login do Funcionário\n\n");
        gets(funcionario.login);
        fflush(stdin);
        funcionario.senha = malloc(sizeof(10));
        printf("\tInsira a senha do Funcionário\n\n");
        gets(funcionario.senha);
        fflush(stdin);
        funcionario.cpf = malloc(sizeof(15));
        printf("\tInsira o Cpf do Funcionário (apenas números)\n\n");
        gets(funcionario.cpf);
        snprintf(query, MAX_STRING, "insert into funcionarios (nome, login, senha, cpf)VALUES('%s','%s','%s','%s');",funcionario.nome, funcionario.login, funcionario.senha, funcionario.cpf);
        MYSQL *conn;
        conn=mysql_init(NULL);
        mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
        mysql_query(conn,query);
        mysql_close(conn);
        getch();
        menuFuncionario();
	}

	void menuFuncionario(){

		int opc;

        system("cls");
        fflush(stdin);
		printf("\tDigite 1 para registrar um novo Funcionario\n\n");
		printf("\tDigite 2 para adicionar/remover/alterar um Produto\n\n");
		printf("\tDigite 3 para ordenar os Produtos\n\n");
		printf("\tDigite 4 para voltar ao menu inicial \n\n");
		scanf("%d",&opc);
		fflush(stdin);

			switch (opc){

			case 1:
			    system("cls");
				cadastraFuncionario();
				menuFuncionario();
				break;

			case 2:

                system("cls");
                printf("\tDigite 1 para ver a lista completa dos Produtos\n\n");
                printf("\tDigite 2 para adicionar um novo Produto\n\n");
                printf("\tDigite 3 para remover determinado Produto\n\n");
                printf("\tDigite 4 para alterar determinado Produto\n\n");
                printf("\tDigite 5 para voltar ao menu do Funcionario\n\n");
                scanf("%d",&opc);

                switch(opc){
                    case 1:
                        listaProdutos();
                        getch();
                        menuFuncionario();
                        break;

                    case 2:
                        registraProduto();
                        break;

                    case 3:
                        removeProduto();
                        break;

                    case 4:
                         system("cls");
                         printf("\tDigite 1 para alterar um Produto pela ID\n\n");
                         printf("\tDigite 2 para alterar um Produto pelo Código\n\n");
                         printf("\tDigite 3 para voltar ao menu do Funcionario\n\n");
                         scanf("%d",&opc);
                         fflush(stdin);

                         switch(opc){

                            case 1:
                                alteraProdutoId();
                                break;

                            case 2:
                                alteraProdutoCodigo();
                                break;

                            case 3:
                                menuFuncionario();
                                break;

                            default:
                                system("cls");
                                printf("\tOpção Inválida \n\n");
                                getch();
                                menuFuncionario();
                                break;
                         }

                         break;

                    case 5:
                        menuFuncionario();
                        break;


                    default:
                        system("cls");
                        printf("\tOpção inválida \n\n");
                        getch();
                        menuFuncionario();
                        break;
                }

				break;

			case 3:
                ordenaProdutos();
				break;

			case 4:
				menuInicial();
				break;

			default:
				printf("\tOpção Inválida");
				menuFuncionario();
				break;
		}
	}

	void loginFuncionario(){

        system("cls");

        fflush(stdin);
        login = malloc(sizeof(login));
        printf("\tDigite o login \n\n");
        gets(login);
        fflush(stdin);

        MYSQL conexao;
        MYSQL_RES *resp;
        MYSQL_ROW *linhas;
        MYSQL_FIELD *campos;
        int i;
        char *senhaRecebida;

        snprintf(query, MAX_STRING, "select * from funcionarios where login = '%s';",login);
        mysql_init(&conexao);

        if (mysql_real_connect(&conexao,server, user,password ,database,0,NULL,0)){
            if (mysql_query(&conexao,query)){
                printf("Erro: %s\n",mysql_error(&conexao));
            }
            else {
                resp = mysql_store_result(&conexao);

                if (resp) {
                    if ((linhas = mysql_fetch_row(resp)) != NULL){
                        printf("\n");
                        senhaRecebida = linhas[3];
                        senha = malloc(sizeof(senha));
                        printf("\t\nDigite a senha\n\n");
                        gets(senha);
                        logar = strcmp(senha,senhaRecebida);
                        if (logar != 0){
                            system("cls");
                            printf("Senha Incorreta \n");
                            getch();
                            menuInicial();
                        }else {
                            system("cls");
                            printf("Bem vindo \n");
                            getch();
                            menuFuncionario();
                        }
                    }else {
                        printf("\tLogin Inválido \n");
                        getch();
                        menuInicial();
                    }
                    mysql_free_result(resp);
                    mysql_close(&conexao);
                }
            }
        }else {
            printf("Conexao Falhou\n");
            if (mysql_errno(&conexao))
                printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
        }
    }
