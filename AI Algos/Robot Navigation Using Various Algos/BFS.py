class Queue:
    __list = []
    def enqueue(self, item):
        self.__list.append(item)
    def dequeue(self):
        self.__list.pop(0) # Popping 1st element
    def display(self):
        print(self.__list)
    def front(self):
        return (self.__list[0])
    def empty(self):
        if(len(self.__list) == 0):
            return True
        else:
            return False
    def clear(self):
        if(not self.empty()):
            while(not self.empty()):
                self.dequeue()

gridSize = 0
grid = []
vis = []
dist = []
path = []
moves = []
backTrackPath = []
resultantDirections = []
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
    global grid
    i = 15
    j = 0
    print(grid)
    grid.reverse()
    for row in grid:
        printRow = ""
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
    f = open('Grid.txt', 'r')
    for line in f.readlines():
        grid.append(list(line.strip()))
    f.close()
    return grid

def initializeVariables():
    vis = [[False for i in range(gridSize)] for j in range(gridSize)]
    backTrackPath = [[[0,0] for i in range(gridSize)] for j in range(gridSize)]
    dist = [[0 for i in range(gridSize)] for j in range(gridSize)]
    for i in range(gridSize):
        for j in range(gridSize):
            if(grid[i][j] == '1'):
                vis[i][j] = True
    return vis, backTrackPath, dist

def BFS(src, end):
    global grid
    endFound = False
    srcX = src['x'] - 1
    srcY = src['y'] - 1
    endX = end['x'] - 1
    endY = end['y'] - 1
    if(isValid(srcX, srcY) and isValid(endX, endY)):
        resultantQueue.enqueue([srcX, srcY])
        vis[srcX][srcY] = True
        backTrackPath[srcX][srcY] = [srcX, srcY]
        while(not resultantQueue.empty()):
            currX = resultantQueue.front()[0]
            currY = resultantQueue.front()[1]
            resultantQueue.dequeue()
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
                    print("BackTrack: " + str(backTrackPath[newX][newY]))
                    dist[newX][newY] = dist[currX][currY] + movCosts[i]
                    resultantQueue.enqueue([newX, newY])
        else:
            print("Vertices are out of bounds!")

        resultantQueue.clear()
        if (endFound):
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
        else:
            print("End not found!")
        grid[srcX][srcY] = "S"
        grid[endX][endY] = "E"
        return grid


def showResults(end):
    path.reverse()
    moves.reverse()
    print("Path: " + str(path))
    print("Moves: " + str(moves))
    print("Total Cost: " + str(dist[end['x']-1][end['y']-1]))
    displayGrid()


grid = extractDataFromText()
gridSize = len(grid)
vis, backTrackPath, dist = initializeVariables()
src = {'x':1, 'y':3}
end = {'x':15, 'y':15}
grid = BFS(src, end)
showResults(end)
