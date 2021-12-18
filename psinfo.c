#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int lencarpeta = strlen(argv[1]);
        int lenruta = 6 + lencarpeta + 7 + 1;
        char ruta[lenruta];
        strcpy(ruta, "/proc/");
        strcat(ruta, argv[1]);
        strcat(ruta, "/status");
        printf("la ruta es %s \n", ruta);

        FILE *archivo = fopen(ruta, "r");
        if (archivo == NULL)
        {
            write(STDERR_FILENO, "Error al abrir el archivo", 50);
            return (1);
        }

        size_t len = 0;
        char *line = NULL;

        //char **datos = malloc(sizeof(char*) * 9);
        char *datos[8];
        //datos[8] = NULL;
        int pos = 0;

        while (getline(&line, &len, archivo) != -1)
        {
            if (strstr(line, "Name") != NULL)
            {
                printf("pos0------%s", line);
                pos = 0;
            }
            else if (strstr(line, "State") != NULL)
            {
                printf("pos1------%s", line);
                pos = 1;
            }
            else if (strstr(line, "VmSize") != NULL)
            {
                printf("pos2------%s", line);
                pos = 2;
            }
            else if (strstr(line, "VmExe") != NULL)
            {
                printf("pos3------%s", line);
                pos = 3;
            }
            else if (strstr(line, "VmData") != NULL)
            {
                printf("pos4------%s", line);
                pos = 4;
            }
            else if (strstr(line, "VmStk") != NULL)
            {
                printf("pos5------%s", line);
                pos = 5;
            }
            else if (strstr(line, "voluntary_ctxt_switches") != NULL)
            {
                printf("pos6------%s", line);
                pos = 6;
            }
            else if (strstr(line, "nonvoluntary_ctxt_switches") != NULL)
            {
                printf("pos7------%s", line);
                pos = 7;
            }
            else
            {
                continue;
            }
            char *token = strsep(&line, ":");
            int lenline = strlen(line);
            datos[pos] = malloc(sizeof(char) * (lenline + 1));
            strcpy(datos[pos], line);
        }
        
        for (int i = 0; i < 8; i++)
        {
            printf("dato[ %d ] : %s\n", i, datos[i]);
            printf("i = %d\n",i);
            free(datos[i]);
        }
        //free(datos);

        fclose(archivo);

        return (0);
    }
    else
    {
        write(STDERR_FILENO, "Numero de argumentos invalido", 50);
        return (1);
    }
}