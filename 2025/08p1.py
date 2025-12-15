import os
import math

class Point:
    def __init__(self, x, y, z, id):
        self.x = x
        self.y = y
        self.z = z
        self.id = id

    def distance(self, other):
        return math.sqrt((self.x - other.x) ** 2 + (self.y - other.y) ** 2 + (self.z - other.z) ** 2)


class DSU:
    def __init__(self, n):
        self.parent = [i.id for i in n]

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        pu, pv = self.find(u), self.find(v)
        if pu == pv:
            return
        self.parent[pu] = pv

def main():
    input_path = "input.txt"
    if not os.path.exists(input_path):
        print(f"Error: {input_path} not found.")
        return

    points = []

    try:
        with open(input_path, "r") as file:
            for line in file:
                line = line.strip().split(',')
                points.append(Point(int(line[0]), int(line[1]), int(line[2]), len(points)))

    except Exception as e:
        print(f"Error reading file: {e}")
        return

    dsu = DSU(points)

    # Priority Queue
    pq = []
    for i in range(len(points)):
        for j in range(i + 1, len(points)):
            pq.append((points[i].distance(points[j]), i, j))
    pq.sort()


    # Kruskal's Algorithm
    count = 0

    while count < 1000:
        d, u, v = pq.pop(0)
        count += 1
        if dsu.find(u) != dsu.find(v):
            dsu.union(u, v)
    
    # Circuit Sizes
    circuit_sizes = {}

    for i in range(len(points)):
        parent = dsu.find(points[i].id)
        if parent not in circuit_sizes:
            circuit_sizes[parent] = 0
        circuit_sizes[parent] += 1

    # Sort circuit sizes
    circuit_sizes = sorted(circuit_sizes.items(), key=lambda x: x[1], reverse=True)

    print(circuit_sizes[0][1] * circuit_sizes[1][1] * circuit_sizes[2][1])


if __name__ == "__main__":
    main()
