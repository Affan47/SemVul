OffsetNodeMeshIndices (aiNode* node, unsigned int offset)
{
	for (unsigned int i = 0; i < node->mNumMeshes;++i)
		node->mMeshes[i] += offset;

	for (unsigned int i = 0; i < node->mNumChildren;++i)
		OffsetNodeMeshIndices(node->mChildren[i],offset);
}
