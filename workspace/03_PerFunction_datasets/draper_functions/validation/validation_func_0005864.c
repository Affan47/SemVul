operator+( Point Q, Point R)
{
	Point P;
	P.x = Q.x + R.x;
	P.y = Q.y + R.y;
	P.z = Q.z + R.z;
	P.dimn = max( Q.dim(), R.dim());
	return P;
}
