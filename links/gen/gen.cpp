#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>
static const int MAXN = 2009;

int T, n1, n2;
double k1, k2, g1, g2;
int n, k, g;

inline int rand_int_between(const int a, const int b) { return a + rand() % (b - a + 1); }
inline int round(const double x) { return (int)(x + 0.5); }

void work()
{
    n = rand_int_between(n1, n2);
    k = rand_int_between(round(k1 * n), round(k2 * n));
    g = rand_int_between(round(g1 * n), round(g2 * n));
    if (n < 2) n = 2;
    if (k < 1) k = 1;
    if (g < 1) g = 1;
    printf("%d %d %d\n", n, k, g);
}

int main(int argc, char *argv[])
{
    unsigned int seed = 0;
    if (argc > 1) seed = atoi(argv[1]);
    if (seed == 0) seed = (unsigned)time(NULL);
    srand(seed);
    fprintf(stderr, "Seed: %u\n", seed);

    scanf("%d%d%d%lf%lf%lf%lf", &T,
        &n1, &n2, &k1, &k2, &g1, &g2);
    printf("%d\n", T);
    do work(); while (--T);

    fclose(stdout);
    return 0;
}

