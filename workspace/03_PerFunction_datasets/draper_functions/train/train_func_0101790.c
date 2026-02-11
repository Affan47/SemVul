EncodeFrame(const CImage* src, void* dest, int* is_keyframe, size_t* size, int* lpckid=0)
    {
	if ((dest == 0) || (src == 0))
	{
	    if (size)
		*size = 0;
	    return 0;
	}
	const CImage* tmp;
	if (header.biBitCount != 24 || header.biCompression)
	{
	    BitmapInfo supp(header);
	    supp.SetBits(24);
	    supp.biBitCount=24;
	    supp.biCompression=0;
	    tmp = new CImage(src, &supp);
	}
	else
	{
	    tmp = src;
	}

	int sz = mjpg_bgr_compress(mjpg_cinfo, (unsigned char*)dest,
				   tmp->Data(), tmp->Pixels());
	if (size)
	    *size = sz;
	if (is_keyframe)
	    *is_keyframe = 16;
	if (src != tmp)
	    delete tmp;
	return 0;
    }
