import unittest
import unreal_engine as ue

class TestFColor(unittest.TestCase):
    def test_create(self):
        c = ue.FColor(1,2,3,4)
        self.assertEqual(c.r, 1)
        self.assertEqual(c.g, 2)
        self.assertEqual(c.b, 3)
        self.assertEqual(c.a, 4)
        print('FColor - test_create')