logResults()
    {
        LogManager::getSingleton().logMessage("----------------------Profiler Results----------------------");

        for(ProfileChildren::iterator it = mRoot.children.begin(); it != mRoot.children.end(); ++it)
        {
            it->second->logResults();
        }

        LogManager::getSingleton().logMessage("------------------------------------------------------------");
    }
