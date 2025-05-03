*** Settings ***
Library           ../BuildLib.py
Test Setup       Set Design    ${DESIGN}
Default Tags     ${DESIGN}
Test Teardown    Should Be Equal As Numbers    ${RESULT}    ${EXPECTED}

*** Variables ***
${DESIGN}      9
${RESULT}      0
${EXPECTED}    0

*** Test Cases ***
Test JPEG
    [Documentation]    Проверка корретности декодирования изображения.
    ...                Проинвертированные размеры изображения (ширина и высота).
    ...                Обработка пикселей происходит последовательно слева направо, сверху вниз с измененными размерами.
    ${RESULT} =    Run Test    test_05_image    huffman2_image    120    bgr
    ${EXPECTED} =    Set Variable    0
