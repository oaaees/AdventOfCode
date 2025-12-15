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
    last_u = None
    last_v = None

    while count < len(points) - 1:
        d, u, v = pq.pop(0)
        if dsu.find(u) != dsu.find(v):
            dsu.union(u, v)
            count += 1
            last_u = points[u]
            last_v = points[v]

    print(last_u.x *  last_v.x)


if __name__ == "__main__":
    main()
