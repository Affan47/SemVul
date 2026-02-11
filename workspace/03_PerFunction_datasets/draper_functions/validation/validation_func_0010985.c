anchorToHomeZone(PCZone * zone)
    {
        mHomeZone = zone;
        if (zone)
        {
            mAnchored = true;
        }
        else
        {
            mAnchored = false;
        }
    }
