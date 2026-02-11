removeFromObjectLists()
{

    if ( documentBeingDestroyed() ) return;

    if (isFloating()) {
        RenderBlock* outermostBlock = containingBlock();
        for (RenderBlock* p = outermostBlock; p && !p->isCanvas() && p->containsFloat(this);) {
            outermostBlock = p;
            if (p->isFloatingOrPositioned())
                break;
            p = p->containingBlock();
        }

        if (outermostBlock)
            outermostBlock->markAllDescendantsWithFloatsForLayout(this);

        RenderObject *p;
        for (p = parent(); p; p = p->parent()) {
            if (p->isRenderBlock())
                static_cast<RenderBlock*>(p)->removeFloatingObject(this);
        }

    }

    if (inPosObjectList()) {
        RenderObject *p;
        for (p = parent(); p; p = p->parent()) {
            if (p->isRenderBlock())
                static_cast<RenderBlock*>(p)->removePositionedObject(this);
        }
    }
}
