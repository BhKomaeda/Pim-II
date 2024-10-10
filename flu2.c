#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char movimentacao[50];
    float valor;
    char tipo[12];
    char data[11];
    char pagamento[20];
} Fluxo;

void AddF(Fluxo **transacoes, int *NumF, char *movimentacao, float valor, char *tipo, char *data, char *pagamento) {
    (*NumF)++;
    *transacoes = (Fluxo *)realloc(*transacoes, (*NumF) * sizeof(Fluxo));
    Fluxo NovoF;
    strcpy(NovoF.movimentacao, movimentacao);
    NovoF.valor = valor;
    strcpy(NovoF.tipo, tipo);
    strcpy(NovoF.data, data);
    strcpy(NovoF.pagamento, pagamento);
    (*transacoes)[*NumF - 1] = NovoF;
}

void ImprimirT(Fluxo *transacoes, int NumF) {
    int i;
    printf("---------------------------------------------------------------------\n");
    printf("                TODAS AS TRANSAÇÕES                \n");
    printf("---------------------------------------------------------------------\n");
    printf("%-5s %-20s %-10s %-15s %-10s %-15s\n", "ID", "Movimentação", "Valor", "Tipo", "Data", "Pagamento");
    printf("---------------------------------------------------------------------\n");
    for (i = 0; i < NumF; i++) {
        printf("%-5d %-20s %-10.2f %-10s %-05s %-15s\n", i, transacoes[i].movimentacao, transacoes[i].valor, transacoes[i].tipo, transacoes[i].data, transacoes[i].pagamento);
    }
    printf("---------------------------------------------------------------------\n");
}

void EditF(Fluxo *transacoes, int NumF, int IndiceT) {
    if (IndiceT >= 0 && IndiceT < NumF) {
    printf("Editar transação:\n");
    printf("Nova movimentação: ");
    scanf("%s", transacoes[IndiceT].movimentacao);
    printf("Novo valor: ");
    scanf("%f", &transacoes[IndiceT].valor);
    printf("Novo tipo (Recebimento ou Gasto): ");
    scanf("%s", transacoes[IndiceT].tipo);
    printf("Nova data (DD/MM/YYYY): ");
    scanf("%s", transacoes[IndiceT].data);
    printf("Nova forma de pagamento: ");
    scanf("%s", transacoes[IndiceT].pagamento);
} 	else {
    printf("Índice inválido.\n");
}
}

void DeletF(Fluxo **transacoes, int *NumF, int IndiceT) {
    if (IndiceT >= 0 && IndiceT < *NumF) {
        char confirmacao;
    printf("Tem certeza que deseja deletar a transação de %s no valor de %.2f? (S/N): ", (*transacoes)[IndiceT].movimentacao, (*transacoes)[IndiceT].valor);
    scanf(" %c", &confirmacao);
        if (confirmacao == 'S' || confirmacao == 's') {
            int i;
    	for (i = IndiceT; i < *NumF - 1; i++) {
            (*transacoes)[i] = (*transacoes)[i + 1];
}
    		(*NumF)--;
			*transacoes = (Fluxo *)realloc(*transacoes, (*NumF) * sizeof(Fluxo));
	printf("Transação deletada com sucesso.\n");
} 	else {
    printf("Operação de exclusão cancelada.\n");
}
} 	else {
    printf("Índice inválido.\n");
}
}
void IFC(Fluxo *transacoes, int NumF) {
    float saldo = 0.0, totalRecebido = 0.0, totalGasto = 0.0;
    char dataDesejada[11];

    printf("Digite a data desejada (DD/MM/YYYY): ");
    scanf("%s", dataDesejada);

    printf("---------------------------------------------------\n");
    printf("      FLUXO DE CAIXA PARA O DIA %s                 \n", dataDesejada);
    printf("---------------------------------------------------\n");
    printf("%-20s %-10s %-10s %-10s %-15s\n", "Movimentação", "Valor", "Tipo", "Data", "Pagamento");
    printf("---------------------------------------------------\n");

    int i;
    for (i = 0; i < NumF; i++) {
        if (strcmp(transacoes[i].data, dataDesejada) == 0) {
    printf("%-20s %-10.2f %-15s %-10s %-15s\n", transacoes[i].movimentacao, transacoes[i].valor, transacoes[i].tipo, transacoes[i].data, transacoes[i].pagamento);
            if (strcmp(transacoes[i].tipo, "Recebimento") == 0) {
                saldo += transacoes[i].valor;
                totalRecebido += transacoes[i].valor;
} 	else {
                saldo -= transacoes[i].valor;
                totalGasto += transacoes[i].valor;
}
}
}
    printf("---------------------------------------------------\n");
    printf("%-20s %-10.2f\n", "Total Recebido:", totalRecebido);
    printf("%-20s %-10.2f\n", "Total Gasto:", totalGasto);
    printf("---------------------------------------------------\n");
    printf("%-20s %-10.2f\n", "Saldo Final:", saldo);
    printf("---------------------------------------------------\n");
}

void GerarR_M(Fluxo *transacoes, int NumF, char *MesAno) {
    float saldo = 0.0, totalRecebido = 0.0, totalGasto = 0.0;

    printf("---------------------------------------------------\n");
    printf("             RELATÓRIO MENSAL DE %s                \n", MesAno);
    printf("---------------------------------------------------\n");
    printf("%-20s %-10s %-15s %-10s %-15s\n", "Movimentação", "Valor", "Tipo", "Data", "Pagamento");
    printf("---------------------------------------------------\n");

    int i;
    for (i = 0; i < NumF; i++) {
        char MesAnoT[8];
        strncpy(MesAnoT, &transacoes[i].data[3], 7);
        MesAnoT[7] = '\0';

        if (strcmp(MesAnoT, MesAno) == 0) {
    printf("%-20s %-10.2f %-15s %-10s %-15s\n", transacoes[i].movimentacao, transacoes[i].valor, transacoes[i].tipo, transacoes[i].data, transacoes[i].pagamento);
            if (strcmp(transacoes[i].tipo, "Recebimento") == 0) {
                saldo += transacoes[i].valor;
                totalRecebido += transacoes[i].valor;
}	 else {
                saldo -= transacoes[i].valor;
                totalGasto += transacoes[i].valor;
}
}
}

    printf("---------------------------------------------------\n");
    printf("%-20s %-10.2f\n", "Total Recebido:", totalRecebido);
    printf("%-20s %-10.2f\n", "Total Gasto:", totalGasto);
    printf("---------------------------------------------------\n");
    printf("%-20s %-10.2f\n", "Saldo do Mês:", saldo);
    printf("---------------------------------------------------\n");
}

void MenuF() {
    printf("\nMenu:\n");
    printf("***************************\n");
    printf("1. Adicionar Transação\n");
    printf("2. Ver Todas as Transações\n");
    printf("3. Editar Transação\n");
    printf("4. Deletar Transação\n");
    printf("5. Imprimir Fluxo de Caixa\n");
    printf("6. Gerar Relatório Mensal\n");
    printf("7. Sair\n");
    printf("***************************\n");
}

void FormaP(char *pagamento) {
    int formaP;
    printf("Forma de pagamento:\n");
    printf("1. Dinheiro\n");
    printf("2. Cartão de Crédito\n");
    printf("3. Cartão de Débito\n");
    printf("4. Pix\n");
    printf("Selecione uma opção: ");
    scanf("%d", &formaP);
    getchar();
    switch (formaP) {
        case 1:
            strcpy(pagamento, "Dinheiro");
            break;
        case 2:
            strcpy(pagamento, "Cartão de Crédito");
            break;
        case 3:
            strcpy(pagamento, "Cartão de Débito");
            break;
        case 4:
            strcpy(pagamento, "Pix");
            break;
        default:
            printf("Opção inválida!\n");
            strcpy(pagamento, "Inválido");
            break;
}
}

int main() {
    setlocale(LC_ALL,"");
    Fluxo *transacoes = NULL;
    int NumF = 0;
    int acao, IndiceT;
    do {

        MenuF();
        printf("Selecione uma Ação: ");
        scanf("%d", &acao);
        
        switch (acao) {
            case 1: {
                char movimentacao[50], data[11], tipo[12], pagamento[20];
                float valor;
                getchar();
                printf("Movimentação: ");
                fgets(movimentacao, sizeof(movimentacao), stdin);
                movimentacao[strcspn(movimentacao, "\n")] = '\0';
                printf("Valor: ");
                scanf("%f", &valor);
                getchar();
                FormaP(pagamento);
                printf("Tipo (Recebimento ou Gasto): ");
                scanf("%s", tipo);
                getchar();
                printf("Data (DD/MM/YYYY): ");
                scanf("%s", data);
                AddF(&transacoes, &NumF, movimentacao, valor, tipo, data, pagamento);
                break;
            }
            case 2:
                ImprimirT(transacoes, NumF);
                break;
            case 3:
                printf("ID da transação para editar: ");
                scanf("%d", &IndiceT);
                EditF(transacoes, NumF, IndiceT);
                break;
            case 4:
                printf("ID da transação para deletar: ");
                scanf("%d", &IndiceT);
                DeletF(&transacoes, &NumF, IndiceT);
                break;
            case 5:
                IFC(transacoes, NumF);
                break;
            case 6: {
                char MesAno[8];
                printf("Mês/Ano para relatório (MM/YYYY): ");
                scanf("%s", MesAno);
                GerarR_M(transacoes, NumF, MesAno);
                break;
}
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
}
} while (acao != 7);

    free(transacoes);
    return 0;
}

