currentActionInstance() const
	{
		if(mCurrentActionIndex < 0 || mCurrentActionIndex >= mScript->actionCount())
			return 0;

		return mScript->actionAt(mCurrentActionIndex);
	}
