*** Settings ***
Library           ../BuildLib.py
Test Setup       Set Design    ${DESIGN}
Default Tags     ${DESIGN}
Test Teardown    Should Be Equal As Numbers    ${RESULT}    ${EXPECTED}

*** Variables ***
${DESIGN}      4
${RESULT}      0
${EXPECTED}    0

*** Test Cases ***
Test JPEG
    [Documentation]    Проверка корретности декодирования изображения размера больше Full HD.
    ...                В частности визуальный баг. Иногда на изображении видны чёрные области.
    ...                Работает с любыми картинками произвольно.
    ${RESULT} =    Run Test    test_05_too_big_image    too_big_image    120    bgr
    ${EXPECTED} =    Set Variable    1
