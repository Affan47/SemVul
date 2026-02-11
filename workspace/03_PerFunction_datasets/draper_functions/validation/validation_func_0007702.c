addOuter(const ConstVector& a, double mult)
{
	if (numRows() != numCols())
		throw SYLV_MES_EXCEPTION("Matrix is not square in GeneralMatrix::addOuter.");
	if (numRows() != a.length())
		throw SYLV_MES_EXCEPTION("Wrong length of a vector in GeneralMatrix::addOuter.");


	for (int i = 0; i < numRows(); i++)
		for (int j = i; j < numRows(); j++) {
			double s = mult*a[i]*a[j];
			get(i,j) = get(i,j) + s;
			if (i != j)
				get(j,i) = get(j,i) + s;
		}
}
