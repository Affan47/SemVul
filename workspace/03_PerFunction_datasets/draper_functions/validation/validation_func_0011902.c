gamgi_io_x3d_render_polygons (FILE *fp,
int *loops, double *points, gamgi_bool * error)
{
	char str[256];
	int p, i, j, n_loops, c;
	int * n_vertices;

	double ** point;

	p = 0;
	c = 0;

	n_loops = loops[p++];
	n_vertices = malloc(sizeof(int)*n_loops);
	point = malloc(sizeof(double *)*n_loops);

	gamgi_io_file_fprintf(fp, "<IndexedFaceSet solid='false' coordIndex='", error);

	for(i=0; i<n_loops; i++)
	{
		n_vertices[i] = loops[p++];
		point[i] = malloc(n_vertices[i]*sizeof(double)*3);

		for(j=0; j<n_vertices[i]; j++)
		{
			if(i==0 && j==0)
				sprintf(str, "%d", c);
			else
				sprintf(str, " %d", c);

			gamgi_io_file_fprintf(fp, str, error);

			c++;

			point[i][j*3] = points[3 * loops[p]];
			point[i][j*3+1] = points[3 * loops[p]+1];
			point[i][j*3+2] = points[3 * loops[p]+2];

			p++;
		}

		sprintf(str, " -1");

		gamgi_io_file_fprintf(fp, str, error);
	}

	gamgi_io_file_fprintf(fp, "'>\n<Coordinate point='", error);
	for(i=0; i<n_loops; i++)
	{
		for(j=0; j<n_vertices[i]; j++)
		{
			sprintf(str, "%f %f %f", point[i][j*3], point[i][j*3+1], point[i][j*3+2]);
			gamgi_io_file_fprintf(fp, str, error);
			if(!(i==n_loops-1&&j==n_vertices[i]-1))
				gamgi_io_file_fprintf(fp, ", ", error);
		}
	}

	gamgi_io_file_fprintf(fp, "'/>\n</IndexedFaceSet>\n", error);

	for(i=0; i<n_loops; i++) free(point[i]);
	free(point);
}
