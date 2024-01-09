from UI import *

def init_board(dim = 3):
    board = [[]] * dim
    for y in range(dim):
        board[y] = [] * dim
        for x in range(dim):
            board[y].append("{},{}".format(x, y))
    return board

def start(board, dim):
    playin = True
    turn = 0
    while(playin):
        print_board(board, dim)
        player = 'X' if turn % 2 == 0 else 'O'
        print("turn {} player is {}".format(turn, player))
        playin = play(board, dim, player)
        if check_win(board, dim, player):
            print_board(board, dim)
            anounce_winner(player)
            playin = False
        turn += 1

def play(board, dim, player):
    is_occupied = True
    if(player == 'X'):
        while is_occupied:
            cord = user_input(dim)
            if(cord == 'q'):
                return False
            if not is_vacant(board, cord[0], cord[1]):
                print("Tile is occupied, try again")
            else:
                is_occupied = False
    else:
        cord = strategy(board, dim)
        print(player, "chose ", cord)
    board[cord[1]][cord[0]] = player
    return True

def strategy(board, dim):
    middle = int(dim / 2)
    if is_vacant(board, middle, middle):
        return middle, middle
    else:
        if board[middle][middle] == 'X':
            if board[middle + 1][middle] == 'X':
                if is_vacant(board, middle, middle - 1):
                    return middle, middle - 1
            
            if board[middle - 1][middle] == 'X':
                if is_vacant(board, middle, middle + 1):
                    return middle, middle + 1
            
            if board[middle][middle + 1] == 'X':
                if is_vacant(board, middle -1, middle):
                    return middle + 1, middle
            
            if board[middle][middle - 1] == 'X':
                if is_vacant(board, middle + 1, middle):
                    return middle + 1, middle
            
            if board[0][0] == 'X':
                if is_vacant(board, dim - 1, dim - 1):
                    return dim - 1, dim - 1
            elif is_vacant(board, 0, 0):
                return 0, 0

            if board[0][dim - 1] == 'X':
                if is_vacant(board, 0, dim - 1):
                    return 0, dim - 1
            elif is_vacant(board, dim - 1, 0):
                return dim - 1, 0

            if board[dim - 1][0] == 'X':
                if is_vacant(board, dim - 1, 0):
                    return dim - 1, 0
            elif is_vacant(board, 0, dim - 1):
                return 0, dim - 1

            if board[dim - 1][dim - 1] == 'X':
                if is_vacant(board, 0, 0):
                    return 0, 0

            elif is_vacant(board, dim - 1, dim - 1):
                    return dim - 1, dim - 1

    if is_vacant(board, middle, middle - 1):
        return middle, middle - 1
            
    elif is_vacant(board, middle, middle + 1):
        return middle, middle + 1
            
    elif is_vacant(board, middle -1, middle):
        return middle + 1, middle
            
    elif is_vacant(board, middle + 1, middle):
        return middle + 1, middle

def is_vacant(board, x, y):
    if board[y][x] == 'X' or board[y][x] == 'O':
        return False
    else:
        return True

def is_legal(x ,y, dim):
    if x not in range(dim) or y not in range(dim):
        return False
    else:
        return True

def check_seroundings(board, x, y, dim):
    pivot = board[y][x]
    if y == board[y + 1][x]:
        if is_legal(x, y - 1, dim) and is_vacant(board, x, y - 1):
            return x, y - 1
        
    if y == board[y - 1][x]:
        if is_legal(x, y + 1, dim) and is_vacant(board, x, y + 1):
            return x, y + 1

    if y == board[y - 1][x]:
        if is_legal(x, y + 1, dim) and is_vacant(board, x, y + 1):
            return x, y + 1
        
        
def check_win(board, dim, player):
    for y in range(dim):
        #check rows
        for x in range(dim):
            if board[y][x] != player:
                x -= 1
                break
        if x + 1 == dim:
            return True
        #check cols
        for x in range(dim):
            if board[x][y] != player:
                x -= 1
                break
        if x + 1 == dim:
            return True
    #check first diagonal
    for x in range(dim):
        if board[x][x] != player:
            x -= 1
            break
    if x + 1 == dim:
        return True
    #check second diagonal
    for x, y in zip(range(dim), range(dim - 1, -1,-1)):
        if board[y][x] != player:
            x -= 1
            break
    if x + 1 == dim:
        return True
    return False

if __name__ == "__main__":
    try:
        dim = int(input("Enter tic tac toe board dimention:(suggested 3)"))
    except(Exception):
        dim = 3
    board = init_board(dim)
    start(board, dim)