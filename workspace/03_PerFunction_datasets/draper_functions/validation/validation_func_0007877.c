GenerateDefaultMaterial()
{
	ai_assert(NULL != mParser);

	bool bHas = false;
	for (std::vector<ASE::Mesh>::iterator i =  mParser->m_vMeshes.begin();i != mParser->m_vMeshes.end();++i) {
		if ((*i).bSkip)continue;
		if (ASE::Face::DEFAULT_MATINDEX == (*i).iMaterialIndex)	{
			(*i).iMaterialIndex = (unsigned int)mParser->m_vMaterials.size();
			bHas = true;
		}
	}
	if (bHas || mParser->m_vMaterials.empty())	{

		mParser->m_vMaterials.push_back ( ASE::Material() );
		ASE::Material& mat = mParser->m_vMaterials.back();

		mat.mDiffuse  = aiColor3D(0.6f,0.6f,0.6f);
		mat.mSpecular = aiColor3D(1.0f,1.0f,1.0f);
		mat.mAmbient  = aiColor3D(0.05f,0.05f,0.05f);
		mat.mShading  = Discreet3DS::Gouraud;
		mat.mName     = AI_DEFAULT_MATERIAL_NAME;
	}
}
