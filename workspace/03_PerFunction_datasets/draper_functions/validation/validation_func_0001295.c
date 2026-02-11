BERDecode(BufferedTransformation &bt)
{
	BERSequenceDecoder parameters(bt);
		Integer p(parameters);
		Integer q(parameters);
		Integer g;
		if (parameters.EndReached())
		{
			g = q;
			q = ComputeGroupOrder(p) / 2;
		}
		else
			g.BERDecode(parameters);
	parameters.MessageEnd();

	SetModulusAndSubgroupGenerator(p, g);
	SetSubgroupOrder(q);
}
