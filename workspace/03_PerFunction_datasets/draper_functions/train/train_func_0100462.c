GetMinVersionNumber()
{
    int i, nVersion = 300;


    for(i=0; i< m_numPen; i++)
    {
        if (m_papsPen[i]->nPointWidth > 0 )
        {
            nVersion = MAX(nVersion, 450);
        }
    }

    return nVersion;
}
