rayQuery(
	const btVector3 & ray_dir,const btVector3 & ray_origin ,
	btAlignedObjectArray<int> & collided_results) const
{
	int curIndex = 0;
	int numNodes = getNodeCount();

	while (curIndex < numNodes)
	{
		btAABB bound;
		getNodeBound(curIndex,bound);


		bool aabbOverlap = bound.collide_ray(ray_origin,ray_dir);
		bool isleafnode = isLeafNode(curIndex);

		if (isleafnode && aabbOverlap)
		{
			collided_results.push_back(getNodeData( curIndex));
		}

		if (aabbOverlap || isleafnode)
		{

			curIndex++;
		}
		else
		{

			curIndex+= getEscapeNodeIndex(curIndex);
		}
	}
	if(collided_results.size()>0) return true;
	return false;
}
