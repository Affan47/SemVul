getChild(const String& name)
    {

        OverlayContainerList::iterator i, iend;
        iend = m2DElements.end();
        for (i = m2DElements.begin(); i != iend; ++i)
        {
            if ((*i)->getName() == name)
            {
                return *i;

            }
        }
        return NULL;
    }
