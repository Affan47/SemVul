readItem(const std::string &luid, std::string &item)
{
    StringPair ids = splitLUID(luid);
    m_sub->readSubItem(ids.first, ids.second, item);
}
