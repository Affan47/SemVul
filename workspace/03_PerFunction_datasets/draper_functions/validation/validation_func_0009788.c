flipHorzImageTGA(ImageTGA* img)
{
	const int pitch = img->sizeX * img->channels;

	for (int line = 0; line < img->sizeY; ++line)
	{
		int srcOffset = (line * pitch);
		int dstOffest = srcOffset + pitch - img->channels;

		for (int pix = 0; pix < img->sizeX / 2; ++pix)
		{
            for (int c = 0; c < img->channels; ++c)
            {
                const uchar tmp = img->data[dstOffest + c];
                img->data[dstOffest + c] = img->data[srcOffset + c];
                img->data[srcOffset + c] = tmp;
            }

            srcOffset += img->channels;
            dstOffest -= img->channels;
		}
	}
}
