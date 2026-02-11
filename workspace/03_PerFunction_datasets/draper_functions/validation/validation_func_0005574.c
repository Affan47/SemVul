updatePassIterationRenderState(void)
    {
        if (mCurrentPassIterationCount <= 1)
            return false;

        --mCurrentPassIterationCount;
        ++mCurrentPassIterationNum;
        if (!mActiveVertexGpuProgramParameters.isNull())
        {
            mActiveVertexGpuProgramParameters->incPassIterationNumber();
            bindGpuProgramPassIterationParameters(GPT_VERTEX_PROGRAM);
        }
        if (!mActiveGeometryGpuProgramParameters.isNull())
        {
            mActiveGeometryGpuProgramParameters->incPassIterationNumber();
            bindGpuProgramPassIterationParameters(GPT_GEOMETRY_PROGRAM);
        }
        if (!mActiveFragmentGpuProgramParameters.isNull())
        {
            mActiveFragmentGpuProgramParameters->incPassIterationNumber();
            bindGpuProgramPassIterationParameters(GPT_FRAGMENT_PROGRAM);
        }
        if (!mActiveTessellationHullGpuProgramParameters.isNull())
        {
            mActiveTessellationHullGpuProgramParameters->incPassIterationNumber();
            bindGpuProgramPassIterationParameters(GPT_HULL_PROGRAM);
        }
        if (!mActiveTessellationDomainGpuProgramParameters.isNull())
        {
            mActiveTessellationDomainGpuProgramParameters->incPassIterationNumber();
            bindGpuProgramPassIterationParameters(GPT_DOMAIN_PROGRAM);
        }
        if (!mActiveComputeGpuProgramParameters.isNull())
        {
            mActiveComputeGpuProgramParameters->incPassIterationNumber();
            bindGpuProgramPassIterationParameters(GPT_COMPUTE_PROGRAM);
        }
        return true;
    }
