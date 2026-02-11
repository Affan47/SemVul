setLodLevels(const LodValueList& lodValues)
    {

        LodValueList::const_iterator i, iend;
        iend = lodValues.end();

        mLodValues.clear();
        mUserLodValues.clear();
        mUserLodValues.push_back(0);
        mLodValues.push_back(mLodStrategy->getBaseValue());
        for (i = lodValues.begin(); i != iend; ++i)
        {
            mUserLodValues.push_back(*i);
            if (mLodStrategy)
                mLodValues.push_back(mLodStrategy->transformUserValue(*i));
        }

    }
