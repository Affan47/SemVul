ReadImage(gdImagePtr im, gdIOCtx *fd, int len, int height, unsigned char (*cmap)[256], int interlace, int *ZeroDataBlockP)
{
	unsigned char c;
	int xpos = 0, ypos = 0, pass = 0;
	int v, i;
	LZW_STATIC_DATA sd;


	if(!ReadOK(fd, &c, 1)) {
		return;
	}

	if(c > MAX_LWZ_BITS) {
		return;
	}


	for(i=0; (i < gdMaxColors); i++) {
		im->red[i] = cmap[CM_RED][i];
		im->green[i] = cmap[CM_GREEN][i];
		im->blue[i] = cmap[CM_BLUE][i];
		im->open[i] = 1;
	}


	im->colorsTotal = gdMaxColors;
	if(LWZReadByte(fd, &sd, TRUE, c, ZeroDataBlockP) < 0) {
		return;
	}


	while((v = LWZReadByte(fd, &sd, FALSE, c, ZeroDataBlockP)) >= 0 ) {
		if(v >= gdMaxColors) {
			v = 0;
		}


		if(im->open[v]) {
			im->open[v] = 0;
		}

		gdImageSetPixel(im, xpos, ypos, v);

		++xpos;
		if(xpos == len) {
			xpos = 0;
			if(interlace) {
				switch (pass) {
				case 0:
				case 1:
					ypos += 8;
					break;
				case 2:
					ypos += 4;
					break;
				case 3:
					ypos += 2;
					break;
				}

				if(ypos >= height) {
					++pass;
					switch (pass) {
					case 1:
						ypos = 4;
						break;
					case 2:
						ypos = 2;
						break;
					case 3:
						ypos = 1;
						break;
					default:
						goto fini;
					}
				}
			} else {
				++ypos;
			}
		}

		if(ypos >= height) {
			break;
		}
	}

fini:
	if(LWZReadByte(fd, &sd, FALSE, c, ZeroDataBlockP) >=0) {

	}
}
