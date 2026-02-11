Collide()
{

	b2Contact* c = m_contactList;
	while (c)
	{
		b2Fixture* fixtureA = c->GetFixtureA();
		b2Fixture* fixtureB = c->GetFixtureB();
		int32 indexA = c->GetChildIndexA();
		int32 indexB = c->GetChildIndexB();
		b2Body* bodyA = fixtureA->GetBody();
		b2Body* bodyB = fixtureB->GetBody();

		if (bodyA->IsAwake() == false && bodyB->IsAwake() == false)
		{
			c = c->GetNext();
			continue;
		}


		if (c->m_flags & b2Contact::e_filterFlag)
		{

			if (bodyB->ShouldCollide(bodyA) == false)
			{
				b2Contact* cNuke = c;
				c = cNuke->GetNext();
				Destroy(cNuke);
				continue;
			}


			if (m_contactFilter && m_contactFilter->ShouldCollide(fixtureA, fixtureB) == false)
			{
				b2Contact* cNuke = c;
				c = cNuke->GetNext();
				Destroy(cNuke);
				continue;
			}


			c->m_flags &= ~b2Contact::e_filterFlag;
		}

		int32 proxyIdA = fixtureA->m_proxies[indexA].proxyId;
		int32 proxyIdB = fixtureB->m_proxies[indexB].proxyId;
		bool overlap = m_broadPhase.TestOverlap(proxyIdA, proxyIdB);


		if (overlap == false)
		{
			b2Contact* cNuke = c;
			c = cNuke->GetNext();
			Destroy(cNuke);
			continue;
		}


		c->Update(m_contactListener);
		c = c->GetNext();
	}
}
