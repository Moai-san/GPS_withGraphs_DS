#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "treemap.h"
#include "list.h"

HashMap* cities;//lista ciudades

/*initializes all the variables*/
void init_var()
{
    cities =(HashMap*)calloc(1,sizeof(HashMap)); 
    cities =createMap(10);
}


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
        //printf("%s\t%s\t%d\n",Acity,Bcity,*distance); //printeo para verificar valores, se eliminara en version final
    }
}

void nearest(char* cityName)
{
    TreeMap* adjCities = searchMap(cities,cityName);
    printf("La ciudad mas cercana a %s es %s\n",cityName,(char*)firstTreeMap(adjCities));
}

int get_adj(char* cityName)
{
    TreeMap* adjCities = searchMap(cities,cityName);
    TreeNode* currentNode =(TreeNode*)calloc(1,sizeof(TreeNode));
    firstTreeMap(adjCities);
    currentNode =adjCities->current;
    printf("lista de ciudades adyascentes a %s\n",cityName);
    int pos =0; //posicion en pantalla
    while(currentNode!=NULL)
    {
        printf("%d - %s\t%d KM\n",pos,(char*)currentNode->value,*(int*)currentNode->key);
        pos++;
        nextTreeMap(adjCities);
        currentNode =adjCities->current;
    }
}

void createRoute(char* cityName)
{
    int option;
    int distance =0;
    TreeNode* currentNode =(TreeNode*)calloc(1,sizeof(TreeNode));
    TreeMap* adjCities = searchMap(cities,cityName);
    List* cityList =create_list();
    while(1)
    {
        push_back(cityList,cityName);
        get_adj(cityName);
        printf("ingrese numero de la ciudad siguiente,si no quiere seguir añadiendo ciudades a la ruta, escriba -1\n");
        scanf("%d",&option);
        if (option==-1)
        {
            break;
        }
        firstTreeMap(adjCities);
        currentNode =adjCities->current;
        for (int i =0;i<option;i =(i+1))
        {
            nextTreeMap(adjCities);
            currentNode =adjCities->current;
        }
        distance =distance+(*(int*)currentNode->key);
        cityName =(char*)currentNode->value;
        adjCities = searchMap(cities,cityName);
    }
    system("reset");
    printf("Distancia Recorrida: %d KM\n",distance);
    printf("Ciudades por las que pasaste\n");
    first(cityList);
    for(int i =0;i<cityList->count;i =(i+1))
    {
        printf("%s\n",(char*)cityList->current->data);
        next(cityList);
    }
}