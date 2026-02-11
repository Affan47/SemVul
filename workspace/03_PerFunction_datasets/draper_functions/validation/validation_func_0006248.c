remStr(const string &name)
{
    checkReadOnly();
    map<string, string>::iterator m=data.find(name);
    if(m != data.end())
    {
        data.erase(m);
        setDirty(true);
    }
}
