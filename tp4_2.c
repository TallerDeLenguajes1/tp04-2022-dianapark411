#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea{
    int TareaID;
    char *Descripcion;
    int Duracion;
};
typedef struct Tarea Tarea;

void cargarDatos(Tarea **Tar, int cantTareas);
void controlDeRealizacion(Tarea **Tar, Tarea **TarRealizadas, int cantTareas);
void mostrarTareas(Tarea **Tar, Tarea **TarRealizadas, int cantTareas);

int main(){
    int cantTareas;
    printf("\nIngrese la cantidad de tareas a realizar: ");
    scanf("%i", &cantTareas);

    Tarea **Tareas;
    Tareas = (Tarea **)malloc(cantTareas*sizeof(Tarea*));

    cargarDatos(Tareas, cantTareas);

    Tarea **TareasRealizadas;
    TareasRealizadas = (Tarea **)malloc(cantTareas*sizeof(Tarea*));

    controlDeRealizacion(Tareas, TareasRealizadas, cantTareas);
    mostrarTareas(Tareas, TareasRealizadas, cantTareas);
    
    //hacer for con free tareas->descripcion
    free(Tareas);
}

void cargarDatos(Tarea **Tar, int cantTareas){
    char *buffer;
    buffer = (char *)malloc(sizeof(char)*150);

    for (int i = 0; i < cantTareas; i++){
        Tar[i] = (Tarea *)malloc(sizeof(Tarea));
        printf("\n---------------CARGAR TAREA [%i]---------------", i+1);
        Tar[i]->TareaID = i;
        printf("\nIngrese la descripcion de la tarea: ");
        fflush(stdin);
        gets(buffer);
        fflush(stdin);
        Tar[i]->Descripcion = (char *)malloc(strlen(buffer+1)*(sizeof(char)));
        strcpy(Tar[i]->Descripcion, buffer);
        
        do{
            printf("Ingrese la duracion de la tarea (entre 10 y 100): ");
            scanf("%i", &Tar[i]->Duracion);
        } while (Tar[i]->Duracion<10 || Tar[i]->Duracion>100);
        
    }
    free(buffer);
}

void controlDeRealizacion(Tarea **Tar, Tarea **TarRealizadas, int cantTareas){
    
    for (int i = 0; i < cantTareas; i++){
        TarRealizadas[i] = (Tarea *)malloc(sizeof(Tarea));
        int flag;
        do{
            printf("\nLa tarea de ID [%i] fue realizada? Ingrese 1 para si y 0 para no: ", Tar[i]->TareaID);
            scanf("%i", &flag);
        } while (flag<0 || flag>1);
        
        if (flag == 1){ //la tarea fue realizada
            TarRealizadas[i]->TareaID = Tar[i]->TareaID;
            TarRealizadas[i]->Descripcion = (char *)malloc(strlen(Tar[i]->Descripcion+1)*(sizeof(char)));
            strcpy(TarRealizadas[i]->Descripcion, Tar[i]->Descripcion);
            TarRealizadas[i]->Duracion = Tar[i]->Duracion;
            Tar[i] = NULL;
        }else{ //la tarea no fue realizada
            TarRealizadas[i] = NULL;
        }
    }
}

void mostrarTareas(Tarea **Tar, Tarea **TarRealizadas, int cantTareas){

    printf("\n\n--------TAREAS REALIZADAS--------");
    for (int i = 0; i < cantTareas; i++){
        if (TarRealizadas[i]!=NULL){
            printf("\nID de la tarea: %i", TarRealizadas[i]->TareaID);
            printf("\nDescripcion de la tarea: ");
            puts(TarRealizadas[i]->Descripcion);
            printf("Duracion de la tarea: %i ", TarRealizadas[i]->Duracion);
        }
    }
    
    printf("\n\n--------TAREAS PENDIENTES--------");
    for (int j = 0; j < cantTareas; j++){
        if (Tar[j]!=NULL){
            printf("\nID de la tarea: %i", Tar[j]->TareaID);
            printf("\nDescripcion de la tarea: ");
            puts(Tar[j]->Descripcion);
            printf("Duracion de la tarea: %i ", Tar[j]->Duracion);
        }                
    }   
}