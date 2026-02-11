sortByName( TFileInfoList &lstFiles, bool ascendingOrder )
{
    std::sort(lstFiles.begin(),lstFiles.end(), ascendingOrder ? cmpFileEntriesName_Asc : cmpFileEntriesName_Desc );
}
