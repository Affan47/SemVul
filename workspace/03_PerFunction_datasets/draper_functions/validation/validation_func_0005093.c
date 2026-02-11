removeListener(LogListener* listener)
    {
        OGRE_LOCK_AUTO_MUTEX;
        mtLogListener::iterator i = std::find(mListeners.begin(), mListeners.end(), listener);
        if (i != mListeners.end())
            mListeners.erase(i);
    }
