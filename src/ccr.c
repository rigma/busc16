#include <stdlib.h>

#include <ccr.h>

ccr_t ccr_init()
{
	return (ccr_t) 0x0f;
}

u8 ccr_Z(ccr_t *ccr)
{
	return (ccr != NULL) ? (u8) (*ccr & 0x08) : FALSE;
}

void ccr_setZ(ccr_t *ccr, u8 value)
{
	if (ccr == NULL)
		return;

	*ccr = (value) ? *ccr | 0x08 : *ccr & 0x07;
}

u8 ccr_N(ccr_t *ccr)
{
	return (ccr != NULL) ? (u8) (*ccr & 0x04) : FALSE;
}

void ccr_setN(ccr_t *ccr, u8 value)
{
	if (ccr == NULL)
		return;

	*ccr = (value) ? *ccr | 0x04 : *ccr & 0x0b;
}

u8 ccr_C(ccr_t *ccr)
{
	return (ccr != NULL) ? (u8) (*ccr & 0x02) : FALSE;
}

void ccr_setC(ccr_t *ccr, u8 value)
{
	if (ccr == NULL)
		return;

	*ccr = (value) ? *ccr | 0x02 : *ccr & 0x0d;
}

u8 ccr_V(ccr_t *ccr)
{
	return (ccr != NULL) ? (u8) (*ccr & 0x01) : FALSE;
}

void ccr_setV(ccr_t *ccr, u8 value)
{
	if (ccr == NULL)
		return;

	*ccr = (value) ? *ccr | 0x01 : *ccr & 0x0e;
}
