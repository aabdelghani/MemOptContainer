
# Custom Dynamic Array Implementation in C

## Overview

This project implements a custom dynamic array in C with functionalities such as initialization, insertion, deletion, access, and resizing. The project also includes a memory pool for efficient memory management.

## Project Structure

```
/your_project
|-- CMakeLists.txt
|-- custom_array.h
|-- custom_array.c
|-- main.c
```

## Requirements

- CMake 3.10 or higher
- A C compiler (e.g., GCC)

## Getting Started

### Building the Project

1. **Clone the repository** (if applicable) or download the project files.

2. **Create a build directory**:

   ```sh
   mkdir build
   cd build
   ```

3. **Run CMake to generate the build system files**:

   ```sh
   cmake ..
   ```

4. **Build the project**:

   ```sh
   cmake --build .
   ```

### Running the Executable

After building, you can run the executable `main`:

```sh
./main
```

### Example Output

```
Initial elements:
10 20 30 40 
After deleting element at index 1:
10 30 40 
```

## File Descriptions

- `CMakeLists.txt`: CMake configuration file to build the project.
- `custom_array.h`: Header file containing the declarations of the custom array functions and structures.
- `custom_array.c`: Source file containing the implementation of the custom array functions.
- `main.c`: Source file containing the main function to test the custom array implementation.

## Functions

### Initialization

```c
void initArray(CustomArray *array, size_t initial_capacity);
```

Initializes the dynamic array with a specified initial capacity.

### Insertion

```c
void insertElement(CustomArray *array, int element);
```

Adds an element to the array, expanding its capacity if necessary.

### Deletion

```c
void deleteElement(CustomArray *array, size_t index);
```

Removes an element from the array and compacts the memory.

### Access

```c
int getElement(CustomArray *array, size_t index);
```

Accesses an element by its index.

### Resizing

```c
void resizeArray(CustomArray *array, size_t new_capacity);
```

Dynamically resizes the array to a new capacity.

### Freeing Memory

```c
void freeArray(CustomArray *array);
```

Frees the memory allocated for the array.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
