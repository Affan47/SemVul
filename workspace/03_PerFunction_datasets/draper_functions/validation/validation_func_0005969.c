setupVertices( const SubMesh* baseSubMesh )
    {
        mRenderOperation.vertexData = OGRE_NEW VertexData();
        mRemoveOwnVertexData = true;

        VertexData *thisVertexData = mRenderOperation.vertexData;
        VertexData *baseVertexData = baseSubMesh->vertexData;

        thisVertexData->vertexStart = 0;
        thisVertexData->vertexCount = baseVertexData->vertexCount;
        mRenderOperation.numberOfInstances = mInstancesPerBatch;

        HardwareBufferManager::getSingleton().destroyVertexDeclaration(
                                                                    thisVertexData->vertexDeclaration );
        thisVertexData->vertexDeclaration = baseVertexData->vertexDeclaration->clone();


        VertexBufferBinding::VertexBufferBindingMap::const_iterator itor = baseVertexData->
                                                            vertexBufferBinding->getBindings().begin();
        VertexBufferBinding::VertexBufferBindingMap::const_iterator end  = baseVertexData->
                                                            vertexBufferBinding->getBindings().end();
        while( itor != end )
        {
            const unsigned short bufferIdx = itor->first;
            const HardwareVertexBufferSharedPtr vBuf = itor->second;
            thisVertexData->vertexBufferBinding->setBinding( bufferIdx, vBuf );
            ++itor;
        }


        HWBoneIdxVec hwBoneIdx;
        HWBoneWgtVec hwBoneWgt;


        const VertexElement *veWeights = baseVertexData->vertexDeclaration->
                                                        findElementBySemantic( VES_BLEND_WEIGHTS );
        if( veWeights )
            mWeightCount = forceOneWeight() ? 1 : veWeights->getSize() / sizeof(float);
        else
            mWeightCount = 1;

        hwBoneIdx.resize( baseVertexData->vertexCount * mWeightCount, 0 );

        if( mMeshReference->hasSkeleton() && !mMeshReference->getSkeleton().isNull() )
        {
            if(mWeightCount > 1)
            {
                hwBoneWgt.resize( baseVertexData->vertexCount * mWeightCount, 0 );
                retrieveBoneIdxWithWeights(baseVertexData, hwBoneIdx, hwBoneWgt);
            }
            else
            {
                retrieveBoneIdx( baseVertexData, hwBoneIdx );
            }

            const VertexElement* pElement = thisVertexData->vertexDeclaration->findElementBySemantic
                                                                                    (VES_BLEND_INDICES);
            if (pElement)
            {
                unsigned short skelDataSource = pElement->getSource();
                thisVertexData->vertexDeclaration->removeElement( VES_BLEND_INDICES );
                thisVertexData->vertexDeclaration->removeElement( VES_BLEND_WEIGHTS );
                if (thisVertexData->vertexDeclaration->findElementsBySource(skelDataSource).empty())
                {
                    thisVertexData->vertexDeclaration->closeGapsInSource();
                    thisVertexData->vertexBufferBinding->unsetBinding(skelDataSource);
                    VertexBufferBinding::BindingIndexMap tmpMap;
                    thisVertexData->vertexBufferBinding->closeGaps(tmpMap);
                }
            }
        }

        createVertexTexture( baseSubMesh );
        createVertexSemantics( thisVertexData, baseVertexData, hwBoneIdx, hwBoneWgt);
    }
