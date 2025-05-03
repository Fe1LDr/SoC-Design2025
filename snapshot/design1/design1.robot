*** Settings ***
Library           ../BuildLib.py
Test Setup       Set Design    ${DESIGN}
Default Tags     ${DESIGN}
Test Teardown    Should Be Equal As Numbers    ${RESULT}    ${EXPECTED}

*** Variables ***
${DESIGN}      1
${RESULT}      0
${EXPECTED}    0

*** Test Cases ***
Test access to DMA registers
    [Documentation]    Проверка доступа к адресному пространству DMA.
    ...                Неправильное значение регистра версии DMA (0x42 вместо 0x01).
    ${RESULT} =    Run Test    test_00_dma_registers    example_image    120    bgr
    ${EXPECTED} =    Set Variable    1
