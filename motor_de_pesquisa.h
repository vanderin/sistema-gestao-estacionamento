#ifndef MOTOR_DE_PESQUISA_H
#define MOTOR_DE_PESQUISA_H

#include "titulos_avulsos.h"
#include "avencas.h"

void pesquisarTitulo(Titulo** head_titulos_avulsos);
void fiscalizar();
int pesquisarAvenca(AvencaAtiva* head, char* matricula);
#endif
