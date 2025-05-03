*** Settings ***
Library           ../BuildLib.py
Test Setup       Set Design    ${DESIGN}
Default Tags     ${DESIGN}
Test Teardown    Should Be Equal As Numbers    ${RESULT}    ${EXPECTED}

*** Variables ***
${DESIGN}      2
${RESULT}      0
${EXPECTED}    0

*** Test Cases ***
Test access to JPEG registers
    [Documentation]    Проверка доступа к адресному пространству JPEG.
    ...                Неправильный режим доступа у регистра версии JPEG (в него можно записать все 0).
    ${RESULT} =    Run Test    test_00_jpeg_registers    example_image    120    bgr
    ${EXPECTED} =    Set Variable    1
