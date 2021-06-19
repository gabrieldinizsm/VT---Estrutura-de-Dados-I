#define MAX_STRING 256
    char query[MAX_STRING] = {0};
    char *login;
    char *senha;
    int logar;

        MYSQL conexao;
        MYSQL_RES *resp;
        MYSQL_ROW linhas;
        MYSQL_FIELD *campos;

        char *server = "localhost";
        char *user = "root";
        char *password = "password";
        char *database = "vt_estrutura";


    struct cliente_loja {
		char *nome;
		char *login;
		char *senha;
		char *cpf;
    }; struct cliente_loja cliente;

    void menuCliente(){
    	
        system("cls");

		int opc;

		printf("\tDigite 1 para ver lista de Produtos completa\n\n");
		printf("\tDigite 2 para pesquisar determinado produto\n\n");
		printf("\tDigite 3 para alterar senha \n\n");
		printf("\tDigite 4 para voltar ao menu inicial \n\n");
		scanf("%d",&opc);

			switch (opc){

			case 1:
                listaProdutos();
                getch();
                menuCliente();
				break;

			case 2:
                buscaProduto();
                getch();
                menuCliente();
				break;

			case 3:
                alteraSenha();
                getch();
                menuCliente();
				break;

			case 4:
                menuInicial();
                break;

			default:
			    system("cls");
			    printf("\tOpção Inválida \n\n");
			    getch();
				menuCliente();
				break;
		}

	}

    void cadastraCliente(){
        fflush(stdin);
        system("cls");
	    cliente.nome = malloc(sizeof(20));
        printf("\tInsira o seu nome\n\n");
        gets(cliente.nome);
        fflush(stdin);
        cliente.login = malloc(sizeof(15));
        printf("\tInsira o seu Login\n\n");
        gets(cliente.login);
        fflush(stdin);
        cliente.senha = malloc(sizeof(10));
        printf("\tInsira a sua senha \n\n");
        gets(cliente.senha);
        fflush(stdin);
        cliente.cpf = malloc(sizeof(15));
        printf("\tInsira o seu Cpf(apenas números)\n\n");
        gets(cliente.cpf);
        snprintf(query, MAX_STRING, "INSERT INTO clientes (nome, login, senha, cpf)VALUES('%s','%s','%s', '%s')",cliente.nome, cliente.login, cliente.senha, cliente.cpf);
        MYSQL *conn;
        conn=mysql_init(NULL);
        mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
        mysql_query(conn, query);
        mysql_close(conn);
        getch();
        menuInicial();
	}

	void loginCliente(){

    system("cls");

    fflush(stdin);
    login = malloc(sizeof(15));
    printf("\tDigite o login \n");
    gets(login);

   MYSQL conexao;
   MYSQL_RES *resp;
   MYSQL_ROW *linhas;
   MYSQL_FIELD *campos;
   int i;
   char *senhaRecebida;

   snprintf(query, MAX_STRING, "select * from clientes where login = '%s';",login);
   mysql_init(&conexao);

   if (mysql_real_connect(&conexao,server, user,password ,database,0,NULL,0)){
           if (mysql_query(&conexao,query)){
                printf("Erro: %s\n",mysql_error(&conexao));
           }
           else {
                resp = mysql_store_result(&conexao);

           if (resp) {
              if ((linhas=mysql_fetch_row(resp)) != NULL){
                printf("\n");
                senhaRecebida = linhas[3];
                printf("\t\nDigite a senha\n\n");
                 senha = malloc(sizeof(senha));
                 gets(senha);
                 logar = strcmp(senha,senhaRecebida);
                 if (logar != 0){
                    system("cls");
                    printf("Senha Incorreta \n");
                    getch();
                    menuInicial();
                 }else {
                   system("cls");
                   printf("Bem vindo Senhor(a) %s \n",linhas[1]);
                   getch();
                   menuCliente();
                }
            }else {
            printf("\tLogin Inválido \n");
            getch();
            menuInicial();
            }
          mysql_free_result(resp);
        }
         mysql_close(&conexao);
    }

   }else {
      printf("Conexao Falhou\n");
      if (mysql_errno(&conexao))
         printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
    }

  }

    void alteraSenha(){

        char *novaSenha;
        system("cls");
        fflush(stdin);

        printf("\tInsira sua nova senha \n\n");
        novaSenha = malloc(sizeof(novaSenha));
        gets(novaSenha);
        printf("%s  \n\n",novaSenha);
        fflush(stdin);
        snprintf(query, MAX_STRING, "update clientes set senha = '%s' where login = '%s';",novaSenha,login);
        mysql_init(&conexao);
        MYSQL *conn;
        conn=mysql_init(NULL);
        mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
        mysql_query(conn, query);
        printf("%s \n\n",query);
        getch();
        mysql_close(conn);
    }
