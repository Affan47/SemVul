performAfterReasoning ( void )
{

	if ( LLM.isWritable(llGTA) )
	{
		logIndentation();
		LL << "ub:";
	}
	CGraph.retestCGBlockedStatus();
	if ( LLM.isWritable(llGTA) )
		LL << "]";
	if ( !TODO.empty() )
		return false;


	if ( !tBox.getSplits()->empty() )
	{
		if ( LLM.isWritable(llGTA) )
		{
			logIndentation();
			LL << "split:";
		}
		bool clash = checkSplitRules();
		if ( LLM.isWritable(llGTA) )
			LL << "]";

		if ( clash )
			return true;
		if ( !TODO.empty() )
			return false;
	}

#ifdef RKG_USE_FAIRNESS

	if ( tBox.hasFC() )
	{
		DlCompletionTree* violator = NULL;

		for ( TBox::ConceptVector::const_iterator p = tBox.Fairness.begin(), p_end = tBox.Fairness.end(); p < p_end; ++p )
		{
			violator = CGraph.getFCViolator((*p)->pName);
			if ( violator )
			{
				nFairnessViolations.inc();

				if ( addToDoEntry ( violator, (*p)->pName, getCurDepSet(), "fair" ) )
					return true;
			}
		}

		if ( !TODO.empty() )
			return false;
	}
#endif

	return false;
}
