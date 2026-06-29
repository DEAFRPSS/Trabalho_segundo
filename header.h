#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define T_STR 100
#define MAX_SENSORES_SETOR 3

typedef char string[T_STR];

typedef struct sensor {
    int identificacao;
    string tipo;
    float faixa_leitura[2];
    struct sensor *prox;
} sensor;

typedef struct setor {
    int identificacao;
    string descricao;
    sensor instalados[MAX_SENSORES_SETOR];
    string horario_primeiro[MAX_SENSORES_SETOR];
    string horario_segundo[MAX_SENSORES_SETOR];
    float leitura_primeira[MAX_SENSORES_SETOR];
    float leitura_segunda[MAX_SENSORES_SETOR];
    int instaladosSensor;
    struct setor *prox;
} setor;

/* Cadastro */
sensor *cadastrar_sensor(sensor *lista);
setor *cadastrar_setor(setor *lista_setor, sensor *lista_sensor);

/* Pesquisas */
void pesquisar(sensor *lista_sensor);
sensor *pesquisar_sensor_recursivo(sensor *lista_sensor, int id);
void pesquisar_sensor_tipo(sensor *lista_sensor);
void pesquisar_setor_descricao(setor *lista_setor);

/* Relatórios */
void relatorio(setor *lista_setor, sensor *lista_sensor);
void relatorio_variacao(setor *lista_setor);
void relatorio_media(setor *lista_setor);
void relatorio_faixa(setor *lista_setor);
void relatorio_media_geral_sensor(sensor *lista_sensor, setor *lista_setor);
void relatorio_sensor_tipo(sensor *lista_sensor);
void relatorio_leituras_setor(setor *lista_setor);
void relatorio_variacao_sensor(setor *lista_setor);

/* Relatórios em CSV */
void relatorio_csv_sensores(sensor *lista_sensor);
void relatorio_csv_setores(setor *lista_setor);
void relatorio_variacao_csv(setor *lista_setor);
void relatorio_media_csv(setor *lista_setor);
void relatorio_faixa_csv(setor *lista_setor);

void exportar_html(sensor *lista_sensor, setor *lista_setor);

/* Exclusão */
void remover_sensor_setor(setor *lista_setor);

/* Menu */
void menu(sensor **listaSensores, setor **listaSetores);

/* Arquivos binários */
int carregar_sensores(sensor **listaSensores);
int carregar_setores(setor **listaSetores);
int salvar_sensores(sensor *listaSensores);
int salvar_setores(setor *listaSetores);

/* Liberar memória */
void liberar_sensores(sensor *listaSensores);
void liberar_setores(setor *listaSetores);

#endif
