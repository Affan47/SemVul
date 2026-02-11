resetWeights(InputData* pData)
	{

		int numOfClasses = pData->getNumClasses();
		vector< int > numPerClasses(numOfClasses);
		int numOfSamples = pData->getNumExamples();
		vector< AlphaReal > wi( numOfClasses );
		vector< AlphaReal > wic( numOfClasses );

		fill(numPerClasses.begin(),numPerClasses.end(), 0 );
		for (int i = 0; i < numOfSamples; ++i)
		{
			vector<Label>& labels = pData->getLabels(i);
			vector<Label>::iterator lIt;

			for ( lIt = labels.begin(); lIt != labels.end(); ++lIt )
			{
				if ( lIt->y > 0 )
					numPerClasses[lIt->idx]++;
			}

		}


		for( int i = 0; i < numOfClasses; i ++ ) {
			wi[i] =  1.0  / (4.0 * numPerClasses[i]);
			wic[i] = 1.0 / (4.0 * ( numOfSamples - numPerClasses[i] ));
		}


		for (int i = 0; i < numOfSamples; ++i)
		{
			vector<Label>& labels = pData->getLabels(i);
			vector<Label>::iterator lIt;


			for ( lIt = labels.begin(); lIt != labels.end(); ++lIt )
			{
				if (lIt->y>0) lIt->weight = wi[lIt->idx];
				else lIt->weight=wic[lIt->idx];
			}

		}

		AlphaReal sumWeight = 0;
		for (int i = 0; i < numOfSamples; ++i)
		{
			vector<Label>& labels = pData->getLabels(i);
			vector<Label>::iterator lIt;


			for (lIt = labels.begin(); lIt != labels.end(); ++lIt )
				sumWeight += lIt->weight;
		}

		if ( !nor_utils::is_zero(sumWeight-1.0, 1E-6 ) )
		{
			cerr << "\nERROR: Sum of weights (" << sumWeight << ") != 1!" << endl;
			cerr << "Try a different weight policy (--weightpolicy under 'Basic Algorithm Options')!" << endl;

		}


	}
