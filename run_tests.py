import os.path
import unittest
import unreal_engine as ue

pyue_base = ue.find_plugin('FatPython').get_base_dir()
print('FatPython Path: ', pyue_base)

loader = unittest.TestLoader()
tests = loader.discover(os.path.join(pyue_base, 'tests'))

runner = unittest.runner.TextTestRunner()
runner.run(tests)
