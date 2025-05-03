__flash =  0x80000000;
__flash_size = 0x01000000;
__ram = 0x81000000;
__ram_size = 0x04000000;
__stack_size = 4k;

__user = 0x85000000;
__user_size = 0x04000000;
__raw_image_size = 16m;

INCLUDE picolibc.ld

MEMORY {
	user(rw!x): ORIGIN = __user, LENGTH = __user_size
}

SECTIONS
{
	.text : {
		*(.text*);
	} >flash AT>flash :text

	.image : ALIGN(4) {
		__IMAGE_START_POSITION = ABSOLUTE(.);
		. = ALIGN(4);
		*(.image*);
		. = ALIGN(4);
		__IMAGE_END_POSITION = ABSOLUTE(.);
		. = ALIGN(4);
		__EXPECTED_START_POSITION = ABSOLUTE(.);
		*(.expected*);
		. = ALIGN(4);
	} > ram AT>ram :ram

	.buffer : ALIGN(4) {
		__BUFFER_START_POSITION = ABSOLUTE(.);
		. = . + __raw_image_size;
		. = ALIGN(32);
	} > user

	.bmp : ALIGN(4) {
		__BMP_START_POSITION = ABSOLUTE(.);
		. = . + __raw_image_size;
		. = ALIGN(32);
	} > user
}
