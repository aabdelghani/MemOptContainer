
Custom Memory Container
========================================

Overview
--------
This project implements a custom dynamic array in C with advanced memory handling and error logging. 
It includes a garbage collection mechanism to reclaim memory from deleted elements, uses a memory pool 
to manage small memory allocations efficiently, and provides thread-safe versions of the operations 
along with error logging functionalities.

Files
-----
- custom_array.h: Header file containing the declarations of the custom array and memory pool functions.
- custom_array.c: Source file implementing the custom array functionalities.
- error_handling.h: Header file containing the declarations for error handling functions.
- error_handling.c: Source file implementing error handling functionalities.
- main.c: Source file containing the main function to demonstrate the usage of the custom array and error logging.
- CMakeLists.txt: CMake build configuration file.

Requirements
------------
- CMake 3.10 or higher
- C compiler (GCC recommended)
- pthread library


Instructions
------------
1. Create a build directory:
   ```
   mkdir build
   cd build
   ```

2. Run CMake to generate the build system files:
   ```
   cmake .. -DBUILD_MAIN=ON -DBUILD_BENCHMARK=OFF
   ```
   or
   ```
   cmake .. -DBUILD_MAIN=OFF -DBUILD_BENCHMARK=ON
   ```

3. Build the project:
   ```
   cmake --build .
   ```

4. Run the executable:
   ```
   ./main
   ```
   or
   ```
   ./benchmark
   ```


Description
-----------
The custom array implementation provides the following functionalities:

1. Initialization:
   - Initialize the array with a specified initial capacity.

2. Insertion:
   - Add elements to the array, expanding capacity as necessary.

3. Deletion:
   - Remove elements from the array and compact the memory.

4. Access:
   - Access elements by index.

5. Resize:
   - Dynamically resize the array to optimize memory usage.

6. Garbage Collection:
   - Reclaim memory from deleted elements.

7. Memory Pool:
   - Manage small memory allocations efficiently using a memory pool.

8. Concurrency:
   - Implement thread-safe versions of insertion, deletion, and access operations.
   - Use synchronization primitives (e.g., mutexes) to ensure thread safety.

9. Error Handling:
   - Log errors for out-of-memory situations, invalid index access, and memory reallocation failures.
   - The log messages are written to "error_log.txt" with timestamps.


Notes
-----
- Ensure that the memory pool is initialized before using the custom array.
- The garbage collection function should be called periodically to reclaim memory from deleted elements.

Contact
-------
For any questions or issues, please contact Ahmed Abdelghany at ahmedabdelghany15@gmail.com
