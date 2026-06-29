#include "./header.h"

sensor *cadastrar_sensor(sensor *lista)
{
    sensor *sensorNovo = NULL;
    sensorNovo = (sensor*)malloc(sizeof(sensor));

    printf("Identificacao: ");
    scanf("%i", &sensorNovo->identificacao);
    getchar();

   for(sensor *i = lista; i != NULL; i = i->prox) {

    if(i->identificacao == sensorNovo->identificacao)
    {
        printf("ID de sensor ja cadastrado!\n");
        free(sensorNovo);
        return lista;
    }
}

    printf("Tipo: ");
    fgets(sensorNovo->tipo, T_STR, stdin);
    sensorNovo->tipo[strcspn(sensorNovo->tipo, "\n")] = '\0';

    printf("Minimo: ");
    scanf("%f", &sensorNovo->faixa_leitura[0]);

    printf("Maximo: ");
    scanf("%f", &sensorNovo->faixa_leitura[1]);

    sensorNovo->prox = NULL;

    if(lista == NULL) {
       return sensorNovo;
    }
    else{
        sensorNovo->prox = lista;
        return sensorNovo;
    }
}

setor *cadastrar_setor(setor *lista_setor,sensor *lista_sensor)
{
    setor *setorNovo = NULL;
    setorNovo = (setor*)malloc(sizeof(setor));

    int identificacaoSensor, posicao = 0;

    setorNovo->instaladosSensor = 0;

    printf("Identificacao: ");
    scanf("%i", &setorNovo->identificacao);
    getchar();

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        if(setorNovo->identificacao==i->identificacao){
            do{
                printf("Identificacao ja existe, bote outra: ");
                scanf("%i", &setorNovo->identificacao);
                getchar();
            } while(setorNovo->identificacao == i->identificacao);
        }
    }

    printf("Descricao: ");
    fgets(setorNovo->descricao, T_STR, stdin);
    setorNovo->descricao[strcspn(setorNovo->descricao, "\n")] = '\0';

    do{

        if(posicao >= MAX_SENSORES_SETOR)
        {
            printf("Maximo de 3 sensores por setor!\n");
            break;
        }

        printf("Identificacao sensor %i: ", posicao + 1);
        scanf("%i", &identificacaoSensor);
        getchar();

        if(identificacaoSensor != 0)
        {
            int achou = 0;

            for(sensor *i = lista_sensor; i != NULL; i = i->prox){
                if(identificacaoSensor == i->identificacao){
                    setorNovo->instalados[posicao] = *i;
                    setorNovo->instaladosSensor++;
                    achou = 1;
                    break;
                }
            }

            if(achou == 0)
            {
                printf("Sensor nao encontrado!\n");
            }
            else
            {
                posicao++;
            }
        }

    }while(identificacaoSensor != 0);

    for(int i = 0; i < setorNovo->instaladosSensor; i++)
    {
        printf("Horario primeira leitura: ");
        fgets(setorNovo->horario_primeiro[i], T_STR, stdin);
        setorNovo->horario_primeiro[i][strcspn(setorNovo->horario_primeiro[i], "\n")] = '\0';

        printf("Valor primeira leitura: ");
        scanf("%f", &setorNovo->leitura_primeira[i]);
        getchar();

        printf("Horario segunda leitura: ");
        fgets(setorNovo->horario_segundo[i], T_STR, stdin);
        setorNovo->horario_segundo[i][strcspn(setorNovo->horario_segundo[i], "\n")] = '\0';

        printf("Valor segunda leitura: ");
        scanf("%f", &setorNovo->leitura_segunda[i]);
        getchar();
    }
    setorNovo->prox = NULL;

    if(lista_setor == NULL) {
       return setorNovo;
    }
    else{
        setorNovo->prox = lista_setor;
        return setorNovo;
    }

}

void relatorio(setor *lista_setor,sensor *lista_sensor)
{
    printf("\n=== SENSORES ===\n");

    /*for(int i = 0; i < sensoresQuantidade; i++){
        printf("\nID: %i", sensores[i].identificacao);
        printf("\nTipo: %s", sensores[i].tipo);
        printf("Faixa: %.2f - %.2f\n", sensores[i].faixa_leitura[0], sensores[i].faixa_leitura[1]);
    }*/

    for(sensor *i = lista_sensor; i != NULL; i = i->prox){
        printf("\nID: %i", i->identificacao);
        printf("\nTipo: %s", i->tipo);
        printf("Faixa: %.2f - %.2f\n", i->faixa_leitura[0], i->faixa_leitura[1]);
    }

    printf("\n=== SETORES ===\n");

    for(setor *i = lista_setor; i != NULL; i = i->prox){
        printf("\nID: %i", i->identificacao);
        printf("\nDescricao: %s", i->descricao);

        for(int j = 0; j < i->instaladosSensor; j++){
            printf("\nSensor: %d", i->instalados[j].identificacao);
            printf("\nHorario 1: %s", i->horario_primeiro[j]);
            printf("Leitura 1: %.2f\n", i->leitura_primeira[j]);
            printf("Horario 2: %s", i->horario_segundo[j]);
            printf("Leitura 2: %.2f\n", i->leitura_segunda[j]);
        }
    }
}

void relatorio_variacao(setor *lista_setor)
{
    printf("\n=== VARIACAO DAS LEITURAS ===\n");

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        printf("\nSetor: %s\n", i->descricao);

        for(int j = 0; j < i->instaladosSensor; j++)
        {
            float variacao = fabs(i->leitura_segunda[j] - i->leitura_primeira[j]);

            printf("Sensor %d\n", i->instalados[j].identificacao);
            printf("Variacao: %.2f\n", variacao);
        }
    }
}

void relatorio_media(setor *lista_setor)
{
    printf("\n=== MEDIA DAS LEITURAS ===\n");

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        printf("\nSetor: %s\n", i->descricao);

        for(int j = 0; j < i->instaladosSensor; j++)
        {
            float media = (i->leitura_primeira[j] + i->leitura_segunda[j]) / 2;

            printf("Sensor %d\n", i->instalados[j].identificacao);
            printf("Media: %.2f\n", media);
        }
    }
}

void relatorio_faixa(setor *lista_setor)
{
    printf("\n=== VERIFICACAO DAS LEITURAS ===\n");

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        printf("\nSetor: %s\n", i->descricao);

        for(int j = 0; j < i->instaladosSensor; j++)
        {
            sensor s = i->instalados[j];

            printf("Sensor %d\n", s.identificacao);

            if(i->leitura_primeira[j] < s.faixa_leitura[0] || i->leitura_primeira[j] > s.faixa_leitura[1])
                printf("Primeira leitura FORA da faixa!\n");
            else
                printf("Primeira leitura OK\n");

            if(i->leitura_segunda[j] < s.faixa_leitura[0] || i->leitura_segunda[j] > s.faixa_leitura[1])
                printf("Segunda leitura FORA da faixa!\n");
            else
                printf("Segunda leitura OK\n");
        }
    }
}

void pesquisar_sensor_tipo(sensor *lista_sensor) // sensor
{
    string tipo;

    printf("Digite o tipo: ");
    getchar();
    fgets(tipo, T_STR, stdin);
    tipo[strcspn(tipo, "\n")] = '\0';

    int encontrou = 0;

    for(sensor *i = lista_sensor; i != NULL; i = i->prox)
    {
        if(strcmp(tipo, i->tipo) == 0)
        {
            printf("\nID: %d", i->identificacao);
            printf("\nTipo: %s", i->tipo);
            printf("\nFaixa: %.2f - %.2f\n", i->faixa_leitura[0], i->faixa_leitura[1]);

            encontrou = 1;
        }
    }

    if(!encontrou){
        printf("Nenhum sensor encontrado.\n");
    }
}

void pesquisar_setor_descricao(setor *lista_setor) //setor
{
    string descricao;

    printf("Descricao: ");
    getchar();
    fgets(descricao, T_STR, stdin);
    descricao[strcspn(descricao, "\n")] = '\0';

    int encontrou = 0;

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        if(strcmp(descricao, i->descricao) == 0)
        {
            printf("\nID: %d", i->identificacao);
            printf("\nDescricao: %s\n", i->descricao);

            encontrou = 1;
        }
    }

    if(!encontrou)
        printf("Setor nao encontrado!\n");
}

void relatorio_media_geral_sensor(sensor *lista_sensor,setor *lista_setor) // sensor e setor
{
    printf("\n=== MEDIA GERAL POR SENSOR ===\n");

    for(sensor *i = lista_sensor; i != NULL; i = i->prox)
    {
        float soma = 0;
        int quantidade = 0;

        for(setor *j = lista_setor; j != NULL; j = j->prox)
        {
            for(int k = 0; k < j->instaladosSensor; k++)
            {
                if(j->instalados[k].identificacao == i->identificacao)
                {
                    soma += j->leitura_primeira[k];
                    soma += j->leitura_segunda[k];
                    quantidade += 2;
                }
            }
        }

        if(quantidade > 0)
        {
            printf("\nSensor %d", i->identificacao);

            printf("\nTipo: %s", i->tipo);

            printf("\nMedia Geral: %.2f\n", soma / quantidade);
        }
    }
}

void relatorio_sensor_tipo(sensor *lista_sensor) //sensor
{
    string tipo;
    int encontrou = 0;

    printf("Digite o tipo do sensor: ");
    getchar();
    fgets(tipo, T_STR, stdin);
    tipo[strcspn(tipo, "\n")] = '\0';

    printf("\n=== RELATORIO POR TIPO DE SENSOR ===\n");

    for(sensor *i = lista_sensor; i != NULL; i = i->prox)
    {
        if(strcmp(tipo, i->tipo) == 0)
        {
            printf("\nID: %d", i->identificacao);
            printf("\nTipo: %s", i->tipo);
            printf("\nFaixa: %.2f - %.2f\n", i->faixa_leitura[0], i->faixa_leitura[1]);

            encontrou = 1;
        }
    }

    if(encontrou == 0)
    {
        printf("\nNenhum sensor encontrado para esse tipo.\n");
    }
}

void relatorio_leituras_setor(setor *lista_setor) //setor
{
    int id;

    printf("ID do setor: ");
    scanf("%d", &id);

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        if(i->identificacao == id)
        {
            printf("\nSetor: %s\n", i->descricao);

            for(int j = 0; j < i->instaladosSensor; j++)
            {
                printf("\nSensor %d",i->instalados[j].identificacao);

                printf("\nLeitura 1: %.2f", i->leitura_primeira[j]);

                printf("\nLeitura 2: %.2f\n", i->leitura_segunda[j]);
            }

            return;
        }
    }

    printf("Setor nao encontrado!\n");
}

void relatorio_variacao_sensor(setor *lista_setor) //setor
{
    int id;

    printf("ID do sensor: ");
    scanf("%d", &id);

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        for(int j = 0; j < i->instaladosSensor; j++)
        {
            if(i->instalados[j].identificacao == id)
            {
                float variacao = fabs(i->leitura_segunda[j] - i->leitura_primeira[j]);

                printf("\nSetor: %s", i->descricao);

                printf("\nVariacao: %.2f\n", variacao);
            }
        }
    }
}

void menu(sensor **listaSensores, setor **listaSetores)
{
    int opcao;

    do {
        printf("1-Cadastrar Sensor\n2-Cadastrar Setor\n3-Relatórios\n4-Pesquisar\n5-Relatorio Variacao\n6-Relatorio Media\n7-Relatorio Faixa\n8-Remover Sensor de um Setor\n9-Exportar HTML\n10-Relatorio CSV Sensores\n11-Relatorio CSV Setores\n12-Relatorio CSV Variacao\n13-Relatorio CSV Media\n14-Relatorio CSV Faixa\n0-Sair\nOpção escolhida: ");
        scanf("%i", &opcao);

        switch(opcao){

            case 1:
                *listaSensores = cadastrar_sensor(*listaSensores);
                break;

            case 2:
                *listaSetores = cadastrar_setor(*listaSetores, *listaSensores);
                break;

            case 3:
                relatorio(*listaSetores, *listaSensores);
                break;

            case 4:
                pesquisar(*listaSensores);
                break;

            case 5:
                relatorio_variacao(*listaSetores);
                break;

            case 6:
                relatorio_media(*listaSetores);
                break;

            case 7:
                relatorio_faixa(*listaSetores);
                break;

            case 8:
                remover_sensor_setor(*listaSetores);
                break;

            case 9:
                exportar_html(*listaSensores, *listaSetores);
                break;

            case 10:
                relatorio_csv_sensores(*listaSensores);
                break;

            case 11:
                relatorio_csv_setores(*listaSetores);
                break;

            case 12:
                relatorio_variacao_csv(*listaSetores);
                break;

            case 13:
                relatorio_media_csv(*listaSetores);
                break;

            case 14:
                relatorio_faixa_csv(*listaSetores);
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");

        }

    } while(opcao != 0);

}

int salvar_sensores(sensor *listaSensores)
{
    FILE *fp = fopen("sensores.bin", "wb");

    if(fp == NULL)
    {
        printf("Erro ao abrir arquivo sensores.bin para escrita!\n");
        return 0;
    }

    for(sensor *i = listaSensores; i != NULL; i = i->prox)
    {
        sensor temp = *i;
        temp.prox = NULL;

        fwrite(&temp, sizeof(sensor), 1, fp);
    }

    fclose(fp);
    return 1;
}

int salvar_setores(setor *listaSetores)
{
    FILE *fp = fopen("setores.bin", "wb");

    if(fp == NULL)
    {
        printf("Erro ao abrir arquivo setores.bin para escrita!\n");
        return 0;
    }

    for(setor *i = listaSetores; i != NULL; i = i->prox)
    {
        setor temp = *i;
        temp.prox = NULL;

        for(int j = 0; j < temp.instaladosSensor; j++)
        {
            temp.instalados[j].prox = NULL;
        }

        fwrite(&temp, sizeof(setor), 1, fp);
    }

    fclose(fp);
    return 1;
}

int carregar_sensores(sensor **listaSensores)
{
    FILE *fp = fopen("sensores.bin", "rb");

    if(fp == NULL)
    {
        return 0;
    }

    sensor temp;

    while(fread(&temp, sizeof(sensor), 1, fp) == 1)
    {
        sensor *novo = (sensor*) malloc(sizeof(sensor));

        if(novo == NULL)
        {
            printf("Erro de memoria!\n");
            fclose(fp);
            return 0;
        }

        *novo = temp;
        novo->prox = NULL;

        if(*listaSensores == NULL)
        {
            *listaSensores = novo;
        }
        else
        {
            sensor *aux = *listaSensores;

            while(aux->prox != NULL)
            {
                aux = aux->prox;
            }

            aux->prox = novo;
        }
    }

    fclose(fp);
    return 1;
}

int carregar_setores(setor **listaSetores)
{
    FILE *fp = fopen("setores.bin", "rb");

    if(fp == NULL)
    {
        return 0;
    }

    setor temp;

    while(fread(&temp, sizeof(setor), 1, fp) == 1)
    {
        setor *novo = (setor*) malloc(sizeof(setor));

        if(novo == NULL)
        {
            printf("Erro de memoria!\n");
            fclose(fp);
            return 0;
        }

        *novo = temp;
        novo->prox = NULL;

        for(int j = 0; j < novo->instaladosSensor; j++)
        {
            novo->instalados[j].prox = NULL;
        }

        if(*listaSetores == NULL)
        {
            *listaSetores = novo;
        }
        else
        {
            setor *aux = *listaSetores;

            while(aux->prox != NULL)
            {
                aux = aux->prox;
            }

            aux->prox = novo;
        }
    }

    fclose(fp);
    return 1;
}

void liberar_sensores(sensor *listaSensores)
{
    sensor *aux;

    while(listaSensores != NULL)
    {
        aux = listaSensores;
        listaSensores = listaSensores->prox;
        free(aux);
    }
}

void liberar_setores(setor *listaSetores)
{
    setor *aux;

    while(listaSetores != NULL)
    {
        aux = listaSetores;
        listaSetores = listaSetores->prox;
        free(aux);
    }
}

sensor *pesquisar_sensor_recursivo(sensor *lista_sensor, int id)
{
    if(lista_sensor == NULL)
    {
        return NULL;
    }

    if(lista_sensor->identificacao == id)
    {
        return lista_sensor;
    }

    return pesquisar_sensor_recursivo(lista_sensor->prox, id);
}

void pesquisar(sensor *lista_sensor)
{
    int id;

    printf("Digite a identificacao do sensor: ");
    scanf("%d", &id);

    sensor *resultado = pesquisar_sensor_recursivo(lista_sensor, id);

    if(resultado != NULL)
    {
        printf("\n=== SENSOR ENCONTRADO ===\n");
        printf("ID: %d\n", resultado->identificacao);
        printf("Tipo: %s\n", resultado->tipo);
        printf("Faixa: %.2f - %.2f\n",
               resultado->faixa_leitura[0],
               resultado->faixa_leitura[1]);
    }
    else
    {
        printf("\nSensor nao encontrado!\n");
    }

    printf("\n");
}

void remover_sensor_setor(setor *lista_setor)
{
    int idSetor, idSensor;
    int encontrouSetor = 0;
    int encontrouSensor = 0;

    printf("Digite o ID do setor: ");
    scanf("%d", &idSetor);

    printf("Digite o ID do sensor que deseja remover do setor: ");
    scanf("%d", &idSensor);

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        if(i->identificacao == idSetor)
        {
            encontrouSetor = 1;

            for(int j = 0; j < i->instaladosSensor; j++)
            {
                if(i->instalados[j].identificacao == idSensor)
                {
                    encontrouSensor = 1;

                    for(int k = j; k < i->instaladosSensor - 1; k++)
                    {
                        i->instalados[k] = i->instalados[k + 1];
                        strcpy(i->horario_primeiro[k], i->horario_primeiro[k + 1]);
                        strcpy(i->horario_segundo[k], i->horario_segundo[k + 1]);
                        i->leitura_primeira[k] = i->leitura_primeira[k + 1];
                        i->leitura_segunda[k] = i->leitura_segunda[k + 1];
                    }

                    i->instaladosSensor--;

                    printf("Sensor removido do setor com sucesso!\n");
                    return;
                }
            }
        }
    }

    if(encontrouSetor == 0)
    {
        printf("Setor nao encontrado!\n");
    }
    else if(encontrouSensor == 0)
    {
        printf("Sensor nao encontrado nesse setor!\n");
    }
}

void exportar_html(sensor *lista_sensor, setor *lista_setor)
{
    FILE *fp = fopen("dados.html", "w");

    if(fp == NULL)
    {
        printf("Erro ao criar arquivo HTML!\n");
        return;
    }

    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "<meta charset='UTF-8'>\n");
    fprintf(fp, "<title>Relatorio de Sensores e Setores</title>\n");
    fprintf(fp, "</head>\n");
    fprintf(fp, "<body>\n");

    fprintf(fp, "<h1>Relatorio de Sensores</h1>\n");
    fprintf(fp, "<table border='1'>\n");
    fprintf(fp, "<tr><th>ID</th><th>Tipo</th><th>Minimo</th><th>Maximo</th></tr>\n");

    for(sensor *i = lista_sensor; i != NULL; i = i->prox)
    {
        fprintf(fp, "<tr>");
        fprintf(fp, "<td>%d</td>", i->identificacao);
        fprintf(fp, "<td>%s</td>", i->tipo);
        fprintf(fp, "<td>%.2f</td>", i->faixa_leitura[0]);
        fprintf(fp, "<td>%.2f</td>", i->faixa_leitura[1]);
        fprintf(fp, "</tr>\n");
    }

    fprintf(fp, "</table>\n");

    fprintf(fp, "<h1>Relatorio de Setores</h1>\n");
    fprintf(fp, "<table border='1'>\n");
    fprintf(fp, "<tr>");
    fprintf(fp, "<th>ID Setor</th>");
    fprintf(fp, "<th>Descricao</th>");
    fprintf(fp, "<th>ID Sensor</th>");
    fprintf(fp, "<th>Horario 1</th>");
    fprintf(fp, "<th>Leitura 1</th>");
    fprintf(fp, "<th>Horario 2</th>");
    fprintf(fp, "<th>Leitura 2</th>");
    fprintf(fp, "</tr>\n");

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        if(i->instaladosSensor == 0)
        {
            fprintf(fp, "<tr>");
            fprintf(fp, "<td>%d</td>", i->identificacao);
            fprintf(fp, "<td>%s</td>", i->descricao);
            fprintf(fp, "<td colspan='5'>Nenhum sensor instalado</td>");
            fprintf(fp, "</tr>\n");
        }
        else
        {
            for(int j = 0; j < i->instaladosSensor; j++)
            {
                fprintf(fp, "<tr>");
                fprintf(fp, "<td>%d</td>", i->identificacao);
                fprintf(fp, "<td>%s</td>", i->descricao);
                fprintf(fp, "<td>%d</td>", i->instalados[j].identificacao);
                fprintf(fp, "<td>%s</td>", i->horario_primeiro[j]);
                fprintf(fp, "<td>%.2f</td>", i->leitura_primeira[j]);
                fprintf(fp, "<td>%s</td>", i->horario_segundo[j]);
                fprintf(fp, "<td>%.2f</td>", i->leitura_segunda[j]);
                fprintf(fp, "</tr>\n");
            }
        }
    }

    fprintf(fp, "</table>\n");
    fprintf(fp, "</body>\n");
    fprintf(fp, "</html>\n");

    fclose(fp);

    printf("Arquivo dados.html criado com sucesso!\n");
}

void relatorio_csv_sensores(sensor *lista_sensor)
{
    string nome;
    printf("Nome do arquivo CSV: ");
    getchar();
    fgets(nome, T_STR, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    FILE *fp = fopen(nome, "w");

    if(fp == NULL)
    {
        printf("Erro ao criar arquivo CSV!\n");
        return;
    }

    fprintf(fp, "ID;Tipo;Minimo;Maximo\n");

    for(sensor *i = lista_sensor; i != NULL; i = i->prox)
    {
        fprintf(fp, "%d;%s;%.2f;%.2f\n",
                i->identificacao,
                i->tipo,
                i->faixa_leitura[0],
                i->faixa_leitura[1]);
    }

    fclose(fp);
    printf("Arquivo CSV de sensores criado com sucesso!\n");
}

void relatorio_csv_setores(setor *lista_setor)
{
    string nome;
    printf("Nome do arquivo CSV: ");
    getchar();
    fgets(nome, T_STR, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    FILE *fp = fopen(nome, "w");

    if(fp == NULL)
    {
        printf("Erro ao criar arquivo CSV!\n");
        return;
    }

    fprintf(fp, "ID_Setor;Descricao;ID_Sensor;Horario_1;Leitura_1;Horario_2;Leitura_2\n");

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        if(i->instaladosSensor == 0)
        {
            fprintf(fp, "%d;%s;Nenhum sensor instalado;;;;\n",
                    i->identificacao,
                    i->descricao);
        }
        else
        {
            for(int j = 0; j < i->instaladosSensor; j++)
            {
                fprintf(fp, "%d;%s;%d;%s;%.2f;%s;%.2f\n",
                        i->identificacao,
                        i->descricao,
                        i->instalados[j].identificacao,
                        i->horario_primeiro[j],
                        i->leitura_primeira[j],
                        i->horario_segundo[j],
                        i->leitura_segunda[j]);
            }
        }
    }

    fclose(fp);
    printf("Arquivo CSV de setores criado com sucesso!\n");
}

void relatorio_variacao_csv(setor *lista_setor)
{
    string nome;

    printf("Nome do arquivo CSV: ");
    getchar();
    fgets(nome, T_STR, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    FILE *fp = fopen(nome, "w");

    if(fp == NULL)
    {
        printf("Erro ao criar arquivo CSV!\n");
        return;
    }

    fprintf(fp, "Setor;Sensor;Variacao\n");

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        for(int j = 0; j < i->instaladosSensor; j++)
        {
            float variacao = fabs(i->leitura_segunda[j] - i->leitura_primeira[j]);

            fprintf(fp, "%s;%d;%.2f\n",
                    i->descricao,
                    i->instalados[j].identificacao,
                    variacao);
        }
    }

    fclose(fp);
    printf("Arquivo CSV de variacao criado com sucesso!\n");
}

void relatorio_media_csv(setor *lista_setor)
{
    string nome;

    printf("Nome do arquivo CSV: ");
    getchar();
    fgets(nome, T_STR, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    FILE *fp = fopen(nome, "w");

    if(fp == NULL)
    {
        printf("Erro ao criar arquivo CSV!\n");
        return;
    }

    fprintf(fp, "Setor;Sensor;Media\n");

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        for(int j = 0; j < i->instaladosSensor; j++)
        {
            float media = (i->leitura_primeira[j] + i->leitura_segunda[j]) / 2;

            fprintf(fp, "%s;%d;%.2f\n",
                    i->descricao,
                    i->instalados[j].identificacao,
                    media);
        }
    }

    fclose(fp);
    printf("Arquivo CSV de media criado com sucesso!\n");
}

void relatorio_faixa_csv(setor *lista_setor)
{
    string nome;

    printf("Nome do arquivo CSV: ");
    getchar();
    fgets(nome, T_STR, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    FILE *fp = fopen(nome, "w");

    if(fp == NULL)
    {
        printf("Erro ao criar arquivo CSV!\n");
        return;
    }

    fprintf(fp, "Setor;Sensor;Leitura_1;Status_1;Leitura_2;Status_2\n");

    for(setor *i = lista_setor; i != NULL; i = i->prox)
    {
        for(int j = 0; j < i->instaladosSensor; j++)
        {
            sensor s = i->instalados[j];

            char status1[20];
            char status2[20];

            if(i->leitura_primeira[j] < s.faixa_leitura[0] || i->leitura_primeira[j] > s.faixa_leitura[1])
                strcpy(status1, "FORA");
            else
                strcpy(status1, "OK");

            if(i->leitura_segunda[j] < s.faixa_leitura[0] || i->leitura_segunda[j] > s.faixa_leitura[1])
                strcpy(status2, "FORA");
            else
                strcpy(status2, "OK");

            fprintf(fp, "%s;%d;%.2f;%s;%.2f;%s\n",
                    i->descricao,
                    s.identificacao,
                    i->leitura_primeira[j],
                    status1,
                    i->leitura_segunda[j],
                    status2);
        }
    }

    fclose(fp);
    printf("Arquivo CSV de faixa criado com sucesso!\n");
}
