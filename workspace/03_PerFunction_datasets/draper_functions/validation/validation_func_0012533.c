snes_sh_update( int param, INT16 **buffer, int length )
{
	INT16 left, right;

	while( length-- > 0 )
	{

		left = 0;
		right = 0;


		*(buffer[0]++) = left;
		*(buffer[1]++) = right;
	}
}
