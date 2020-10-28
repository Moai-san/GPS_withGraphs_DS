#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "treemap.h"
#include "City.c"

int main ()
{
    /*idea 1: tabla hash con clave ciudad, donde se guarde un arbol con las ciudades adyascentes ordenadas por distancia*/
    init_var();
    import("distances");
    nearest("Chicago");
}