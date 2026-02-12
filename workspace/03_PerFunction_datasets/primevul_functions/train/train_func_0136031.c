static void k_dead(struct vc_data *vc, unsigned char value, char up_flag)
{
	static const unsigned char ret_diacr[NR_DEAD] = {
		'`',
		'\'',
		'^',
		'~',
		'"',
		',',
		'_',
		'U',
		'.',
		'*',
		'=',
		'c',
		'k',
		'i',
		'#',
		'o',
		'!',
		'?',
		'+',
		'-',
		')',
		'(',
		':',
		'n',
		';',
		'$',
		'@',
	};

	k_deadunicode(vc, ret_diacr[value], up_flag);
}
