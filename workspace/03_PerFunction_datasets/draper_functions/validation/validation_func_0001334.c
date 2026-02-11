synchronizeMotionStates()
{

	for ( int i=0;i<m_collisionObjects.size();i++)
	{
		btCollisionObject* colObj = m_collisionObjects[i];
		btRigidBody* body = btRigidBody::upcast(colObj);
		if (body && body->getMotionState())
		{
			if (body->getActivationState() != ISLAND_SLEEPING)
			{
				body->getMotionState()->setWorldTransform(body->getWorldTransform());
			}
		}
	}

}
