invalidate(const String& materialName, const String& groupName)
{
    SGTechniqueIterator itTech;


    bool doAutoDetect = groupName == ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME;
    for (itTech = mTechniqueEntries.begin(); itTech != mTechniqueEntries.end(); ++itTech)
    {
        SGTechnique* curTechEntry = *itTech;
        const SGMaterial* curMaterial = curTechEntry->getParent();
        if ((curMaterial->getMaterialName() == materialName) &&
            ((doAutoDetect == true) || (curMaterial->getGroupName() == groupName)))
        {

            curTechEntry->setBuildDestinationTechnique(true);
            break;
        }
    }

    mOutOfDate = true;
}
