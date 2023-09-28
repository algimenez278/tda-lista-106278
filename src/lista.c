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
	lista_t *lista;
	nodo_t *nodo_actual;
};

///// un nodo /////
nodo_t *crear_nodo(void* elemento){

	nodo_t *nodo= calloc(1, sizeof (nodo_t));

	if(nodo == NULL){
		return NULL;
	}

	nodo->elemento= elemento; 
	nodo->siguiente= NULL;

	return nodo;
}

void nodo_destruir(nodo_t* nodo){

	free(nodo);
}
//y su destrucción


//////INSERCIONES AL INICIO///

lista_t *lista_insertar_inicio(lista_t *lista, void *elemento){
	
	nodo_t *nuevo= crear_nodo(elemento);
	nuevo->siguiente= lista->nodo_inicio;
	lista->nodo_inicio= nuevo;
	lista->tamanio++;

	return lista;
}

//// AL FINAL///
lista_t *lista_insertar_final(lista_t *lista, void *elemento){
	
	nodo_t *nuevo= crear_nodo(elemento);
	if(nuevo == NULL){
		return NULL;
	}
	nodo_t *ultimo= lista->nodo_inicio;

	while(ultimo->siguiente != NULL){
		ultimo= ultimo->siguiente;
	}

	ultimo->siguiente= nuevo;
	lista->tamanio++;

	return lista;
}

////// AL MEDIO //////
lista_t *lista_insertar_medio(lista_t *lista, void *elemento, size_t posicion){

	nodo_t *nuevo= crear_nodo(elemento);
	if(nuevo == NULL){
		return NULL;
	}

	nodo_t *anterior= lista->nodo_inicio;
	for(size_t i=0; i<posicion; i++){
		anterior= anterior->siguiente;
	}

	nuevo->siguiente= anterior->siguiente;
	anterior->siguiente= nuevo;
	lista->tamanio++;

	return lista;
}

///////// FIN FUNCIONES MIAS :)  ////////

lista_t *lista_crear()
{	
	lista_t *lista= calloc(1, sizeof(lista_t));
	if(lista == NULL){
		return NULL;
	}

	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if(lista == NULL){
		return NULL;
	}

	if(lista->tamanio == 0){
		lista->nodo_inicio = crear_nodo(elemento);
		lista->tamanio++;
		return lista;		
	}

	lista= lista_insertar_final(lista, elemento);

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if(lista == NULL){
		return NULL;
	}

	if((lista->nodo_inicio == NULL) || (lista->tamanio == 0) || posicion >= lista->tamanio){
		lista= lista_insertar(lista, elemento);		
	}

	if(posicion == 0){
		lista= lista_insertar_inicio(lista, elemento);
	}

	if(posicion < lista->tamanio){
		lista= lista_insertar_medio(lista, elemento, posicion);
	}

	return lista;	
}

void *lista_quitar(lista_t *lista)
{
	if(lista == NULL || lista->tamanio == 0 || lista->nodo_inicio == NULL){
		return NULL;
	}

	void* elemento_eliminado;

	if(lista->tamanio == UN_ELEMENTO){
		elemento_eliminado= lista->nodo_inicio->elemento;
		nodo_destruir(lista->nodo_inicio);
		lista->tamanio--;
		return elemento_eliminado;
	}

	nodo_t *aux= lista->nodo_inicio;

	while(aux->siguiente != NULL){
		aux= aux->siguiente;
	}

	elemento_eliminado= aux->elemento;

	nodo_destruir(aux->siguiente);
	lista->tamanio--;
	
	return elemento_eliminado;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if(lista == NULL || lista->tamanio == 0 || lista->nodo_inicio == NULL){
		return NULL;
	}

	void* elemento_eliminado;

	if(lista->tamanio == UN_ELEMENTO || posicion >= lista->tamanio){
		elemento_eliminado= lista_quitar(lista);
		return elemento_eliminado;
	}

	if(posicion == 0){
		elemento_eliminado= lista->nodo_inicio->elemento;
		nodo_t *aux= lista->nodo_inicio;
		lista->nodo_inicio= lista->nodo_inicio->siguiente;
		nodo_destruir(aux);
		lista->tamanio--;
		return elemento_eliminado;
	}

	size_t posicion_actual= 0;
	nodo_t *nodo_anterior_al_eliminado= lista->nodo_inicio;
	nodo_t *nodo_a_eliminar= lista->nodo_inicio->siguiente;

	while(posicion_actual != (posicion-1)){
		nodo_anterior_al_eliminado= nodo_anterior_al_eliminado->siguiente;
		nodo_a_eliminar= nodo_a_eliminar->siguiente;
		posicion_actual++;
	}

	elemento_eliminado= nodo_a_eliminar->elemento;
	nodo_anterior_al_eliminado->siguiente= nodo_a_eliminar->siguiente;

	nodo_destruir(nodo_anterior_al_eliminado->siguiente);
	lista->tamanio--;

	return elemento_eliminado;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	//////////falta
	return NULL;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	///////////falta
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if(lista == NULL || lista->tamanio == 0){
		return NULL;
	}

	return &lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if(lista == NULL || (lista->tamanio == 0)){
		return NULL;
	}

	if(lista->tamanio == UN_ELEMENTO){
		return &lista->nodo_inicio->elemento;
	}

	nodo_t *ultimo= lista->nodo_inicio;
	while(ultimo->siguiente != NULL){
		ultimo= ultimo->siguiente;
	}

	return &ultimo->elemento;
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

	if(lista->tamanio == UN_ELEMENTO){
		nodo_destruir(lista->nodo_inicio);
		lista->tamanio= (lista->tamanio -UN_ELEMENTO);		
	}
	else{
		nodo_t *aux;

		while(!lista_vacia(lista)){
			aux= lista->nodo_inicio;
			lista->nodo_inicio = lista->nodo_inicio->siguiente;
			nodo_destruir(aux);
			lista->tamanio = (lista->tamanio - UN_ELEMENTO);
		}		
	}

	free(lista);

}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
}

/////////////////////////////////////////////////

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if(lista == NULL){
		return NULL;
	}

	lista_iterador_t *iterador= calloc(1, sizeof(lista_iterador_t));
	if(iterador == NULL){
		return NULL;
	}

	iterador->lista= lista;
	iterador->nodo_actual= lista->nodo_inicio;
	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if(iterador== NULL || iterador->lista == NULL || iterador->nodo_actual == NULL){
		return false;
	}

	return (iterador->nodo_actual->siguiente != NULL);
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if(iterador == NULL){
		return false;
	}

	if(lista_iterador_tiene_siguiente(iterador)){
		iterador->nodo_actual = iterador->nodo_actual->siguiente;
	}
	return(iterador->nodo_actual != NULL);
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if(iterador == NULL || iterador->lista == NULL || iterador->nodo_actual == NULL || iterador->nodo_actual->siguiente == NULL ){
		return NULL;
	}

	return(iterador->nodo_actual->elemento);
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if(iterador == NULL || iterador->lista == NULL){
		return;
	}

	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}



