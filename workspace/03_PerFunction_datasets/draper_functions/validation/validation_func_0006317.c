findNewestTimeLine(TimeLineID startTLI)
{
	TimeLineID	newestTLI;
	TimeLineID	probeTLI;


	newestTLI = startTLI;

	for (probeTLI = startTLI + 1;; probeTLI++)
	{
		if (existsTimeLineHistory(probeTLI))
		{
			newestTLI = probeTLI;
		}
		else
		{

			break;
		}
	}

	return newestTLI;
}
