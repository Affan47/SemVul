FindParameters(FCDENodeList& nodes, StringList& names)
{
	for (const FCDENode** itN = (const FCDENode**) children.begin(); itN != children.end(); ++itN)
	{
		const FCDENode* node = (*itN);
		if (node->GetChildNodeCount() == 0)
		{
			nodes.push_back(const_cast<FCDENode*>(node));
			names.push_back(node->GetName());
		}
	}
}
