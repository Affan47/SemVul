softwareVertexPoseBlend(Real weight,
        const map<size_t, Vector3>::type& vertexOffsetMap,
        const map<size_t, Vector3>::type& normalsMap,
        VertexData* targetVertexData)
    {

        if (weight == 0.0f)
            return;

        const VertexElement* posElem =
            targetVertexData->vertexDeclaration->findElementBySemantic(VES_POSITION);
        const VertexElement* normElem =
            targetVertexData->vertexDeclaration->findElementBySemantic(VES_NORMAL);
        assert(posElem);

        bool normals = normElem && !normalsMap.empty() && posElem->getSource() == normElem->getSource();
        HardwareVertexBufferSharedPtr destBuf =
            targetVertexData->vertexBufferBinding->getBuffer(
            posElem->getSource());

        size_t elemsPerVertex = destBuf->getVertexSize()/sizeof(float);


        float* pBase = static_cast<float*>(
            destBuf->lock(HardwareBuffer::HBL_NORMAL));


        for (map<size_t, Vector3>::type::const_iterator i = vertexOffsetMap.begin();
            i != vertexOffsetMap.end(); ++i)
        {

            float *pdst = pBase + i->first*elemsPerVertex;

            *pdst = *pdst + (i->second.x * weight);
            ++pdst;
            *pdst = *pdst + (i->second.y * weight);
            ++pdst;
            *pdst = *pdst + (i->second.z * weight);
            ++pdst;

        }

        if (normals)
        {
            float* pNormBase;
            normElem->baseVertexPointerToElement((void*)pBase, &pNormBase);
            for (map<size_t, Vector3>::type::const_iterator i = normalsMap.begin();
                i != normalsMap.end(); ++i)
            {

                float *pdst = pNormBase + i->first*elemsPerVertex;

                *pdst = *pdst + (i->second.x * weight);
                ++pdst;
                *pdst = *pdst + (i->second.y * weight);
                ++pdst;
                *pdst = *pdst + (i->second.z * weight);
                ++pdst;

            }
        }
        destBuf->unlock();
    }
