processImage(imageStruct &image)
{
  unsigned char *src = image.data;
  unsigned char *dest;

  int x, y, xx, yy, i;
  unsigned char *p, *q;

  if (m_force || (myImage.xsize*myImage.ysize*myImage.csize != image.xsize*image.ysize*image.csize)){
    int dataSize = image.xsize * image.ysize * image.csize;
    myImage.clear();
    m_force = false;

    myImage.allocate(dataSize);

    makePuzzleBlocks(image.xsize, image.ysize, image.csize);
    shuffle();
  }

  myImage.xsize = image.xsize;
  myImage.ysize = image.ysize;
  myImage.csize = image.csize;
  myImage.type  = image.type;

  dest = myImage.data;

  i=0;
  for (y=0; y<blockh; y++){
    for(x=0; x<blockw; x++) {
      p = &src[blockoffset[blockpos[i]]];
      q = &dest[blockoffset[i]];
      if(m_game && spacepos == i) {
	for(yy=0; yy<blockysize; yy++) {
	  for(xx=0; xx<blockxsize*image.csize; xx++) {
	    q[xx] = 0;
	  }
	  q += image.xsize*image.csize;
	}
      } else {
	for(yy=0; yy<blockysize; yy++) {
	  for(xx=0; xx<blockxsize*image.csize; xx++) {
	    q[xx] = p[xx];
	  }
	  q += image.xsize*image.csize;
	  p += image.xsize*image.csize;
	}
      }
      i++;
    }
  }

  p = src +  blockw * blockxsize;
  q = dest + blockw * blockxsize;

  if(marginw) {
    for(y=0; y<blockh*blockysize; y++) {
      for(x=0; x<marginw; x++) {
	*q++ = *p++;
      }
      p += image.xsize - marginw;
      q += image.xsize - marginw;
    }
  }

  if(marginh) {
    p = src + (blockh * blockysize) * image.xsize;
    q = dest + (blockh * blockysize) * image.xsize;
    memcpy(p, q, marginh*image.xsize*image.csize);
  }

  image.data=myImage.data;
}
