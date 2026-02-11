ReplaceTextureWithColor(const aiTexture* pcTexture)
{
	ai_assert(NULL != pcTexture);

	aiColor4D clrOut;
	clrOut.r = get_qnan();
	if (!pcTexture->mHeight || !pcTexture->mWidth)
		return clrOut;

	const unsigned int iNumPixels = pcTexture->mHeight*pcTexture->mWidth;
	const aiTexel* pcTexel = pcTexture->pcData+1;
	const aiTexel* const pcTexelEnd = &pcTexture->pcData[iNumPixels];

	while (pcTexel != pcTexelEnd)
	{
		if (*pcTexel != *(pcTexel-1))
		{
			pcTexel = NULL;
			break;
		}
		++pcTexel;
	}
	if (pcTexel)
	{
		clrOut.r = pcTexture->pcData->r / 255.0f;
		clrOut.g = pcTexture->pcData->g / 255.0f;
		clrOut.b = pcTexture->pcData->b / 255.0f;
		clrOut.a = pcTexture->pcData->a / 255.0f;
	}
	return clrOut;
}
