createLogicalParameterMappingStructures(bool recreateIfExists) const
    {
        if (recreateIfExists || mFloatLogicalToPhysical.isNull())
            mFloatLogicalToPhysical = GpuLogicalBufferStructPtr(OGRE_NEW GpuLogicalBufferStruct());
        if (recreateIfExists || mIntLogicalToPhysical.isNull())
            mIntLogicalToPhysical = GpuLogicalBufferStructPtr(OGRE_NEW GpuLogicalBufferStruct());
    }
