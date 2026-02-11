Evaluate()
{
	ResultList *result = 0;

	operands.Start_Get();
	Query *next = (Query *)operands.Get_Next();
	if(next)
	{
		result = (ResultList *)next->GetResults();
		next = (Query *)operands.Get_Next();
	}
	if(result)
	{
		result = new ResultList(*result);
	}
	while(result && next)
	{
		ResultList *r = next->GetResults();
		if(r)
		{
			if(result->IsIgnore())
			{
				delete result;
				result = new ResultList(*r);
			}
			else if(!r->IsIgnore())
			{
				ResultList *tmp = result;
				result = Near(*tmp, *r);
				delete tmp;
			}
			next = (Query *)operands.Get_Next();
		}
		else
		{
			delete result;
			result = 0;
		}
	}
	return result;
}
