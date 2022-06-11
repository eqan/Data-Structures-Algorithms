class Queue:
    __list = []
    def enqueue(self, item):
        self.__list.append(item)
    def dequeue(self):
        self.__list.pop(0)
    def display(self):
        print(self.__list)
    def front(self):
        return (self.__list[0])
    def empty(self):
        if(len(self.__list) == 0):
            return True
        else:
            return False
    def remove(self,value):
        self.__list.pop(self.__list.index(value))

    def clear(self):
        if(not self.empty()):
            while(not self.empty()):
                self.dequeue()

def minCostNode(pathQueue): # g(n) function gives minimum cost
    cost = []
    treeCoordinates=[]
    while(not pathQueue.empty()):
        treeCoordinates.append(pathQueue.front())
        pathQueue.dequeue()
    treeCoordinates.reverse()
    for node in treeCoordinates:
        cost.append(combinedValues[tuple(node)])
    mincost = min(cost)
    for coordinates in combinedValues.keys():
        if combinedValues[coordinates]==mincost:
            if coordinates in exlist:
                continue
            for node in treeCoordinates:
                pathQueue.enqueue(node)
            return coordinates[0],coordinates[1]

gridSize = 0
grid = []
vis = []
dist = {}
heuristicValues = {}
combinedValues = {}
exlist = []
path = []
moves = []
backTrackPath = []
movCosts = [2, 2, 3] # Up, Right, Right Diagonal Costs
resultantQueue = Queue()


def prRed(skk): print("\033[91m {}\033[00m" .format(skk),   end="")
def prGreen(skk): print("\033[92m {}\033[00m" .format(skk),   end="")
def prYellow(skk): print("\033[93m {}\033[00m" .format(skk),   end="")
def prLightPurple(skk): print("\033[94m {}\033[00m" .format(skk),   end="")
def prPurple(skk): print("\033[95m {}\033[00m" .format(skk),   end="")
def prCyan(skk): print("\033[96m {}\033[00m" .format(skk),   end="")
def prLightGray(skk): print("\033[97m {}\033[00m" .format(skk),   end="")
def prBlack(skk): print("\033[98m {}\033[00m" .format(skk),   end="")

def displayGrid():
    i = 15
    grid.reverse()
    for row in grid:
        if(i < 10):
            print('\n' + str(i) + ":  ",  end="" )
        else:
            print('\n' + str(i) + ": ",  end="")

        for char in row:
            if(char == 'S'):
                prGreen('S ')
            elif(char == 'E'):
                prRed('E ')
            elif(char == '*'):
                prCyan('* ')
            elif(char == '#'):
                prYellow('# ')
            else:
                prLightGray(char + ' ')
        i-=1

def isValid(srcX, srcY):
    if(srcX < 0 or srcX >= gridSize or srcY < 0 or srcY >= gridSize):
        return False
    if(vis[srcX][srcY] == True):
        return False
    return True

def extractDataFromText():
    f = open('Grid4.txt', 'r')
    for line in f.readlines():
        grid.append(list(line.strip()))
    f.close()
    return grid

def initializeVariables():
    vis = [[False for i in range(gridSize)] for j in range(gridSize)]
    backTrackPath = [[[0,0] for i in range(gridSize)] for j in range(gridSize)]
    for i in range(gridSize):
        for j in range(gridSize):
            if(grid[i][j] == '1'):
                vis[i][j] = True
    return vis, backTrackPath

def getFinalResults(srcX, srcY, endX, endY):
    resultantQueue.clear()
    resultantQueue.enqueue([endX, endY])
    while(not resultantQueue.empty()):
        currX = resultantQueue.front()[0]
        currY = resultantQueue.front()[1]
        prevX = backTrackPath[currX][currY][0]
        prevY = backTrackPath[currX][currY][1]
        resultantQueue.dequeue()
        if(prevX != srcX and prevY != srcY):
            grid[prevX][prevY] = '*'
            path.append((prevX,prevY))
            resultantQueue.enqueue([prevX, prevY])
        if(prevX + 1 == currX and prevY == currY):
            moves.append("🡱")
        elif(prevX == currX and prevY + 1 == currY):
            moves.append("🡲")
        elif(prevX+1==currX and prevY+1==currY):
            moves.append("🡵")
        else:
            break

# Heuristic distance between two positions using elucidian distance
def returnHeuristic(a, b):
    x1, y1 = a
    x2, y2 = b
    return (((x2-x1)**2 + (y2-y1)**2)**(0.5))


def A_Star(src, end):
    endFound = False
    srcX = src['x'] - 1
    srcY = src['y'] - 1
    endX = end['x'] - 1
    endY = end['y'] - 1
    if(isValid(srcX, srcY) and isValid(endX, endY)):
        resultantQueue.enqueue([srcX, srcY])
        vis[srcX][srcY] = True
        dist[(srcX,srcY)]=0
        heuristicValues[(srcX,srcY)]=0
        combinedValues[(srcX,srcY)]=0
        while(not resultantQueue.empty()):
            currX ,currY = minCostNode(resultantQueue)
            resultantQueue.remove([currX,currY])
            exlist.append((currX,currY))
            if(currX == endX and currY == endY):
                endFound = True
                break
            for i in range(3):
                newX = currX
                newY = currY
                if(i == 0 and isValid(currX, currY + 1)): # Up Movement
                    newY += 1
                elif(i == 1 and isValid(currX + 1, currY)): # Right Movement
                    newX += 1
                elif(i == 2 and isValid(currX + 1, currY + 1)): # Right Diagonal Movement
                    newX += 1
                    newY += 1
                if(currX != newX or currY != newY):
                    grid[newX][newY] = "#"
                    vis[newX][newY] = 1
                    backTrackPath[newX][newY] = [currX, currY]
                    dist[(newX, newY)] = dist[(currX, currY)] + movCosts[i]
                    heuristicValues[(newX, newY)] = returnHeuristic((newX, newY), (endX, endY))
                    combinedValues[(newX, newY)] = dist[(newX, newY)] + heuristicValues[(newX, newY)]
                    resultantQueue.enqueue([newX, newY])
        else:
            print("Vertices are out of bounds!")

        if (endFound):
            getFinalResults(srcX, srcY, endX, endY)
        else:
            print("End not found!")
        grid[srcX][srcY] = "S"
        grid[endX][endY] = "E"
        return grid

def showResults(end):
    endX = end['x'] - 1
    endY = end['y'] - 1
    path.reverse()
    moves.reverse()
    print("Path: " + str(path))
    print("Moves: " + str(moves))
    print("Total Cost: " + str(dist[(endX, endY)]))
    displayGrid()

grid = extractDataFromText()
gridSize = len(grid)
vis, backTrackPath = initializeVariables()
src = {'x':1, 'y':5}
end = {'x':15, 'y':15}
grid = A_Star(src, end)
showResults(end)
