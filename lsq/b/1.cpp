#include <cstdio>
#include <algorithm>
using std::max;
using std::min;
static const int MAXN = 1009;

int n, m, t, r;
char a[MAXN * 3][MAXN * 3];
int f[MAXN * 3][MAXN * 3] = { 0 }, g[MAXN * 3][MAXN * 3] = { 0 };
int ct[MAXN * MAXN] = { 0 };

inline int get_diagonal_sqr_sum(int crow, int ccol) {
    return
        f[min(crow + r, MAXN * 3 - 1)][ccol] -
        (ccol - r - 1 >= 0 ? g[crow - 1][ccol - r - 1] : 0) -
        (crow + r < MAXN * 3 ? g[crow - 1][ccol + r] : 0) +
        f[max(crow - r - 1, 0)][ccol];
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &t, &r); getchar();
    for (int i = 0; i < MAXN * 3; ++i)
        for (int j = 0; j < MAXN * 3; ++j) a[i][j] = '*';
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= m; ++j) a[i + MAXN][j + MAXN] = getchar();

    for (int i = 1; i < MAXN * 3; ++i) {
        f[i][0] = f[i - 1][1] + (a[i - 1][0] == 'O') + (a[i][0] == 'O');
        for (int j = 1; j < MAXN * 3; ++j) {
            f[i][j] = g[i - 1][j - 1] + g[i - 1][j] - f[i - 1][j] + (a[i][j] == 'O');
        }
        for (int j = 0; j < MAXN * 3 - 1; ++j) {
            g[i][j] = f[i][j] + f[i][j + 1] - g[i - 1][j];
        }
        g[i][MAXN * 3 - 1] = f[i][MAXN * 3 - 1];    // Actually undefined
    }

    /*for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            printf("%d%c", g[MAXN + i][MAXN + j], j == m - 1 ? '\n' : ' ');*/
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) if (a[MAXN + i][MAXN + j] == '*') {
            ct[i * m + j] = get_diagonal_sqr_sum(MAXN + i, MAXN + j);
        }
    std::sort(ct, ct + n * m);
    std::reverse(ct, ct + n * m);

    long long ans = 0;
    for (int i = 0; i < min(n * m, t); ++i) ans += ct[i];
    printf("%lld\n", ans);

    return 0;
}

