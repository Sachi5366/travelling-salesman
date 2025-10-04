#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;
int n;
vector<vector<int>> dist;
vector<vector<int>> dp;

// tsp(mask, pos): mask represents the set of visited cities, pos is the current city
int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1) {
        return dist[pos][0]; // return to starting city
    }

    if (dp[mask][pos] != -1) return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            ans = min(ans, newAns);
        }
    }

    return dp[mask][pos] = ans;
}

int main() {
    cout << "Enter number of cities: ";
    cin >> n;

    dist.assign(n, vector<int>(n));
    cout << "Enter distance matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    dp.assign(1 << n, vector<int>(n, -1));

    int minCost = tsp(1, 0);  // start from city 0, visited mask is 1 (only 0th city)
    cout << "Minimum cost of visiting all cities: " << minCost << endl;

    return 0;
}
