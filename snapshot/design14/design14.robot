*** Settings ***
Library           ../BuildLib.py
Test Setup       Set Design    ${DESIGN}
Default Tags     ${DESIGN}
Test Teardown    Should Be Equal As Numbers    ${RESULT}    ${EXPECTED}

*** Variables ***
${DESIGN}      14
${RESULT}      0
${EXPECTED}    0

*** Test Cases ***
Test JPEG
    [Documentation]    Проверка корретности декодирования изображения.
    ...                Появляются полосы в вертикальной плоскости с определенной периодичностью.
    ${RESULT} =    Run Test    test_05_image    huffman2_image    120    bgr
    ${EXPECTED} =    Set Variable    1
