#pragma once

#include "mem_access.h"

extern int __IMAGE_START_POSITION;
extern int __IMAGE_END_POSITION;
extern int __BMP_START_POSITION;
extern int __BUFFER_START_POSITION;
extern int __EXPECTED_START_POSITION;
extern int __EXPECTED_END_POSITION;

#define kImageSize          ((int)(&__IMAGE_END_POSITION - &__IMAGE_START_POSITION))
#define pJpegImage          (&__IMAGE_START_POSITION)
#define pSocAxilOutBuffer   (&__BUFFER_START_POSITION)
#define pInnerDecodeBuffer  (&__BMP_START_POSITION)
#define pGoldenImage        (&__EXPECTED_START_POSITION)

int sim_main();
