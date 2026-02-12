decode(unsigned char **cpp)
{
	register int x;

	x = *(*cpp)++;
	if(x == 0){
		return pull16(cpp) & 0xffff;
	} else {
		return x & 0xff;
	}
}
