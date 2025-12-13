import os

def main():
    input_path = "input.txt"
    if not os.path.exists(input_path):
        print(f"Error: {input_path} not found.")
        return

    ranges = []
    try:
        with open(input_path, "r") as file:
            for line in file:
                line = line.split(",")
                for rang in line:
                    r = rang.split("-")
                    ranges.append([int(r[0]), int(r[1])])
    except Exception as e:
        print(f"Error reading file: {e}")
        return

    sum = 0

    for r in ranges:
        for i in range(r[0], r[1] + 1):
            if len(str(i)) % 2 == 1:
                continue
            else:
                s_1 = str(i)[:len(str(i))//2]
                s_2 = str(i)[len(str(i))//2:]
                if s_1 == s_2:
                    sum += i
    print(sum)


if __name__ == "__main__":
    main()
