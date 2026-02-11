parseFile()
{
    if(readOffsetFile(m_filename, &m_break))
    {
        m_count = m_allocated;
        emit progress(100);
        return true;
    }

    if(m_break)
    {
        return false;
    }

    bool ok = parseFileIntern();

    writeOffsetFile(m_filename);
    return ok;
}
