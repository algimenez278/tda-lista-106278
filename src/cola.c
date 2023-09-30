#include "cola.h"
#include "lista.h"

cola_t *cola_crear() { return (cola_t *)lista_crear(); }

cola_t *cola_encolar(cola_t *cola, void *elemento) {
  if (cola == NULL) {
    return NULL;
  }
  lista_insertar((lista_t *)cola, elemento);
  return cola;
}

void *cola_desencolar(cola_t *cola) {
  if (cola == NULL) {
    return NULL;
  }
  void *elemento = NULL;
  elemento = lista_quitar_de_posicion((lista_t *)cola, 0);
  return elemento;
}

void *cola_frente(cola_t *cola) {
  if (cola == NULL) {
    return NULL;
  }
  void *elemento = NULL;
  elemento = lista_primero((lista_t *)cola);
  return elemento;
}

size_t cola_tamanio(cola_t *cola) {
  if (cola == NULL) {
    return 0;
  }
  return lista_tamanio((lista_t *)cola);
}

bool cola_vacia(cola_t *cola) {
  return ((cola == NULL) || (lista_tamanio((lista_t *)cola) == 0));
}

void cola_destruir(cola_t *cola) { lista_destruir((lista_t *)cola); }
