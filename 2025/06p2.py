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
                line = [x for x in line]
                text.append(line)

                
    except Exception as e:
        print(f"Error reading file: {e}")
        return

    # find rectangle bounds, will be bounded by: bottom-left = either "+" or "*" and will go until another "+" or "*" is found
    left = 0
    right = 0
    bottom = 0

    submatrices = []
    operations = []

    for i in range(len(text)):
        for j in range(len(text[i])):
            if text[i][j] == "+" or text[i][j] == "*":
                operations.append(text[i][j])
                right = j
                bottom = i
                if left == right:
                    continue
                else:
                    submatrices.append([row[left:right - 1] for row in text[0:bottom]])
                left = right
    submatrices.append([row[left:len(text[i])] for row in text[0:bottom]])

    # Transpose each submatrix
    for i, submatrix in enumerate(submatrices):
        transposed = [list(x) for x in zip(*submatrix)]
        submatrices[i] = transposed

    # Join again
    for i, submatrix in enumerate(submatrices):
        submatrices[i] = [int("".join(row)) for row in submatrix]

    # Perform Operations
    results = [0 if x == "+" else 1 for x in operations]

    for i, submatrix in enumerate(submatrices):
        for j in range(len(submatrix)):
            if operations[i] == "+":
                results[i] += submatrix[j]
            else:
                results[i] *= submatrix[j]

    sum = 0
    for i in range(len(results)):
        sum += results[i]

    print(sum)

if __name__ == "__main__":
    main()
