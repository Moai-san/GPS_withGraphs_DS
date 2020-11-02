#include <stdio.h>
#include "list.h"
#include "hashtable.h"
//#include "City.c"

/*System Condition, only if it's Compiled in windows, includes the library*/
#ifdef _WIN32
    #include <windows.h>
#endif

/*Cleans The Screen (yup, i know that is obvious, but i have to comment that)*/
void clear_Screen()
{
    #ifdef _WIN32
    {
        system("cls");
    }
    #else
    {
        system("reset");
    }
    #endif
}

/*Menu (yup, i know that is obvious, but i have to comment that)*/
int menu ()
{
    printf("Bienvenid@ a tu nuevo GPS! OwO\nQue te gustaria hacer hoy?(\'w\')\na)Importar Archivo TXT\nb)Mostrar la ciudad mas cercana a \'x\' ciudad\nc)Crear una ruta desde \'x\' ciudad\nd)Ruta mas corta entre 2 ciudades\ne)Mejor ruta que pasa por 3 ciudades\nf)Limpiar la pantalla\nSi no quieres nada, solo presiona la tecla enter uwu\n");
    char option;
    short int flag;
    flag =(-1);
    char garbageBin;//papelera para la basura que se situa en stdin
    do
    {
        if (flag==(1))
        {
            printf("Te gustaria Hacer algo Mas?(\'w\')\na)Importar Archivo TXT\nb)Mostrar la ciudad mas cercana a \'x\' ciudad\nc)Crear una ruta desde \'x\' ciudad\nd)Ruta mas corta entre 2 ciudades\ne)Mejor ruta que pasa por 3 ciudades\nf)Limpiar la pantalla\nSi no quieres nada, solo presiona la tecla enter uwu\n");
        }
        scanf("%c",&option);
            switch (option)
            {
                case 'a': //caso a, importar archivo
                {
                    char* file;
                    file =((char*)calloc(105,sizeof(char)));
                    printf("Ingresa el nombre del archivo a importar! OwO (nombre sin el formato) uwu \n");
                    scanf("%c",&garbageBin);
                    scanf("%[^\n]",file);
                    clear_Screen();
                    import(file);
                    break;
                }
                case 'b': //caso b, mostrar ciudad mas cercana
                {
                    char* name;
                    name =((char*)calloc(105,sizeof(char)));
                    printf("Ingrese el nombre de la ciudad uwu \n");
                    scanf("%c",&garbageBin);
                    scanf("%[^\n]",name);
                    clear_Screen();
                    nearest(name);
                    break;
                }
                case 'c': //caso c, crear ruta desde x ciudad
                {
                    char* name;
                    name =((char*)calloc(105,sizeof(char)));
                    printf("Ingrese ciudad de origen uwu \n");
                    scanf("%c",&garbageBin);
                    scanf("%[^\n]",name);
                    clear_Screen();
                    createRoute(name);
                    break;
                }
                case 'd': //caso d, ruta mas corta entre 2 ciudades
                {
                    char cityA [105];
                    char cityB [105];
                    printf("Ingrese ciudad de origen\n");
                    scanf("%c",&garbageBin);
                    scanf("%[^\n]",cityA);
                    printf("Ingrese ciudad de destino\n");
                    scanf("%c",&garbageBin);
                    scanf("%[^\n]",cityB);
                    clear_Screen();
                    shortestRoute(cityA,cityB);
                    break;
                }
                case 'e': //caso e, mejor ruta que pasa por 3 ciudades
                {
                    char cityA [105];
                    char cityB [105];
                    char cityC [105];
                    printf("Ingrese ciudad A\n");
                    scanf("%c",&garbageBin);
                    scanf("%[^\n]",cityA);
                    printf("Ingrese ciudad B\n");
                    scanf("%c",&garbageBin);
                    scanf("%[^\n]",cityB);
                    printf("Ingrese ciudad C\n");
                    scanf("%c",&garbageBin);
                    scanf("%[^\n]",cityC);
                    clear_Screen();
                    bestRoute(cityA,cityB,cityC);
                    break;
                }
                case 'f': //caso f, limpiar pantalla
                {
                    clear_Screen();
                    break;
                }
                case '\n': //caso enter, cambia el flag
                {
                    flag =(0);
                    break;
                }
                default: //caso cualquier otra tecla (excepto la ñ, que no la toma como letra, me parece que por el numero en la tabla ascii)
                    clear_Screen();
                    printf("Entrada invalida!");
                    break;
            }
            if (flag!=0)
            {
                scanf("%c",&garbageBin);//llamada a la papelera para la basura que se situa en stdin
                flag =(1);
            }
    }
    while (flag!=(0)); //si el flag es 0 (apretaron enter), se corta el while y cierra el programa
    return(0);
}