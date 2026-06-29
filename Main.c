#include "./header.h"

int main()
{
    sensor *listaSensores = NULL;
    setor *listaSetores = NULL;

    carregar_sensores(&listaSensores);
    carregar_setores(&listaSetores);

    menu(&listaSensores, &listaSetores);

    salvar_sensores(listaSensores);
    salvar_setores(listaSetores);

    liberar_sensores(listaSensores);
    liberar_setores(listaSetores);

    return 0; 
}
