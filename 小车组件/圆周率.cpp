#include <iostream>

int main() {
    int steps = 0;
    double pi = 0.0;
    double denominator = 1.0;
    double sign = 1.0;

    for (int i = 0; ; i++) {
        double term = sign / denominator;
        if (term < 1e-8) {
            break;
        }

        pi += term;
        sign = -sign;
        denominator += 2.0;
        steps++;
    }

    pi *= 4;

    std::cout << "steps=" << steps << " PI=" << std::fixed << std::setprecision(5) << pi << std::endl;

    return 0;
}