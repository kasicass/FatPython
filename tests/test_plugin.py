import unittest
import unreal_engine as ue

class TestPlugin(unittest.TestCase):
    def test_find(self):
        plugin = ue.find_plugin('FatPython')
        self.assertEqual(plugin.get_name(), 'FatPython')
        
    def test_enabled(self):
        plugin = ue.find_plugin('FatPython')
        self.assertTrue(plugin.is_enabled)
