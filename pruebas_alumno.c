#include "pa2m.h"
#include "src/lista.h"


void prueba_simple()
{
	int i = 14;
	int j = 16;
	pa2m_afirmar(i != j, "i=14 es diferente de j=16");
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	prueba_simple();

	int num= 9;
	int *numerito;
	numerito= &num;

	lista_t *lista =lista_crear();
	lista_insertar(lista, numerito);

	return pa2m_mostrar_reporte();
}
