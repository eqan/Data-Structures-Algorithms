import os
from copy import deepcopy

# The above function will only initialize the board
def initialize_Board():
    return [['X', 'O', 'X'],
            ['O', 'O', 'X'],
            ['_', '_', '_']]

# just to print the board
def print_Board(Board):
    for row in Board:
        print('| ' + ' | '.join(row) + ' |')
    return

def player_Turn(Board):  # {
    count_player1 = 0
    count_player2 = 0
    for row in Board:  # {
        for counter in row:  # {
            if counter == 'X':  # {
                count_player1 = count_player1 + 1
                # }
            if counter == 'O':  # {
                count_player2 = count_player2 + 1
                # }
            # }
        # }
    return 'O' if count_player1 > count_player2 else 'X'

# The function will calculate the winning conditions otherwise it the program continue
def winning_Condtion(Board,ch):
    flag_row = flag_col = True
    for i in range(3):
        for j in range(3):
            if Board[j][i] != ch:
                flag_col = False
            if Board[i][j] != ch:
                flag_row = False

        if flag_col or flag_row:
            return True
        flag_row = True
        flag_col = True
# the above is for row and coloumn wining condition

    flag_row = flag_col = True
    for i in range(3):
        if Board[i][2-i] != ch:
            flag_row = False
        if Board[i][i] != ch:
            flag_col = False
    if flag_col or flag_row:
        return True
# the above is for diagonal wining condition

    return False


# The function will check the termination of our program
def terminate(Board):  # {
    flag = winning_Condtion(Board, 'X')
    if flag:
        # print()
        #print_Board(Board)
        return True
    flag = winning_Condtion(Board, 'O')
    if flag:
        return True
    # If nothing then this means there are empty states available
    for i in range(3):
        for j in range(3):
            if (Board[i][j] == '_'):
                return False
    # If empty states are also filled then it should terminate
    return True
    # }

# This is the utility function
def utility_Function(Board):
    flag = winning_Condtion(Board, 'X')
    if flag:
        return 1
    flag = winning_Condtion(Board, 'O')
    if flag:
        return -1
    return 0


# Return the empty spaces indexes list
def actions(Board):
    action_Move = list()
    for i, row in enumerate(Board):
        for j, col in enumerate(row):
            if col == '_':
                action_Move.append((i, j))
    return action_Move

# The function will put the turn in the respective position
def result(Board, coordinate):
    row, col = coordinate
    if (Board[row][col] == '_'):
        move = player_Turn(Board)
        copy_Board[row][col] = move
        return copy_Board
    else:
        raise Exception("Invalid Move")


def Max_Value_Pruning(state, Alpha, Beta):
    if terminate(state):
        return utility_Function(state) , None
    value = -1000
    best_Action = None
    actions_pos = actions(state)
    for a in actions_pos:
        Value_get = Min_Value_Pruning(result(state, a), Alpha, Beta)[0]
        # value = max(value, Value_get)
        if (Value_get > value):
            value = Value_get
            best_Action = a
        # best_Action = a

        r, c = a
        state[r][c] = '_'
        if (value >= Beta):  # A condition for pruning
            return value, best_Action
        Alpha = max(Alpha, value)
    return value, best_Action


def Min_Value_Pruning(state, Alpha, Beta):
    if terminate(state):
        return utility_Function(state), None
    value = 1000
    best_Action = None
    actions_pos = actions(state)
    for a in actions_pos:
        Value_get = Max_Value_Pruning(result(state, a), Alpha, Beta)[0]
        if (Value_get < value):
            value = Value_get
            best_Action = a
        # value = min(value, Value_get)
        # best_Action = a
        r, c = a
        state[r][c] = '_'
        if (value <= Alpha):  # A condition for pruning
            return value, best_Action
        Beta = min(Beta, value)
    return value, best_Action


def Alpha_Beta_Search(Board):
    print("\nInitital State")
    print_Board(Board)
    global copy_Board
    while (True):
        if terminate(Board):
            #print("\n\nboard terminate")
            # print_Board(Board)
            break
        if (player_Turn(Board) == 'X'):
            value, Best_Move = Max_Value_Pruning(copy_Board, -1000, 1000) # -1 or 1 [The player X or Y] and coordinates
            R, C = Best_Move
            Board[R][C] = 'X'
            copy_Board = list(Board)
            # print()
            #print_Board(Board)
        elif (player_Turn(Board) == 'O'):
            value_get, Best_Move = Min_Value_Pruning(copy_Board, -1000, 1000)
            R, C = Best_Move
            Board[R][C] = 'O'
            copy_Board = list(Board)
            # print()
            
        else:
            # Human vs Computer
            
            # row = int(input("Enter your Row = "))
            # col = int(input("Enter your Col = "))
            # Board[row][col] = 'O'
            # copy_Board = list(Board)
            # print_Board(Board)
            raise Exception("Error for Optimal Moves")
            
    if(utility_Function(Board) == 1):
        print("\nX has won!")
    elif(utility_Function(Board) == -1):
        print("\nO has won!")
    else:
        print("\nGame has been drawn!")
    print_Board(Board)

Board = initialize_Board()
copy_Board = initialize_Board()
Alpha_Beta_Search(Board)
#print_Board(Board)