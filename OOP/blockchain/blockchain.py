import hashlib
from datetime import datetime

class Block():
    def __init__(self, index, timestamp, data, previousHash):
        self.index = index
        self.timestamp = timestamp
        self.data = data
        self.previousHash = previousHash
        self.hash = self.hashBlock()

    def hashBlock(self):
        sha = hashlib.sha256()
        sha.update(bytes(self.index)
                 + bytes(self.timestamp, 'utf-8')
                 + bytes(self.data, 'utf-8')
                 + bytes(self.previousHash, 'utf-8'))
        return sha.hexdigest()

def createGenesisBlock():
    return Block(0, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), 'Genesis Block', '0')

def newBlock(lastBlock):
    thisIndex = lastBlock.index + 1
    thisTimestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    thisData = 'Transaction Number: ' + str(thisIndex)
    thisHash = lastBlock.hash
    return Block(thisIndex, thisTimestamp, thisData, thisHash)