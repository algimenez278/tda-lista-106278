#include "pa2m.h"
#include "src/lista.h"


int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");

	int n0= 3;
	int n1= 9;
	int n2= 7;
	int n3= 5;

	lista_t *lista =lista_crear();

	lista_insertar(lista, &n0);
	lista_insertar(lista, &n1);
	lista_insertar(lista, &n2);
	lista_insertar(lista, &n3);

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &n0, "El elemento se encuentra en la pos correcta");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &n1, "El elemento se encuentra en la pos correcta");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == &n2, "El elemento se encuentra en la pos correcta");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == &n3, "El elemento se encuentra en la pos correcta");

	lista_quitar(lista);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == NULL, "El elemento fue eliminado (:");

	lista_quitar_de_posicion(lista, 1);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &n2, "El elemento se encuentra en la pos correcta");


	lista_destruir(lista);
	return pa2m_mostrar_reporte();
}
