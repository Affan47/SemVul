Execute( aiScene* pScene)
{
	DefaultLogger::get()->debug("JoinVerticesProcess begin");


	int iNumOldVertices = 0;
	if (!DefaultLogger::isNullLogger()) {
		for( unsigned int a = 0; a < pScene->mNumMeshes; a++)	{
			iNumOldVertices +=	pScene->mMeshes[a]->mNumVertices;
		}
	}


	int iNumVertices = 0;
	for( unsigned int a = 0; a < pScene->mNumMeshes; a++)
		iNumVertices +=	ProcessMesh( pScene->mMeshes[a],a);


	if (!DefaultLogger::isNullLogger())
	{
		if (iNumOldVertices == iNumVertices)
		{
			DefaultLogger::get()->debug("JoinVerticesProcess finished ");
		} else
		{
			char szBuff[128];
			sprintf(szBuff,"JoinVerticesProcess finished | Verts in: %i out: %i | ~%.1f%%",
				iNumOldVertices,
				iNumVertices,
				((iNumOldVertices - iNumVertices) / (float)iNumOldVertices) * 100.f);
			DefaultLogger::get()->info(szBuff);
		}
	}

	pScene->mFlags |= AI_SCENE_FLAGS_NON_VERBOSE_FORMAT;
}
