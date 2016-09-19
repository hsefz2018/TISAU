#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
typedef unsigned long long uint64;
static const int INF32 = 0x7fffffff;
static const int MAXN = 50004;
static const int MAXLEN = 22;
static const int H_BASE = 1e7 + 7;
static const int H_OFFSET = 233;

inline uint64 hash(const char *s) {
    uint64 ans = 0;
    for (; *s; ++s) ans = ans * H_BASE + *s + H_OFFSET;
    return ans;
}
static const uint64 SRC_HASHVAL = hash("Xiaodao");

int n;
char s[MAXN * 3][MAXLEN];
std::pair<uint64, int> p[MAXN * 3];
int h[MAXN * 3];
std::pair<char *, int> nom[MAXN * 3];
int dist[MAXN * 3];

inline bool cmp_pspi(const std::pair<char *, int> &lhs, const std::pair<char *, int> &rhs) {
    return strcmp(lhs.first, rhs.first) < 0;
}

int m = 0;
int head[MAXN * 3];
int dest[MAXN * 3], next[MAXN * 3];

inline void add_edge(int u, int v) {
    dest[m] = v; next[m] = head[u]; head[u] = m++;
    dest[m] = u; next[m] = head[v]; head[v] = m++;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < 3; ++j) {
            scanf("%s", s[i * 3 + j]);
            p[i * 3 + j] = std::make_pair(hash(s[i * 3 + j]), i * 3 + j);
        }
    std::sort(p, p + n * 3);
    int rk = -1, cen_rk = -1;
    for (int i = 0; i < n * 3; ++i) {
        if (i == 0 || p[i].first != p[i - 1].first)
            nom[++rk] = std::make_pair(s[p[i].second], rk);
        h[p[i].second] = rk;
        if (p[i].first == SRC_HASHVAL) cen_rk = rk;
    }
    ++rk;

    // Sort names according to alphabetical order
    std::sort(nom, nom + rk, cmp_pspi);
    //for (int i = 0; i < rk; ++i) puts(nom[i].first);

    // Graph construction
    for (int i = 0; i < rk; ++i) head[i] = -1;
    for (int i = 0; i < n; ++i) {
        add_edge(h[i * 3 + 0], h[i * 3 + 1]);
        add_edge(h[i * 3 + 0], h[i * 3 + 2]);
        add_edge(h[i * 3 + 1], h[i * 3 + 2]);
    }
    // BFS
    static int q[MAXN * 3];
    int qhead = 1, qtail = 0;
    q[0] = cen_rk;
    for (int i = 0; i < rk; ++i) dist[i] = INF32;
    dist[cen_rk] = 0;
    while (qhead > qtail) {
        int u = q[qtail++];
        for (int w = head[u]; w != -1; w = next[w]) if (dist[dest[w]] == INF32) {
            dist[dest[w]] = dist[u] + 1;
            q[qhead++] = dest[w];
        }
    }

    for (int i = 0; i < rk; ++i) {
        printf("%s ", nom[i].first);
        if (dist[nom[i].second] == INF32) printf("undefined\n");
        else printf("%d\n", dist[nom[i].second]);
    }

    return 0;
}

