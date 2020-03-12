from random import randrange as rand

edges = set()
with open("input.txt", 'w') as file:
    file.write("50000 1000000\n")
    for i in range(1000000):
        first, second = (rand(0, 50000) for _ in range(2))
        while (first, second) in edges:
            first, second = (rand(0, 50000) for _ in range(2))
        file.write(str(first) + ' ' + str(second) + '\n')
        edges.add((first, second))
        edges.add((second, first))
