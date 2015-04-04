#include <opcodes.h>

static u8 add(u8 *d0, u8 input, ccr_t *ccr)
{
	u16 tmp = *d0 + input;

	*d0 = (u8) (tmp & 0xff);
	if (tmp > 0xff)
		ccr_setC(ccr);

	return TRUE;
}

static u8 sub(u8 *d0, u8 input, ccr_t *ccr)
{
	short tmp = (short) *d0 - (short) input;

	*d0 = (u8) (tmp & 0xff);
	if (!tmp)
		ccr_setZ(ccr);
	else if (tmp < 0x0)
		ccr_setN(ccr);

	return TRUE;
}

static u8 mul(u8 *d0, u8 input, ccr_t *ccr)
{
	u16 tmp = *d0 * input;

	*d0 = (u8) (tmp & 0xff);
	if (tmp > 0xff)
		ccr_setV(ccr);

	return TRUE;
}

static u8 div(u8 *d0, u8 input, ccr_t *ccr)
{
	u16 tmp = *d0 / input;

	*d0 = (u8) (tmp & 0xff);
	if (tmp > 0xff)
		ccr_setV(ccr);

	return TRUE;
}

static u8 cmp(u8 *d0, u8 input, ccr_t *ccr)
{
	short tmp = (short) *d0 - (short) input;

	if (!tmp)
		ccr_setZ(ccr);
	else if (tmp < 0x0)
		ccr_setN(ccr);

	return TRUE;
}

u8 (*const opcodes[])(u8 *d0, u8 input, ccr_t *ccr) = {
	(void*) 0x0, (void*) 0x0, (void*) 0x0, (void*) 0x0, (void*) 0x0, (void*) 0x0, (void*) 0x0, (void*) 0x0,
	add, sub, mul, div, cmp, (void*) 0x0, (void*) 0x0, (void*) 0x0,
	(void*) 0x0, (void*) 0x0, (void*) 0x0, (void*) 0x0, (void*) 0x0, (void*) 0x0, (void*) 0x0, (void*) 0x0,
	(void*) 0x0, (void*) 0x0, (void*) 0x0, (void*) 0x0, (void* )0x0, (void*) 0x0, (void*) 0x0, (void*) 0x0
};
