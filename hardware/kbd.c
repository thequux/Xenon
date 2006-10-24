#include "ctools.h"
#include "video.h"
void apply_mod (int *xlated, int *mod) ;



#define KT_BREAK	0x100

#define KT_KEYPAD	0x200
#define KT_INVAL	0x000
#define KT_ASCIZ	0x400
#define KT_PFX		0x600
#define KT_MODTOGGLE	0x800
#define KT_MODTOGGLE_I	0xA00
#define KT_MODLOCK	0xC00
#define KT_FX		0xE00
#define KT_MISC		0x1000
#define KT_GREY		0x1200
#define KT_MASK		(~0x1FF)

#define F(x)		(KT_FX+ x)
#define K(x)		(KT_KEYPAD + x)
#define MOD_LSHIFT	0
#define MOD_RSHIFT	1
#define MOD_LALT	2
#define MOD_RALT	3
#define MOD_LCTRL	4
#define MOD_RCTRL	5
#define MOD_CAPS	6
#define MOD_NUML	7
#define MOD_SCRL	8
#define MOD_FAKELSH	9
#define MOD_FAKERSH	10

#define BUCKY_SHIFT	((1<<MOD_LSHIFT) | (1 << MOD_RSHIFT) | (1<<MOD_FAKELSH) | (1<<MOD_FAKERSH))
#define BUCKY_CTRL	((1<<MOD_LCTRL) | (1 << MOD_RCTRL))

#define KEY_LCTRL	(KT_MODTOGGLE	| MOD_LCTRL)
#define KEY_RCTRL	(KT_MODTOGGLE	| MOD_RCTRL)
#define KEY_LSHIFT	(KT_MODTOGGLE 	| MOD_LSHIFT)
#define KEY_RSHIFT	(KT_MODTOGGLE	| MOD_RSHIFT)
#define KEY_LALT	(KT_MODTOGGLE	| MOD_LALT)
#define KEY_RALT	(KT_MODTOGGLE	| MOD_RALT)
#define KEY_CAPS	(KT_MODLOCK	| MOD_CAPS)
#define KEY_SCRL	(KT_MODLOCK	| MOD_SCRL)
#define KEY_NUML	(KT_MODLOCK	| MOD_NUML)
#define KEY_FAKELSH	(KT_MODTOGGLE_I	| MOD_FAKELSH)
#define KEY_FAKERSH	(KT_MODTOGGLE_I	| MOD_FAKERSH)
#define ASR		(KT_MISC	| 0x01) /* alt-sysrq */
#define CTRL_PSCR	(KT_MISC	| 0x02)	/* Ctrl-PrintScr */
#define	PSCR		(KT_MISC	| 0x03) /* PrintScr */		
#define CBRK		(KT_MISC	| 0x04) /* CTRL_BRK */

#define GREY_LEFT	(KT_GREY	| 0x01)
#define GREY_RIGHT	(KT_GREY	| 0x02)
#define GREY_UP		(KT_GREY	| 0x03)
#define GREY_DOWN	(KT_GREY	| 0x04)
#define GREY_HOME	(KT_GREY	| 0x05)
#define GREY_END	(KT_GREY	| 0x06)
#define GREY_INS	(KT_GREY	| 0x07)
#define GREY_DEL	(KT_GREY	| 0x08)
#define GREY_PGUP	(KT_GREY	| 0x09)
#define GREY_PGDN	(KT_GREY	| 0x0A)
#define KEY_IGNORE		(~0x0)

struct kmap_ent {
	char type;
	union {
		char cval;
		char* sval;
		int pfxTable;
		char mod;
	} u;
};
/* 0x37: only on 83-key (KP-*) and 84-key (*,PRNTSCR)
 * 0x55: F11 on a Cherry G80-0777 keyboard, as F12 on a Telerate keyboard, as PF1 on a Focus 9000 keyboard, and as FN on an IBM ThinkPad.\
 * 0x56: unlabeled, on nonus usually
 * 0x59-0x7f: unsupported
 */

int kmap[128]  = {
/*	0x_0, 0x_1, 0x_2, 0x_3, 0x_4, 0x_5, 0x_6, 0x_7, 0x_8, 0x_9, 0x_A, 0x_B, 0x_C, 0x_D, 0x_E, 0x_F, */
/*0_*/	0x00, 0x1b, '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',  '-',  '=',  0x08, '\t',
/*1_*/  'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',  'o',  'p',  '[',  ']',  '\n', KEY_LCTRL, 'a', 's',
/*2_*/	'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  '\'', '`',  KEY_LSHIFT, '\\', 'z', 'x', 'c', 'v',
/*3_*/	'b',  'n',  'm',  ',',  '.',  '/', KEY_RSHIFT,  0x00, KEY_LALT, ' ', KEY_CAPS, F(1), F(2), F(3), F(4), F(5),
/*4_*/	F(6),F(7),F(8),F(9),F(10),KEY_NUML,KEY_SCRL,K('7'),K('8'),K('9'),K('-'),K('4'),K('5'),K('6'),K('+'),K('1'),
/*5_*/	K('2'),K('3'),K('0'),K('.'),ASR,0x00,0x00,F(11),F(12),0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*6_*/	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*7_*/	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

int kmap_e0[128] = {
/*	0x_0, 0x_1, 0x_2, 0x_3, 0x_4, 0x_5, 0x_6, 0x_7, 0x_8, 0x_9, 0x_A, 0x_B, 0x_C, 0x_D, 0x_E, 0x_F, */
/*0_*/	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*1_*/	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,K('\n'),KEY_RCTRL, 0x00, 0x00,
/*2_*/	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, KEY_FAKELSH, 0x00, 0x00, 0x00, 0x00, 0x00,
/*3_*/	0x00, 0x00, 0x00, 0x00, 0x00,K('/'),KEY_FAKERSH,CTRL_PSCR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*4_*/	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, CBRK, GREY_HOME, GREY_UP, GREY_PGUP, 0x00, GREY_LEFT, 0x00, GREY_RIGHT, 0x00, GREY_END,
/*5_*/	GREY_DOWN, GREY_PGDN, GREY_INS, GREY_DEL, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*6_*/	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*7_*/	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//
//
//`1234567890-=
// 0000000 60 31 32 33 34 35 36 37 38 39 30 2d 3d 20 20 0a
// 0000020 7e 21 40 23 24 25 5e 26 2a 28 29 5f 2b 20 20 0a
// ~!@#$%^&*()_+

int shift_asc[128] = {
/*	0x_0, 0x_1, 0x_2, 0x_3, 0x_4, 0x_5, 0x_6, 0x_7, 0x_8, 0x_9, 0x_A, 0x_B, 0x_C, 0x_D, 0x_E, 0x_F, */
/*0_*/	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
/*1_*/	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 
/*2_*/	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x5f, 0x3e, 0x3f, 
/*3_*/	0x29, 0x21, 0x40, 0x23, 0x24, 0x25, 0x5e, 0x26, 0x2a, 0x28, 0x00, 0x3a, 0x00, 0x2b, 0x00, 0x00, 
/*4_*/	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
/*5_*/	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7b, 0x7c, 0x7d, 0x00, 0x00, 
/*6_*/	0x7e, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 
/*7_*/	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00  } ;
//kmap_ent keymap[256][16] = {
//	{ /* 0 */

int parse_buf (unsigned char* buf) { // 0: invalid key. Otherwise, the value of the key (unshifted)
			    // < 128: ascii key
			    // > 128: non-ascii
	static int mod;
	int xlated;
	if        (buf[0] == 0x00) {
		k_swrite("\x1b[32mINVALID SCANCODE: ", OUT_DBG);
		//k_swrite(buf, OUT_DBG);
		k_swrite("\x1b[39m\n", OUT_DBG);
	} else if (buf[0] == 0xe0) { // look in KMAP_E0
	} else if (buf[0] == 0xe1) { // Check for BREAK
		;
	} else {
		char buf2[] = {0,0};
		char IS_BREAK = buf[0] & 0x80;
		char tmp = buf[0] & 0x7f;
		xlated = kmap[(int)tmp] | (IS_BREAK ? KT_BREAK : 0);
		apply_mod(&xlated, &mod);
		if ((xlated != KEY_IGNORE) && (!IS_BREAK)) {
			buf2[0] = xlated & 0x7f;
			k_swrite(buf2, OUT_STD);
		}

		;
	}
	return 0;
}

void apply_mod (int *_xlated, int *_mod) {
	int xlated = *_xlated;
	int mod = *_mod;
	int val = xlated & 0xff;
	switch (xlated & KT_MASK) {
		case KT_MODTOGGLE:
			if(xlated & KT_BREAK) {
				mod &= ~(1 << val);
			} else {
				mod |=  (1 << val);
			}
			xlated=KEY_IGNORE;
			break;
		case KT_MODTOGGLE_I:
			if (xlated & KT_BREAK) {
				mod |=  (1 << val);
			} else {
				mod &= ~(1 << val);
			}
			xlated = KEY_IGNORE;
			break;
		case KT_MODLOCK:
			if (!(xlated & KT_BREAK))
				mod ^= (1 << val);
			xlated = KEY_IGNORE;
			break;

		case 0:
			//ascii:
			//if (val >= 'a' && val <= 'z') {
			//	val = val & ~0x20;
			//} 
			if (val >= 0x00 && val < 0x80) {
				int shift = (mod & BUCKY_SHIFT);
				if (val >= 'a' && val <= 'z')
					//shift = 1;
					shift = shift | (mod & (1 <<MOD_CAPS));

				if (shift) {
					
					val = shift_asc[val];
					if (val == 0) {
						k_swrite("INVALID SHIFT!\n", OUT_DBG);
					}
					xlated = val;
				}
			}
			break;
	}
	*_xlated = xlated;
	*_mod = mod;
}


void sc_proc (unsigned char keycode) {
	static unsigned char scbuf[6];
	static unsigned int scpos = 0;

	scbuf[scpos++]=keycode;
	switch (scbuf[0]) {
		case 0xe0: // 1 escape
			if (scpos < 2)
				return;
			k_swrite("\x1b[1m1\x1b[0m", OUT_STD);
			scpos = 0;
			break;
		case 0xe1: // 2 escapes
			if (scpos < 3)
				return;
			scpos = 0;
			//k_swrite("2", OUT_STD);
			break;
		default:
			//k_swrite("0", OUT_STD);
			parse_buf(scbuf);
			scpos = 0;
			break;

	}
	return;
}
