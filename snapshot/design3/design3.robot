*** Settings ***
Library           ../BuildLib.py
Test Setup       Set Design    ${DESIGN}
Default Tags     ${DESIGN}
Test Teardown    Should Be Equal As Numbers    ${RESULT}    ${EXPECTED}

*** Variables ***
${DESIGN}      3
${RESULT}      0
${EXPECTED}    0

*** Test Cases ***
Test interrupt
    [Documentation]    Проверка корректности работы подсистемы в составе СнК в режиме работы с прерываниями (interrupt).
    ...                Не работает прерывание от writer DMA.
    ${RESULT} =    Run Test    test_01_interrupt    example_image    40    bgr
    ${EXPECTED} =    Set Variable    124
