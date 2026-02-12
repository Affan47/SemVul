void TiffReader::postProcess()
    {
        setMnState();
        postProc_ = true;
        for (PostList::const_iterator pos = postList_.begin(); pos != postList_.end(); ++pos) {
            (*pos)->accept(*this);
        }
        postProc_ = false;
        setOrigState();
    }
