#include "lista.h"
#include <stddef.h>
#include <stdlib.h>


#include <stdio.h>
#define UN_ELEMENTO 1

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	size_t tamanio;
};

struct lista_iterador {
	//y acá?
	int sarasa;
};

///// un nodo /////
nodo_t *crear_nodo(void* elemento){

	nodo_t *nodo= calloc(1, sizeof (nodo_t));

	if(nodo == NULL){
		return NULL;
	}

	nodo->elemento= malloc(sizeof (elemento));
	nodo->elemento= elemento; 
	nodo->siguiente= NULL;

	return nodo;
}

void nodo_destruir(nodo_t* nodo){

	free(nodo->elemento);
	free(nodo);
}
//y su destrucción


lista_t *lista_crear()
{	
	lista_t *lista= calloc(1, sizeof(lista_t));
	if(lista == NULL){
		return NULL;
	}

	lista->nodo_inicio= crear_nodo(NULL);
	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if(lista == NULL){
		return NULL;
	}

	nodo_t *nodo = crear_nodo(elemento);
	if(nodo == NULL){
		return NULL;
	}

	//no puedo usar el lista_vacia porque esta def dsp.
	if(lista->tamanio == 0){
		lista->nodo_inicio = nodo;
		lista->tamanio++;		
	}
	else{
		nodo_t *aux = lista->nodo_inicio;
		while(aux->siguiente != NULL){
			aux= aux->siguiente;
		}
		aux->siguiente = nodo;
		lista->tamanio++;
	}

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if(lista == NULL){
		return NULL;
	}

	nodo_t *nuevo= crear_nodo(elemento);

	if((lista->nodo_inicio == NULL) || (lista->tamanio == 0)){
		lista->nodo_inicio = nuevo;
		lista->tamanio++;
		return lista;		
	}

	if(posicion > lista->tamanio){
		lista_insertar(lista, elemento);
		return lista;
	}

	nodo_t *aux = lista->nodo_inicio;
	int posicion_actual=0;

	//si pos es 2, esto es para guardarme el en aux al 1, su siguiente es 2
	while(posicion_actual != posicion){
		aux= aux->siguiente;
		posicion_actual++;
	}
	
	nuevo->siguiente= aux->siguiente;
	aux->siguiente = nuevo;
	lista->tamanio++;

	return lista;	
}

void *lista_quitar(lista_t *lista)
{
	if(lista == NULL || lista->tamanio == 0 || lista->nodo_inicio == NULL){
		return NULL;
	}

	if(lista->tamanio == UN_ELEMENTO){
		nodo_destruir(lista->nodo_inicio);
		lista->tamanio= (lista->tamanio -UN_ELEMENTO);
		return lista;
	}

	nodo_t *aux= lista->nodo_inicio;

	while((aux->siguiente)->siguiente != NULL){
		aux= aux->siguiente;
	}

	void* elemento_eliminado= aux->elemento;

	nodo_destruir(aux->siguiente);
	aux->siguiente= NULL;
	lista->tamanio= (lista->tamanio -UN_ELEMENTO);
	
	return elemento_eliminado;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if(lista == NULL){
		return NULL;
	}

	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if(lista == NULL || (lista->tamanio == 0)){
		return NULL;
	}

	if(lista->tamanio == UN_ELEMENTO){
		return lista->nodo_inicio->elemento;
	}

	nodo_t *ultimo= lista->nodo_inicio;
	while(ultimo->siguiente != NULL){
		ultimo= ultimo->siguiente;
	}

	return ultimo->elemento;
}

bool lista_vacia(lista_t *lista)
{
	return ((lista == NULL) || (lista->tamanio == 0));
}

size_t lista_tamanio(lista_t *lista)
{	
	if(lista == NULL || lista->nodo_inicio == NULL){
		return 0;
	}

	return lista->tamanio;
}

void lista_destruir(lista_t *lista)
{
	if(lista == NULL){
		return;
	}

	nodo_t *aux= lista->nodo_inicio; 

	while(lista_vacia(lista)){
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		nodo_destruir(aux);
		lista->tamanio = (lista->tamanio - UN_ELEMENTO);
	}
	free(lista);

}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
}

/////////////////////////////////////////////////

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}



