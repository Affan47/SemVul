buildDependencies(SceneGraph& sg, int pcol1, int pcol2, int which)
{
	int node1 = sg.getTopNode(pcol1), node2 = sg.getTopNode(pcol2);
	if (node1 == -1 || node2 == -1)
		return;

	while (true)
	{


		if (sg.nodes[node1].bi.occludes(sg.nodes[node2].bi))
		{
			int next1 = sg.nodes[node1].children[0];
			while (next1 != -1 && sg.nodes[next1].bi.occludes(sg.nodes[node2].bi))
			{
				node1 = next1;
				next1 = sg.nodes[node1].children[0];
			}
			sg.nodes[node1].children[which] = node2;
			node1 = next1;
		}

		if (node1 == -1)
			return;


		if (sg.nodes[node2].bi.occludes(sg.nodes[node1].bi))
		{
			int next2 = sg.nodes[node2].children[0];
			while (next2 != -1 && sg.nodes[next2].bi.occludes(sg.nodes[node1].bi))
			{
				node2 = next2;
				next2 = sg.nodes[node2].children[0];
			}
			sg.nodes[node2].children[which - 3] = node1;
			node2 = next2;
		}

		if (node2 == -1)
			return;
	}
}
