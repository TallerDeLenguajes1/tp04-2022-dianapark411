#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea{
    int TareaID;
    char *Descripcion;
    int Duracion;
};
typedef struct Tarea Tarea;

typedef struct{
    Tarea T;
    struct TNodoTarea *siguiente;
}NodoTarea;


void cargarTareas(NodoTarea **Start, int cantTareas);
void controlDeRealizacion(NodoTarea **TP, NodoTarea **TR);
void mostrarTareas(NodoTarea *Start);

int main(){
    int cantTareas, id = 0;

    printf("\nIngrese la cantidad de tareas a realizar: ");
    scanf("%i", &cantTareas);
  

    NodoTarea * TP = NULL;
    NodoTarea * TR = NULL;

    cargarTareas(&TP,cantTareas);

    controlDeRealizacion(&TP,&TR);

    printf("\n\n--------TAREAS REALIZADAS--------");
    mostrarTareas(TR);
    printf("\n\n--------TAREAS PENDIENTES--------");
    mostrarTareas(TP);
    
    
    //hacer for con free tareas->descripcion
    //free(Tareas);
}


void cargarTareas(NodoTarea **Start, int cantTareas){
    char *buffer;
    NodoTarea *Aux=*Start;
    NodoTarea *NuevaTarea;
    buffer = (char *)malloc(sizeof(char)*150);
     
    for (int i = 0; i < cantTareas; i++){

        NuevaTarea = (NodoTarea *)malloc(sizeof(NodoTarea));
        NuevaTarea->siguiente=NULL;

        NuevaTarea->T.TareaID = i;
        do{
            printf("Ingrese la duracion de la tarea (entre 10 y 100): ");
            scanf("%i", &NuevaTarea->T.Duracion);
            fflush(stdin);
        } while (NuevaTarea->T.Duracion<10 || NuevaTarea->T.Duracion>100);

        printf("\nIngrese la descripcion de la tarea: ");
        gets(buffer);
        NuevaTarea->T.Descripcion = (char *)malloc(strlen(buffer+1)*(sizeof(char)));
        strcpy(NuevaTarea->T.Descripcion, buffer);

        //cargando al comienzo
        NuevaTarea->siguiente = *Start;
        *Start = NuevaTarea;

        //cargando al final
        if (Aux!=NULL)
        {
            while(Aux!=NULL)
            {
                Aux=Aux->siguiente;
            }
            Aux=NuevaTarea; 
        }
        else
        {
            *Start=NuevaTarea;
        }
        Aux=*Start;  
    }

    free(buffer);
}

void controlDeRealizacion(NodoTarea **TP, NodoTarea **TR){
    
    //TNR es TareaNoRealizada
    NodoTarea *TNR=*TP;
    while (TNR!=NULL)
    {
        int flag;
        do{
            printf("\nLa tarea de ID [%i] fue realizada? Ingrese 1 para si y 0 para no: ", TNR->T.TareaID);
            scanf("%i", &flag);
        } while (flag<0 || flag>1);
        
        if (flag == 1){ //la tarea fue realizada
        //MOVER LA TAREA DE UNA LISTA A LA OTRA

            // TRealiz->T.TareaID =  Tar[i]->TareaID;
            //TRealiz->T.Descripcion = (char *)malloc(strlen(Tar[i]->Descripcion+1)*(sizeof(char)));
            //strcpy(TRealiz->T.Descripcion, Tar[i]->Descripcion);
            //TRealiz->T.Duracion = Tar[i]->Duracion;
            //Tar[i] = NULL;

        }else{ //la tarea no fue realizada
       //     TRealiz = NULL;
        }

        TNR=TNR->siguiente;
    }
}

void mostrarTareas(NodoTarea *Start){

    /*
    
    for (int i = 0; i < cantTareas; i++){
        if (TarRealizadas[i]!=NULL){
            printf("\nID de la tarea: %i", TarRealizadas[i]->TareaID);
            printf("\nDescripcion de la tarea: ");
            puts(TarRealizadas[i]->Descripcion);
            printf("Duracion de la tarea: %i ", TarRealizadas[i]->Duracion);
        }
    }
    
    
    for (int j = 0; j < cantTareas; j++){
        if (Tar[j]!=NULL){
            printf("\nID de la tarea: %i", Tar[j]->TareaID);
            printf("\nDescripcion de la tarea: ");
            puts(Tar[j]->Descripcion);
            printf("Duracion de la tarea: %i ", Tar[j]->Duracion);
        }                
    } 
    */
}

