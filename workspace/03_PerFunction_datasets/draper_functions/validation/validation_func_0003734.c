compareIgnoreCase(const char* s1, const char* s2)
{
    const char* it1 = s1;
    const char* it2 = s2;
    while (*it1 && *it2)
    {
        if (*it1 != *it2)
        {
            char c1 = std::toupper(*it1);
            char c2 = std::toupper(*it2);
            if (c1 < c2)
                return -1;
            else if (c2 < c1)
                return 1;
        }
        ++it1;
        ++it2;
    }

    return *it1 ? 1
                : *it2 ? -1 : 0;
}

}
