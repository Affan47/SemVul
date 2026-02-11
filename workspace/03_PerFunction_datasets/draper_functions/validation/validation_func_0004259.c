extendDrawArgsIfNeccessary(
	UT_Rect *thisCallRect,
	const UT_Rect *clipRectFromGraphics,
	bool bDirtyRunsOnly)
{
	if(clipRectFromGraphics == NULL)
		clipRectFromGraphics = thisCallRect;

	if(mostExtArgs.callCount == 0)
	{

		mostExtArgs.bDirtyRunsOnly = bDirtyRunsOnly;
		mostExtArgs.fullRect = *thisCallRect;
		mostExtArgs.clipRect = *clipRectFromGraphics;
	}
	else
	{


		if(bDirtyRunsOnly == false) mostExtArgs.bDirtyRunsOnly = false;


		mostExtArgs.fullRect.unionRect(thisCallRect);


		mostExtArgs.clipRect.unionRect(clipRectFromGraphics);
	}

	mostExtArgs.callCount++;
}
