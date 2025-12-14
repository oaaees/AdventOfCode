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

    for ingredient in ingredients:
        for range in ranges:
            if ingredient >= range[0] and ingredient <= range[1]:
                sum += 1
                break

    print(sum)


if __name__ == "__main__":
    main()
