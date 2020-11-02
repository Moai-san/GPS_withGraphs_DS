#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "treemap.h"
#include "list.h"
#include "mymenu.h"

HashMap* cities;//lista ciudades

/*initializes all the variables*/
void init_var()
{
    cities =(HashMap*)calloc(1,sizeof(HashMap)); 
    cities =createMap(10);
}

//importa archivo txt
void import(char* name)
{
    FILE* input;
    char fileName[105];
    snprintf(fileName,sizeof(fileName),"%s%s",name,".txt");
    input =fopen(fileName,"r"); //apertura del archivo ingresado
    if (input==NULL)
    {
      printf("Pucha, No Existe El Archivo Especificado! (ΠΦΠ)/\n");
      return;
    }
    char* A =((char*)calloc(30,sizeof(char))); //ciudad A, se usa para la lectura en fscanf, luego el valor se traspasa a otra variable para asi ingresarlo al arbol donde se guardaran los datos.
    char* B =((char*)calloc(30,sizeof(char))); //ciudad B, se usa para la lectura en fscanf, luego el valor se traspasa a otra variable para asi ingresarlo al arbol donde se guardaran los datos.
    TreeMap* auxTree =(TreeMap*)calloc(1,sizeof(TreeMap)); //arbol binario donde se guardaran distancias.
    int d; //distancia, se usa para la lectura en fscanf, luego el valor se traspasa a otra variable para asi ingresarlo al arbol donde se guardaran los datos.
    while((fscanf(input,"%s%s%d",A,B,&d))!=EOF) //mientras fscanf no llegue al fin del archivo
    {
        char* Acity =((char*)calloc(30,sizeof(char))); //se declara ciudad A para ingreso en arbol, ya que si usaramos la variable del fscanf, se sobreescribirian los valores ya que seria el mismo puntero siempre.
        char* Bcity =((char*)calloc(30,sizeof(char))); //se declara ciudad B para ingreso en arbol, ya que si usaramos la variable del fscanf, se sobreescribirian los valores ya que seria el mismo puntero siempre.
        strcpy(Acity,A); //se ingresa valor a ciudad A, para arbor
        strcpy(Bcity,B); //se ingresa valor a ciudad B, para arbor
        int* distance =(int*)calloc(1,sizeof(int)); //se declara distancia para ingreso en arbol, ya que si usaramos la variable del fscanf, se sobreescribirian los valores ya que seria el mismo puntero siempre.
        *distance =d;
        if(searchMap(cities,Acity)!=NULL) //si la ciudad "A" está en la tabla hash de ciudades
        {
            auxTree =cities->buckets[cities->current]->value; //se usa auxtree para facilitar la lectura del codigo
            insertTreeMap(auxTree,distance,Bcity); //se ingresa la ciudad B al arbol de la ciudad A
        }
        else //si no está, se crea un arbol, se le ingresa la ciudad B, y se ingresa en la casilla de la tabla hash de la ciudad A
        {
            auxTree =createTreeMap(lower_than_int);
            insertTreeMap(auxTree,distance,Bcity);
            insertMap(cities,Acity,auxTree);
        }
        //lo mismo que arriba, pero con la ciudad B a evaluar, y la A, a ingresar en arbol
        if(searchMap(cities,Bcity)!=NULL)
        {
            auxTree =cities->buckets[cities->current]->value;
            insertTreeMap(auxTree,distance,Acity);
        }
        else
        {
            auxTree =createTreeMap(lower_than_int);
            insertTreeMap(auxTree,distance,Acity);
            insertMap(cities,Bcity,auxTree);
        }
    }
    fclose(input);
}

//encuentra ciudad mas cercana
void nearest(char* cityName)
{
    TreeMap* adjCities = searchMap(cities,cityName); //arbol con las ciudades adyascentes a la ciudad ingresada
    if(firstTreeMap(adjCities)==NULL) //si la ciudad no existe, se imprime mensaje de error, si la ciudad existe, se imprime la ciudad mas cercana, osea el primer nodo de nuestro arbol binario, ya que esta ordenado por distancias
    {
        printf("Ciudad no se encuentra en la lista de distancias!\n");
        return;
    }
    printf("La ciudad mas cercana a %s es %s\n",cityName,(char*)firstTreeMap(adjCities));
}

//obtiene ciudades adyascentes y las imprime, retorna cantidad de ciudades adyascentes
int get_adj(char* cityName)
{
    TreeMap* adjCities = searchMap(cities,cityName); //arbol de ciudades adyascentes
    TreeNode* currentNode =(TreeNode*)calloc(1,sizeof(TreeNode)); //nodo actual
    firstTreeMap(adjCities); //posicionamos la primera posicion del arbol
    currentNode =adjCities->current; //cambiamos current
    printf("lista de ciudades adyascentes a %s\n",cityName);
    int pos =0; //posicion en pantalla
    while(currentNode!=NULL) //mientras existan ciudades adyascentes
    {
        printf("%d - %s\t%d KM\n",pos,(char*)currentNode->value,*(int*)currentNode->key); //imprime numero de opcion, ciudad, y distancia a la ciudad inicial, ejemplo: (0 - Chicago    117 KM)
        pos++; //aumentamos en uno la opcion impresa en pantalla
        nextTreeMap(adjCities); //avanzamos en el arbol
        currentNode =adjCities->current; //cambiamos current
    }
    return(pos-1); //retornamos cuantas ciudades hay
}

//crea ruta personalizada desde la ciudad ingresada
void createRoute(char* cityName)
{
    int option; //opcion a seleccionar en el menu
    int distance =0; //distancia acumulada en la ruta recorrida
    int valid; //flag para saber si la opcion ingresada es valida
    TreeNode* currentNode =(TreeNode*)calloc(1,sizeof(TreeNode)); //ciudad actual (al momento de crear la ruta sera la actual, ya que ahora esta vacia)
    TreeMap* adjCities = searchMap(cities,cityName); //arbol binario de ciudades, con clave la distancia al nodo buscado, ejemplo, si creo ruta desde chicago, este arbol contendra las ciudades adyascentes a chicago
    if(firstTreeMap(adjCities)==NULL) //si el arbol de ciudades adyascentes esta vacio significa que la ciudad que se buscó, no existe, ya que cada ciudad tiene almenos una adyascente debido a que el archivo contiene pares de ciudades
    {
        printf("Ciudad no se encuentra en la lista de distancias!\n");
        return;
    }
    List* cityList =create_list(); //lista de ciudades de la ruta armada (esta se imprimira en pantalla al finalizar la ruta)
    while(1)
    {
        push_back(cityList,cityName); //ingreso la ciudad actual a la lista de ciudades de la ruta
        valid =get_adj(cityName); //imprimo las adyascentes a esta, en pantalla para que el usuario seleccione una
        printf("ingrese numero de la ciudad siguiente,si no quiere seguir añadiendo ciudades a la ruta, escriba -1\n");
        scanf("%d",&option);
        while (option>valid)
        {
            printf("opcion invalida, ingrese numero de la ciudad siguiente,si no quiere seguir añadiendo ciudades a la ruta, escriba -1\n");
            scanf("%d",&option);
        }
        if (option==-1) //si la opcion ingresada por el usuario es -1, detengo el ciclo while ya que la ruta concluyó
        {
            break;
        }
        firstTreeMap(adjCities); //obtengo la primera ciudad de la lista de adjuntas ya que asi puedo ir al numero que ingreso el usuario como opcion
        currentNode =adjCities->current; //pongo de ciudad actual a la primera de la lista de adjuntas
        for (int i =0;i<option;i =(i+1)) //ciclo for que itera segun el numero ingresado por el usuario, ya que el arbol esta ordenado, por lo cual el numero de opcion se condice con el numero de veces que hago next
        {
            nextTreeMap(adjCities);
            currentNode =adjCities->current;
        }
        distance =distance+(*(int*)currentNode->key); //aumento la distancia recorrida (distancia = distancia actual + distancia con la ciudad seleccionada, como el arbol es ordenado por clave, distancia = clave)
        cityName =(char*)currentNode->value; //se cambia cityname para mostrar el nombre correctamente en pantalla, y hacer la busqueda del siguiente arbol de adyascentes
        adjCities = searchMap(cities,cityName);
    }
    clear_Screen(); //limpieza de pantalla
    printf("Distancia Recorrida: %d KM\n",distance);
    printf("Ciudades por las que pasaste\n");
    first(cityList); //me sitúo en la ciudad inicial de la lista de ruta, luego con un for y la funcion next imprimo cada ciudad
    for(int i =0;i<cityList->count;i =(i+1))
    {
        printf("%s\n",(char*)cityList->current->data);
        next(cityList);
    }
}

void shortestRoute(char* originName, char* destinyName)
{
    /*si origen y destino son iguales, se imprime que no es necesario moverse, si son distintos debiese usarse un grafo de busqueda e implementar una busqueda en anchura usando
    nodos con punteros, sin embargo esto ultimo no fue implementado por lo que solo se hizo un printeo*/
    if(strcmp(originName,destinyName)==0) 
    {
        printf("La ruta ingresada no requiere moverse, ya que inicia y termina en %s\n",originName);
        return;
    }
    else
    {
        printf("Funcion no implementada completamente\n");
    }
    
    /*node* origin =create_graphNode();
    strcpy(origin->o_city,originName);
    strcpy(origin->c_city,originName);
    strcpy(origin->d_city,destinyName);
    List* adyascentes =adj_nodes(origin,cities);
    first(adyascentes);
    //necesito sumar el origen, con cada uno de sus adyascentes, despues a cada uno de los resultantes necesito sumarle cada uno de los adyascentes
    //y asi hasta llegar al destino, luego hacer una lista con los nodos finales y sacar el mas conveniente, cada nodo debiera ser una lista para poder reconstruir el camino
    while (adyascentes->current!=NULL)
    {
        DHS((node*)adyascentes->current->data,cities);
        next(adyascentes);
    }*/
    
}

void bestRoute(char* a,char* b,char* c)
{
    printf("No pude implementar la funcion :'C\n");
    return;
}