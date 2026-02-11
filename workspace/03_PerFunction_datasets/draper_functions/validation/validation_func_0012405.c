accur_terror_sort ()
{
	gint i, j;
	gunichar uchr;
	gulong correct;
	gulong wrong;

	for (i = 1; i < terror_n; i++)
	{
		for (j = i; j > 0; j--)
		{
			if (terror[j].correct < terror[j-1].correct)
			{
				uchr = terror[j].uchr;
				terror[j].uchr = terror[j-1].uchr;
				terror[j-1].uchr = uchr;

				wrong = terror[j].wrong;
				terror[j].wrong = terror[j-1].wrong;
				terror[j-1].wrong = wrong;

				correct = terror[j].correct;
				terror[j].correct = terror[j-1].correct;
				terror[j-1].correct = correct;
			}
		}
	}
	for (i = 1; i < terror_n; i++)
	{
		for (j = i; j > 0; j--)
		{
			if (terror[j].wrong > terror[j-1].wrong)
			{
				uchr = terror[j].uchr;
				terror[j].uchr = terror[j-1].uchr;
				terror[j-1].uchr = uchr;

				wrong = terror[j].wrong;
				terror[j].wrong = terror[j-1].wrong;
				terror[j-1].wrong = wrong;

				correct = terror[j].correct;
				terror[j].correct = terror[j-1].correct;
				terror[j-1].correct = correct;
			}
		}
	}
}
