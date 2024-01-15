#include "sym_matrix.hpp"
#include <cassert>


int main()
{
    SymMatrix<int> m(10);  // 100x100 matrix, all lements it to 0 

    m(3, 2) = 4.2;     // element at row 4 column 3
    //assert( m(3, 2) == m(2,3) );
    
    std::cout << "print m:\n" << m;  // will print the matrix
    
    SymMatrix<int> k = m;
    k += m;
    std::cout << "print k: (k = m, k += m)\n" << k;

    SymMatrix<long> w = m;
    w += k;
    std::cout << "print w: (w = m, w += k)\n" << w;
     
    m = k + k;
    std::cout<< "print m: (m = k + k)\n" << m;

    k *= 8.2;
    std::cout << "print k: (k *= 8.2)\n" << k;

    k = m * 8.2;
    std::cout << "print k: (k = m * 8.2)\n" << k;

    m = 8.2 * w;
    std::cout<< "print m: (m = 8.2 * w)\n" << m;
}