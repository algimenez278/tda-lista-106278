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
//PRE: -
//POST: crea un nodo con el elemento enviado.
nodo_t *crear_nodo(void* elemento){

	nodo_t *nodo= calloc(1, sizeof (nodo_t));
	if(nodo == NULL){
		return NULL;
	}

	nodo->elemento= elemento; 
	nodo->siguiente= NULL;

	return nodo;
}

//PRE: -
//POST:	libera la memoria reservada para un nodo.
void nodo_destruir(nodo_t* nodo){

	if(nodo == NULL){
		return;
	}

	nodo->elemento = NULL;
	free(nodo);
}


//////INSERCIONES AL INICIO///
//PRE: lista no debe ser NULL
//observación: no hago el chequeo porque en el flujo de mi progama,
//si utiliza esta función previamente se chequea que la lista no sea NULL.
//POST: inserta un elemento en "la posicion 0", al inicio, de la lista.
lista_t *lista_insertar_inicio(lista_t *lista, void *elemento){
	
	nodo_t *nuevo= crear_nodo(elemento);
	if(nuevo == NULL){
		return NULL;
	}

	nuevo->siguiente= lista->nodo_inicio;
	lista->nodo_inicio= nuevo;
	lista->tamanio++;

	return lista;
}

//// AL FINAL///
//PRE: lista no debe ser NULL
//observación: no hago el chequeo porque en el flujo de mi progama,
//si utiliza esta función previamente se chequea que la lista no sea NULL.
//POST: inserta un elemento en "la ultima posicion", al final, de la lista.
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
//PRE: lista no debe ser NULL, la posicion debe ser mayor a 0 y menor
//		al tamanio de la lista
//observación: no hago el chequeo porque en el flujo de mi progama,
//si utiliza esta función previamente se chequea que la lista no sea NULL.
//observación2: también por el flujo de mi programa, si utiliza esta función,
//previamente se hicieron chequeos de que la posición es válida.
//POST: inserta un elemento en la lista, en la posicion enviada.
lista_t *lista_insertar_medio(lista_t *lista, void *elemento, size_t posicion){

	nodo_t *nuevo= crear_nodo(elemento);
	if(nuevo == NULL){
		return NULL;
	}

	nodo_t *anterior= lista->nodo_inicio;
	size_t i=0;
	if(anterior->siguiente!= NULL){
		while(i != (posicion-1)){
			anterior= anterior->siguiente;
			i++;
		}		
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
		return lista_insertar_inicio(lista, elemento);		
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
		return lista_insertar(lista, elemento);
	}

	if(posicion == 0){
		return lista_insertar_inicio(lista, elemento);
	}


	return lista_insertar_medio(lista, elemento, posicion);
}

void *lista_quitar(lista_t *lista)
{
	if(lista == NULL || lista->tamanio == 0 || lista->nodo_inicio == NULL){
		return NULL;
	}

	void* elemento_eliminado = NULL;

	if(lista->tamanio == UN_ELEMENTO){
		elemento_eliminado= lista->nodo_inicio->elemento;
		nodo_destruir(lista->nodo_inicio);
		lista->tamanio--;
		lista->nodo_inicio = NULL;
		return elemento_eliminado;
	}

	nodo_t *aux= lista->nodo_inicio;

	if(aux->siguiente != NULL){
		while(aux->siguiente->siguiente != NULL){	
			aux= aux->siguiente;		
		}
		elemento_eliminado= aux->siguiente->elemento;
		nodo_destruir(aux->siguiente);	
		aux->siguiente= NULL;
		lista->tamanio--;		
	}
	
	return elemento_eliminado;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if(lista == NULL || lista->tamanio == 0 || lista->nodo_inicio == NULL){
		return NULL;
	}

	void* elemento_eliminado = NULL;

	if(lista->tamanio == UN_ELEMENTO || posicion >= lista->tamanio){
		return lista_quitar(lista);;
	}

	if(posicion == 0){

		nodo_t *aux= lista->nodo_inicio;
		lista->nodo_inicio= lista->nodo_inicio->siguiente;		
		elemento_eliminado= aux->elemento;		
		nodo_destruir(aux);
		lista->tamanio--;
		return elemento_eliminado;
	}

	size_t pos= 0;
	nodo_t *anterior= lista->nodo_inicio;
	if(anterior->siguiente != NULL){
		while(pos != (posicion-1)){
			anterior= anterior->siguiente;
			pos++;
		}
		nodo_t *eliminado= anterior->siguiente;
		elemento_eliminado= eliminado->elemento;
		anterior->siguiente= eliminado->siguiente;
		nodo_destruir (eliminado);
		lista->tamanio--;		
	}

	return elemento_eliminado;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if(lista == NULL || lista->nodo_inicio== NULL || posicion >= lista->tamanio){
		return NULL;
	}

	if(posicion == 0){
		return lista->nodo_inicio->elemento;
	}

	nodo_t *nodo = lista->nodo_inicio;
	size_t i=0;
	while(i!=posicion){
		nodo= nodo->siguiente;
		i++;
	}

	return nodo->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if(lista == NULL || comparador == NULL || lista->nodo_inicio == NULL){
		return NULL;
	}

	if(lista->tamanio == UN_ELEMENTO){
		if(comparador(lista->nodo_inicio->elemento, contexto) == 0){
			return lista->nodo_inicio->elemento;
		}
	}

	nodo_t *nodo = lista->nodo_inicio;
	for(size_t i=0; i < lista->tamanio; i++){
		if(comparador(nodo->elemento, contexto) == 0){
			return nodo->elemento;
		}
		nodo= nodo->siguiente;
	}

	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if(lista == NULL || lista->tamanio == 0){
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
	if(lista == NULL || lista->nodo_inicio == NULL){
		return;
	}

	if(funcion == NULL){
		lista_destruir(lista);
		return;
	}

	nodo_t *aux;
	while(!lista_vacia(lista)){
		aux= lista->nodo_inicio;
		funcion(aux->elemento);
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		nodo_destruir(aux);
		lista->tamanio--;
	}
	free(lista);
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

	return (iterador->nodo_actual != NULL);
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
	if(iterador == NULL || iterador->lista == NULL || iterador->nodo_actual == NULL){
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
	if(!lista || !funcion)
		return 0;

	size_t contador = 0;
	nodo_t *actual = lista->nodo_inicio;

	while (actual != NULL) {
		contador++;

		if(funcion(actual->elemento, contexto) == false)
			return contador;
		actual = actual->siguiente;
	}

	return contador;
}



