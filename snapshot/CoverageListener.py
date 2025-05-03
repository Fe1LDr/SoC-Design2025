from robot import result, running
from robot.api.interfaces import ListenerV3
import subprocess

kNotCollectedMsg = 'Покрытие не собрано, возможную причину см. в TEST_GUIDELINE.md, раздел "Результаты теста"'


class CoverageListener(ListenerV3):

    def end_suite(self, data: running.TestCase, result: result.TestCase):
        try:
            result.doc = subprocess.check_output(["lcov", "-summary", f"./build/sim/merged.info"], text=True)[42:-56]
        except Exception:
            result.doc = kNotCollectedMsg
