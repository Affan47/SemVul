center_coordinate(DistType ** coords, int n, int dim)
{
    int i, j;
    double sum, avg;
    for (i = 0; i < dim; i++) {
	sum = 0;
	for (j = 0; j < n; j++) {
	    sum += coords[i][j];
	}
	avg = sum / n;
	for (j = 0; j < n; j++) {
	    coords[i][j] -= (DistType) avg;
	}
    }
}
