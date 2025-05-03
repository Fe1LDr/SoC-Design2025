*** Settings ***
Library           ../BuildLib.py
Test Setup       Set Design    ${DESIGN}
Default Tags     ${DESIGN}
Test Teardown    Should Be Equal As Numbers    ${RESULT}    ${EXPECTED}

*** Variables ***
${DESIGN}      13
${RESULT}      0
${EXPECTED}    0

*** Test Cases ***
Test access to DMA registers
    [Documentation]    Проверка доступа к адресному пространству DMA.
    ...                Все регистры нулевые, в них нельзя писать.
    ${RESULT} =    Run Test    test_00_dma_registers    example_image    120    bgr
    ${EXPECTED} =    Set Variable    1
