*** Settings ***
Library           ../BuildLib.py
Test Setup       Set Design    ${DESIGN}
Default Tags     ${DESIGN}
Test Teardown    Should Be Equal As Numbers    ${RESULT}    ${EXPECTED}

*** Variables ***
${DESIGN}      6
${RESULT}      0
${EXPECTED}    0

*** Test Cases ***
Test interrupt
    [Documentation]    Проверка корректности работы подсистемы в составе СнК в режиме работы с прерываниями (interrupt).
    ...                Не работает interrupt JPEG декодера.
    ${RESULT} =    Run Test    test_01_interrupt    example_image    120    bgr
    ${EXPECTED} =    Set Variable    124
Test JPEG
    [Documentation]    Подмена изображения на rickroll.
    ${RESULT} =    Run Test    test_05_image    comment_image    120    bgr
    ${EXPECTED} =    Set Variable    1
