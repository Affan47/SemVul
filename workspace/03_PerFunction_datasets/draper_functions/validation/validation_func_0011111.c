drawImage(
	int						x,
	int						y,
	const utils::CImage	&img )
{
	MRPT_START

	int		img_lx = img.getWidth();
	int		img_ly = img.getHeight();

	if (img.isColor())
	{
		for (int xx=0;xx<img_lx;xx++)
			for (int yy=0;yy<img_ly;yy++)
				setPixel(x+xx,y+yy, *((int*)img(xx,yy)) );
	}
	else
	{
		unsigned char	c;
		int				col;
		for (int xx=0;xx<img_lx;xx++)
			for (int yy=0;yy<img_ly;yy++)
			{
				c = *((unsigned char *)img(xx,yy));
				col = c | (c<<8) | (c<<16);
				setPixel(x+xx,y+yy, col );
			}
	}


	MRPT_END
}
