setUpdateBoundingBoxFromSkeleton(bool update)
    {
        mUpdateBoundingBoxFromSkeleton = update;
        if (mMesh->isLoaded() && mMesh->getBoneBoundingRadius() == Real(0))
        {
            mMesh->_computeBoneBoundingRadius();
        }
    }
