createClone(ISceneNode* node, ISceneManager* newManager)
{
	if (!newManager) newManager = SceneManager;

	CSceneNodeAnimatorCollisionResponse * newAnimator =
		new CSceneNodeAnimatorCollisionResponse(newManager, World, Object, Radius,
				(Gravity * 1000.0f), Translation, SlidingSpeed);

	return newAnimator;
}
