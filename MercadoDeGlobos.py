N, K = [int(x) for x in input().split()]
V = [int(x) for x in input().split()]
C = [int(x) for x in input().split()]
P = [int(x) for x in input().split()]

dp = [[None] * K for _ in range(N)]


def solve(i: int, k: int):
    if i >= len(dp) or k <= 0:
        return 0
    if dp[i][k-1] is None:
        dp[i][k-1] = 0
        G = P[i]*max(0, k-C[i])
        for j in range(k+1):
            R = V[i]*j
            next = solve(i+1, k-j)
            dp[i][k-1] = max(dp[i][k-1], R-G+next)
    return dp[i][k-1]


print(solve(0, K))
