#define PI 3.14159265358979323846
#define DOUBLE_PI 6.283185307179586232
#define PI_HALF 1.570796326794896558
#define THREE_PI_HALF 4.712388980384689674

double _fmod(double x, double y) {
    if (y == 0.0) {
        return 0.0;
    }

    double result = x - (double)((int)(x / y)) * y;

    return (result < 0) ? (result + y) : result;
}

double _pow(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

double _sin(double x) {
    double z = _fmod(x, 2 * PI);
    
    double result = 0;
    if (z <= PI_HALF) {
        result = 0.028644811879990944 * _pow(z, 4) - 0.20385110262323103 * _pow(z, 3) + 0.02090994802843416 * _pow(z, 2) + 0.9954617512319969 * z + 0.00023060949853418496;
    } else if (z <= PI) {
        result = 0.028643221500985257 * _pow(z, 4) - 0.15610299471228117 * _pow(z, 3) - 0.20406096277925495 * _pow(z, 2) + 1.3562229703585635 * z - 0.1964080629634316;
    } else if (z <= THREE_PI_HALF) {
        result = -0.028646247913692567 * _pow(z, 4) + 0.5638421123687306 * _pow(z, 3) - 3.638654926239317 * _pow(z, 2) + 8.725053225623561 * z - 6.190950354465874;
    } else {
        result = -0.028646283653384758 * _pow(z, 4) + 0.516096855586553827 * _pow(z, 3) - 2.963668250249625657 * _pow(z, 2) + 5.536807811523057232 * z - 1.159489388771234974;
    }
    return result;
}

double _cos(double x) {
    return _sin(PI_HALF - x);
}
