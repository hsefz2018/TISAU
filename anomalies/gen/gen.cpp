#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>
static const int MAXN = 150005 * 3;

int n, max_g;
int g[MAXN * 3];

inline void rand_distinct_2(int &a, int &b) {
    do { a = rand() % max_g; b = rand() % max_g; } while (a == b);
}
inline void rand_distinct_3(int &a, int &b, int &c) {
    rand_distinct_2(a, c);
    do b = rand() % max_g; while (b == a || b == c);
}

int main(int argc, char *argv[])
{
    unsigned int seed = 0;
    if (argc > 1) seed = atoi(argv[1]);
    if (seed == 0) seed = (unsigned)time(NULL);
    srand(seed);
    fprintf(stderr, "Seed: %u\n", seed);

    scanf("%d%d", &n, &max_g);
    assert(n >= 1);
    assert(max_g >= 3 || max_g == 0);
    g[0] = 0;
    if (max_g == 0) {
        for (int i = 1; i < n * 3; ++i) g[i] = i;
        std::random_shuffle(g + 1, g + n * 3);
    } else {
        do rand_distinct_2(g[1], g[2]); while (g[1] == 0 || g[2] == 0);
        for (int i = 1; i < n; ++i) rand_distinct_3(g[i * 3], g[i * 3 + 1], g[i * 3 + 2]);
    }

    printf("%d\n", n);
    for (int i = 0; i < n * 3; ++i) printf("%d%c", g[i] + 1, i % 3 == 2 ? '\n' : ' ');

    fclose(stdout);
    return 0;
}

