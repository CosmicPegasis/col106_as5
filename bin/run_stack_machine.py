import sys
input_file = open(sys.argv[1], "r")
input_file_lines = input_file.readlines()
input_file.close()

stk = [];
mem = [0] * int(sys.argv[2])


for line in input_file_lines:
    if(line == "" or line == "\n"):
        continue;
    else:
        line = line.strip()
       # print(line)
    if line == "RET = POP":
        print(stk.pop())
    elif line[0:3] == "mem":
        tokens = line.split()
        mem_index = int(tokens[0][4])
        mem[mem_index] = stk.pop()
    elif line[0:3] == "DEL":
        continue
    else:
        tokens = line.split()
        if tokens[0] == "PUSH":
            if tokens[1].isnumeric():
                stk.append(tokens[1])
            else:
                stored_value = eval(tokens[1])
                stk.append(stored_value)

        else:
            first = stk.pop()
            second = stk.pop()
            if first == "NULL" or second == "NULL":
                stk.append("NULL")
                continue
            first = int(first)
            second = int(second)
            if tokens[0] == "ADD":
                stk.append(first + second)
            elif tokens[0] == "SUB":
                stk.append(first - second)
            elif tokens[0] == "MUL":
                stk.append(first * second)
            elif tokens[0] == "DIV":
                if (second == 0):
                    stk.append("NULL")
                else:
                    stk.append(first // second)
