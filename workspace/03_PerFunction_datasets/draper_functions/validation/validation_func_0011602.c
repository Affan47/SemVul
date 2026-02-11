gd_format(GVJ_t * job)
{
    gdImagePtr im;
    unsigned int x, y, color, alpha;
    unsigned int *data = (unsigned int*)(job->imagedata);
    unsigned int width = job->width;
    unsigned int height = job->height;
    gdIOCtx ctx;

    ctx.putBuf = gvdevice_gd_putBuf;
    ctx.putC = gvdevice_gd_putC;
    ctx.tell = (void*)job;

    im = gdImageCreateTrueColor(width, height);
    switch (job->device.id) {
#ifdef HAVE_GD_PNG
    case FORMAT_PNG:
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                color = *data++;


	        alpha = (color >> 25) & 0x7f;
	        im->tpixels[y][x] = (color & 0xffffff) | ((0x7f - alpha) << 24);
	    }
        }
        break;
#endif
    default:

#define TRANSPARENT 0x7ffffffe

        gdImageColorTransparent(im, TRANSPARENT);
        gdImageAlphaBlending(im, FALSE);
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                color = *data++;


	        if ((alpha = (color >> 25) & 0x7f) >= 0x20)

		    im->tpixels[y][x] = (color & 0xffffff) | ((0x7f - alpha) << 24);
	        else
		    im->tpixels[y][x] = TRANSPARENT;
	    }
        }
        break;
    }

    switch (job->device.id) {
#ifdef HAVE_GD_GIF
    case FORMAT_GIF:
	gdImageTrueColorToPalette(im, 0, 256);
	gdImageGifCtx(im, &ctx);
        break;
#endif

#ifdef HAVE_GD_JPEG
    case FORMAT_JPEG:


#define JPEG_QUALITY -1
	gdImageJpegCtx(im, &ctx, JPEG_QUALITY);
	break;
#endif

#ifdef HAVE_GD_PNG
    case FORMAT_PNG:
	gdImageSaveAlpha(im, TRUE);
	gdImagePngCtx(im, &ctx);
        break;
#endif

    case FORMAT_GD:
	gdImageGd(im, job->output_file);
	break;

    case FORMAT_GD2:
#define GD2_CHUNKSIZE 128
#define GD2_RAW 1
#define GD2_COMPRESSED 2
	gdImageGd2(im, job->output_file, GD2_CHUNKSIZE, GD2_COMPRESSED);
	break;

#ifdef HAVE_GD_GIF
    case FORMAT_WBMP:
	{

            int black = gdImageColorResolveAlpha(im, 0, 0, 0, gdAlphaOpaque);
	    gdImageWBMPCtx(im, black, &ctx);
	}
	break;
#endif

#if 0

#ifdef HAVE_GD_XPM
    case FORMAT_XBM:
	gdImageXbm(im, job->output_file);
#endif
#endif
	break;
    default:
	break;
    }

    gdImageDestroy(im);
}
