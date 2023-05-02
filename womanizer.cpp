#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

typedef pair<long long int, long long int> PII; // PII represents (distance, node)

long long int n, m, petrol;
vector<vector<pair<long long int, long long int>>> graph; // adjacency list to store graph
vector<long long int> ratings; // ratings of women

// function to find the maximum rating for a path that obeys the neighbor constraint
long long int find_max_rating(long long int node, long long int rating) {
    long long int max_rating = rating;

    // find the maximum rating among neighbors that don't violate the neighbor constraint
    for (auto &edge : graph[node]) {
        long long int next_node = edge.first;
        long long int cost = edge.second;

        // check if next_node is a neighbor that has already been visited in the same path
        bool neighbor_visited = false;
        for (auto &edge2 : graph[node]) {
            long long int neighbor_node = edge2.first;
            if (neighbor_node != next_node) {
                if (ratings[neighbor_node] > ratings[node] && ratings[neighbor_node] >= ratings[next_node]) {
                    neighbor_visited = true;
                    break;
                }
            }
        }

        if (!neighbor_visited && cost <= petrol) {
            long long int next_rating = find_max_rating(next_node, rating + ratings[next_node]);
            max_rating = max(max_rating, next_rating);
        }
    }

    return max_rating;
}

int main() {
    cin >> n >> m >> petrol;
    graph.resize(n + 1); // resize graph to store n nodes (1-indexed)

    // read m edges and add them to graph (undirected)
    for (long long int i = 0; i < m; i++) {
        long long int u, v, w;
        cin >> u >> v >> w;
        if (w == LLONG_MAX) {
            continue; // skip edges between neighboring women
        }
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    ratings.push_back(0);
    for (long long int i = 0; i < n; i++) {
        long long int rating;
        cin >> rating;
        ratings.push_back(rating);
    }

    long long int max_total_rating = 0;
    for (long long int i = 1; i <= n; i++) {
        // initialize distances to all nodes as infinity, except starting node
        vector<long long int> distance(n + 1, LLONG_MAX);
        distance[i] = petrol;

        // initialize priority queue for Dijkstra's algorithm
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        pq.push({petrol, i});

        // run Dijkstra's algorithm
        while (!pq.empty()) {
            PII p = pq.top();
            pq.pop();

            long long int u = p.second;
            long long int d = p.first;

            // skip this node if we've already found a shorter path to it
            if (d > distance[u]) {
                continue;
            }

            // check if this node has a better rating than any previous node
            max_total_rating = max(max_total_rating, find_max_rating(u, ratings[u]));

            for (auto &edge : graph[u]) {
                long long int v = edge.first;
                long long int w = edge.second;

               
            if (distance[u] >= w) {
                // if we have enough petrol to reach the next node, update its distance and add it to the priority queue
                long long int next_distance = distance[u] - w;
                if (next_distance > distance[v]) {
                    distance[v] = next_distance;
                    pq.push({distance[v], v});
                }
            }
        }
    }
}

cout << max_total_rating << endl;

return 0;
}