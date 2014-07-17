// Adapted from : https://github.com/LukasFolwarczny/insalg

#pragma once
#include <vector>

template<typename Scalar, typename Vector, typename Container, typename distFunciton>
void geometric_median( const Container &X, Vector & geo_median, distFunciton distance, int iterations = 200 )
{
    size_t dim = geo_median.size();
    size_t N = X.size();
    if(N < 3) return;

    // initial guess
    std::vector<Vector> A (2, (X[0] + X[1]) / Scalar(2));

    for(int it = 0; it < iterations; it++)
    {
        Vector numerator; for(size_t i = 0; i < dim; i++) numerator[i] = 0;
        Scalar denominator = 0;

        int t = it % 2;

        for (int n = 0; n < N; n++)
        {
            Scalar dist = distance(X[n], A[t]);

            if (dist != 0)
            {
                numerator += X[n] / dist;
                denominator += 1.0 / dist;
            }
        }

        A[1-t] = numerator / denominator;
    }

    geo_median = A[iterations%2];
}



