exportNodes( NodeMap& allNodes, std::list< Element* >& allElements )
{
	std::list< Vertex* >::iterator vxIt;
	for( vxIt = allVertices.begin(); vxIt != allVertices.end(); ++vxIt )
	{
		Vertex *vtx = (*vxIt);
		if( !(vtx->isDeleted() || vtx->isExternal()))
		{
			vtx->newTag();
			allElements.push_back( vtx );

			for(int i = 0; i < 3; ++i)
			{
				allNodes[ vtx->nodeAt(i)->tag ] = vtx->nodeAt(i);
			}
		}
	}


	std::vector< BoundaryElement * > bels;
	bounds->collectBoundaryElements( bels );


	int i, len;
	Vertex *v = root;
	len = bels.size();

	for( i = 0; i < len; ++i )
	{
		v = bels[i]->setHolder( v );
	}

}
