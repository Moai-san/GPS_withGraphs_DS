#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "treemap.h"

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
        printf("%s\t%s\t%d\n",Acity,Bcity,*distance); //printeo para verificar valores, se eliminara en version final
    }
}

void get_adj(char* cityName)
{
    TreeMap* adjCities = searchMap(cities,cityName);
    TreeNode* currentNode =createTreeNode;
    currentNode =firstTreeMap(adjCities);
    while(currentNode!=NULL)
    {
        
        currentNode =nextTreeMap(adjCities);
    }
}