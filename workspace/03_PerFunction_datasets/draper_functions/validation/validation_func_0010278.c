doParticleSystem(u32 time)
{
	if (LastEmitTime==0)
	{
		LastEmitTime = time;
		return;
	}

	u32 now = time;
	u32 timediff = time - LastEmitTime;
	LastEmitTime = time;


	if (Emitter && IsVisible)
	{
		SParticle* array = 0;
		s32 newParticles = Emitter->emitt(now, timediff, array);

		if (newParticles && array)
		{
			s32 j=Particles.size();
			if (newParticles > 16250-j)
				newParticles=16250-j;
			Particles.set_used(j+newParticles);
			for (s32 i=j; i<j+newParticles; ++i)
			{
				Particles[i]=array[i-j];
				AbsoluteTransformation.rotateVect(Particles[i].startVector);
				if (ParticlesAreGlobal)
					AbsoluteTransformation.transformVect(Particles[i].pos);
			}
		}
	}


	core::list<IParticleAffector*>::Iterator ait = AffectorList.begin();
	for (; ait != AffectorList.end(); ++ait)
		(*ait)->affect(now, Particles.pointer(), Particles.size());

	if (ParticlesAreGlobal)
		Buffer->BoundingBox.reset(AbsoluteTransformation.getTranslation());
	else
		Buffer->BoundingBox.reset(core::vector3df(0,0,0));


	f32 scale = (f32)timediff;

	for (u32 i=0; i<Particles.size();)
	{

		if (now > Particles[i].endTime)
			Particles.erase(i);
		else
		{
			Particles[i].pos += (Particles[i].vector * scale);
			Buffer->BoundingBox.addInternalPoint(Particles[i].pos);
			++i;
		}
	}

	const f32 m = (ParticleSize.Width > ParticleSize.Height ? ParticleSize.Width : ParticleSize.Height) * 0.5f;
	Buffer->BoundingBox.MaxEdge.X += m;
	Buffer->BoundingBox.MaxEdge.Y += m;
	Buffer->BoundingBox.MaxEdge.Z += m;

	Buffer->BoundingBox.MinEdge.X -= m;
	Buffer->BoundingBox.MinEdge.Y -= m;
	Buffer->BoundingBox.MinEdge.Z -= m;

	if (ParticlesAreGlobal)
	{
		core::matrix4 absinv( AbsoluteTransformation, core::matrix4::EM4CONST_INVERSE );
		absinv.transformBoxEx(Buffer->BoundingBox);
	}
}
