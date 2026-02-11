handleResponse(const WorkQueue::Response* res, const WorkQueue* srcQ)
    {

        PageResponse pres = any_cast<PageResponse>(res->getData());
        PageRequest preq = any_cast<PageRequest>(res->getRequest()->getData());


        if (preq.srcPage!= this)
            return;


        if (res->succeeded())
        {
            if(!pres.pageData->collectionsToAdd.empty())
                std::swap(mContentCollections, pres.pageData->collectionsToAdd);

            loadImpl();
        }

        OGRE_DELETE pres.pageData;

        mDeferredProcessInProgress = false;

    }
