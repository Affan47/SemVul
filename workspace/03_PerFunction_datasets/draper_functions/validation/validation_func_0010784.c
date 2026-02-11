AssertPartitionIntegrity(OpRcPtrVec & gpuPreOps,
                                  OpRcPtrVec & gpuLatticeOps,
                                  OpRcPtrVec & gpuPostOps)
    {

        for(unsigned int i=0; i<gpuPreOps.size(); ++i)
        {
            if(!gpuPreOps[i]->supportsGpuShader())
            {
                throw Exception("Patition failed check. gpuPreOps");
            }
        }


        if(gpuLatticeOps.size()>0)
        {
            bool requireslattice = false;
            for(unsigned int i=0; i<gpuLatticeOps.size(); ++i)
            {
                if(!gpuLatticeOps[i]->supportsGpuShader()) requireslattice = true;
            }

            if(!requireslattice)
            {
                throw Exception("Patition failed check. gpuLatticeOps");
            }
        }


        for(unsigned int i=0; i<gpuPostOps.size(); ++i)
        {
            if(!gpuPostOps[i]->supportsGpuShader())
            {
                throw Exception("Patition failed check. gpuPostOps");
            }
        }
    }
