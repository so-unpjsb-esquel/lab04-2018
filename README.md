# Laboratorio 4 - Administración de Memoria

## Ejercicio 1: Contador de páginas en _xv6_
Agregar a _xv6_ una llamada al sistema de nombre `pgcnt()` que retorne la cantidad de páginas en uso del proceso actual. El código de la llamada al sistema se encuentra en el archivo `sys_pgcnt.c`. El archivo `pgcnt.c` es un programa de usuario que invoca a esta llamada al sistema.

Modificar el programa `pgcnt.c` para acepte como argumento un número que indique la cantidad de páginas que tiene que reservar de memoria dinámicante. El programa debe imprimir primero cuantas páginas utiliza antes y despues de reservar más memoria. Por ejemplo, si se ejecuta pidiendo 5 páginas:
```
$ pgcnt 5
6
11
$
```
_Tip_: pueden usar las funciones `malloc()` o `sbrk()` para incrementar la memoria utilizada por el proceso.

### Entrega:
Copiar en el repositorio el archivo `pgcnt.c` modificado, con el código comentado explicando las modificaciones.

## Ejercicio 2: _Lazy allocation_ en _xv6_
Muchos programas reservan memoria que pueden no utilizar nunca, como por ejemplo, un arreglo de gran tamaño. El sistema operativo puede retrasar la asignación de memoria a estas secciones hasta que sean requeridos para su lectura/escritura. Cuando un proceso quiere acceder a estas secciones de memoria, ocurre un _page fault_ (fallo de página), y el sistema operativo carga las páginas requeridas desde disco, o bien reserva la memoria requerida. Una estrategia basada en este comportamiento se denomina _lazy allocation_. En este ejercicio vamos a implementar este esquema para la asignación de memoria dinámica en _xv6_.

### Parte 1
En _xv6_ los procesos piden más memoria al sistema por medio de la llamada a sistema `sbrk()`, implementada con la función `sys_sbrk()` en el archivo `sysproc.c`. 

Primero se eliminara la reserva de memoria que realiza `sys_sbrk()`, comentando la llamada a `growproc()`. De esta manera, sólo se incrementa la variable que indica tamaño del proceso (`proc->sz`) y se retorna el tamaño anterior, pero sin reservar efectivamente memoria.

Hecha esta modificación, compilar y ejecutar _xv6_ y ejecutar el comando `echo hola`.
- ¿Qué error aparece? ¿A qué tipo de error se refiere el número indicado por `trap`?

### Parte 2
Modificar el código en el archivo `trap.c`, para que ante un _page fault_, producido por un programa a nivel de usuario, realice la carga de la página correspondiente a la dirección de memoria virtual que causó el _page fault_. No se necesitan cubrir todos los casos posibles de error, debe bastar para ejecutar comando simples como `echo` o `ls`.

El código a agregar en `trap.c` se puede encontrar en el archivo `pgflt.txt`, que debe ser agregado en la función `trap()`, y realiza las siguients acciones:
- Para verificar si ocurrió un _page fault_, comprueba si `tf->trapno` es igual a `T_PGFLT`.
- Usa código de la función `allocuvm()` en el archivo `vm.c`, que es la función que invoca `growproc()`.
- Usa `PGROUNDDOWN()` para obtener la dirección base de la página física (marco).
- Invoca a `mappages()`, por lo que hay que eliminar la sentencia `static` de su declaración en el archivo `vm.c`, y agregar su prototipo en `trap.c`.

### Entrega
Copiar en el repositorio del Laboratorio el archivo `trap.c` modificado, y un archivo de texto donde se responda las preguntas de la Parte 1 del Ejercicio.

---

¡Fín del Laboratorio 4!