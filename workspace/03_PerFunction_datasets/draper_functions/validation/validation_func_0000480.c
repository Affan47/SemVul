expand_object(array_2d<unsigned char >& obj, double r)
{
	const unsigned int width(obj.width);
	const unsigned int height(obj.height);
	const unsigned int size(obj.size);

	array_2d<edist > dists(width, height);
	edist max_dist = edist(-(width + height), -(width + height));
	edist zero = edist(0,0);

	for(unsigned int i = 0; i < size; i++)
	{
		dists[i] = (obj[i] ? zero : max_dist);
	}

	expand_dist_map(dists);

	double r_squared = r * r;

	for(unsigned int i = 0; i < size; i++)
	{
		obj[i] = dists[i] <= r_squared;
	}

}
