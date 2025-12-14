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
        max = -1
        max_index = -1

        for i, battery in enumerate(bank):
            if battery > max:
                max = battery
                max_index = i
    
        if max_index < len(bank) - 1:
            bank_2 = bank[max_index + 1:]
            max_2 = -1

            for battery_2 in bank_2:
                if battery_2 > max_2:
                    max_2 = battery_2

            sum += (max * 10) + max_2
        else: 
            bank_2 = bank[:max_index]
            max_2 = -1

            for battery_2 in bank_2:
                if battery_2 > max_2:
                    max_2 = battery_2

            sum += (max_2 * 10) + max

    print(sum)


if __name__ == "__main__":
    main()
