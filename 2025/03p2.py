import os

def main():
    input_path = "input.txt"
    if not os.path.exists(input_path):
        print(f"Error: {input_path} not found.")
        return

    banks = []
    try:
        with open(input_path, "r") as file:
            for line in file:
                bank = []
                for c in line:
                    if c != '\n':
                        bank.append(int(c))
                banks.append(bank)
                
    except Exception as e:
        print(f"Error reading file: {e}")
        return

    sum = 0

    for bank in banks:
        numbers_left = 12
        start_index = 0
        joltage = 0

        while numbers_left >= 1:
            max = -1
            for i in range(start_index, len(bank) - (numbers_left - 1)):
                if bank[i] > max:
                    max = bank[i]
                    start_index = i
            joltage += max * (10 ** (numbers_left - 1))
            numbers_left -= 1
            start_index += 1

        sum += joltage

    print(sum)


if __name__ == "__main__":
    main()
