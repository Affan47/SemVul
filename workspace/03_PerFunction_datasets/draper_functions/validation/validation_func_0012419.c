bindGpuProgramPassIterationParameters(GpuProgramType gptype)
    {
        switch (gptype)
        {
        case GPT_VERTEX_PROGRAM:
            mCurrentVertexProgram->bindProgramPassIterationParameters(mActiveVertexGpuProgramParameters);
            break;
        case GPT_GEOMETRY_PROGRAM:
            mCurrentGeometryProgram->bindProgramPassIterationParameters(mActiveGeometryGpuProgramParameters);
            break;
        case GPT_FRAGMENT_PROGRAM:
            mCurrentFragmentProgram->bindProgramPassIterationParameters(mActiveFragmentGpuProgramParameters);
            break;
        case GPT_COMPUTE_PROGRAM:
        case GPT_DOMAIN_PROGRAM:
        case GPT_HULL_PROGRAM:
            break;
        }
    }
