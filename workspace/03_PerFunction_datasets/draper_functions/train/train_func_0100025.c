determineAccess()
    {
        mAccess = 0;
        if (mInStream)
            mAccess |= READ;
        if (mFStream)
            mAccess |= WRITE;
    }
