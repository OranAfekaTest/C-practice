
x = input("Enter 4 digit number")
hidden = list(x)
print(hidden)

def check_number(num):
    lst = list(num)
    result = []
    for i in range(len(lst)):
        if hidden[i] == lst[i]:
            result.append("bull")
        else:
            if lst[i] in hidden:
                result.append("hit")
    return result