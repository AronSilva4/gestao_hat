#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "forn.h"
#include "valid.h"

void ler_cnpj1(char*);
void ler_nome1(char*);
void ler_nome2(char*);
void ler_nome3(char*);
void ler_cel1(char*);

// função do módulo de fornecedores

void modulo_forn(void) {
    Fornecedor* forn_x;
    char op;
    do{
        op = tela_fornecedoras();
        switch (op) {
            case '1':   forn_x = tela_cad_forn();
                        esc_forn(forn_x);
                        free(forn_x);
                        break;
            case '2':   forn_x = tela_pes_forn();
                        free(forn_x);
                        break;
            case '3':   tela_edit_forn();
                        break;
            case '4':   tela_exc_forn();
                        break;
        }

    }while (op != '0');
}

char tela_fornecedoras(void) {
    char op;
    system("clear||cls");
    printf("\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("§                                                                             §\n");
    printf("§              < < < < < < < < Fornecedoras > > > > > > > >                   §\n");
    printf("§                                                                             §\n");
    printf("§              1. Cadastro de Fornecedoras                                    §\n");
    printf("§              2. Pesquisar Fornecedoras                                      §\n");
    printf("§              3. Editar Dados de Fornecedoras                                §\n");
    printf("§              4. Excluir uma Fornecedora do Sistema                          §\n");
    printf("§              0. Retornar ao Menu Principal                                  §\n");
    printf("§                                                                             §\n");
    printf("§                                                                             §\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("\n");
    printf("§              Digite o número da opção desejada: ");
    scanf("%c", &op);
    getchar();
    return op;
}

Fornecedor* tela_cad_forn(void) {
  Fornecedor* forn;

  system("clear||cls");
  printf("\n");
  printf("-----------------------------------------------------------------------------\n");
  printf("                                                                             \n");
  printf("              < < < < < < < Cadastro - Fornecedoras > > > > > > >            \n");
  printf("                                                                             \n");
  printf("              Digite as informações a seguir:                                \n");
  printf("                                                                             \n");

  forn = (Fornecedor*) malloc(sizeof(Fornecedor));
    
  ler_cnpj1(forn->cnpj);

  ler_nome1(forn->nome_est);

  ler_nome3(forn->cid);

  ler_nome2(forn->nome_prop);

  ler_cel1(forn->cel);

  forn->status = 'c';
  printf("                                                                             \n");
  printf("                                                                             \n");
  printf("-----------------------------------------------------------------------------\n");
  printf("\n");
  printf("\t\t\t>>> Processando as informações...\n");
  sleep(1);
  printf("\t\t\t>>> Cadastro concluído!\n");
  printf("\t\t\t>>> Tecle <ENTER> para continuar...\n");
  getchar();
  return forn;
}

Fornecedor* tela_pes_forn(void) {
  FILE* fp;
  Fornecedor* forn;
  char cnpj[15];
  system("clear||cls");
  printf("\n");
  printf("-----------------------------------------------------------------------------\n");
  printf("                                                                             \n");
  printf("              < < < < < < < Pesquisa - Fornecedoras > > > > > > >            \n");
  printf("                                                                             \n");
  printf("Informe o CNPJ que deseja pesquisar: ");
  fgets (cnpj, 15, stdin);
  getchar();
  printf("\n");
  forn = (Fornecedor*) malloc(sizeof(Fornecedor));
  fp = fopen("forn.dat", "rb");
  if (fp == NULL) {
    printf("\t\t\t>>> Processando as informações...\n");
    sleep(1);
    printf("\t\t\t>>> Houve um erro ao abrir o arquivo!\n");
    printf("\t\t\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
  } else {
      while(!feof(fp)) {
        fread(forn, sizeof(Fornecedor), 1, fp);
        if((strcmp(forn->cnpj, cnpj) == 0) && (forn->status != 'e')) {
          exb_forn(forn);
          printf("\n");
          printf("\t\t\t>>> Tecle <ENTER> para continuar...\n");
          getchar();
          fclose(fp);
          return forn;
        }
      }
    }
  fclose(fp);
  return NULL;
}

void tela_edit_forn(void) {
  char cnpj[15];
  Fornecedor* new_forn = (Fornecedor*) malloc(sizeof(Fornecedor));
  FILE* fp;
  int forn_found = 0;
  system("clear||cls");
  printf("\n");
  printf("-----------------------------------------------------------------------------\n");
  printf("                                                                             \n");
  printf("              < < < < < < < Edição - Fornecedoras > > > > > > >              \n");
  printf("                                                                             \n");
  printf("Informe o CNPJ para edição de dados: ");
  fgets (cnpj, 15, stdin);
  getchar();
  fp = fopen("forn.dat", "r+b");
  if (fp == NULL) {
    printf("\t\t\t>>> Processando as informações...\n");
    sleep(1);
    printf("\t\t\t>>> Houve um erro ao abrir o arquivo!\n");
    printf("\t\t\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
  } else {
    while (fread(new_forn, sizeof(Fornecedor), 1, fp) == 1) {
      if(strcmp(new_forn->cnpj, cnpj) == 0) {
        printf("\n");
        printf("\t\t\t= = = Fornecedora Encontrada = = =\n");
        printf("\n");

        ler_cnpj1(new_forn->cnpj);

        ler_nome1(new_forn->nome_est);

        ler_nome3(new_forn->cid);

        ler_nome2(new_forn->nome_prop);

        ler_cel1(new_forn->cel);

        new_forn->status = 'c';

        fseek(fp, -sizeof(Fornecedor), SEEK_CUR);
        fwrite(new_forn, sizeof(Fornecedor), 1, fp);
        forn_found = 1;
        break;
      }
    }
  }
  if (!forn_found) {
        printf("\n");
        printf("\t\t\tCNPJ não encontrado!\n");
    } else {
        printf("\n");
        printf("\t\t\tFornecedora atualizada com sucesso!\n");
    }
  printf("\n");
  printf("\t\t\t>>> Tecle <ENTER> para continuar...\n");
  getchar();
  fclose(fp);
}

void tela_exc_forn(void) {
  char cnpj[15];
  Fornecedor* new_forn = (Fornecedor*) malloc(sizeof(Fornecedor));
  FILE* fp;
  int forn_found = 0;
  system("clear||cls");
  printf("\n");
  printf("-----------------------------------------------------------------------------\n");
  printf("                                                                             \n");
  printf("              < < < < < < < Exclusão - Fornecedoras > > > > > > >            \n");
  printf("                                                                             \n");
  printf("Informe o CNPJ para excluir do sistema: ");
  fgets (cnpj, 15, stdin);
  getchar();
  fp = fopen("forn.dat", "r+b");
  if (fp == NULL) {
    printf("\t\t\t>>> Processando as informações...\n");
    sleep(1);
    printf("\t\t\t>>> Houve um erro ao abrir o arquivo!\n");
    printf("\t\t\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
  } else {
    while (fread(new_forn, sizeof(Fornecedor), 1, fp) == 1) {
      if(strcmp(new_forn->cnpj, cnpj) == 0) {
        printf("\n");
        printf("\t\t\t= = = Fornecedora Encontrada = = =\n");
        printf("\n");

        new_forn->status = 'e';

        fseek(fp, -sizeof(Fornecedor), SEEK_CUR);
        fwrite(new_forn, sizeof(Fornecedor), 1, fp);
        forn_found = 1;
        break;
      }
    }
  }
  if (!forn_found) {
        printf("\n");
        printf("\t\t\tCNPJ não encontrado!\n");
    } else {
        printf("\n");
        printf("\t\t\tFornecedora excluída com sucesso!\n");
    }
  printf("\n");
  printf("\t\t\t>>> Tecle <ENTER> para continuar...\n");
  getchar();
  fclose(fp);
}

void ler_cnpj1 (char* cnpj) {
  fflush(stdin);
  printf("Digite o CNPJ (Apenas Números): ");
  fgets (cnpj, 15, stdin);
  getchar();
  while ((!valid_cnpj(cnpj)) || (!verificaCNPJ1Duplicado(cnpj))) {
    printf("CNPJ inválido! Digite o CNPJ novamente: ");
    fflush(stdin);
    fgets (cnpj, 15, stdin);
    getchar();
  }
}

void ler_nome1(char* nome_est) {
  fflush(stdin);
  printf("Nome do estabelecimento: ");
  fgets(nome_est, 50, stdin); 
  // Remove o caractere de nova linha do final, se estiver presente
  int tam = strlen(nome_est);
  if (tam > 0 && nome_est[tam - 1] == '\n') {
    nome_est[tam - 1] = '\0';
    fflush(stdin);
  }
  while (!validarNome(nome_est)) {
    printf("Nome inválido: %s\n", nome_est);
    printf("Informe um novo nome de estabelecimento: ");
    fflush(stdin);
    fgets(nome_est, 50, stdin); 
    // Remove o caractere de nova linha do final, se estiver presente
    tam = strlen(nome_est);
    if (tam > 0 && nome_est[tam - 1] == '\n') {
      nome_est[tam - 1] = '\0';
      fflush(stdin);
    }
  } 
}

void ler_nome2(char* nome_prop) {
  fflush(stdin);
  printf("Nome do proprietário: ");
  fgets(nome_prop, 50, stdin); 
  // Remove o caractere de nova linha do final, se estiver presente
  int tam = strlen(nome_prop);
  if (tam > 0 && nome_prop[tam - 1] == '\n') {
    nome_prop[tam - 1] = '\0';
    fflush(stdin);
  }
  while (!validarNome(nome_prop)) {
    printf("Nome inválido: %s\n", nome_prop);
    printf("Informe um novo nome: ");
    fflush(stdin);
    fgets(nome_prop, 50, stdin); 
    // Remove o caractere de nova linha do final, se estiver presente
    tam = strlen(nome_prop);
    if (tam > 0 && nome_prop[tam - 1] == '\n') {
      nome_prop[tam - 1] = '\0';
      fflush(stdin);
    }
  } 
}

void ler_nome3(char* cid) {
  fflush(stdin);
  printf("Cidade do estabelecimento: ");
  fgets(cid, 50, stdin); 
  // Remove o caractere de nova linha do final, se estiver presente
  int tam = strlen(cid);
  if (tam > 0 && cid[tam - 1] == '\n') {
    cid[tam - 1] = '\0';
    fflush(stdin);
  }
  while (!validarNome(cid)) {
    printf("Cidade inválida: %s\n", cid);
    printf("Informe uma nova cidade do estabelecimento: ");
    fflush(stdin);
    fgets(cid, 50, stdin); 
    // Remove o caractere de nova linha do final, se estiver presente
    tam = strlen(cid);
    if (tam > 0 && cid[tam - 1] == '\n') {
      cid[tam - 1] = '\0';
      fflush(stdin);
    }
  } 
}

void ler_cel1 (char* cel) {
    fflush (stdin);
    printf("Digite o Telefone (Apenas Números): ");
    fgets (cel, 12, stdin);

    while (!validarFone (cel)) {
        printf("Telefone inválido! Digite novamente: ");
        fgets (cel, 12, stdin);
    
    }
    getchar();
}

void esc_forn(Fornecedor* forn) {
  FILE* fp;
  fp = fopen("forn.dat", "ab");
  if (fp == NULL) {
    printf("\t\t\t>>> Processando as informações...\n");
    sleep(1);
    printf("\t\t\t>>> Houve um erro ao abrir o arquivo!\n");
    printf("\t\t\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
  }
  else {
    fwrite(forn, sizeof(Fornecedor), 1, fp);
    fclose(fp);
  }
}

void exb_forn(Fornecedor* forn) {
  if ((forn == NULL) || (forn->status == 'e')) {
    printf("\n");
    printf("\t\t\tCNPJ não encontrado!\n");
    printf("\n");
    printf("\t\t\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
  }else{
    char sit[20];
    printf("\t\t\t= = = Fornecedora Cadastrada = = =\n");
    printf("\n");
    printf("CNPJ: %s\n", forn->cnpj);
    printf("Nome do estabelecimento: %s\n", forn->nome_est);
    printf("Cidade: %s\n", forn->cid);
    printf("Nome do proprietário: %s\n", forn->nome_prop);
    printf("Telefone: %s\n", forn->cel);
    if (forn->status == 'c') {
      strcpy(sit, "Cadastrado");
    } else {
      strcpy(sit, "Não Informado");
    }
    printf("Situação da Revendedora: %s\n", sit);
    printf("\n");
  }
}

int verificaCNPJ1Duplicado(const char* cnpj) {
    FILE* fp = fopen("forn.dat", "rb");

    Fornecedor forn;
    while (fread(&forn, sizeof(Fornecedor), 1, fp)) {
        if (strcmp(forn.cnpj, cnpj) == 0) {
            fclose(fp);
            return 0;
        }
    }

    fclose(fp); 
    return 1; 
}