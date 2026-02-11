FreeMatrices()
	{
		if (this->MatricesSize==0)
			return;

		for (i = 0; i < this->MatricesSize; i++)
		{
			delete [] VandermondeMatrix[i];
			delete [] SecondMember[i];
		}

		delete [] VandermondeMatrix;
		delete [] SecondMember;
		this->MatricesSize=0;
	}
