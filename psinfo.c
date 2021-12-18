#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int pillarDatos(char *nombreFichero, int modo)
{
    int lencarpeta = strlen(nombreFichero);
    int lenruta = 6 + lencarpeta + 7 + 1;
    char ruta[lenruta];
    strcpy(ruta, "/proc/");
    strcat(ruta, nombreFichero);
    strcat(ruta, "/status");
    //printf("la ruta es %s \n", ruta);

    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL)
    {
        return (1);
    }

    size_t len = 0;
    char *line = NULL;

    while (getline(&line, &len, archivo) != -1)
    {
        if (strstr(line, "Name") != NULL)
        {
            printf("%s", line);
        }
        else if (strstr(line, "State") != NULL)
        {
            printf("%s", line);
        }
        else if (strstr(line, "VmSize") != NULL)
        {
            printf("%s", line);
        }
        else if (strstr(line, "VmExe") != NULL)
        {
            printf("%s", line);
        }
        else if (strstr(line, "VmData") != NULL)
        {
            printf("%s", line);
        }
        else if (strstr(line, "VmStk") != NULL)
        {
            printf("%s", line);
        }
        else if (strstr(line, "voluntary_ctxt_switches") != NULL)
        {
            printf("%s", line);
        }
        else if (strstr(line, "nonvoluntary_ctxt_switches") != NULL)
        {
            printf("%s", line);
        }
    }

    fclose(archivo);

    return (0);
}

/*
Devuelve el numero total de caracteres que tiene un arreglo de strings desde la posicion 2, nunca se cuenta el caracter de fin de string de ninguno de los strings en el arreglo.
*/
int numeroLetras(char *arreglo[], int tamanoArreglo)
{
    int sum = 0;
    for (int i = 2; i < tamanoArreglo; i++)
    {
        sum += strlen(arreglo[i]);
    }
    return sum;
}
/*
Devuelve el nombre para el reporte de psinfo -r, el nombre será escrito en nombreArchivo
*/
char *getNombreReporte(char *arreglo[], int tamanoArreglo, char nombreArchivo[])
{
    strcpy(nombreArchivo, "psinfo-report");
    for (int i = 2; i < tamanoArreglo; i++)
    {
        strcat(nombreArchivo, "-");
        strcat(nombreArchivo, arreglo[i]);
    }
    strcat(nombreArchivo, ".info");
    return (nombreArchivo);
}

int getInfoProcesos(int argc, char *argv[], int modo)
{
    for (int i = 2; i < argc; i++)
    {
        printf("\nPid: %s", argv[i]);
        if (pillarDatos(argv[i],modo) == 1)
        {
            printf("Error al abrir el archivo %s\n", argv[i]); //error
            return(1);
        }
    }
    return(0);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Psinfo necesita argumentos\n"); //error
        exit(1);
    }
    else
    {
        if (strstr(argv[1], "-l"))
        {
            int modo = 0;
            if (argc < 3)
            {
                printf("Psinfo -l necesita uno o mas argumentos\n"); //error
                exit(1);
            }
            for (int i = 2; i < argc; i++)
            {
                printf("\nPid: %s", argv[i]);
                if (pillarDatos(argv[i]) == 1)
                {
                    printf("Error al abrir el archivo %s\n", argv[i]); //error
                    exit(1);
                }
            }
            exit(0);
        }
        else if (strstr(argv[1], "-r"))
        {
            int modo = 1;
            if (argc < 3)
            {
                printf("Psinfo -r necesita uno o mas argumentos\n"); //error
                exit(1);
            }
            int lenNombres = numeroLetras(argv, argc); //psinfo-report-10898-1342.info
            char nombreArchivo[13 + argc + lenNombres + 5 + 1];
            getNombreReporte(argv, argc, nombreArchivo);
            FILE *reporte = fopen(nombreArchivo, "w+");
            if (reporte == NULL)
            {
                printf("El reporte %s no existe\n", nombreArchivo); //error
                exit(1);
            }
            for (int i = 2; i < argc; i++)
            {
                printf("\nPid: %s", argv[i]);
                if (pillarDatos(argv[i]) == 1)
                {
                    printf("Error al abrir el archivo %s\n", argv[i]); //error
                    exit(1);
                }
            }
            fclose(reporte);
        }
        else
        {
            if (argc != 2)
            {
                printf("Numero de argumentos invalido\n"); //error
                exit(1);
            }

            if (pillarDatos(argv[1]) == 1)
            {
                printf("Error al abrir el archivo\n"); //error
                exit(1);
            }
            exit(0);
        }
    }
}