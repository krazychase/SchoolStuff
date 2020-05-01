import unittest
import blockchain

class BlockTest(unittest.TestCase):
    def testGenisis(self):
        genesis = blockchain.createGenesisBlock()
        self.assertEqual(genesis.index, 0)
        self.assertEqual(genesis.data, 'Genesis Block')

    def testBlock(self):
        genesis = blockchain.createGenesisBlock()
        testBlock = blockchain.newBlock(genesis)
        self.assertEqual(testBlock.index, 1)
        self.assertEqual(testBlock.data, 'Transaction Number: 1')
        self.assertEqual(testBlock.previousHash, genesis.hash)