*** Settings ***
Library           ../BuildLib.py
Test Setup       Set Design    ${DESIGN}
Default Tags     ${DESIGN}
Test Teardown    Should Be Equal As Numbers    ${RESULT}    ${EXPECTED}

*** Variables ***
${DESIGN}      12
${RESULT}      0
${EXPECTED}    0

*** Test Cases ***
Test interrupt
    [Documentation]    Проверка корректности работы подсистемы в составе СнК в режиме работы с прерываниями (interrupt).
    ...                Не приходит decode JPEG.
    ${RESULT} =    Run Test    test_01_interrupt    example_image    20    bgr
    ${EXPECTED} =    Set Variable    124
