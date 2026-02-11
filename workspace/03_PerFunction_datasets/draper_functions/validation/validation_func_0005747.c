multiply_float_matrix(const char *input_file, int dim, int dry_run)
{
	float *in_matrix = malloc(dim*dim*sizeof(float));

	if(!in_matrix)
	{
		fprintf(stderr, "Malloc failed\n");
		exit(1);
	}

	read_input_file_float(input_file, dim, in_matrix);

	if(dry_run) { free(in_matrix); return; }

	float *out_matrix = malloc(dim*dim*sizeof(float));

	if(!out_matrix)
	{
		fprintf(stderr, "Malloc failed\n");
		exit(1);
	}

	int i, j, k;

	for(i = 0; i < dim; i++)
	{
		for(j = 0; j < dim; j++)
		{
			float res = 0;
			for(k = 0; k < dim; k++)
				res += INDEX(in_matrix, dim, i, k)*INDEX(in_matrix, dim, k, j);
			INDEX(out_matrix, dim, i, j) = res;
		}
	}

	free(in_matrix);
	free(out_matrix);
}
