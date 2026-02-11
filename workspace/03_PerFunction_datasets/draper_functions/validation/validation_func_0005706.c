K056832_UpdatePageLayout(void)
{
	int layer, rowstart, rowspan, colstart, colspan, r, c, pageIndex, setlayer;


	K056832_LayerAssociation = K056832_DefaultLayerAssociation;


	for (layer=0; layer<4; layer++)
	{
		if (!K056832_Y[layer] && !K056832_X[layer] && K056832_H[layer]==3 && K056832_W[layer]==3)
		{
			K056832_LayerAssociation = 0;
			break;
		}
	}


	for (pageIndex=0; pageIndex<K056832_PAGE_COUNT; pageIndex++)
	{
		K056832_LayerAssociatedWithPage[pageIndex] = -1;
	}


	for (layer=0; layer<4; layer++)
	{
		rowstart = K056832_Y[layer];
		colstart = K056832_X[layer];
		rowspan  = K056832_H[layer]+1;
		colspan  = K056832_W[layer]+1;

		setlayer = (K056832_LayerAssociation) ? layer : K056832_ActiveLayer;

		for (r=0; r<rowspan; r++)
		{
			for (c=0; c<colspan; c++)
			{
				pageIndex = (((rowstart + r) & 3) << 2) + ((colstart + c) & 3);
if (stricmp(Machine->gamedrv->source_file+12, "djmain.c") || K056832_LayerAssociatedWithPage[pageIndex] == -1)
					K056832_LayerAssociatedWithPage[pageIndex] = setlayer;
			}
		}
	}


	K056832_MarkAllTilemapsDirty();
}
