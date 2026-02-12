void Parser::FinishBackgroundRegExpNodes()
{


    Assert(!this->IsBackgroundParser());
    Assert(this->fastScannedRegExpNodes);
    Assert(this->backgroundParseItems != nullptr);

    BackgroundParseItem *currBackgroundItem;

#if DBG
    for (currBackgroundItem = this->backgroundParseItems;
         currBackgroundItem;
         currBackgroundItem = currBackgroundItem->GetNext())
    {
        if (currBackgroundItem->RegExpNodeList())
        {
            FOREACH_DLIST_ENTRY(ParseNodePtr, ArenaAllocator, pnode, currBackgroundItem->RegExpNodeList())
            {
                Assert(pnode->sxPid.regexPattern == nullptr);
            }
            NEXT_DLIST_ENTRY;
        }
    }
#endif


    currBackgroundItem = this->backgroundParseItems;
    FOREACH_DLIST_ENTRY(ParseNodePtr, ArenaAllocator, pnodeFgnd, this->fastScannedRegExpNodes)
    {
        Assert(pnodeFgnd->nop == knopRegExp);
        Assert(pnodeFgnd->sxPid.regexPattern != nullptr);
        bool quit = false;

        while (!quit)
        {

            while (currBackgroundItem && currBackgroundItem->RegExpNodeList() == nullptr)
            {
                currBackgroundItem = currBackgroundItem->GetNext();
            }
            if (!currBackgroundItem)
            {
                break;
            }


            FOREACH_DLIST_ENTRY(ParseNodePtr, ArenaAllocator, pnodeBgnd, currBackgroundItem->RegExpNodeList())
            {
                Assert(pnodeBgnd->nop == knopRegExp);

                if (pnodeFgnd->ichMin <= pnodeBgnd->ichMin)
                {


                    if (pnodeFgnd->ichMin == pnodeBgnd->ichMin)
                    {
                        Assert(pnodeFgnd->ichLim == pnodeBgnd->ichLim);
                        pnodeBgnd->sxPid.regexPattern = pnodeFgnd->sxPid.regexPattern;
                    }
                    quit = true;
                    break;
                }
            }
            NEXT_DLIST_ENTRY;

            if (!quit)
            {

                currBackgroundItem = currBackgroundItem->GetNext();
            }
        }
    }
    NEXT_DLIST_ENTRY;

#if DBG
    for (currBackgroundItem = this->backgroundParseItems;
         currBackgroundItem;
         currBackgroundItem = currBackgroundItem->GetNext())
    {
        if (currBackgroundItem->RegExpNodeList())
        {
            FOREACH_DLIST_ENTRY(ParseNodePtr, ArenaAllocator, pnode, currBackgroundItem->RegExpNodeList())
            {
                Assert(pnode->sxPid.regexPattern != nullptr);
            }
            NEXT_DLIST_ENTRY;
        }
    }
#endif
}
