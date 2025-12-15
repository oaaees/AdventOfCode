import os

def main():
    input_path = "input.txt"
    if not os.path.exists(input_path):
        print(f"Error: {input_path} not found.")
        return

    text = []

    try:
        with open(input_path, "r") as file:
            for line in file:
                line = line.strip()
                line = [x if x != 'S' else '|' for x in line]
                text.append(line)

                
    except Exception as e:
        print(f"Error reading file: {e}")
        return

    # create matrix same size as text
    rows = len(text)
    cols = len(text[0])
    count_matrix = [[0 for x in range(cols)] for y in range(rows)]

    for j in range(cols):
        if text[0][j] == '|':
            count_matrix[0][j] = 1


    for i in range(rows - 1):
        for j in range(cols):
            if text[i + 1][j] == '^' and count_matrix[i][j] > 0:
                if j + 1 < cols:
                    count_matrix[i + 1][j + 1] += count_matrix[i][j]
                if j - 1 >= 0:
                    count_matrix[i + 1][j - 1] += count_matrix[i][j]
            else:
                count_matrix[i + 1][j] += count_matrix[i][j]

    print(count_matrix)

    sum = 0
    
    for i in range(cols):   
        sum += count_matrix[-1][i]

    print(sum)

if __name__ == "__main__":
    main()
