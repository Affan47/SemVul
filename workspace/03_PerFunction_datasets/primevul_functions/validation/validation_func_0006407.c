calculateNumTiles (int *numTiles,
		   int numLevels,
		   int min, int max,
		   int size,
		   LevelRoundingMode rmode)
{
    for (int i = 0; i < numLevels; i++)
    {

        Int64 l = levelSize (min, max, i, rmode);
        numTiles[i] = (l + size - 1) / size;
    }
}
