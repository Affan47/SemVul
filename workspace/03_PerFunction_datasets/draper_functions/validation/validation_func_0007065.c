AddPathsToSet(const std::string& FileName, std::set<std::string>* set)
{
    std::list<std::string> templist;
    AddInclPathsToList(FileName, &templist);
    set->insert(templist.begin(), templist.end());
}
