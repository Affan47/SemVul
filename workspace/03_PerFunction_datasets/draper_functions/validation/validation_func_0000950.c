init_tour(Gene *tour, int num_gene)
{
	Gene	   *tmp;
	int			remainder;
	int			next,
				i;


	tmp = (Gene *) palloc(num_gene * sizeof(Gene));

	for (i = 0; i < num_gene; i++)
		tmp[i] = (Gene) (i + 1);

	remainder = num_gene - 1;

	for (i = 0; i < num_gene; i++)
	{

		next = (int) geqo_randint(remainder, 0);

		tour[i] = tmp[next];

		tmp[next] = tmp[remainder];
		remainder--;
	}


	if (num_gene >= 2 && tour[0] > tour[1])
	{
		Gene		gtmp = tour[0];

		tour[0] = tour[1];
		tour[1] = gtmp;
	}

	pfree(tmp);
}
