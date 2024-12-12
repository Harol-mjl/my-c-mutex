#include "my_lib.h"

/**
 * Count the number of characters in a string
 * @param *str: Pointer to the string whose length need to be counted 
 * @return number of characters in the string, not including character null
 */
size_t my_strlen(const char *str){
  int num_bytes = 0;
  
  while(*str++){
    num_bytes = num_bytes + 1;
  }
  return num_bytes;
}

/**
 * Compare two strings character by cahracter. If a characters are diferents,
 * the function return which string is greater or lesser based on the ASCII values.
 *
 *@param str1: Pointer to the first string to be compare
 *@param str2: Pointer to the second string to compare with the first one
 *@return: >0 if str1 is greater than str2
 *       : <0 if str1 is less than str2
 *       : 0 if str1 and str2 are equal
 */
int my_strcmp(const char *str1 , const char *str2){
  while(*str1 && *str2){
    if(*str1 != *str2){
      return (int)*str1 - (int)*str2;
    }
    str1++;
    str2++;
  }
  return (int)(*str1 - *str2);
}

/**
 * Copies the string from src inside the memory pointed by dest
 *
 *@param dest: Pointer to the destination where the string will be copied.
 *@param src:  Pointer to the source string to be copied.
 *@return the pointer to the first character of dest.
 */

char *my_strcpy(char *dest, const char *src){
  char *origin_dest = dest;
  
  while(*src){
    *dest++ = *src++;
  }
  *dest = '\0';
  return origin_dest;
}

/*
 * Replaces the characters in 'dest' with the 'n' characters from 'src'
 * if 'n' is greater than 'strlen(src), the remaining character in 'dest' will be set to 0's
 *
 * @param dest: Pointer to the destination where the characters from 'src' will be copied
 * @param src: Pointer to the source string to copy
 * @param m: the number of characters to copy form 'src' to 'dest,
 *
 */
char *my_strncpy(char *dest, const char *src, size_t n){
  char *origin_dest = dest;
  int contador = 0;
  
  if (n > strlen(src)){
    memset(dest, 0, n);
  }
  
  while(*src && contador < n){
    *dest++ = *src++;
    contador++;
  }

  return origin_dest;
}

/*
 * Copies te string from i'src' to the end of the string 'dest' overwriting the null character of 'dest'.
 * @param dest: Pointer to the destination where the 'src' string will be concatenated to'dest'
 * @param src: Pinter to the string to the concatenated with 'dest'
 * @return: the first position of 'dest' saved in 'origin_dest'
 */

char *my_strcat(char *dest, char const *src){
  char *origin_dest = dest;
  //Move the pointer "dest" until the null character   
  while(*dest){
    dest++;
  }
  while(*src){
    *dest++ = *src++; 
  }
  //add the character null at the final of the concatenated string
  *dest = '\0';

  return origin_dest;
}

/*
 * Move the pointer character to character until to find the first chataracter like c into str
 *
 * @param str: Pointer to the string in which we search the character 'c'
 * @param c: Character in code ASCII to find.
 * return: the pointer to the first character 'c' in the string or null if not found;
 */
char *my_strchr(const char *str, int c){
  while(*str++){
    if(*str == (char)c){
      return (char*)str;
    }
  }
  return NULL;
};

struct my_stack *my_stack_init(int size){
	//En cado de que nos pasen un tamaño menor o igual a 0, la pila no se creará y
	//devolverá null
	if(size < 1){
		return NULL;
	}
	//Reservamos memoria para la ms(my stack) de 16 bytes
	struct my_stack *ms = malloc(sizeof(struct my_stack));

	//iniciamos el top de ms a null y el tamaño al que nos pasan como segundo parametro
	ms -> top = NULL;
	ms -> size = size;
	//devolvemos la pila creada
	return ms;
}

int my_stack_push(struct my_stack *stack, void *data){
	//Comprobamos que la pila pasada por parametro existe
	if(stack == NULL){
		perror("La pila pasada por parametro no existe");
		return -1;
	}
	//comprobamos que el tamaño de la pila sea mayor que 0
	if(stack->size < 0){
		perror("El parametro size de la pila es < a 0");
	}
	//Reservamos memoria para el nodo de 16 bytes
	struct my_stack_node *node_aux = malloc(sizeof(struct my_stack_node));
	// En caso de que la pila este vacia el primer nodo introducido
	// en la pila apuntará a null ya que top apunta a null
	// En el cado de que la pila tenga por lo menos 1 node, el next del nuevo nodo
	// apuntará al anterior
	node_aux -> next = stack -> top;
	node_aux -> data = data;
	//Con la siguiente linea hacemos que el top de la pila apunte al nuevo nodo introducido
	stack -> top = node_aux;

	return 0;
}

void *my_stack_pop(struct my_stack *stack){
	//Comprobamos que la pila existe
	if(stack == NULL){
		perror("La pila no existe");
		return NULL;
	}
	//Comprobamos que la pila tiene almenos un elemento para poder extraer
	if(stack->top == NULL){
		perror("La pila esta vacia, no se pueden extraer elementos");
		return NULL;
	}
	//Nodo auxiliar que apuntará donde apunta top
	struct my_stack_node *node_aux = stack->top;
	//Guardamos el data del nodo top
	void *last_data = node_aux->data;
	//Cambiamos el apuntador del nodo top al siguiente
	stack->top=stack->top->next;
	//liberamos la memoria del nodo apuntado por node_aux
	free(node_aux);
	//devolvemos el valor guardado del ultimo nodo lierado
	return last_data;
}

int my_stack_len(struct my_stack *stack){
	//Comprobamos que la pila existe
	if(stack == NULL){
		perror("la pila no existe");
		return -1;
	}
	//nodo auxiliar que apuntará al nodo que apunta top
	struct my_stack_node *node_aux = stack->top;
	//iniciamos contador a 0
	int contador = 0;
	//mientras el nodo_aux sea diferente del NULL(que la pila no tenga mas nodos)
	//el contador se sumara en uno
	while(node_aux != NULL){
		contador += 1;
		//Cambiamos el nodo aux para que pase al siguiente nodo
		node_aux = node_aux->next;
	}
	//Devolvemos el resultado del contador;
	return contador;
}

int my_stack_purge(struct my_stack *stack){
	//comprobamos que la pila existe
	if(stack == NULL){
		perror("La pila no existe");
		return 0;
	}
	//Iniciamos bytes_liberados a 0
	int bytes_liberados = 0;
	//Creamos un nodo auxiliar que apuntará al nodo que apunte el top del stack
	struct my_stack_node *node_aux = stack->top;
	//mientras ese nodo no sea igual a NULL recorrerá todos los nodos
	while(node_aux != NULL){
		//metemos dentro de bytes liberados el tamaño de un my_stack_node que son 16 bytes
		bytes_liberados += sizeof(*node_aux);
		// Dentro te ese nodo tenemos un data que añadimos mediante la funcion my_stack_push
		// Al liberar el nodo esta memoria reservada para el data tambien se eliminará
		// el tamaño de esos bytes para datos se guardan dentro del size a la hora de crear
		// la pila con la funcion my_stack_init() por lo tanto debemos sumarlos a la hora de
		// eliminar un nodo.
		bytes_liberados += stack->size;
		//cambiamos el puntero top al siguiente nodo
		stack -> top= node_aux->next;
		//liberamos la momeria reservada del nodo
		free(node_aux);
		node_aux = stack->top;
	}
	//Tambien necesitamos liberar la memoria de la pila que asignamos mediante la funcion
	//my_stack_init y tambien se tiene que añadir el tamaño de esa memoria asignada al
	//total de bytes liberados
	bytes_liberados += sizeof(*stack);
	free(stack);
	//devlvemos lo bytes liberados
	return bytes_liberados;
}

int my_stack_write(struct my_stack *stack, char *filename){
	//Comprobamos que la pila existe
	if (stack == NULL){
		perror("La pila no existe");
		return -1;
	}
	//O_WRONLY = Abre el fichero en modo de solo escritura
	//O_CREAT  = Crea el archivo si no existe
	//O_TRUNC  = Si el archivo existe, borrará todo su contenido
	//S_IRUSR  = Permiso de lectura, solo para el propietario del archivo
	//S_IWUSR  = Permiso de escritura, solo para el propietario del archivo
	int fd = open(filename,O_WRONLY | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR);
	//Si el fd(file descriptor) es menor que 0 es que ha ocurrido un error al abrir el archivo
	if(fd < 0){
		perror("Error al abrir el fichero");
		return -1;
	}
	//Para poder recuperar los datos en un orden correcto desde el fichero debemos
	//invertir la pila lo hacemos creando una pila auxiliar
	struct my_stack *ms_aux = my_stack_init(stack->size);
	struct my_stack_node *node_aux = stack->top;
	while(node_aux != NULL){
		void *data2 = node_aux->data;
		my_stack_push(ms_aux,data2);
		node_aux = node_aux ->next;
	}
	ssize_t bytes_escritos = 0;
	int contador_nodo = 0;

	//para escribir los datos en el fichero necesitamos usar la funcion write
	//que necesitamos 3 parametros
	//(file descriptor),(Datos que queremos escribir),(El tamaño de esos datos)
	//Lo primero que escribamos en el fichero será el size de la pila
	//ya que sin esto no podremos restaurar la pila
	bytes_escritos = write(fd,&stack->size,sizeof(int));
	//En el caso de que no se haya podido escribir el size en el fichero write devolverá
	//un número negativo, este será el indicador de que ha habido un error.
	if(bytes_escritos < 0){
		perror("Error al escribir el tamaño de los nodos");
		return -1;
	}
	//Recorremos la pila auxiliar y metemos los datos dentro del fichero
	//incrementadmos en 1 contador_nodo cada vez que pasamos por un nodo
	node_aux = ms_aux->top;
 	while(node_aux != NULL){
		void *data_aux = node_aux->data;
		bytes_escritos = write(fd,data_aux, stack->size);
		if(bytes_escritos < 0){
			perror("Error al escribir un nodo dentro del fichero");
			return -1;
		}
		contador_nodo += 1;
		node_aux = node_aux->next;
	}
	//Liberamos el espacio que reservamos para invertir la pila
	my_stack_purge(ms_aux);
	//Cerramos el file descriptor
	close(fd);
	//devolvemos el total de nodos que tiene la pila
	return contador_nodo;
}

struct my_stack *my_stack_read(char *filename){
	//Abrimos el fichero con open con el flag que nos permite solo leer
	int fd = open(filename,O_RDONLY);
	//Comprobamos que no hay ningun error a la hora de abir el fichero
	if(fd < 0){
		perror("Error al abrir el fichero");
		return NULL;
	}
	int size;
	ssize_t bytes_leidos = 0;
       	//El primer elemento del fichero es el size de la pila, que necesitamos para restaurar la pila
	bytes_leidos = read(fd,&size,sizeof(int));
	//Comprobamos que no hay ningun error a la hora de buscar el size de la pila
	if(bytes_leidos < 0){
		perror("Error en la lectura del size del fichero");
		return NULL;
	}
	//Creamos la pila con la funcion my_stack_init y con el size guardado anteriormente
	struct my_stack *ms = my_stack_init(size);
	//reservamos memoria para los datos;
	void *data = malloc(size);
	// comprobamos que no hay ningun error a la hora de reservar memoria para los datos
	if(data == NULL){
		perror("Error al reservar memeria para los datos");
		return NULL;
	}
	//Recorremos la pila hasta el final.
	//Cuando llegamos al final la funcion read nos devuelve 0
	while(read(fd,data,size)>0){
		//Añadimos ese dato dentro de la pila y reservamos memoria para el proximo dato
		my_stack_push(ms,data);
		data = malloc(size);
		if(data == NULL){
			perror("Error al reservar memoria para los datos");
			return NULL;
		}
	}
	//Cerramos el file descriptor
	close(fd);
	//devolvemos la pila con los datos cargados desdel el fichero
	return ms;
}
