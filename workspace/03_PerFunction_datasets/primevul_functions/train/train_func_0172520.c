BOOL Parser::NodeIsEvalName(ParseNodePtr pnode)
{

    return pnode->nop == knopName && (pnode->sxPid.pid == wellKnownPropertyPids.eval);
}
