import unittest
import unreal_engine as ue

class TestFColor(unittest.TestCase):
    def test_create(self):
        c = ue.FColor(1,2,3,4)
        self.assertEqual(c.r, 1)
        self.assertEqual(c.g, 2)
        self.assertEqual(c.b, 3)
        self.assertEqual(c.a, 4)
        
    def test_methods(self):
        c = ue.FColor(1,2,3,4)
        #print('to_hex', c.to_hex())
        #print('str', c)
    
    def test_getset(self):
        c = ue.FColor(1,2,3,4)
        c.r = 100
        c.g = 101
        c.b = 102
        c.a = 255
        self.assertEqual(c.r, 100)
        self.assertEqual(c.g, 101)
        self.assertEqual(c.b, 102)
        self.assertEqual(c.a, 255)

    def test_number_methods(self):
        c = ue.FColor(1,2,3,4)
        c += 10
        self.assertEqual(c.r, 11)
        self.assertEqual(c.g, 12)
        self.assertEqual(c.b, 13)
        self.assertEqual(c.a, 14)
    
    def test_sequence_methods(self):
        c = ue.FColor(1,2,3,4)
        self.assertEqual(len(c), 4)
        self.assertEqual(c[0], 1)
        self.assertEqual(c[1], 2)
        self.assertEqual(c[2], 3)
        self.assertEqual(c[3], 4)
    
    def test_default_colors(self):
        c = ue.FColor.Red
        self.assertEqual(c.r, 255)
        self.assertEqual(c.g, 0)
        self.assertEqual(c.b, 0)
        self.assertEqual(c.a, 255)
        
        c = ue.FColor.Blue
        self.assertEqual(c.r, 0)
        self.assertEqual(c.g, 0)
        self.assertEqual(c.b, 255)
        self.assertEqual(c.a, 255)
        
        c = ue.FColor.Yellow
        self.assertEqual(c.r, 255)
        self.assertEqual(c.g, 255)
        self.assertEqual(c.b, 0)
        self.assertEqual(c.a, 255)
        