void LibRaw::identify_finetune_by_filesize(int fsize)
{

	if (fsize == 4771840)
	{

		if (!timestamp && nikon_e995())
			strcpy(model, "E995");
	}
	else if (fsize == 2940928)
	{
		if (!timestamp && !nikon_e2100())
			strcpy(model, "E2500");
	}
	else if (fsize == 4775936)
	{


		if (!timestamp)
			nikon_3700();
	}
	else if (fsize == 5869568)
	{

		if (!timestamp && minolta_z2())
		{
			maker_index = LIBRAW_CAMERAMAKER_Minolta;
			strcpy(make, "Minolta");
			strcpy(model, "DiMAGE Z2");
		}
	}
}
