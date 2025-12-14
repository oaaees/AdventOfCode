import os

def main():
    input_path = "input.txt"
    if not os.path.exists(input_path):
        print(f"Error: {input_path} not found.")
        return

    ranges = []
    ingredients = []
    change = False

    try:
        with open(input_path, "r") as file:
            for line in file:
                if line == "\n":
                    change = True
                    continue
                if not change:
                    range = line.split("-")
                    ranges.append([int(range[0]), int(range[1])])
                else:
                    ingredients.append(int(line))

                
    except Exception as e:
        print(f"Error reading file: {e}")
        return

    sum = 0
    # Combine overlaping ranges
    ranges = sorted(ranges, key=lambda x: x[0])
    new_ranges = []
    
    for range in ranges:
        if not new_ranges or new_ranges[-1][1] < range[0]:
            new_ranges.append(range)
        else:
            new_ranges[-1][1] = max(new_ranges[-1][1], range[1])
    ranges = new_ranges

    for range in ranges:
        sum += range[1] - range[0] + 1

    print(sum)


if __name__ == "__main__":
    main()
