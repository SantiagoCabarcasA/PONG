### `INSTRUCCIONES DE USO`
**`Jugador 1`**: Usa las teclas **`W`** (arriba) y **`S`** (abajo) para mover la paleta

**`Jugador 2`**: Usa las teclas **`I`** (arriba) y **`K`** (abajo) para mover la paleta

Para detener el juego presiona la tecla **`Q`**

El juego empieza cuando alguno de los dos jugadores mueve su paleta, por lo que la pelota se moverá en una dirección aleatoria hasta rebotar con una pared o una paleta

El objetivo es hacer que la pelota toque la pared del oponente y evitar que toque tu lado de la pared

El juego no tiene puntuación límite por lo que la partida podrá durar lo que gusten los jugadores


### `DESCRIPCIÓN DEL CÓDIGO`

El `enum eDir` define las posibles direcciones en las que la pelota puede moverse, las cuales son:

- **`PARAR`**: La pelota está detenida
- **`IZQUIERDA`**: Movimiento hacia la izquierda
- **`DERECHA`**: Movimiento hacia la derecha
- **`ARRIBA_IZQUIERDA`**: Movimiento diagonal hacia arriba a la izquierda
- **`ABAJO_IZQUIERDA`**: Movimiento diagonal hacia abajo a la izquierda
- **`ARRIBA_DERECHA`**: Movimiento diagonal hacia arriba a la derecha
- **`ABAJO_DERECHA`**: Movimiento diagonal hacia abajo a la derecha


### 2. Clase `cPelota`

La clase `cPelota` representa la pelota en el juego. Sus atributos y métodos son:

#### Atributos:
- **`x`, `y`**: Coordenadas actuales de la pelota
- **`xOriginal`, `yOriginal`**: Coordenadas iniciales de la pelota (se usan para restablecer la posición)
- **`direccion`**: Dirección actual en la que se mueve la pelota

#### Métodos:
- **`Reiniciar()`**: Restablece la pelota a su posición inicial y la detiene
- **`cambiarDireccion(eDir d)`**: Cambia la dirección de la pelota
- **`direccionAleatoria()`**: Asigna una dirección aleatoria a la pelota
- **`Mover()`**: Mueve la pelota en la dirección indicada
- **`operator<<`**: Sobrecarga del operador `<<` para imprimir la posición y dirección de la pelota

### 3. Clase `cPaleta`

La clase `cPaleta` representa las paletas de los jugadores. Sus atributos y métodos son:

#### Atributos:
- **`x`, `y`**: Coordenadas actuales de la paleta
- **`xOriginal`, `yOriginal`**: Coordenadas iniciales de la paleta (para restablecer su posición)

#### Métodos:
- **`Reiniciar()`**: Restaura la paleta a su posición original
- **`moverArriba()`**: Mueve la paleta hacia arriba
- **`moverAbajo()`**: Mueve la paleta hacia abajo

### 4. Clase `cAdminJuego`

La clase `cAdminJuego` se encarga de manejar el juego, incluyendo la lógica del movimiento, las colisiones, y las puntuaciones. Los atributos y métodos de esta clase son:

#### Atributos:
- **`ancho`, `alto`**: Dimensiones del área de juego
- **`puntuacion1`, `puntuacion2`**: Puntuaciones de los jugadores
- **`arriba1`, `abajo1`, `arriba2`, `abajo2`**: Teclas asignadas para controlar las paletas de los jugadores
- **`salir`**: Bandera que controla cuándo terminar el juego
- **`pelota`**, **`jugador1`**, **`jugador2`**: Punteros a los objetos de la pelota y las paletas

#### Métodos:
- **`aumentarPuntuacion(cPaleta* jugador)`**: Incrementa la puntuación del jugador y restablece las posiciones de la pelota y las paletas
- **`limpiarPantalla()`**: Limpia la pantalla para evitar parpadeos y actualizar el área de juego
- **`Dibujar()`**: Dibuja el área de juego, la pelota, las paletas y las puntuaciones
- **`Entrada()`**: Lee las teclas presionadas por los jugadores y mueve las paletas
- **`Logica()`**: Implementa la lógica del movimiento de la pelota, las colisiones con las paletas y las paredes, y la actualización de la puntuación
- **`Ejecutar()`**: Es Bucle principal del juego y llama a los métodos `Dibujar()`, `Entrada()` y `Logica()` de forma continua para mantener el juego ejecutandose

### 5. Función `OcultarCursor()`

Oculta el cursor de la consola para una mejor experiencia de juego






