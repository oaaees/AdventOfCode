import os

def main():
    input_path = "input.txt"
    if not os.path.exists(input_path):
        print(f"Error: {input_path} not found.")
        return

    map = []

    try:
        with open(input_path, "r") as file:
            for line in file:
                row = []
                for c in line:
                    if c != '\n':
                        row.append(c)
                map.append(row)
                
    except Exception as e:
        print(f"Error reading file: {e}")
        return

    sum = 0

    for i in range(len(map)):
        for j in range(len(map[i])):
            if map[i][j] == '@':
                # Check neighbors 
                count = 0
                for x in range(-1, 2):
                    for y in range(-1, 2):
                        if x == 0 and y == 0:
                            continue
                        if i + x < 0 or i + x >= len(map) or j + y < 0 or j + y >= len(map[i]):
                            continue
                        if map[i + x][j + y] == '@':
                            count += 1
                if count < 4:
                    sum += 1
        

    print(sum)


if __name__ == "__main__":
    main()