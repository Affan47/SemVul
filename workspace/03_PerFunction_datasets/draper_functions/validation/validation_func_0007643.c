IMGbltTransDecompress(char* imageBuf, int pitch, int desX, int desY, char* bitmapBuf)
{
	int destline = desY * pitch + desX;
	int width = ((unsigned char*)bitmapBuf)[0] + (((unsigned char*)bitmapBuf)[1]<<8);
	int height = ((unsigned char*)bitmapBuf)[2] + (((unsigned char*)bitmapBuf)[3]<<8);
	int esi = 4;
	int pixelsToSkip = 0;
	int al;

	for ( int j=0; j<height; ++j,destline+=pitch )
	{
		for ( int i=0; i<width; ++i )
		{
			if (pixelsToSkip != 0)
			{
				if (pixelsToSkip >= width-i)
				{

					pixelsToSkip -= width-i;
					break;
				}
				i += pixelsToSkip;
				pixelsToSkip = 0;
			}
			al = ((unsigned char*)bitmapBuf)[ esi++ ];
			if (al < MIN_TRANSPARENT_CODE)
			{
				imageBuf[ destline + i ] = al;
			}
			else if (al == MANY_TRANSPARENT_CODE)
			{
				pixelsToSkip = ((unsigned char*)bitmapBuf)[ esi++ ] -1;
			}
			else
			{
				pixelsToSkip = 256 - al -1;
			}
		}
	}
}
