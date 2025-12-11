import os

def main():
    input_path = "input.txt"
    if not os.path.exists(input_path):
        print(f"Error: {input_path} not found.")
        return

    instructions = []
    try:
        with open(input_path, "r") as file:
            for line in file:
                line = line.strip()
                if not line:
                    continue
                
                is_r = line[0] == 'R'
                # Handle potential errors if line is too short or format is wrong
                try:
                    steps = int(line[1:])
                except ValueError:
                    continue

                if is_r:
                    instructions.append(steps)
                else:
                    instructions.append(-steps)
    except Exception as e:
        print(f"Error reading file: {e}")
        return

    count = 0
    current = 50

    for step in instructions:
        current += step
        
        if current == 0 or current % 100 == 0:
            count = count + 1

    print(count)

if __name__ == "__main__":
    main()
