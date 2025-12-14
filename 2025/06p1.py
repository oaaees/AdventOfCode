import os

def main():
    input_path = "input.txt"
    if not os.path.exists(input_path):
        print(f"Error: {input_path} not found.")
        return

    numbers = []
    operations = []

    try:
        with open(input_path, "r") as file:
            for line in file:
                line = line.split()
                if line[0].isnumeric():
                    numbers.append([int(i) for i in line])
                else:
                    operations.extend(line)

                
    except Exception as e:
        print(f"Error reading file: {e}")
        return

    results = [1 if x == "*" else 0 for x in operations]

    for j in range(len(numbers)):
        for i in range(len(numbers[j])):
            if operations[i] == "+":
                results[i] += numbers[j][i]
            else:
                results[i] *= numbers[j][i]

    sum = 0
    for i in range(len(results)):
        sum += results[i]

    print(sum)


if __name__ == "__main__":
    main()
