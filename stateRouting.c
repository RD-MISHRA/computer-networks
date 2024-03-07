#include <stdio.h>
#include <stdbool.h>

#define INFINITY 9999
#define MAX_NODES 10

int graph[MAX_NODES][MAX_NODES]; // Adjacency matrix representing the network graph
int distance[MAX_NODES]; // Array to store distances from source node
int next_hop[MAX_NODES]; // Array to store next hop for each destination
bool visited[MAX_NODES]; // Array to mark visited nodes

// Function to initialize the network graph
void initialize(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INFINITY;
        }
    }
}

// Function to perform the distance vector routing algorithm
void distanceVector(int n, int source) {
    for (int i = 0; i < n; i++) {
        distance[i] = graph[source][i];
        if (distance[i] != INFINITY)
            next_hop[i] = i;
        else
            next_hop[i] = -1;
        visited[i] = false;
    }
    
    distance[source] = 0;
    visited[source] = true;
    
    for (int i = 0; i < n - 1; i++) {
        int min_dist = INFINITY;
        int u = -1;
        
        // Find the node with minimum distance from the source
        for (int j = 0; j < n; j++) {
            if (!visited[j] && distance[j] < min_dist) {
                min_dist = distance[j];
                u = j;
            }
        }
        
        visited[u] = true;
        
        // Update distance and next_hop arrays based on the newly visited node
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != INFINITY && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
                next_hop[v] = next_hop[u];
            }
        }
    }
}

// Function to display the routing table
void displayRoutingTable(int n, int source) {
    printf("\nRouting table for node %d:\n", source);
    printf("Destination\tNext Hop\tDistance\n");
    for (int i = 0; i < n; i++) {
        if (i != source) {
            printf("%d\t\t%d\t\t%d\n", i, next_hop[i], distance[i]);
        }
    }
}

int main() {
    int n; // Number of nodes in the network
    int source; // Source node for distance vector calculation
    
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    
    initialize(n); // Initialize the network graph
    
    // Input the adjacency matrix representing the network graph
    printf("Enter the adjacency matrix (use INFINITY for unreachable nodes):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    printf("Enter the source node: ");
    scanf("%d", &source);
    
    distanceVector(n, source); // Perform distance vector routing algorithm
    
    // Display routing table for the source node
    displayRoutingTable(n, source);
    
    return 0;
}
