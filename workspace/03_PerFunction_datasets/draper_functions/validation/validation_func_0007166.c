prepareTempBlendBuffers(void)
    {
        if (mSkelAnimVertexData)
        {
            OGRE_DELETE mSkelAnimVertexData;
            mSkelAnimVertexData = 0;
        }
        if (mSoftwareVertexAnimVertexData)
        {
            OGRE_DELETE mSoftwareVertexAnimVertexData;
            mSoftwareVertexAnimVertexData = 0;
        }
        if (mHardwareVertexAnimVertexData)
        {
            OGRE_DELETE mHardwareVertexAnimVertexData;
            mHardwareVertexAnimVertexData = 0;
        }

        if (hasVertexAnimation())
        {

            if (mMesh->sharedVertexData
                && mMesh->getSharedVertexDataAnimationType() != VAT_NONE)
            {


                mSoftwareVertexAnimVertexData = mMesh->sharedVertexData->clone(false);
                extractTempBufferInfo(mSoftwareVertexAnimVertexData, &mTempVertexAnimInfo);


                mHardwareVertexAnimVertexData = mMesh->sharedVertexData->clone(false);
            }
        }

        if (hasSkeleton())
        {

            if (mMesh->sharedVertexData)
            {


                mSkelAnimVertexData =
                    cloneVertexDataRemoveBlendInfo(mMesh->sharedVertexData);
                extractTempBufferInfo(mSkelAnimVertexData, &mTempSkelAnimInfo);
            }

        }


        SubEntityList::iterator i, iend;
        iend = mSubEntityList.end();
        for (i = mSubEntityList.begin(); i != iend; ++i)
        {
            SubEntity* s = *i;
            s->prepareTempBlendBuffers();
        }


        mPreparedForShadowVolumes = mMesh->isPreparedForShadowVolumes();
    }
