changeEnableState()
    {
        for( TProfileSessionListener::iterator i = mListeners.begin(); i != mListeners.end(); ++i )
            (*i)->changeEnableState(mNewEnableState);

        mEnabled = mNewEnableState;
    }
