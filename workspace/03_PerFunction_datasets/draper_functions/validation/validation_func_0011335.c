first_user_slot(DB_Version version)
{
    int count = 16;

    if (version >= DBV_Float)
	count += 2;

    if (version >= DBV_Map)
        count += 1;

    return count;
}
