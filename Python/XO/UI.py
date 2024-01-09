def print_board(board, dim):
    for y in range(dim):
        for x in range(dim):
            print("{0:^3}".format(board[y][x]), end= "")
            if x < dim - 1:
                print("|", end= "")
        print()
        if y < dim - 1:    
            for x in range(dim):
                print("--- ", end= "")
            print()

def user_input(dim):
    illegal_input = True
    while illegal_input:
        move = input("Choose a tile to play (x,y) or 'q' to quit: ")
        if(move == 'q'):
            return move
        try:
            move = move.split(',')
            x = int(move[0])
            y = int(move[1])
        except(Exception):
            x = -1
            y = -1
        if x < 0 or y < 0 or dim <=x or dim <= y:
            print("Wrong input, try again")
        else:
            illegal_input = False
    return x, y

def anounce_winner(player):
    print("And the winner is {} !!".format(player))