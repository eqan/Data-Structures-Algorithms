def convertNumberToAlphabet(num):
    return (chr(num + 96))

def convertAlphabetToNumber(char):
    return (ord(char) - 96)

def encryptionFormula(a, b, x):
    return (a * convertAlphabetToNumber(x) + b) % m

def decryptionFormula(a, b, x):
    return ((modInverse(a, m)) * (convertAlphabetToNumber(x)-b)) % m

def modInverse(a, m):
    a %= m
    for i in range(1, m):
        if((a*i)%m == 1):
            return i
    return 1

# Encryption: E(y) = (a*x + b) % 26
def cipher(a, b, inputText):
    cipherText = ""
    for x in inputText:
        if(x != ' '):
            cypherNumber = encryptionFormula(a, b, x)
            cipherText += convertNumberToAlphabet(cypherNumber)
        else:
            cipherText += ' '
    return cipherText

# Decrypyion: E−1(y) = a−1(y − b) MOD 26
def decypher(a,b,inputText):
    decypherText = ""
    for x in inputText:
        if(x != ' '):
            decypherNumber = decryptionFormula(a, b, x)
            decypherText += convertNumberToAlphabet(decypherNumber)
        else:
            decypherText += ' '
    return decypherText

print('\nEnter Keys For Ciphering\n')

# a = input("A: ")
# b = input("B: ")
# inputText = input("Enter Input Text To Cipher: ")
m = 26
a = 7
b = 2
print("A: ", a)
print("B: ", b)
inputText = "hello"


print("Input Text: ", inputText)
cipherText = cipher(a,b,inputText)

print("Cipher Text: ", cipherText)
decypherText = decypher(a, b, cipherText)

print("Decypher Text: ", decypherText)