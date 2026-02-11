TwoFishAlloc(unsigned long len,bool binhex,bool decrypt,TWOFISH *tfdata)
{

	if(decrypt)
	{	if(binhex)
			len/=2;
		len-=TwoFish_BLOCK_SIZE;
	}
	else
	{	len+=TwoFish_BLOCK_SIZE;
		if(binhex)
			len*=2;
	}
	tfdata->output=malloc(len+TwoFish_BLOCK_SIZE);

	return tfdata->output;
}
