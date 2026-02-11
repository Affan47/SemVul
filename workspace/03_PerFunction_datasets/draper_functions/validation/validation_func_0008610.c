enc_unpack(pTHX_ U8 **sp, U8 *e, STRLEN size, U8 endian)
{
    U8 *s = *sp;
    UV v = 0;
    if (s+size > e) {
	croak("Partial character %c",(char) endian);
    }
    switch(endian) {
    case 'N':
	v = *s++;
	v = (v << 8) | *s++;
    case 'n':
	v = (v << 8) | *s++;
	v = (v << 8) | *s++;
	break;
    case 'V':
    case 'v':
	v |= *s++;
	v |= (*s++ << 8);
	if (endian == 'v')
	    break;
	v |= (*s++ << 16);
	v |= (*s++ << 24);
	break;
    default:
	croak("Unknown endian %c",(char) endian);
	break;
    }
    *sp = s;
    return v;
}
