check_alloc_btres_lock(struct bttv *btv, struct bttv_fh *fh, int bit)
{
	int xbits;

	if (fh->resources & bit)

		return 1;

	xbits = bit;
	if (bit & (RESOURCE_VIDEO_READ | RESOURCE_VIDEO_STREAM))
		xbits |= RESOURCE_VIDEO_READ | RESOURCE_VIDEO_STREAM;


	if (btv->resources & xbits) {

		goto fail;
	}

	if ((bit & VIDEO_RESOURCES)
	    && 0 == (btv->resources & VIDEO_RESOURCES)) {

		__s32 top = btv->crop[!!fh->do_crop].rect.top;

		if (btv->vbi_end > top)
			goto fail;


		btv->crop_start = top;
	} else if (bit & VBI_RESOURCES) {
		__s32 end = fh->vbi_fmt.end;

		if (end > btv->crop_start)
			goto fail;


		btv->vbi_end = end;
	}


	fh->resources  |= bit;
	btv->resources |= bit;
	return 1;

 fail:
	return 0;
}
