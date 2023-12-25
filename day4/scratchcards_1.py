import sys

def main():
    
    if len(sys.argv) != 2:
        print(f"Usage: python3 {sys.argv[0]} <input.txt>")
        sys.exit()

    with open(sys.argv[1], "r") as input:
        text = input.readlines()
        total = sum(map(score, text))
        print(total)


def score(line: str) -> int:
    split_line = line.split(':')[1]

    winners, has = split_line.split('|')
    winners, has = get_numbers(winners), get_numbers(has)

    winner_count = sum(map(lambda x: x in winners, has))

    return 0 if winner_count == 0 else 2**(winner_count - 1)


def get_numbers(string: str)->list:
    numbers_list = string.split()
    numbers_list = map(lambda x: int(x), numbers_list)
    return list(numbers_list)
    
    
if __name__ == '__main__':
    main()

