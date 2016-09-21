#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>
static const int MAXN = 150005 * 3;

int T, n1, n2, m1, m2, t1, t2, r1, r2;
int n, m, t, r;
double p_empty, p_target, p_obstacle, p_sum;

inline int rand_int_between(const int a, const int b) { return a + rand() % (b - a + 1); }

void work()
{
    n = rand_int_between(n1, n2);
    m = rand_int_between(m1, m2);
    t = rand_int_between(t1, t2);
    r = rand_int_between(r1, r2);
    printf("%d %d %d %d\n", n, m, t, r);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double w = (double)rand() / RAND_MAX * p_sum;
            if (w < p_target) putchar('O');
            else if (w < p_target + p_empty) putchar('*');
            else putchar('X');
        }
        putchar('\n');
    }
}

int main(int argc, char *argv[])
{
    unsigned int seed = 0;
    if (argc > 1) seed = atoi(argv[1]);
    if (seed == 0) seed = (unsigned)time(NULL);
    srand(seed);
    fprintf(stderr, "Seed: %u\n", seed);

    scanf("%d%d%d%d%d%d%d%d%d", &T,
        &n1, &n2, &m1, &m2, &t1, &t2, &r1, &r2);
    scanf("%lf%lf%lf", &p_empty, &p_target, &p_obstacle);
    p_sum = p_empty + p_target + p_obstacle;
    if (t1 == 0 && t2 == 0) { t1 = (n + m) / 2; t2 = 1e8; }
    printf("%d\n", T);
    do work(); while (--T);

    fclose(stdout);
    return 0;
}

