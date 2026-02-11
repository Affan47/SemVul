addFaceTangentSpaceToVertices(
        size_t indexSet, size_t faceIndex, size_t *localVertInd,
        const Vector3& faceTsU, const Vector3& faceTsV, const Vector3& faceNorm,
        Result& result)
    {

        int faceParity = calculateParity(faceTsU, faceTsV, faceNorm);

        for (int v = 0; v < 3; ++v)
        {


            Real angleWeight = calculateAngleWeight(localVertInd[v],
                localVertInd[(v+1)%3], localVertInd[(v+2)%3]);


            VertexInfo* vertex = &(mVertexArray[localVertInd[v]]);


            bool splitVertex = false;
            size_t reusedOppositeParity = 0;
            bool splitBecauseOfParity = false;
            bool newVertex = false;
            if (!vertex->parity)
            {

                vertex->parity = faceParity;
                newVertex = true;
            }
            if (mSplitMirrored)
            {
                if (!newVertex && faceParity != calculateParity(vertex->tangent, vertex->binormal, vertex->norm))
                {

                    if (vertex->oppositeParityIndex)
                    {


                        reusedOppositeParity = vertex->oppositeParityIndex;
                        vertex = &(mVertexArray[reusedOppositeParity]);
                    }
                    else
                    {
                        splitVertex = true;
                        splitBecauseOfParity = true;

                        LogManager::getSingleton().stream(LML_TRIVIAL)
                            << "TSC parity split - Vpar: " << vertex->parity
                            << " Fpar: " << faceParity
                            << " faceTsU: " << faceTsU
                            << " faceTsV: " << faceTsV
                            << " faceNorm: " << faceNorm
                            << " vertTsU:" << vertex->tangent
                            << " vertTsV:" << vertex->binormal
                            << " vertNorm:" << vertex->norm;

                    }
                }
            }

            if (mSplitRotated)
            {


                if (!newVertex && !splitVertex)
                {

                    Vector3 uvCurrent = vertex->tangent + vertex->binormal;


                    Vector3 vRotHalf = uvCurrent - faceNorm;
                    vRotHalf *= faceNorm.dotProduct(uvCurrent);

                    if ((faceTsU + faceTsV).dotProduct(vRotHalf) < 0.0f)
                    {
                        splitVertex = true;
                    }
                }
            }

            if (splitVertex)
            {
                size_t newVertexIndex = mVertexArray.size();
                VertexSplit splitInfo(localVertInd[v], newVertexIndex);
                result.vertexSplits.push_back(splitInfo);

                if (splitBecauseOfParity)
                {
                    vertex->oppositeParityIndex = newVertexIndex;
                }

                VertexInfo locVertex = *vertex;
                locVertex.tangent = Vector3::ZERO;
                locVertex.binormal = Vector3::ZERO;
                locVertex.parity = faceParity;
                mVertexArray.push_back(locVertex);
                result.indexesRemapped.push_back(IndexRemap(indexSet, faceIndex, splitInfo));

                vertex = &(mVertexArray[newVertexIndex]);

            }
            else if (reusedOppositeParity)
            {

                VertexSplit splitInfo(localVertInd[v], reusedOppositeParity);
                result.indexesRemapped.push_back(IndexRemap(indexSet, faceIndex, splitInfo));

            }


            vertex->tangent += (faceTsU * angleWeight);
            vertex->binormal += (faceTsV * angleWeight);


        }

    }
