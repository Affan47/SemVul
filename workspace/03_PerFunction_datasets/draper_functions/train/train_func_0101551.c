setTriangleData(ITerrainSceneNode* node, s32 LOD)
{
	core::triangle3df tri;
	core::array<u32> indices;


	video::S3DVertex2TCoords* vertices = static_cast<video::S3DVertex2TCoords*>(node->getRenderBuffer()->getVertices());


	const s32 count = (static_cast<CTerrainSceneNode*>(node))->TerrainData.PatchCount;
	TrianglePatches.TotalTriangles = 0;
	TrianglePatches.NumPatches = count*count;

	TrianglePatches.TrianglePatchArray.reallocate(TrianglePatches.NumPatches);
	for (s32 o=0; o<TrianglePatches.NumPatches; ++o)
		TrianglePatches.TrianglePatchArray.push_back(SGeoMipMapTrianglePatch());

	s32 tIndex = 0;
	for(s32 x = 0; x < count; ++x )
	{
		for(s32 z = 0; z < count; ++z )
		{
			TrianglePatches.TrianglePatchArray[tIndex].NumTriangles = 0;
			TrianglePatches.TrianglePatchArray[tIndex].Box = node->getBoundingBox( x, z );
			u32 indexCount = node->getIndicesForPatch( indices, x, z, LOD );

			TrianglePatches.TrianglePatchArray[tIndex].Triangles.reallocate(indexCount/3);
			for(u32 i = 0; i < indexCount; i += 3 )
			{
				tri.pointA = vertices[indices[i+0]].Pos;
				tri.pointB = vertices[indices[i+1]].Pos;
				tri.pointC = vertices[indices[i+2]].Pos;
				TrianglePatches.TrianglePatchArray[tIndex].Triangles.push_back(tri);
				++TrianglePatches.TrianglePatchArray[tIndex].NumTriangles;
			}

			TrianglePatches.TotalTriangles += TrianglePatches.TrianglePatchArray[tIndex].NumTriangles;
			++tIndex;
		}
	}
}
