import numpy as np
import string


def removeDuplicates(string):
    return ''.join(list(dict.fromkeys(list(key))))

def convertStringToChunks(string): # O(n) Time Complexity
    tempString = string.replace(" ", "")
    j = 1
    pairs = []

    for i in range(len(tempString)):
        if( j == 2):
            if(tempString[i-1] == tempString[i]):
                if(tempString[i-1] == 'x' and tempString[i] == 'x'):
                    pairs.append((tempString[i-1] + 'z'))
                else:
                    pairs.append((tempString[i-1] + 'x'))

                if(i == len(tempString)-1):
                    pairs.append((tempString[i] + 'z'))
                else:
                    pairs.append((tempString[i] + 'x'))
            else:
                pairs.append((tempString[i-1] + tempString[i]))
            j = 0

        elif (i == len(tempString)-1):
            pairs.append((tempString[i] + 'z'))
        j+=1

    return pairs


def generatePlayFairKeyMatrix(key, n): # O(n) Time Complexity
    alphabets = list(string.ascii_lowercase)

    if 'j' in key:
        alphabets.remove('i')

    else:
        alphabets.remove('j')        
    
    if 'i' and 'j' in key:
        s.replace('j', '')

    playFairKeyMatrix = []
    duplicateCleanString = removeDuplicates(key)
    duplicateCleanString = duplicateCleanString.replace(" ", "")

    tempArr = []
    for letter in duplicateCleanString:
        if len(tempArr) >=  n:
            playFairKeyMatrix.append(tempArr)
            tempArr = []
        try:
           tempArr.append(letter) 
           alphabets.remove(letter)
        except:
            continue
    if len(tempArr) == n :
        playFairKeyMatrix.append(tempArr)
        tempArr = []

    for letter in alphabets:
        if len(tempArr) >=  n:
            playFairKeyMatrix.append(tempArr)
            tempArr = []
        tempArr.append(letter)
    if len(tempArr) > 0:
        playFairKeyMatrix.append(tempArr)
        tempArr = []
    return playFairKeyMatrix

def playFairCipherEncryptAlgo(plainTextPairs, playFairKeyMatrix): # O(n^3) Time Complexity
    encryptedCypher = ""
    for pair in plainTextPairs:
        i = []
        j = []
        for letter in pair:
            for rowIndex in range(len(playFairKeyMatrix)):
                for colIndex in range(len(playFairKeyMatrix[rowIndex])):
                    if letter == playFairKeyMatrix[rowIndex][colIndex]:
                        if(len(i) < 1):
                            i = [rowIndex, colIndex]
                        else:
                            j = [rowIndex, colIndex]
                            # If Column Matches
                            if(i[1] == j[1]):
                                try:
                                    encryptedCypher += playFairKeyMatrix[i[0]+1][i[1]]
                                except:
                                    encryptedCypher += playFairKeyMatrix[0][i[1]]
                                try:
                                    encryptedCypher += playFairKeyMatrix[j[0]+1][j[1]]
                                except:
                                    encryptedCypher += playFairKeyMatrix[0][j[1]]
                                break
                            # If Row Matches
                            elif(i[0] == j[0]):
                                try:
                                    encryptedCypher += playFairKeyMatrix[i[0]][i[1]+1]
                                except:
                                    encryptedCypher += playFairKeyMatrix[i[0]][0]
                                try:
                                    encryptedCypher += playFairKeyMatrix[j[0]][j[1]+1]
                                except:
                                    encryptedCypher += playFairKeyMatrix[j[0]][0]
                                break
                            # If row and column are close to each other
                            elif(i[0]+1 == j[0] and i[1] == j[1]-1):
                                try:
                                    encryptedCypher += playFairKeyMatrix[i[0]][i[1]+1]
                                except:
                                    encryptedCypher += playFairKeyMatrix[i[0]][0]
                                try:
                                    encryptedCypher += playFairKeyMatrix[j[0]][j[1]-1]
                                except:
                                    encryptedCypher += playFairKeyMatrix[j[0]][len(playFairKeyMatrix)-1]
                                break
                            # Otherwise use row method to switch places
                            else:
                                try:
                                    encryptedCypher += playFairKeyMatrix[i[0]][j[1]]
                                except:
                                    encryptedCypher += playFairKeyMatrix[i[0]][0]
                                try:
                                    encryptedCypher += playFairKeyMatrix[j[0]][i[1]]
                                except:
                                    encryptedCypher += playFairKeyMatrix[j[0]][len(playFairKeyMatrix)-1]
                                break
    return encryptedCypher

def playFairCipherDecryptAlgo(decryptedCipherPairs, playFairKeyMatrix):
    decryptedCipher = ""
    for pair in decryptedCipherPairs:
        i = []
        j = []
        for letter in pair:
            for rowIndex in range(len(playFairKeyMatrix)):
                for colIndex in range(len(playFairKeyMatrix[rowIndex])):
                    if letter == playFairKeyMatrix[rowIndex][colIndex]:
                        if(len(i) < 1):
                            i = [rowIndex, colIndex]
                        else:
                            j = [rowIndex, colIndex]
                            # If Column Matches
                            if(i[1] == j[1]):
                                try:
                                    decryptedCipher += playFairKeyMatrix[i[0]-1][i[1]]
                                except:
                                    decryptedCipher += playFairKeyMatrix[i[len([playFairKeyMatrix])-1]][i[1]]
                                try:
                                    decryptedCipher += playFairKeyMatrix[j[0]-1][j[1]]
                                except:
                                    decryptedCipher += playFairKeyMatrix[j[len(playFairKeyMatrix)-1]][j[1]]
                                break
                            # If Row Matches
                            elif(i[0] == j[0]):
                                try:
                                    decryptedCipher += playFairKeyMatrix[i[0]][i[1]-1]
                                except:
                                    decryptedCipher += playFairKeyMatrix[i[0]][len(playFairKeyMatrix[i[0]])-1]
                                try:
                                    decryptedCipher += playFairKeyMatrix[j[0]][j[1]-1]
                                except:
                                    decryptedCipher += playFairKeyMatrix[j[0]][len(playFairKeyMatrix[j[0]])-1]
                                break
                            # If row and column are close to each other
                            elif(i[0]+1 == j[0] and i[1] == j[1]-1):
                                try:
                                    decryptedCipher += playFairKeyMatrix[i[0]][i[1]-1]
                                except:
                                    decryptedCipher += playFairKeyMatrix[i[0]][len(playFairKeyMatrix)-1]
                                try:
                                    decryptedCipher += playFairKeyMatrix[j[0]][j[1]+1]
                                except:
                                    decryptedCipher += playFairKeyMatrix[j[0]][0]
                                break
                            # Otherwise use row method to switch places
                            else:
                                try:
                                    decryptedCipher += playFairKeyMatrix[i[0]][j[1]]
                                except:
                                    decryptedCipher += playFairKeyMatrix[i[0]][0]
                                try:
                                    decryptedCipher += playFairKeyMatrix[j[0]][i[1]]
                                except:
                                    decryptedCipher += playFairKeyMatrix[j[0]][len(playFairKeyMatrix)-1]
                                break

    return decryptedCipher

# message = input("Enter Message: ")
# key = input("Enter Key: ")
# n = int(input("Enter Matrix Size: "))

n = 2
message = "khlfpsoqlakdfeptlqzy"
key = "masood"
# encryptedCipherPairs = convertStringToChunks(message)
playFairKeyMatrix = generatePlayFairKeyMatrix(key, n=5)
# encryptedCypher = playFairCipherEncryptAlgo(encryptedCipherPairs, playFairKeyMatrix)
decryptedCipherPairs = convertStringToChunks(message)
decryptedCipher = playFairCipherDecryptAlgo(decryptedCipherPairs, playFairKeyMatrix)
print("Plain Text: ", message)
print("Key: ", key)
# print("Encrypted Text: ", encryptedCypher)
print("Decrypted Text: ", decryptedCipher)
