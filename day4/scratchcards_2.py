import sys

def main():
    
    if len(sys.argv) != 2:
        print(f"Usage: python3 {sys.argv[0]} <input.txt>")
        sys.exit()

    with open(sys.argv[1], "r") as input:
        text = input.readlines()
        
        total = 0
        for i in range(len(text)):
            total += score_recursive(i, text)
        print(total)


def score(line: str) -> int:
    split_line = line.split(':')[1]

    winners, has = split_line.split('|')
    winners, has = get_numbers(winners), get_numbers(has)

    return sum(map(lambda x: x in winners, has))


def get_numbers(string: str)->list:
    numbers_list = string.split()
    numbers_list = map(lambda x: int(x), numbers_list)
    return list(numbers_list)


def score_recursive(idx: int, lines: list):
    if idx > len(lines):
        return 0
    matches = score(lines[idx])
    current_score = 1

    for i in range(idx + 1, idx + matches + 1):
        current_score += score_recursive(i, lines)
    return current_score
    
    
if __name__ == '__main__':
    main()

