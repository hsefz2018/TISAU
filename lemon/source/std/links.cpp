#include <cstdio>
#include <cstring>
typedef long long int64;
static const int MAXN = 2005;
static const int MODULUS = 1e9 + 7;
#define _ % MODULUS

int n, k, g;
int f[MAXN][MAXN] = {{ 0 }};

inline int fpow(int base, int exp) {
    int64 ans = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) ans = (ans * base)_;
        base = (int64)base * base _;
    }
    return (int)ans;
}
inline int inv(int x) { return fpow(x, MODULUS - 2); }
int fact[MAXN], fact_inv[MAXN];
inline int nCr(int n, int m) {
    if (n < m || n < 0 || m < 0) return 0;
    return (int64)fact[n] * fact_inv[m]_ * fact_inv[n - m]_;
}

void work()
{
    scanf("%d%d%d", &n, &k, &g);
    if (k == n) k = n - 1;

    memset(f, 0, sizeof f);
    f[0][0] = f[1][1] = 1;
    for (int i = 2; i <= k; ++i) {
        for (int j = 1; j <= g; ++j)
            f[i][j] = ((int64)f[i - 1][j] * j _ * 2 + (int64)f[i - 1][j - 1] * (j - 1)_ + (int64)f[i - 1][j + 1] * (j + 1)_)_;
    }

    int ans = 0;
    for (int i = 1; i <= g; ++i) ans = ((int64)f[k][i] * nCr(n - k - 1, i - 1)_ * n _ + ans)_;
    printf("%d\n", ans);
}

int main()
{
    freopen("links.in", "r", stdin);
    freopen("links.out", "w", stdout);

    fact[0] = fact_inv[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = (int64)fact[i - 1] * i _;
        fact_inv[i] = inv(fact[i]);
    }

    int T; scanf("%d", &T);
    do work(); while (--T);

    fclose(stdin); fclose(stdout);
    return 0;
}

