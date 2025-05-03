*** Settings ***
Library           ../BuildLib.py
Test Setup       Set Design    ${DESIGN}
Default Tags     ${DESIGN}
Test Teardown    Should Be Equal As Numbers    ${RESULT}    ${EXPECTED}

*** Variables ***
${DESIGN}      0
${RESULT}      0
${EXPECTED}    0

*** Test Cases ***
Test access to DMA registers
    [Documentation]    Проверка доступа к адресному пространству DMA.
    ${RESULT} =    Run Test    test_00_dma_registers    example_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test access to JPEG registers
    [Documentation]    Проверка доступа к адресному пространству JPEG.
    ${RESULT} =    Run Test    test_00_jpeg_registers    example_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test polling
    [Documentation]    Проверка корректности работы подсистемы в составе СнК в режиме опроса (polling).
    ${RESULT} =    Run Test    test_01_polling    example_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test interrupt
    [Documentation]    Проверка корректности работы подсистемы в составе СнК в режиме работы с прерываниями (interrupt).
    ${RESULT} =    Run Test    test_01_interrupt    example_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test simultaniously
    [Documentation]    Проверка корректности работы подсистемы при одновременной работе Read/Write.
    ${RESULT} =    Run Test    test_02_simultaniously    example_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test consistently
    [Documentation]    Проверка корректности работы подсистемы при последовательной работе Read/Write.
    ${RESULT} =    Run Test    test_02_consistently    example_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test transaction more than max length
    [Documentation]    Проверка корректности работы подсистемы при длине транзакции больше 1024 байт.
    ${RESULT} =    Run Test    test_03_too_big_transaction_length    example_image    120    bgr
    ${EXPECTED} =    Set Variable    124
Test transaction max length
    [Documentation]    Проверка корректности работы подсистемы при длине транзакции 1024 байт.
    ${RESULT} =    Run Test    test_03_transaction_length    example_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test transaction 32 byte length
    [Documentation]    Проверка корректности работы подсистемы при длине транзакции 32 байта (8 слов).
    ${RESULT} =    Run Test    test_03_32_transaction_length    example_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test transaction zero length
    [Documentation]    Проверка корректности работы подсистемы при длине транзакции 0.
    ${RESULT} =    Run Test    test_03_zero_transaction_length    example_image    120    bgr
    ${EXPECTED} =    Set Variable    124
Test transaction 1 length by 1 transaction
    [Documentation]    Проверка корректности работы подсистемы при одном слове на транзакцию.
    ${RESULT} =    Run Test    test_03_one_length_by_transaction    example_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test stride for 2D transfer
    [Documentation]    Проверка корректности работы подсистемы при ненулевом stride.
    ${RESULT} =    Run Test    test_04_stride    example_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test stride for 2D transfer error
    [Documentation]    Проверка некорректности работы подсистемы при ненулевом неверном stride.
    ${RESULT} =    Run Test    test_04_stride_error    example_image    120    bgr
    ${EXPECTED} =    Set Variable    1
Test more than Full HD JPEG
    [Documentation]    Проверка корретности декодирования изображения размера больше Full HD.
    ${RESULT} =    Run Test    test_05_too_big_image    too_big_image    120    bgr
    ${EXPECTED} =    Set Variable    1
Test Full HD JPEG
    [Documentation]    Проверка корретности декодирования изображения размера Full HD.
    ${RESULT} =    Run Test    test_05_image    full_hd_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test zero size JPEG
    [Documentation]    Проверка корретности декодирования изображения размера 0.
    ${RESULT} =    Run Test    test_05_image    zero_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test 333x555 JPEG
    [Documentation]    Проверка корретности декодирования изображения 333x555.
    ${RESULT} =    Run Test    test_05_image    333x555_image    120    bgr
    ${EXPECTED} =    Set Variable    1
Test colorless JPEG
    [Documentation]    Проверка корретности декодирования бесцветного изображения.
    ${RESULT} =    Run Test    test_05_image    colorless_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test monochrome JPEG
    [Documentation]    Проверка корретности декодирования монохромного изображения.
    ${RESULT} =    Run Test    test_05_image    monochrome_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test baseline JPEG
    [Documentation]    Проверка корретности декодирования baseline изображения.
    ${RESULT} =    Run Test    test_05_image    baseline_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test progressive JPEG
    [Documentation]    Проверка корретности декодирования только 1 слоя progressive изображения.
    ${RESULT} =    Run Test    test_05_progressive_image    progressive_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test errors JPEG
    [Documentation]    Проверка корретности декодирования изображения с ошибками в кадрах.
    ${RESULT} =    Run Test    test_05_image    errors_image    120    bgr
    ${EXPECTED} =    Set Variable    1
Test JPEG with DRI
    [Documentation]    Проверка корретности декодирования изображения с DRI меткой.
    ${RESULT} =    Run Test    test_05_image    dri_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test JPEG with comment
    [Documentation]    Проверка корретности декодирования изображения с комментарием.
    ${RESULT} =    Run Test    test_05_image    comment_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test JPEG with escaping FF00 characters
    [Documentation]    Проверка корретности декодирования изображения с поддержкой экранирования символов FF00.
    ${RESULT} =    Run Test    test_05_image    ff00_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test JPEG with YCbCr 4:4:4
    [Documentation]    Проверка корретности декодирования изображения с поддержкой режима цветовой субдискретизации YCbCr 4:4:4.
    ${RESULT} =    Run Test    test_05_image    ycbcr_444_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test JPEG with YCbCr 4:2:2H
    [Documentation]    Проверка корретности декодирования изображения с поддержкой режима цветовой субдискретизации YCbCr 4:2:2H.
    ${RESULT} =    Run Test    test_05_image    ycbcr_422h_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test JPEG with YCbCr 4:2:2V
    [Documentation]    Проверка корретности декодирования изображения с поддержкой режима цветовой субдискретизации YCbCr 4:2:2V.
    ${RESULT} =    Run Test    test_05_image    ycbcr_422v_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test JPEG with more than 4 Huffman tables
    [Documentation]    Проверка корретности декодирования изображения содержащее больше 4 таблиц Huffman.
    ${RESULT} =    Run Test    test_05_image    huffman5_image    120    bgr
    ${EXPECTED} =    Set Variable    1
Test JPEG with 4 Huffman tables
    [Documentation]    Проверка корретности декодирования изображения содержащее 4 таблицы Huffman.
    ${RESULT} =    Run Test    test_05_image    huffman4_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test JPEG with 2 Huffman tables
    [Documentation]    Проверка корретности декодирования изображения содержащее 2 таблицы Huffman.
    ${RESULT} =    Run Test    test_05_image    huffman2_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test JPEG with no Huffman tables
    [Documentation]    Проверка корретности декодирования изображения не содержащее таблиц Huffman.
    ${RESULT} =    Run Test    test_05_image    huffman0_image    120    bgr
    ${EXPECTED} =    Set Variable    0
Test PNG
    [Documentation]    Проверка корретности декодирования изображения формата PNG.
    ${RESULT} =    Run Test    test_05_not_jpg_image    png_image    120    bgr
    ${EXPECTED} =    Set Variable    1
Test GIF
    [Documentation]    Проверка корретности декодирования изображения формата GIF.
    ${RESULT} =    Run Test    test_05_not_jpg_image    gif_image    40    bgr
    ${EXPECTED} =    Set Variable    1
Test correct programm reset
    [Documentation]    Проверка корректности декодирования изображения при выполнении программного сброса.
    ${RESULT} =    Run Test    test_06_programm_reset    progressive_image    40    bgr
    ${EXPECTED} =    Set Variable    0
