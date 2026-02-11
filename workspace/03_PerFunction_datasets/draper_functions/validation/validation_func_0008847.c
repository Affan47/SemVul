visitRenderables(Renderable::Visitor* visitor,
        bool debugRenderables)
    {
        for (SectionList::iterator i = mSectionList.begin(); i != mSectionList.end(); ++i)
        {
            visitor->visit(*i, 0, false);
        }

    }
