init_myers()
{
	register int i;

	group = (int *)ckalloc( (MAXN+1) * sizeof (int));

	alist = (int *)ckalloc( (MAXN+1) * sizeof (int));
	fst_list = (int *)ckalloc( (MAXN+1) * sizeof (int));
	snd_list = (int *)ckalloc( (MAXN+1) * sizeof (int));

	naa1 = (int **)ckalloc(21 * sizeof (int *) );
	for(i=0;i<21;i++)
		naa1[i]=(int *)ckalloc( (MAXLEN+1)*sizeof (int));
	naa2 = (int **)ckalloc(21 * sizeof (int *) );
	for(i=0;i<21;i++)
		naa2[i]=(int *)ckalloc( (MAXLEN+1)*sizeof (int));
	naas = (int **)ckalloc(21 * sizeof (int *) );
	for(i=0;i<21;i++)
		naas[i]=(int *)ckalloc( (MAXLEN+1)*sizeof (int));

	dna_gap_open    = 10;
	dna_gap_extend  = 10;

	prot_gap_open   = 10;
	prot_gap_extend = 10;

	is_weight = TRUE;
}
