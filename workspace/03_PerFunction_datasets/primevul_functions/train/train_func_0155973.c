usesLongNames (const Header &header)
{


    for (Header::ConstIterator i = header.begin();
         i != header.end();
         ++i)
    {
        if (strlen (i.name()) >= 32 || strlen (i.attribute().typeName()) >= 32)
            return true;
    }

    const ChannelList &channels = header.channels();

    for (ChannelList::ConstIterator i = channels.begin();
         i != channels.end();
         ++i)
    {
        if (strlen (i.name()) >= 32)
            return true;
    }

    return false;
}
