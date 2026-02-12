static void S_AL_SrcKill(srcHandle_t src)
{
	src_t *curSource = &srcList[src];


	if(curSource->isLocked)
		return;


	if(curSource->isLooping)
	{
		curSource->isLooping = qfalse;

		if(curSource->entity != -1)
		{
			sentity_t *curEnt = &entityList[curSource->entity];

			curEnt->srcAllocated = qfalse;
			curEnt->srcIndex = -1;
			curEnt->loopAddedThisFrame = qfalse;
			curEnt->startLoopingSound = qfalse;
		}

		S_AL_NewLoopMaster(curSource, qtrue);
	}


	if(curSource->isPlaying)
	{
		qalSourceStop(curSource->alSource);
		curSource->isPlaying = qfalse;
	}


	qalSourcei(curSource->alSource, AL_BUFFER, 0);

	curSource->sfx = 0;
	curSource->lastUsedTime = 0;
	curSource->priority = 0;
	curSource->entity = -1;
	curSource->channel = -1;
	if(curSource->isActive)
	{
		curSource->isActive = qfalse;
		srcActiveCnt--;
	}
	curSource->isLocked = qfalse;
	curSource->isTracking = qfalse;
	curSource->local = qfalse;
}
