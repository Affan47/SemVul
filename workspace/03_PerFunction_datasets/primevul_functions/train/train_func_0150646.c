BGD_DECLARE(void) gdImagePngCtx (gdImagePtr im, gdIOCtx * outfile)
{

	gdImagePngCtxEx (im, outfile, -1);
}
