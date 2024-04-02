#include "math.c"
#include <stdio.h>
#include <unistd.h>

#define WIDTH 100
#define SPEED 0.004

#define SPEED_B SPEED / 2
#define HEIGHT WIDTH / 2.0
#define MAX (int)(WIDTH * HEIGHT)

int main() {
    float A = 0, B = 0, i, j;
    float z[MAX];
    char b[MAX];
    char buffer[MAX * 2];
    printf("\x1b[2J");
    for (;;) {
        memset(b, 32, MAX);
        memset(z, 0, MAX * sizeof(float));
        int buf_p = 0;
        for (j = 0; DOUBLE_PI > j; j += 0.07) {
            for (i = 0; DOUBLE_PI > i; i += 0.02) {
                float c = _sin(i),
                      d = _cos(j),
                      e = _sin(A),
                      f = _sin(j),
                      g = _cos(A),
                      h = d + 2,
                      D = 1 / (c * h * e + f * g + 5),
                      l = _cos(i),
                      m = _cos(B),
                      n = _sin(B),
                      t = c * h * g - f * e;
                int x = WIDTH / 2.0 + WIDTH / 1.6 * D * (l * h * m - t * n),
                    y = HEIGHT / 2.0 + HEIGHT / 1.6 * D * (l * h * n + t * m),
                    o = x + WIDTH * y,
                    N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if (HEIGHT > y && y > 0 && x > 0 && WIDTH > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,:;~=*oO#$@"[N > 0 ? N : 0];
                }
            }
        }

        for (int k = 0; MAX + 1 > k; k++) {
            buf_p += sprintf(&buffer[buf_p], "%c", k % WIDTH ? b[k] : '\n');
        }

        printf("\x1b[H%s", buffer);

        A += SPEED;
        B += SPEED_B;
    }
}
