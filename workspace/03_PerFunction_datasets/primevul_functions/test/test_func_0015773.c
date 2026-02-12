gdImageCopyMerge (gdImagePtr dst, gdImagePtr src, int dstX, int dstY, int srcX, int srcY, int w, int h, int pct)
{

  int c, dc;
  int x, y;
  int tox, toy;
  int ncR, ncG, ncB;
  toy = dstY;
  for (y = srcY; (y < (srcY + h)); y++)
    {
      tox = dstX;
      for (x = srcX; (x < (srcX + w)); x++)
	{
	  int nc;
	  c = gdImageGetPixel (src, x, y);

	  if (gdImageGetTransparent (src) == c)
	    {
	      tox++;
	      continue;
	    }

	  if (dst == src)
	    {
	      nc = c;
	    }
	  else
	    {
	      dc = gdImageGetPixel (dst, tox, toy);

	      ncR = (int)(gdImageRed (src, c) * (pct / 100.0f)
		+ gdImageRed (dst, dc) * ((100 - pct) / 100.0f));
	      ncG = (int)(gdImageGreen (src, c) * (pct / 100.0f)
		+ gdImageGreen (dst, dc) * ((100 - pct) / 100.0f));
	      ncB = (int)(gdImageBlue (src, c) * (pct / 100.0f)
		+ gdImageBlue (dst, dc) * ((100 - pct) / 100.0f));


	      nc = gdImageColorResolve (dst, ncR, ncG, ncB);
	    }
	  gdImageSetPixel (dst, tox, toy, nc);
	  tox++;
	}
      toy++;
    }
}
