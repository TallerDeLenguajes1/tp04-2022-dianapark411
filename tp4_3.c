#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea{
    int TareaID;
    char *Descripcion;
    int Duracion;
};
typedef struct Tarea Tarea;

struct NodoTarea{
    Tarea T;
    struct NodoTarea *siguiente;
};
typedef struct NodoTarea *Lista;

Lista cargarTareas(Lista Start, int cantTareas);
void controlDeRealizacion(Lista *TP, Lista *TR);
void mostrarTareas(Lista Start);
void liberarMemoria(Lista *tareas);

int main(){
    int cantTareas, id = 0;

    printf("\nIngrese la cantidad de tareas a realizar: ");
    scanf("%i", &cantTareas);
  
    Lista TP = NULL;  //Creo las listas vacias
    Lista TR = NULL;

    TP = cargarTareas(TP,cantTareas);
    controlDeRealizacion(&TP,&TR);

    printf("\n\n--------TAREAS REALIZADAS--------");
    mostrarTareas(TR);
    printf("\n\n--------TAREAS PENDIENTES--------");
    mostrarTareas(TP);
    
    
    liberarMemoria(&TP);
    liberarMemoria(&TR);
}

void liberarMemoria(Lista *tareas){
    struct NodoTarea *auxLiberarMemoria = NULL;
    while(tareas){
        free((*tareas)->T.Descripcion);
        auxLiberarMemoria = *tareas;
        *tareas = (*tareas)->siguiente;
        free(auxLiberarMemoria);
    }
}

Lista cargarTareas(Lista Start, int cantTareas){
    char *buffer;

    //esta asignacion es para cargar nodos al final
    //Lista auxiliar = Start;

    struct NodoTarea *NuevaTarea;
    buffer = (char *)malloc(sizeof(char)*150);
     
    for (int i = 0; i < cantTareas; i++){

        printf("\n\nCARGANDO TAREA %i", i+1);
        NuevaTarea = (struct NodoTarea*)malloc(sizeof(struct NodoTarea));
        NuevaTarea ->T.TareaID = i;
        do{
            printf("\nIngrese la duracion de la tarea (entre 10 y 100): ");
            scanf("%i", &NuevaTarea->T.Duracion);
            fflush(stdin);
        } while (NuevaTarea->T.Duracion<10 || NuevaTarea->T.Duracion>100);

        printf("\nIngrese la descripcion de la tarea: ");
        gets(buffer);
        fflush(stdin);
        NuevaTarea->T.Descripcion = (char *)malloc(strlen(buffer+1)*(sizeof(char)));
        strcpy(NuevaTarea->T.Descripcion, buffer);

        //cargando al comienzo
        NuevaTarea->siguiente = Start;
        Start = NuevaTarea;

        //cargando al final
        /*
        if (auxiliar!=NULL){
            while(auxiliar->siguiente!=NULL){
                auxiliar= auxiliar->siguiente;
            }
            NuevaTarea->siguiente = NULL;
            auxiliar->siguiente=NuevaTarea; 
        }else{
            NuevaTarea->siguiente = NULL;
            Start=NuevaTarea;
        }
        auxiliar = Start;
        */
    }

    free(buffer);
    return Start;
}

void controlDeRealizacion(Lista *TP, Lista *TR){
    
    //TNR es TareaNoRealizada
    Lista TNR=*TP;
    Lista TRealizadas=*TR;

    //Defino puntero auxiliar
    struct NodoTarea *aux;

    while (TNR!=NULL){
        int flag;
        do{
            printf("\nLa tarea de ID [%i] fue realizada? Ingrese 1 para si y 0 para no: ", TNR->T.TareaID);
            scanf("%i", &flag);
        } while (flag<0 || flag>1);
        
        if (flag == 1){ //la tarea fue realizada
            
            //MOVER LA TAREA DE UNA LISTA A LA OTRA
            // me paro con aux donde apunta la cabecera de las tareas pendientes;
            aux =  TNR;

            // apunto la cabecera de tareas pendientes al siguiente nodo
            TNR = TNR->siguiente;

            //apunto el nodo que quiero mover a donde apunta la cabecera de realizadas
            aux =  TRealizadas;

            //muevo la cabecera para que apunte al que agregue 
            TRealizadas=aux;

        }else{ //la tarea no fue realizada
            //muevo la cabecera para que apunte al siguiente
            TNR = TNR->siguiente;
        }
    }
}

void mostrarTareas(Lista Start){
    while(Start != NULL){
        printf("\nID de la tarea: %i", Start->T.TareaID);
        printf("\nDescripcion de la tarea: ");
        puts(Start->T.Descripcion);
        printf("Duracion de la tarea: %i ", Start->T.Duracion);
        
        //muevo la cabecera al siguiente nodo de la lista
        Start = Start->siguiente;
    }
}

