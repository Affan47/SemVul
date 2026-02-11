set(const string& dimensionSymbols)
{
	size_t limit = dimensionSymbols.length();

	for (size_t i = 0; i < limit; i++)
	{
		int row = i / firstDim;
		int col = i % secondDim;
		matrix[row][col] = Dimension::toDimensionValue(dimensionSymbols[i]);
	}
}
