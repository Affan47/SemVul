_update(bool updateChildren, bool parentHasChanged)
    {
        Node::_update(updateChildren, parentHasChanged);
        if (mParent) _updateBounds();

        mPrevPosition = mNewPosition;
        mNewPosition = mDerivedPosition;
    }
