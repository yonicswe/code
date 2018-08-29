/* how to set or reset a bit in a bitmask
 * set    : bitmask != bit
 * reset  : bitmask &= ~bit
 *
 * note
 *   it wont work
 *   when u use define instead of enum for the bit
 *   e.g
 *   	#define BIT3 1<<3
 *
 *   i still dont understand why
 */

enum {
	BIT0 = 1 << 0,
	BIT1 = 1 << 1,
	BIT2 = 1 << 2,
	BIT3 = 1 << 3,
	BIT4 = 1 << 4,
	BIT5 = 1 << 5,
	BIT6 = 1 << 6,
	BIT7 = 1 << 7,
};

int main()
{
	int bitmask = 0xffff;
	int b = BIT3;

	/* set bit 3 */
	bitmask &= ~BIT3;
	/* reset bit 3 */
	bitmask |= BIT3;

	/* set bit 5 */
	bitmask &= ~BIT5;
	/* reset bit 5 */
	bitmask |= BIT5;

	return 0;
}
