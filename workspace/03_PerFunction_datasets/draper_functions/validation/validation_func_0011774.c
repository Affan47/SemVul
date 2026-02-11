getWireBoundingBox()
    {

        if(mWireBoundingBox == 0)
            mWireBoundingBox = OGRE_NEW WireBoundingBox();

        mWireBoundingBox->setupBoundingBox(mBox);
        return mWireBoundingBox;
    }
