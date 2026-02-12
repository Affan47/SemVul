bool PnBlock::HasBlockScopedContent() const
{


    if (this->pnodeLexVars != nullptr || this->blockType == Parameter)
    {
        return true;
    }


    for (ParseNodePtr pnode = this->pnodeScopes; pnode;)
    {
        switch (pnode->nop) {

        case knopFncDecl:
            return true;

        case knopBlock:
            pnode = pnode->sxBlock.pnodeNext;
            break;

        case knopCatch:
            pnode = pnode->sxCatch.pnodeNext;
            break;

        case knopWith:
            pnode = pnode->sxWith.pnodeNext;
            break;

        default:
            Assert(UNREACHED);
            return true;
        }
    }

    return false;
}
