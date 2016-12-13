import unittest
import operator

class Robot():
    movement = { 'N':(0,1), 'E':(1,0), 'S':(0,-1), 'W':(-1,0) }
    compass = {0:'N', 1:'E', 2:'S', 3:'W'}
    turning = {'L':-1, 'R':1}

    def __init__(self, directions):
        self.facing = 0;
        self.loc = (0, 0) 
        self.visitedLocs = {}
        self.firstLoc = None
        for direction in directions.rsplit(", "):
            turn, number = direction[0], direction[1:]
            self._turn(turn)
            self._move(int(number))

    def _evaluate(self, turn, number):
        self._turn(turn)
        self._move(number)

    def _turn(self, direction):
        self.facing = (self.facing + self.turning[direction]) % 4

    def _move(self, number):
        for _ in range(number):
            self.loc = tuple(map(operator.add, self.loc , self.movement[self.compass[self.facing]]))
            if self.loc in self.visitedLocs and not self.firstLoc:
                self.firstLoc = self.loc
            else:
                self.visitedLocs[self.loc] = True

    def distance(self):
        return abs(self.loc[0]) + abs(self.loc[1])

    def distanceRevisit(self):
        return abs(self.firstLoc[0]) + abs(self.firstLoc[1])

class MyTest(unittest.TestCase):
    def test_1(self):
        rob = Robot("R2, L3")
        self.assertEqual(rob.distance(), 5)

    def test_2(self):
        rob = Robot("R2, R2, R2")
        self.assertEqual(rob.distance(), 2)

    def test_3(self):
        rob = Robot("R5, L5, R5, R3")
        self.assertEqual(rob.distance(), 12)

    def test_4(self):
        rob = Robot("R8, R4, R4, R8")
        self.assertEquals(rob.distanceRevisit(), 4)

if __name__ == '__main__':
    rob = Robot("R3, R1, R4, L4, R3, R1, R1, L3, L5, L5, L3, R1, R4, L2, L1, R3, L3, R2, R1, R1, L5, L2, L1, R2, L4, R1, L2, L4, R2, R2, L2, L4, L3, R1, R4, R3, L1, R1, L5, R4, L2, R185, L2, R4, R49, L3, L4, R5, R1, R1, L1, L1, R2, L1, L4, R4, R5, R4, L3, L5, R1, R71, L1, R1, R186, L5, L2, R5, R4, R1, L5, L2, R3, R2, R5, R5, R4, R1, R4, R2, L1, R4, L1, L4, L5, L4, R4, R5, R1, L2, L4, L1, L5, L3, L5, R2, L5, R4, L4, R3, R3, R1, R4, L1, L2, R2, L1, R4, R2, R2, R5, R2, R5, L1, R1, L4, R5, R4, R2, R4, L5, R3, R2, R5, R3, L3, L5, L4, L3, L2, L2, R3, R2, L1, L1, L5, R1, L3, R3, R4, R5, L3, L5, R1, L3, L5, L5, L2, R1, L3, L1, L3, R4, L1, R3, L2, L2, R3, R3, R4, R4, R1, L4, R1, L5")
    print rob.distance()
    print rob.distanceRevisit()
    unittest.main()


