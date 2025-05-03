import os

exit_code_file = ".exit_code"
TIMEOUT_ERROR_CODE = 124


class BuildLib:
    def __init__(self) -> None:
        self.design = ""

    def set_design(self, design):
        self.design = design

    def run_test(self, testname, imagename, timeout="60", format="bmp"):
        os.system(
            f"make TEST_NAME={testname} IMAGE_NAME={imagename} \
                DESIGN_NUM={self.design} TIMEOUT={timeout} IMAGE_FORMAT={format}\
                EXIT_CODE_FILE={exit_code_file} all"
        )
        with open(exit_code_file, "r") as file:
            ret = int(file.read())
        os.remove(exit_code_file)
        if self.design == "0" and ret != TIMEOUT_ERROR_CODE:
            os.system("make coverage")
        return ret
