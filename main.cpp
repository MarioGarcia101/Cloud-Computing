/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <iomanip>
#include <omp.h>

#define N 1000
#define CHUNK 100
#define MOSTRAR 10

void imprimeArreglo(const float *d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";

    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++)
    {
        a[i] = i * 10.0f;
        b[i] = (i + 3) * 3.7f;
    }

    int pedazos = CHUNK;

    double t0 = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            std::cout << "Hilos usados: " << omp_get_num_threads() << "\n";
        }

        #pragma omp for schedule(static, pedazos)
        for (i = 0; i < N; i++)
            c[i] = a[i] + b[i];
    }

    double t1 = omp_get_wtime();
    std::cout << "Tiempo de suma paralela: " << std::fixed << std::setprecision(6)
              << (t1 - t0) << " segundos\n\n";

    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);

    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);

    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

    return 0;
}

void imprimeArreglo(const float *d)
{
    for (int x = 0; x < MOSTRAR; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}
