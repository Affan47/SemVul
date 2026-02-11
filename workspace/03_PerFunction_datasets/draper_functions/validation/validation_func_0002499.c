isInClosedList(dtPolyRef ref) const
{
	if (!m_nodePool) return false;

	dtNode* nodes[DT_MAX_STATES_PER_NODE];
	int n= m_nodePool->findNodes(ref, nodes, DT_MAX_STATES_PER_NODE);

	for (int i=0; i<n; i++)
	{
		if (nodes[i]->flags & DT_NODE_CLOSED)
			return true;
	}

	return false;
}
