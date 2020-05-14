#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//struct
 typedef struct{
   char nome[20];
   float preco;
   int quantidade;
}Produto;

typedef struct{
   char nome[20];
   float preco;
   int quantidade;
   char cliente[20];
   float total;
}ProdutoBaixa;

//var struct
Produto produto[20];
ProdutoBaixa produtoBaixa[20];

//var baixas
char nomeBusca[20];
int quantidadeBaixa = 0;
int contadorEstoque = 0, contadorBaixas = 0;
int posicaoRemover = 0;
bool removeVetor = false;
int resp = 1;
char nomeCliente[20];

//var pesquisa
char nomePesquisa[20];

void Cadastro()
{
    contadorEstoque++;
    system("cls");

    printf("Informe a descricao do Produto: ");
    fgets(produto[contadorEstoque].nome,20,stdin);
    fflush(stdin);

    printf("\nInforme o valor do Produto: ");
    scanf("%f", &produto[contadorEstoque].preco);
    fflush(stdin);

    printf("\nInforme a quantidade do Produto: ");
    scanf("%i", &produto[contadorEstoque].quantidade);
    fflush(stdin);

    system("pause");
}

void Relatorio(){

    system("cls");
    for(int i = 1; i <= contadorEstoque; i++){

        printf("********************** %d\n" , i);
        printf("Produto.. : %s\n", produto[i].nome);
        printf("Valor.....: %.2f R$\n", produto[i].preco);
        printf("Quantidade: %d\n", produto[i].quantidade);
        printf("**********************\n\n");
    }
    system("pause");

}

void Baixas(){
    system("cls");

    resp = 1;
    while(resp == 1){
        printf("\nPRODUTO A SER VENDIDO: ");
        fgets(nomeBusca,20,stdin);
        fflush(stdin);



        //corre o vetor de produtos para encontrar o nome do produto
        for(int i = 1; i <= contadorEstoque; i++){

            //teste do nome do produto
            if(strcmp(nomeBusca, produto[i].nome) == 0){

                //caso encontrado:
                printf("Quantidade: ");
                scanf("%d", &quantidadeBaixa);
                fflush(stdin);


                //se houver produtos suficientes no estoque, retira a quantidade desejada
                if(quantidadeBaixa < produto[i].quantidade){
                    produto[i].quantidade = produto[i].quantidade - quantidadeBaixa;
                    contadorBaixas++;

                }
                //caso venda todo o estoque
                else if(quantidadeBaixa == produto[i].quantidade){
                    //esse bool aciona o shift de posiçoes do vetor de produtos para "reorganizar o estoque", caso a quantidade acabe com o estoque
                    removeVetor = true;
                    printf("Atencao: %s --FIM DE ESTOQUE--\n ", nomeBusca);
                    posicaoRemover = i;
                    contadorBaixas++;
                }
                //se nao houver quantidade suficiente
                else{
                    printf("Quantidade em estoque insuficiente\n");
                    break;
                }
                //"nota fiscal"
                //nome do cliente que comprou
                //pega todas as informaçoes de compra do estoque, cria uma nota e joga no relatorio de transaçoes
                printf("Cliente: ");
                fgets(nomeCliente,20,stdin);
                fflush(stdin);

                strcpy(produtoBaixa[contadorBaixas].nome, produto[i].nome);
                produtoBaixa[contadorBaixas].preco = produto[i].preco;
                produtoBaixa[contadorBaixas].quantidade = quantidadeBaixa;
                produtoBaixa[contadorBaixas].total = quantidadeBaixa * produto[i].preco;
                strcpy(produtoBaixa[contadorBaixas].cliente, nomeCliente);


                break;
            }
            else{
                if(i == contadorEstoque){
                    printf("Produto nao encontrado no estoque\n");
                }
            }
        }

        //shift de posiçoes do vetor
        if(removeVetor == true){
                if(posicaoRemover == contadorEstoque){
                    --contadorEstoque;
                    removeVetor = false;
                }
                else{
                    for(posicaoRemover; posicaoRemover < contadorEstoque; posicaoRemover++){
                        produto[posicaoRemover] = produto[posicaoRemover + 1];
                    }
                    --contadorEstoque;
                    removeVetor = false;
                }
        }

        resp = 0;
        printf("Deseja continuar ? [1] SIM - [2] NAO\n");
        scanf("%d", &resp);
        fflush(stdin);

    }



    system("pause");
}

void Transacoes(){

    system("cls");
    for(int i = 1; i <= contadorBaixas; i++){

        printf("********************** %d\n" , i);
        printf("Produto.. : %s\n", produtoBaixa[i].nome);
        printf("Valor.....: %.2f R$\n", produtoBaixa[i].preco);
        printf("Quantidade: %d\n", produtoBaixa[i].quantidade);
        printf("TOTAL.....: %.2f R$\n", produtoBaixa[i].total);
        printf("Cliente...: %s\n", produtoBaixa[i].cliente);
        printf("**********************\n\n");
    }
    system("pause");

}

void Pesquisa(){
    system("cls");

    printf("\nNOME DO PRODUTO: ");
    fgets(nomePesquisa,20,stdin);
    fflush(stdin);

    for(int i = 1; i <= contadorEstoque; i++){

        if(strcmp(nomePesquisa, produto[i].nome) == 0){

            printf("\n**********************\n" , i);
            printf("Produto.. : %s\n", produto[i].nome);
            printf("Valor.....: %.2f R$\n", produto[i].preco);
            printf("Quantidade: %d\n", produto[i].quantidade);
            printf("**********************\n\n");

            break;
        }
        else{
            if(i == contadorEstoque){
                printf("Produto nao encontrado no estoque!\n");
            }
        }
    }
    system("pause");
}

int main(){

int op;
    while (op != 6)
    {
        system("cls");
        printf("- - - - MENU DE OPCOES - - - -\n\n");
        printf("[1] Cadastro de Produtos\n");
        printf("[2] Relatorio do Estoque\n");
        printf("[3] Baixa de produtos em Estoque\n");
        printf("[4] Relatorio de baixas\n");
        printf("[5] Pesquisa no Estoque\n");
        printf("[6] Sair\n");
        printf("\nInforme a opcao Desejada...: ");
        scanf("%d", &op);
        fflush(stdin);

        switch (op)
        {
        case 1:
            Cadastro();
            break;
        case 2:
            Relatorio();
            break;
        case 3:
            Baixas();
            break;
        case 4:
            Transacoes();
            break;
        case 5:
            Pesquisa();
            break;
        case 6:
            op = 6;
            system("pause");
            break;
        default:
            printf("Opcao invalida, tente novamente..\n");
        }
    }





return 0;
}

