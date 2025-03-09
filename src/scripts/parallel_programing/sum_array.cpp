// Online C++ compiler to run C++ program online
#include <iostream>
#include <omp.h>
#include <chrono>

// no items that array a, b and result would have
#define size_array 1000
// no threads
#define chunk_size 10
// limit items to show
#define show_n_elements 10


float* generate_array(float b) {
    // generates an array of global variable size_array defined 
    float* new_array = new float[size_array];
    
    // iterates until max size of array
    for(int i = 0; i < size_array; i++){
        // every iteration the index access to new_array position to apply a mathematical operation
        // item value x constant value
        new_array[i] = i * b;
    }
    // return the new array created
    return new_array;
}

void print_array_items(float *items){
    // this function helps to avoid show all the items of an array
    for(int i = 0; i < show_n_elements; i++){
        // print the array's item
        std::cout << items[i] << " - ";
    }
    std::cout << std::endl;
}

void show_info(float a[], float b[], float result[], float elapsed_ms){
    // print limited array "a" values
    std::cout << "Print the first " << show_n_elements << " values of array a " << std::endl;
    print_array_items(a);
    // print limited  array "b" values
    std::cout << "Print the first " << show_n_elements << " values of array b " << std::endl;
    print_array_items(b);
    // print limited  array of a + b arrays
    std::cout << "Print the first " << show_n_elements << " values of result array " << std::endl;
    print_array_items(result);
    
    // print the execution time by sum
    std::cout << "Execution time in sum array: " << elapsed_ms << " Microseconds" << std::endl;
}


void openmp_available(){
    // function to knows if openmp is available
    #ifdef _OPENMP
      std::cout << "OMP available" << std::endl;
    #else
      std::cout << "OMP not available \n" << std::endl;
    #endif
}


void sum_array(float a[], float b[]) {
    // result array with have the values of a + b
    float* result = new float[size_array];
    std::cout << "<<<<<< Sequential sum arrays >>>>>>" << std::endl;
    
    // get initial time
    auto start = std::chrono::high_resolution_clock::now();

    // iterate the arrays with the same size
    for(int i = 0; i < size_array; ++i){
        // sume the array a and b
        result[i] = a[i] + b[i];
    }
    
    // get end time
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calculate elapsed time in milliseconds
    auto elapsed_ms = std::chrono::duration<float>(end - start).count();

    // show info
    show_info(a,b,result, elapsed_ms);
}

void sum_parallel(float a[], float b[]){
    // set a result array with the size defined previously
    float* result = new float[size_array];
    std::cout << "<<<<<< Parallel sum arrays >>>>>>" << std::endl;
    
    // get initial time
    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for schedule(static, chunk_size)
    // iterate the arrays with the same size
    for(int j = 0; j < size_array; ++j){
        // sume the array a and b
        result[j] = a[j] + b[j];
    }
    
    // get end time
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calculate elapsed time in milliseconds
    auto elapsed_ms = std::chrono::duration<float>(end - start).count();
    
    // show info
    show_info(a,b,result, elapsed_ms);
}




int main() {
    
    // test openmp availability
    openmp_available();
    
    // generate arrays 
    float* array_a = generate_array(20);
    float* array_b = generate_array(5.5);
    
    // show secuential sum of arrays
    sum_array(array_a, array_b);
    std::cout << "" << std::endl;
    // show parallel sum of arrays
    sum_parallel(array_a, array_b);

    return 0;
}