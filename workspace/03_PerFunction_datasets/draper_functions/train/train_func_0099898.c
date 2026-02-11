insertSub(DcmDirectoryRecord *dirRec,
                                          unsigned long where,
                                          OFBool before)
{
    if (dirRec != NULL)
    {
        if (checkHierarchy(DirRecordType, dirRec->DirRecordType).good())
            errorFlag = lowerLevelList->insert(dirRec, where, before);
        else
        {
            errorFlag = EC_IllegalCall;
            DCMDATA_DEBUG("DcmDirectoryRecord::insertSub() dcdirrec: ("
                << DRTypeNames[getRecordType()] << " -> "
                << DRTypeNames[dirRec->getRecordType()] << ") hierarchy not allowed");
        }
    }
    return errorFlag;
}
