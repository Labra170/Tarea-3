#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"
#include "list.h"

typedef struct { // Estructura del libro
  char titulo[101];
  int cantPalabras;
  char autor[101];
  int cantCaracteres;
  char  IP[10];
}Libro;

// Función para cargar un libro desde un archivo
void cargar(const char *nombreArchivo, Libro *libro, HashMap* mapaLibros) {
  FILE *file = fopen(nombreArchivo, "r"); // Se abre el archivo en modo lectura
  if (file == NULL) { // Si no se pudo abrir se retorna.
    printf("No se pudo abrir el archivo: %s\n", nombreArchivo);
    return;
  }

  // Inicializar los valores del libro
  strcpy(libro->titulo, "");
  strcpy(libro->autor, "");
  libro->cantPalabras = 0;
  libro->cantCaracteres = 0;
  strcpy(libro->IP, nombreArchivo);

  char linea[256];
  while (fgets(linea, sizeof(linea), file)) {
    if (strstr(linea, "Title: ") != NULL) { // Para conseguir el titulo
      sscanf(linea, "Title: %101[^\n]", libro->titulo);
    } else if (strstr(linea, "Author: ") != NULL) { // Para conseguir el autor
      sscanf(linea, "Author: %101[^\n]", libro->autor);
    } else { // Para el conteo de palabras y caracteres
      char *palabra = strtok(linea, " \t\n");
      while (palabra != NULL) {
        libro->cantPalabras++;
        libro->cantCaracteres += strlen(palabra);
        palabra = strtok(NULL, " \t\n");
      }

    }
  }
  insertMap(mapaLibros, libro->titulo, libro);

  fclose(file);
}

void cargarDocumento(HashMap*mapaLibros) // Función 1
{
  Libro * biblioteca = (Libro*)malloc(101*sizeof(Libro));
  int cont = 0;
  printf("Ingrese el nombre de los archivo: \n");
  printf("Ingrese 'salir' para terminar el proceso.\n");
  while (cont < 101) {//101 por que el doc es d 100 archivos
    
    char nombreArchivo[101];
    scanf("%s", nombreArchivo);//lee el nombre del archivo a cargar

    if (strcmp(nombreArchivo, "salir") == 0) {//ingrese salir de la wea
      break ;
    }

    cargar(nombreArchivo, &biblioteca[cont], mapaLibros); //llama a la funcion cargar 
    cont++;
  }
  free(biblioteca);
  return;
}



void mostrarOrdenados(HashMap *mapaLibros) // Función 2
{
  Pair *current = firstMap(mapaLibros); // Puntero al inicio del mapa
  int contadorEspacioMapa = 0; // Contador para los espacios ocupados en el mapa
  Libro* actual; // Para usar la "casilla" value, del pair.

  while (current != NULL) // Mientras hayan espacios usados
    {
      contadorEspacioMapa = contadorEspacioMapa + 1; // Se aumenta el contador en 1
      current = nextMap(mapaLibros); // Se avanza al siguiente espacio
    }

  Libro* librosOrdenados[contadorEspacioMapa]; // Una lista estática para ordenar los libros
  current = firstMap(mapaLibros); // Puntero al inicio del mapa
  for (int i = 0; i < contadorEspacioMapa; i++) // Recorrer la lista
    {
      actual = current->value; // Copiar el value, en la variable actual, para acceder a los datos del struct
      strcpy(librosOrdenados[i]->IP, actual->IP); // Se copia la IP/ID
      strcpy(librosOrdenados[i]->titulo, actual->titulo); // Se copia el título
      librosOrdenados[i]->cantPalabras = actual->cantPalabras; // Se copia la cantidad de palabras
      librosOrdenados[i]->cantCaracteres = actual->cantCaracteres; // Se copia la cantidad de caracteres
      current = nextMap(mapaLibros); // Se avanza al siguiente espacio en el mapa
    }
  // Implementar la función QuickSort
}

void buscarTitulo(HashMap*mapaLibros)
{// Funcion 3
  char buscar[100];
  printf("Ingrese el titulo del libro.\n");
  if(fgets(buscar, sizeof(buscar), stdin)!=NULL)//lee la cadena completa 
  {
    char *palabra=strtok(buscar, "\t\n");//para ir separando la cadena por espacios
  
    while (palabra!=NULL){//recorrer las cadenas separadas por espacios
    
      printf("%s\n", palabra);  
      int encontrado=0;//variable booleana para saber cuando se encuentra el titulo correspondiente 
      //recorrer la tabla para encontrar coincidencias
      Pair* actual =firstMap(mapaLibros);
      while (actual !=NULL){//recorre la lista de libros para buscar coincidencias con lo ingresado
        Libro *libro=(Libro*)actual->value;
        if(strstr(libro->titulo, palabra)!=NULL){//comparacion
        
          printf("Titulo: %s\n", libro->titulo);
          encontrado=1;//cambio de la variable booleana cuando ya fue encontrado el libro
          break;
        }
        actual=nextMap(mapaLibros);//pasa al siguiente libro si no fue encontrada 
      }

      if (!encontrado){
        printf("No se encontraron coincidencias.");
      }
      palabra=strtok(NULL, "\t\n");//pasa a la siguiente cadena de caracteres para seguir comaparando 
    }  
  }
}

void palabrasMayorFrecuencia() // Función 4
{
  
}

void palabrasMasRelevantes() // Función 5
{
  
}

void buscarPalabra() // Función 6
{
  
}

void mostrarContexto() // Función 7
{
  
}

void proceso(int opcion)
{
  long capacidad = 100;//se lee un drive de 100 libros xd
  HashMap* mapaLibros = createMap(capacidad);
  switch(opcion)
    {
      case 1:
        cargarDocumento(mapaLibros);
        break;
      case 2:
        mostrarOrdenados(mapaLibros);
        break;
      case 3:
        buscarTitulo(mapaLibros );
        break;
      case 4:
        palabrasMayorFrecuencia();
        break;
      case 5:
        palabrasMasRelevantes();
        break;
      case 6:
        buscarPalabra();
        break;
      case 7:
        mostrarContexto();
        break;
      case 0:
        printf("\nPrograma finalizado\n");
        break;
      default:
        printf("\nOpción no valida\n");
        break;
    }
  printf("\n-----------------------\n");
}

void menu()
{
  int opcion;
  do
    {
      printf("\nBienvenido al buscador de texto\n");
      printf("Elige una opción\n");
      printf("\nOpción 1: Cargar documentos");
      printf("\nOpción 2: Mostrar documentos ordenados");
      printf("\nOpción 3: Buscar libro por título");
      printf("\nOpción 4: Palabras con mayor frecuencia");
      printf("\nOpción 5: Palabras más relevantes");
      printf("\nOpción 6: Buscar por palabra");
      printf("\nOpción 7: Mostrar palabras en su contexto dentro del libro");
      printf("\nOpción 0: Salir del programa\n");
      printf("\nOpción: ");
      scanf(" %d", &opcion);
      printf("\n-----------------------\n");

      proceso(opcion);
      
    }while(opcion != 0);
}



int main()
{
  menu();
  return 0;
}
