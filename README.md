# Para los tests

## Opción 1: Compilar y Ejecutar desde CLion

## Opción 2:

### Compilación:

1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`

### Ejecución:

Desde el inicio del proyecto:

1. `cd build/`
2. `./correrTests`

############################

# Para la interfaz gráfica

# Dependencias

Se necesitan dependencias que pueden ser instaladas en Ubuntu corriendo el siguiente comando en una terminal:

    sudo apt install libsdl2-dev libsdl2-image-dev
    
# Para compilar con la interfaz gráfica, descomentar la línea 7 del archivo CMakeLists.txt

## Opción 1: Compilar y Ejecutar desde CLion

## Opción 2:

### Compilación:

Si ya se creó la carpeta `build`, es necesario borrarla:

    `rm -r build`

Luego:

1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`

### Ejecución:

Desde el inicio del proyecto:

1. `cd build/`
2. `./sokobanGUI`

