CCubeSceneNode(f32 size, ISceneNode* parent, ISceneManager* mgr,
		s32 id, const core::vector3df& position,
		const core::vector3df& rotation, const core::vector3df& scale)
	: IMeshSceneNode(parent, mgr, id, position, rotation, scale),
	Mesh(0), Size(size)
{
	#ifdef _DEBUG
	setDebugName("CCubeSceneNode");
	#endif

	setSize();
}
