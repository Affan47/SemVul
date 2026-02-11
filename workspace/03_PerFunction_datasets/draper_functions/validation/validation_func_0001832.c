_rationaliseBoneAssignments(size_t vertexCount, Mesh::VertexBoneAssignmentList& assignments)
    {

        unsigned short maxBones = 0;
        bool existsNonSkinnedVertices = false;
        VertexBoneAssignmentList::iterator i;

        for (size_t v = 0; v < vertexCount; ++v)
        {

            short currBones = static_cast<unsigned short>(assignments.count(v));
            if (currBones <= 0)
                existsNonSkinnedVertices = true;


            if (maxBones < currBones)
                maxBones = currBones;

            if (currBones > OGRE_MAX_BLEND_WEIGHTS)
            {


                std::pair<VertexBoneAssignmentList::iterator, VertexBoneAssignmentList::iterator> range;

                WeightIteratorMap weightToAssignmentMap;
                range = assignments.equal_range(v);

                for (i = range.first; i != range.second; ++i)
                {

                    weightToAssignmentMap.insert(
                        WeightIteratorMap::value_type(i->second.weight, i));
                }

                unsigned short numToRemove = currBones - OGRE_MAX_BLEND_WEIGHTS;
                WeightIteratorMap::iterator remIt = weightToAssignmentMap.begin();

                while (numToRemove--)
                {

                    assignments.erase(remIt->second);
                    ++remIt;
                }
            }


            std::pair<VertexBoneAssignmentList::iterator, VertexBoneAssignmentList::iterator> normalise_range = assignments.equal_range(v);
            Real totalWeight = 0;

            for (i = normalise_range.first; i != normalise_range.second; ++i)
            {
                totalWeight += i->second.weight;
            }

            if (!Math::RealEqual(totalWeight, 1.0f))
            {
                for (i = normalise_range.first; i != normalise_range.second; ++i)
                {
                    i->second.weight = i->second.weight / totalWeight;
                }
            }

        }

        if (maxBones > OGRE_MAX_BLEND_WEIGHTS)
        {

            LogManager::getSingleton().logMessage("WARNING: the mesh '" + mName + "' "
                "includes vertices with more than " +
                StringConverter::toString(OGRE_MAX_BLEND_WEIGHTS) + " bone assignments. "
                "The lowest weighted assignments beyond this limit have been removed, so "
                "your animation may look slightly different. To eliminate this, reduce "
                "the number of bone assignments per vertex on your mesh to " +
                StringConverter::toString(OGRE_MAX_BLEND_WEIGHTS) + ".", LML_CRITICAL);

            maxBones = OGRE_MAX_BLEND_WEIGHTS;

        }

        if (existsNonSkinnedVertices)
        {

            LogManager::getSingleton().logMessage("WARNING: the mesh '" + mName + "' "
                "includes vertices without bone assignments. Those vertices will "
                "transform to wrong position when skeletal animation enabled. "
                "To eliminate this, assign at least one bone assignment per vertex "
                "on your mesh.", LML_CRITICAL);
        }

        return maxBones;
    }
