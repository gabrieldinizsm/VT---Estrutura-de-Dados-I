    struct produto_loja{
		char *nome;
		int codigo;
		char *preco;
		int quantidadeEstoque;
	}; struct produto_loja produto;

    void registraProduto(){
        system("cls");
	    fflush(stdin);
	    produto.nome = malloc(sizeof(produto.nome));
        printf("\tInsira o nome do Produto\n\n");
        gets(produto.nome);
        fflush(stdin);
        printf("\tInsira o codigo do Produto\n\n");
        scanf("%d",&produto.codigo);
        fflush(stdin);
        produto.preco = malloc(sizeof(produto.preco));
        printf("\tInsira o preco do Produto (Utilize . em vez de ,)\n\n");
        gets(produto.preco);
        printf("\tInsira a quantidade em Estoque do Produto\n\n");
        scanf("%d",&produto.quantidadeEstoque);
        snprintf(query, MAX_STRING, "INSERT INTO produtos (nome, codigo, preco, quantidade)VALUES('%s', %d, '%s', %d);",produto.nome, produto.codigo, produto.preco, produto.quantidadeEstoque);
        MYSQL *conn;
        conn=mysql_init(NULL);
        mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
        mysql_query(conn, query);
        printf("%s \n",query);
        logar = mysql_affected_rows(conn);
        if (logar >=1)
            printf("\tProduto Cadastrado com sucesso \n\n");
        else
            printf("\tN�o foi poss�vel cadastrar o produto  \n\n");
        mysql_close(conn);
        getch();
        menuFuncionario();
	}

	void listaProdutos(){

        system("cls");

        char query[]="SELECT * FROM produtos;";
        int i;

        mysql_init(&conexao);
        if (mysql_real_connect(&conexao,server,user,password,database,0,NULL,0)){
            if (mysql_query(&conexao,query)){
                printf("Erro: %s\n",mysql_error(&conexao));
            } else{
                resp = mysql_store_result(&conexao);
                if (resp){
                    printf("ID \tNome \tC�digo \tPre�o \tQuantidade \n");
                    if (mysql_num_fields(resp)>1)
                       // printf("\t");
                        printf("\n");

                    while ((linhas=mysql_fetch_row(resp)) != NULL){
                        for (i=0;i<mysql_num_fields(resp);i++)
                            printf("%s\t",linhas[i]);
                            printf("\n");
                    }
                }
                    mysql_free_result(resp);
                    mysql_close(&conexao);
              }
        } else{
            printf("Conexao Falhou\n");
            if (mysql_errno(&conexao))
                printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
       }
   }

    void removeProduto(){

        unsigned int id, codigo;
        int opc;
        MYSQL *conn;

        system("cls");
        fflush(stdin);

        printf("\t Digite 1 para remover um produto pela ID  \n\n");
        printf("\t Digite 2 para remover um produto pelo C�digo  \n\n");
        printf("\t Digite 3 para voltar ao menu Funcion�rio \n\n");
        scanf("%d",&opc);

        switch (opc){

            case 1:
                system("cls");
                fflush(stdin);
                printf("\t Digite a ID do produto a ser removido \n\n");
                scanf("%d",&id);
                snprintf(query, MAX_STRING, "Delete from produtos where id = %d;",id);
                conn=mysql_init(NULL);
                mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
                mysql_query(conn, query);
                logar = mysql_affected_rows(conn);
                if (logar >=1)
                    printf("\tOpera��o realizada com sucesso \n\n");
                else
                    printf("\tN�o foi poss�vel realizar essa opera��o  \n\n");
                mysql_close(conn);
                getch();
                menuFuncionario();
                break;

            case 2:
                system("cls");
                fflush(stdin);
                printf("\t Digite o C�digo do produto a ser removido \n\n");
                scanf("%d",&codigo);
                snprintf(query, MAX_STRING, "Delete from produtos where codigo = %d;",codigo);
                conn=mysql_init(NULL);
                mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
                mysql_query(conn, query);
                logar = mysql_affected_rows(conn);
                if (logar >=1)
                    printf("\tOpera��o realizada com sucesso \n\n");
                else
                    printf("\tN�o foi poss�vel realizar essa opera��o  \n\n");
                mysql_close(conn);
                getch();
                menuFuncionario();
                break;

            case 3:
                system("cls");
                menuFuncionario();
                break;

            default:
                system("cls");
                printf("\tOp��o Inv�lida \n\n");
                getch();
                removeProduto();
                break;
       }

    }

    void alteraProdutoId(){

        unsigned int idProduto, opc, codigo;
        char *preco;
        char *nome;

        system("cls");
        fflush(stdin);

        printf("\t Insira o ID do produto a ser alterado \n\n");
        scanf("%d",&idProduto);

        system("cls");
        printf("\t Digite 1 para alterar o Nome do Produto  \n\n");
        printf("\t Digite 2 para alterar o C�digo do Produto  \n\n");
        printf("\t Digite 3 para alterar o Pre�o do Produto \n\n");
        printf("\t Digite 4 para voltar ao menu Funcion�rio  \n\n");
        fflush(stdin);
        scanf("%d",&opc);

        switch (opc){

            case 1:
                system("cls");
                fflush(stdin);
                nome = malloc(sizeof(nome));
                printf("\t Insira o novo Nome do produto  \n\n");
                gets(nome);
                snprintf(query, MAX_STRING, "Update produtos set nome = '%s' where id = %d;",nome, idProduto);
                MYSQL *conn;
                conn=mysql_init(NULL);
                mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
                mysql_query(conn, query);
                logar = mysql_affected_rows(conn);
                if (logar >=1)
                    printf("\tOpera��o realizada com sucesso \n\n");
                else
                    printf("\tN�o foi poss�vel realizar essa opera��o  \n\n");
                mysql_close(conn);
                getch();
                menuFuncionario();
                break;

            case 2:
                system("cls");
                fflush(stdin);
                printf("\t Insira o novo do c�digo do produto  \n\n");
                scanf("%d",&codigo);
                snprintf(query, MAX_STRING, "Update produtos set codigo = %d where id = %d;",codigo, idProduto);
                conn=mysql_init(NULL);
                mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
                mysql_query(conn, query);
                logar = mysql_affected_rows(conn);
                if (logar >=1)
                    printf("\tOpera��o realizada com sucesso \n\n");
                else
                    printf("\tN�o foi poss�vel realizar essa opera��o  \n\n");
                mysql_close(conn);
                getch();
                menuFuncionario();
                break;

            case 3:
                system("cls");
                fflush(stdin);
                preco = malloc(sizeof(nome));
                printf("\t Insira o novo do Pre�o do produto (Utilize . em vez de ,) \n\n");
                gets(preco);
                printf("%s", preco);
                getch();
                snprintf(query, MAX_STRING, "Update produtos set preco = '%s' where id = %d;",preco, idProduto);
                conn=mysql_init(NULL);
                mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
                mysql_query(conn, query);
                logar = mysql_affected_rows(conn);
                if (logar >=1)
                    printf("\tOpera��o realizada com sucesso \n\n");
                else
                    printf("\tN�o foi poss�vel realizar essa opera��o  \n\n");
                mysql_close(conn);
                getch();
                menuFuncionario();
                break;

            default :
                menuFuncionario();
                break;

        }
    }

    void alteraProdutoCodigo(){

        unsigned int id, opc, codigo, codigoProduto;
        char *preco;
        char *nome;

        system("cls");
        fflush(stdin);

        printf("\t Insira o C�digo do produto a ser alterado \n\n");
        scanf("%d",&codigoProduto);

        system("cls");
        printf("\t Digite 1 para alterar o Nome do Produto  \n\n");
        printf("\t Digite 2 para alterar o C�digo do Produto  \n\n");
        printf("\t Digite 3 para alterar o Pre�o do Produto \n\n");
        printf("\t Digite 4 para voltar ao menu Funcion�rio  \n\n");
        fflush(stdin);
        scanf("%d",&opc);

        switch (opc){

            case 1:
                system("cls");
                fflush(stdin);
                nome = malloc(sizeof(nome));
                printf("\t Insira o novo Nome do produto  \n\n");
                gets(nome);
                snprintf(query, MAX_STRING, "Update produtos set nome = '%s' where codigo = %d;",nome, codigoProduto);
                MYSQL *conn;
                conn=mysql_init(NULL);
                mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
                mysql_query(conn, query);
                logar = mysql_affected_rows(conn);
                if (logar >=1)
                    printf("\tOpera��o realizada com sucesso \n\n");
                else
                    printf("\tN�o foi poss�vel realizar essa opera��o  \n\n");
                mysql_close(conn);
                getch();
                menuFuncionario();
                break;

            case 2:
                system("cls");
                fflush(stdin);
                printf("\t Insira o novo do c�digo do produto  \n\n");
                scanf("%d",&codigo);
                snprintf(query, MAX_STRING, "Update produtos set codigo = %d where codigo = %d;",codigo, codigoProduto);
                conn=mysql_init(NULL);
                mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
                mysql_query(conn, query);
                logar = mysql_affected_rows(conn);
                if (logar >=1)
                    printf("\tOpera��o realizada com sucesso \n\n");
                else
                    printf("\tN�o foi poss�vel realizar essa opera��o  \n\n");
                mysql_close(conn);
                getch();
                menuFuncionario();
                break;

            case 3:
                system("cls");
                fflush(stdin);
                preco = malloc(sizeof(nome));
                printf("\t Insira o novo do Pre�o do produto (Utilize . em vez de ,) \n\n");
                gets(preco);
                printf("%s", preco);
                getch();
                snprintf(query, MAX_STRING, "Update produtos set preco = '%s' where codigo = %d;",preco, codigoProduto);
                conn=mysql_init(NULL);
                mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
                mysql_query(conn, query);
                logar = mysql_affected_rows(conn);
                if (logar >=1)
                    printf("\tOpera��o realizada com sucesso \n\n");
                else
                    printf("\tN�o foi poss�vel realizar essa opera��o  \n\n");
                mysql_close(conn);
                getch();
                menuFuncionario();
                break;

            default :
                menuFuncionario();
                break;

        }
    }

    void buscaProduto(){

        int i;
        unsigned int id, opc, codigo;
        MYSQL *conn;

        system("cls");
        fflush(stdin);

        printf("\tDigite 1 para pesquisar o Produto pela ID \n\n");
        printf("\tDigite 2 para pesquisar o Produto pelo C�digo \n\n");
        printf("\tDigite 3 para retornar ao Menu de Clientes \n\n");
        scanf("%d",&opc);
        fflush(stdin);

        switch (opc){

            case 1:
            system("cls");
            printf("\tDigite a ID do Produto \n\n");
            scanf("%d",&id);
            system("cls");
            snprintf(query, MAX_STRING, "Select * from produtos where id = %d;",id);
            conn=mysql_init(NULL);
            mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
            mysql_query(conn, query);
            resp = mysql_store_result(conn);
            logar = mysql_num_rows(resp);
            if (logar !=0){
                campos = mysql_fetch_fields(resp);
                printf("Id\t Nome\t C�digo\t Pre�o\t Quantidade\t \n");
                printf("\n\n");

                while ((linhas=mysql_fetch_row(resp)) != NULL){
                    for (i=0;i<mysql_num_fields(resp);i++)
                        printf("%s\t",linhas[i]);
                        printf("\n");
                   }
            }else
                printf("\tN�o h� nenhum produto com ID %d\n\n",id);
            getch();
            mysql_close(conn);
            mysql_free_result(resp);

            break;

            case 2:
            system("cls");
            printf("\tDigite o C�digo do Produto \n\n");
            scanf("%d",&codigo);
            system("cls");
            snprintf(query, MAX_STRING, "Select * from produtos where codigo = %d;",codigo);
            conn=mysql_init(NULL);
            mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
            mysql_query(conn, query);
            resp = mysql_store_result(conn);
            logar = mysql_num_rows(resp);
            if (logar !=0){
                campos = mysql_fetch_fields(resp);
                printf("Id\t Nome\t C�digo\t Pre�o\t Quantidade\t \n");
                printf("\n\n");

                while ((linhas=mysql_fetch_row(resp)) != NULL){
                      for (i=0;i<mysql_num_fields(resp);i++)
                            printf("%s\t",linhas[i]);
                            printf("\n");
                   }
            }else
                printf("\tN�o h� nenhum produto com C�digo %d \n\n",codigo);
            getch();
            mysql_close(conn);
            mysql_free_result(resp);
            break;

            default:
                menuCliente();
                break;
        }
    }

    void ordenaProdutos(){

        unsigned int opc;
        int i;
        MYSQL *conn;

        fflush(stdin);
        system("cls");
        printf("\tDigite 1 para ordenar os Produtos pelo nome \n\n");
        printf("\tDigite 2 para ordenar os Produtos pelo c�digo \n\n");
        printf("\tDigite 3 para ordenar os Produtos pelo pre�o \n\n");
        printf("\tDIgite 4 para voltar ao menu Funcion�rio  \n\n");
        scanf("%d", &opc);
        fflush(stdin);

        switch (opc){

            case 1:
                system("cls");
                snprintf(query, MAX_STRING, "Select * from produtos order by nome;");
                conn=mysql_init(NULL);
                mysql_init(conn);
                if (mysql_real_connect(conn,server,user,password,database,0,NULL,0)){
                    if (mysql_query(conn,query))
                        printf("Erro: %s\n",mysql_error(conn));
                    else{
                        resp = mysql_store_result(conn);
                        if (resp){
                            printf("Id\t Nome\t C�digo\t Pre�o\t Quantidade\t \n");
                            printf("\n");

                            while ((linhas=mysql_fetch_row(resp)) != NULL){
                                for (i=0;i<mysql_num_fields(resp);i++)
                                    printf("%s\t",linhas[i]);
                                printf("\n");
                            }
                        }
                        mysql_free_result(resp);
                   }
                    mysql_close(conn);
               } else{
                    printf("Conexao Falhou\n");
                    if (mysql_errno(&conexao))
                        printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
                }

                break;

            case 2:
                system("cls");
                snprintf(query, MAX_STRING, "Select * from produtos order by codigo;");
                conn = mysql_init(NULL);
                mysql_init(conn);
                if (mysql_real_connect(conn,server,user,password,database,0,NULL,0)){
                    if (mysql_query(conn,query))
                        printf("Erro: %s\n",mysql_error(conn));
                    else{
                        resp = mysql_store_result(conn);
                        if (resp){
                            printf("Id\t Nome\t C�digo\t Pre�o\t Quantidade\t \n");

                            printf("\n");

                            while ((linhas=mysql_fetch_row(resp)) != NULL){
                                for (i=0;i<mysql_num_fields(resp);i++)
                                    printf("%s\t",linhas[i]);
                                    printf("\n");
                            }
                        }
                        mysql_free_result(resp);
                  }
                  mysql_close(conn);
               } else{
                    printf("Conexao Falhou\n");
                    if (mysql_errno(&conexao))
                        printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
                }

                break;

            case 3:
                system("cls");
                snprintf(query, MAX_STRING, "Select * from produtos order by preco;");
                conn=mysql_init(NULL);
                mysql_init(conn);
                if (mysql_real_connect(conn,server,user,password,database,0,NULL,0)){
                    if (mysql_query(conn,query))
                        printf("Erro: %s\n",mysql_error(conn));
                    else{
                        resp = mysql_store_result(conn);
                        if (resp){
                            printf("Id\t Nome\t C�digo\t Pre�o\t Quantidade\t \n");

                            printf("\n");

                            while ((linhas=mysql_fetch_row(resp)) != NULL){
                                for (i=0;i<mysql_num_fields(resp);i++)
                                    printf("%s\t",linhas[i]);
                                    printf("\n");
                            }
                        }
                        mysql_free_result(resp);
                  }
                  mysql_close(conn);
               } else{
                    printf("Conexao Falhou\n");
                    if (mysql_errno(&conexao))
                        printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
                }

                break;

            case 4:
                menuFuncionario();
                break;

            default:
                printf("\tOp��o Inv�lida \n\n");
                getch();
                menuFuncionario();
                break;
        }
        getch();
        menuFuncionario();
    }



