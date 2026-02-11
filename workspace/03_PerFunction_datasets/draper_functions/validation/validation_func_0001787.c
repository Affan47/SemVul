releaseVertexBufferCopy(
        const HardwareVertexBufferSharedPtr& bufferCopy)
    {
        OGRE_LOCK_MUTEX(mTempBuffersMutex);

        TemporaryVertexBufferLicenseMap::iterator i =
            mTempVertexBufferLicenses.find(bufferCopy.get());
        if (i != mTempVertexBufferLicenses.end())
        {
            const VertexBufferLicense& vbl = i->second;

            vbl.licensee->licenseExpired(vbl.buffer.get());

            mFreeTempVertexBufferMap.insert(
                FreeTemporaryVertexBufferMap::value_type(vbl.originalBufferPtr, vbl.buffer));
            mTempVertexBufferLicenses.erase(i);
        }
    }
