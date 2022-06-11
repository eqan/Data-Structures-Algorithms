'''
let solution be initial
let t be an initial temperature
until t is almost zero
    let neighbor be a random neighbor of solution
    if the cost of neighbor is less than the cost of solution
        let solution be neighbor
        stop if the cost is now 0
    otherwise
        let c be the cost increase
        compute p = e^(-c/t)
        with probability p, let solution be neighbor
    multiply t by a decay rate
return solution
'''

import random
from math import exp
from copy import deepcopy
import time

grid = []

def prRed(skk): print("\033[91m {}\033[00m" .format(skk),   end="")
def prGreen(skk): print("\033[92m {}\033[00m" .format(skk),   end="")
def prYellow(skk): print("\033[93m {}\033[00m" .format(skk),   end="")
def prLightPurple(skk): print("\033[94m {}\033[00m" .format(skk),   end="")
def prPurple(skk): print("\033[95m {}\033[00m" .format(skk),   end="")
def prCyan(skk): print("\033[96m {}\033[00m" .format(skk),   end="")
def prLightGray(skk): print("\033[97m {}\033[00m" .format(skk),   end="")
def prBlack(skk): print("\033[98m {}\033[00m" .format(skk),   end="")

def initializeVariables(gridSize):
    global grid
    grid = [[0 for i in range(gridSize)] for j in range(gridSize)]

def constructResultantGrid(board):
    global grid
    for column, row in board.items():
        grid[row][column] = 1

def displayBoard(board):
    global grid
    constructResultantGrid(board)
    i = 1
    for row in grid:
        if(i < 10):
            print('\n' + str(i) + ":  ",  end="" )
        else:
            print('\n' + str(i) + ": ",  end="")

        for element in row:
            if(element == 1):
                prCyan('1 ')
            else:
                prLightGray(str(element) + ' ')
        i+=1
    print('\n')

def calculateThreat(n):
    if n < 2: # This means only 1 or no queens reside in the column so no threat
        return 0
    if n == 2: # This means 2 queens reside in the column so 1 threat
        return 1
    return (n - 1) * n / 2 # The rest n queens we can calculate an approximate threat level


def createBoard(n):
    # chessBoard = {0:0, 1:1, 2:2, 3:3, 4:4}
    # print(chessBoard[0])
    chessBoard = {}
    temp = list(range(n))
    random.shuffle(temp) # Reorganize the list
    column = 0

    while len(temp) > 0:
        row = random.choice(temp) # Randomly selects
        chessBoard[column] = row
        temp.remove(row)
        column += 1
    del temp
    return chessBoard


def calculateCost(chessBoard):
    '''Calculate how many pairs of threaten queen'''
    threat = 0
    chessBoardA = {}
    chessBoardB = {}

    for column in chessBoard:
        resultForChessBoardA = column - chessBoard[column] # column - row
        resultForChessBoardB = column + chessBoard[column]
        ''' Storing in local chessboards in two different specturms '''
        if resultForChessBoardA not in chessBoardA:
            chessBoardA[resultForChessBoardA] = 1 # Set the column index to 1 as only 1 queen is present here
        else:
            chessBoardA[resultForChessBoardA] += 1 # Add the queen in to the column, i.e queens are colliding
        if resultForChessBoardB not in chessBoardB:
            chessBoardB[resultForChessBoardB] = 1
        else:
            chessBoardB[resultForChessBoardB] += 1
    ''' Calculating threat levels '''
    for i in chessBoardA:
        threat += calculateThreat(chessBoardA[i])
    del chessBoardA

    for i in chessBoardB:
        threat += calculateThreat(chessBoardB[i])
    del chessBoardB

    # returning the total threat
    return threat


def simulatedAnnealing(queens, temperature):
    start = time.time()
    solutionFound = False
    resultantQueensCoordinates = createBoard(queens)
    prRed("Initial N-Queens Solution: ")
    displayBoard(resultantQueensCoordinates)
    initializeVariables(queens)

    # To avoid recounting when can not find a better state
    #print(resultantQueensCoordinates)
    calculatedCost = calculateCost(resultantQueensCoordinates)

    t = temperature
    decayRate = 0.80

    while t > 0:
        if((time.time() - start) > 3):
            prRed("Time has exceeded the set limit!\n")
            break
        t *= decayRate
        successor = deepcopy(resultantQueensCoordinates)
        # Randomly picking two coordinates for two queens
        while True:
            index1 = random.randrange(0, queens - 1)
            index2 = random.randrange(0, queens - 1)
            if index1 != index2:
                break
        successor[index1], successor[index2] = successor[index2], successor[index1]  # swap two chosen queens
        delta = calculateCost(successor) - calculatedCost # Successors cost - Current cost
        delta = -delta
        if delta > 0 or 1 > exp(delta / t): # Check delta or probability is smaller than 1 of the probability function
            resultantQueensCoordinates = deepcopy(successor)
            calculatedCost = calculateCost(resultantQueensCoordinates)
        if calculatedCost == 0: # Success condition satisfied
            solutionFound = True
            prGreen("Resultant N-Queens Solution: ")
            displayBoard(resultantQueensCoordinates)
            break
    if solutionFound is False:
        prRed("Failed")

queens = int(input("Enter Number Of Queens: "))
temperature = int(input("Enter Temperature: "))
initializeVariables(queens)
simulatedAnnealing(queens, temperature)