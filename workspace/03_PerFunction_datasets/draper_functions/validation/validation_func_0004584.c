check_artist(string &artist)
{
    try
    {
        Q q("SELECT artist FROM Artists WHERE similar(artist, ?);");
        q << artist;

        if (q.next())
        {
            q >> artist;
            return true;
        }
    }
    WARNIFFAILED();
    return false;
}
