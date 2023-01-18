'''
 Encryption:
 Cipher -> C = Kp (mod 26) Where K = Key, p is a plaintext and M x 1 matrix, K is M x M matrix
 and resultant cipher would also be 1 x M matrix

 Decryption:
 Decrypted -> P = K^-1(mod 26)
'''
import numpy as np

def convertAsciiToChar(ascii):
    return (chr(ascii+96))

def convertCharToAscii(char):
    return (ord(char) - 96)

def modInverse(a, m):
    a %= m
    for i in range(1, m):
        if((a*i)%m == 1):
            return i
    return 1

def assignNumbersToChunks(stringChunks):
    pairs = []
    for chunk in stringChunks:
        arr = []
        for i in range(len(chunk)):
            arr.append(convertCharToAscii(chunk[i]))
        if (len(chunk) < n):
            for i in range(len(chunk), n):
                arr.append(convertCharToAscii(x))
        pairs.append(arr)
    return pairs


def convertStringToChunks(string, n):
    return [string[i:i + n] for i in range(0, len(string), n)]


def hillCipher(textPairs, keys, m):
    text = ""
    for i in range(len(textPairs)):
        tempResult = np.dot(keys, textPairs[i])
        tempResult = np.mod(tempResult, m)
        for j in range(len(tempResult)):
            try:
                text += convertAsciiToChar(tempResult[j])
            except:
                continue
    return text

def calculcateInverseOfMatrix(inverseofkey):
    for i in range(n):
        temp = []
        for j in range(n):
            temp.append(int(adjK[i][j] * kMod))
        inverseofkey.append(temp)
    return inverseofkey

def getCofactor(A, temp, p, q, n):
    i = 0
    j = 0
    for row in range(n):
        for col in range(n):
            if (row != p and col != q):
                temp[i][j] = A[row][col]
                j += 1
                if (j == n - 1):
                    j = 0
                    i += 1

def determinant(A, n, N):
    D = 0
    if (n == 1):
        return A[0][0]
    temp = []
    for i in range(N):
        temp.append([None for _ in range(N)])
    sign = 1
    for f in range(n):
        getCofactor(A, temp, 0, f, n)
        D += sign * A[0][f] * determinant(temp, n - 1,N)
        sign = -sign
    return D

def adjoint(A, adj):
    if (n == 1):
        adj[0][0] = 1
        return
    sign = 1
    temp = []
    for i in range(n):
        temp.append([None for _ in range(n)])

    for i in range(n):
        for j in range(n):
            getCofactor(A, temp, i, j, n)
            sign = [1, -1][(i + j) % 2]
            adj[j][i] = (sign) * (determinant(temp, n - 1,n))

m=26
n = 3

# n = int(input("Enter Dimension: "))
# keys = []
# plainText = input("Enter Plain Text: ")
# plainTextPairs = []

# print("\n Now Enter Keys \n")
# for i in range(n):
#     tempArray = []
#     for j in range(n):
#         elem = input(f'Enter Key[{i+j}]: ')
#         charNumber = ord(elem) - 97
#         tempArray.append(charNumber)
#     keys.append(tempArray)
# print(keys)


keys = [[1,2,3], [4,5,6], [7,8,0]]
inverseofkey=[]
adjK = [None for _ in range(n)]
for i in range(n):
    adjK[i] = [None for _ in range(n)]
plainText = "wow"
x = '0'

# Encryption Alogorithm
tempString = convertStringToChunks(plainText,n)
plainTextPairs = assignNumbersToChunks(tempString)
cipherText = hillCipher(plainTextPairs, keys, m)
print("Plain Text: ", plainText)
print("Cipher Text: ", cipherText)

# Decryption Alogorithm
d = determinant(keys,n,n)%m
kMod = modInverse(d,m)
adjoint(keys,adjK)
adjK=np.mod(adjK,m)
print("Adjoint of Matrix: \n",adjK)
inverseofkey=calculcateInverseOfMatrix(inverseofkey)
inverseofkey=np.mod(inverseofkey,m)
print("Inverse Matrix: \n",inverseofkey)
verify=np.dot(keys,inverseofkey)
verify=np.mod(verify,m)
tempString = convertStringToChunks(cipherText,n)
cypherTextPairs = assignNumbersToChunks(tempString)
inverseofkey = (np.ceil(inverseofkey)).astype(int)
plainText = hillCipher(cypherTextPairs, inverseofkey, m)
print("Plain Text: ", plainText)