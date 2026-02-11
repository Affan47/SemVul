_make_nodelist(char *nodes, List nodelist)
{
	int i, j = 0;
	int start[params.cluster_dims];
	int end[params.cluster_dims];

	if (!nodelist)
		nodelist = list_create(_nodelist_del);

	while (nodes[j] != '\0') {
		int mid = j   + params.cluster_dims + 1;
		int fin = mid + params.cluster_dims + 1;
		if (((nodes[j] == '[')   || (nodes[j] == ','))   &&
		    ((nodes[mid] == 'x') || (nodes[mid] == '-')) &&
		    ((nodes[fin] == ']') || (nodes[fin] == ','))) {
			j++;
			for (i = 0; i < params.cluster_dims; i++, j++)
				start[i] = select_char2coord(nodes[j]);
			j++;
			for (i = 0; i < params.cluster_dims; i++, j++)
				end[i] = select_char2coord(nodes[j]);
			_addto_nodelist(nodelist, start, end);
			if (nodes[j] != ',')
				break;
			j--;
		} else if (((nodes[j] >= '0') && (nodes[j] <= '9')) ||
			   ((nodes[j] >= 'A') && (nodes[j] <= 'Z'))) {
			for (i = 0; i < params.cluster_dims; i++, j++)
				start[i] = select_char2coord(nodes[j]);
			_addto_nodelist(nodelist, start, start);
			if (nodes[j] != ',')
				break;
			j--;
		}
		j++;
	}

	return 1;
}
