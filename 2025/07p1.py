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
                line = [x if x != 'S' else '|' for x in line]
                text.append(line)

                
    except Exception as e:
        print(f"Error reading file: {e}")
        return

    count = 0

    for i in range(len(text) - 1):
        for j in range(len(text[i])):
            if text[i][j] == '|':
                if text[i + 1][j] == '^':
                    text[i + 1][j + 1] = '|'
                    text[i + 1][j - 1] = '|'
                    count += 1
                else:
                    text[i + 1][j] = '|'

    print(count)

if __name__ == "__main__":
    main()
