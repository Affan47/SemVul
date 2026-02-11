writeMesh(const Mesh* pMesh)
    {
        exportedLodCount = 1;


        writeChunkHeader(M_MESH, calcMeshSize(pMesh));
        {

        bool skelAnim = pMesh->hasSkeleton();
        writeBools(&skelAnim, 1);

            pushInnerChunk(mStream);


        if (pMesh->sharedVertexData)
            writeGeometry(pMesh->sharedVertexData);


        for (unsigned short i = 0; i < pMesh->getNumSubMeshes(); ++i)
        {
            LogManager::getSingleton().logMessage("Writing submesh...");
            writeSubMesh(pMesh->getSubMesh(i));
            LogManager::getSingleton().logMessage("Submesh exported.");
        }


        if (pMesh->hasSkeleton())
        {
            LogManager::getSingleton().logMessage("Exporting skeleton link...");

            writeSkeletonLink(pMesh->getSkeletonName());
            LogManager::getSingleton().logMessage("Skeleton link exported.");


            if (!pMesh->mBoneAssignments.empty())
            {
                LogManager::getSingleton().logMessage("Exporting shared geometry bone assignments...");

                Mesh::VertexBoneAssignmentList::const_iterator vi;
                for (vi = pMesh->mBoneAssignments.begin();
                vi != pMesh->mBoneAssignments.end(); ++vi)
                {
                    writeMeshBoneAssignment(vi->second);
                }

                LogManager::getSingleton().logMessage("Shared geometry bone assignments exported.");
            }
        }

#if !OGRE_NO_MESHLOD

        if (pMesh->getNumLodLevels() > 1)
        {
            LogManager::getSingleton().logMessage("Exporting LOD information....");
                writeLodLevel(pMesh);
            LogManager::getSingleton().logMessage("LOD information exported.");

        }
#endif


        LogManager::getSingleton().logMessage("Exporting bounds information....");
        writeBoundsInfo(pMesh);
        LogManager::getSingleton().logMessage("Bounds information exported.");


        LogManager::getSingleton().logMessage("Exporting submesh name table...");
        writeSubMeshNameTable(pMesh);
        LogManager::getSingleton().logMessage("Submesh name table exported.");


        if (pMesh->isEdgeListBuilt())
        {
            LogManager::getSingleton().logMessage("Exporting edge lists...");
            writeEdgeList(pMesh);
            LogManager::getSingleton().logMessage("Edge lists exported");
        }


        writePoses(pMesh);
        if (pMesh->hasVertexAnimation())
        {
            writeAnimations(pMesh);
        }


        writeExtremes(pMesh);
            popInnerChunk(mStream);
        }
    }
