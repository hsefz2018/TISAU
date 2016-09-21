#include <cstdio>
#include <algorithm>
#include <utility>
static const int INF = 0x7fffffff;
static const int MAXN = 150005;

int n, ct, m = 0;
int h[MAXN * 3], g[MAXN][3];
int d[MAXN * 3];

template <typename T> int discretize(T *a, int *b, int n)
{
    static std::pair<T, int> p[MAXN * 3];
    for (int i = 0; i < n; ++i) p[i] = std::make_pair(a[i], i);
    std::sort(p, p + n);
    int rk = 0;
    for (int i = 0; i < n; ++i) {
        if (i && p[i].first != p[i - 1].first) ++rk;
        b[p[i].second] = rk;
        a[rk] = p[i].first;
    }
    return rk + 1;
}

int head[MAXN * 3], dest[MAXN * 6], next[MAXN * 6];
inline void add_edge(int u, int v) {
    dest[m] = v; next[m] = head[u]; head[u] = m++;
    dest[m] = u; next[m] = head[v]; head[v] = m++;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < 3; ++j) scanf("%d", &h[i * 3 + j]);
    ct = discretize(h, &g[0][0], n * 3);
    //for (int i = 0; i < n; ++i)
    //    for (int j = 0; j < 3; ++j) printf("%d%c", g[i][j], j == 2 ? '\n' : ' ');

    for (int i = 0; i < ct; ++i) head[i] = -1;
    for (int i = 0; i < n; ++i) {
        add_edge(g[i][0], g[i][1]);
        add_edge(g[i][0], g[i][2]);
        add_edge(g[i][1], g[i][2]);
    }

    for (int i = 0; i < ct; ++i) d[i] = INF;
    // BFS
    static int q[MAXN * 3], qhead, qtail;
    qhead = 1, qtail = 0, q[0] = 0, d[0] = 0;
    while (qhead > qtail) {
        int u = q[qtail++];
        for (int w = head[u]; w != -1; w = next[w]) if (d[dest[w]] == INF) {
            d[dest[w]] = d[u] + 1;
            q[qhead++] = dest[w];
        }
    }

    for (int i = 0; i < ct; ++i) printf("%d %d\n", h[i], d[i] == INF ? -1 : d[i]);

    return 0;
}

