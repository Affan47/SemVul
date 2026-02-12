void Parser::ParseExpressionLambdaBody(ParseNodePtr pnodeLambda)
{
    ParseNodePtr *lastNodeRef = nullptr;


    ParseNodePtr pnodeRet = nullptr;

    if (buildAST)
    {
        pnodeRet = CreateNodeWithScanner<knopReturn>();
        pnodeRet->grfpn |= PNodeFlags::fpnSyntheticNode;
        pnodeLambda->sxFnc.pnodeScopes->sxBlock.pnodeStmt = pnodeRet;
    }

    IdentToken token;
    charcount_t lastRParen = 0;
    ParseNodePtr result = ParseExpr<buildAST>(koplAsg, nullptr, TRUE, FALSE, nullptr, nullptr, nullptr, &token, false, nullptr, &lastRParen);

    this->MarkEscapingRef(result, &token);

    if (buildAST)
    {
        pnodeRet->sxReturn.pnodeExpr = result;

        pnodeRet->ichMin = pnodeRet->sxReturn.pnodeExpr->ichMin;
        pnodeRet->ichLim = pnodeRet->sxReturn.pnodeExpr->ichLim;


        pnodeRet->sxStmt.grfnop = 0;
        pnodeRet->sxStmt.pnodeOuter = nullptr;

        pnodeLambda->ichLim = max(pnodeRet->ichLim, lastRParen);
        pnodeLambda->sxFnc.cbLim = m_pscan->IecpLimTokPrevious();
        pnodeLambda->sxFnc.pnodeScopes->ichLim = pnodeRet->ichLim;

        pnodeLambda->sxFnc.pnodeBody = nullptr;
        AddToNodeList(&pnodeLambda->sxFnc.pnodeBody, &lastNodeRef, pnodeLambda->sxFnc.pnodeScopes);


        ParseNodePtr end = CreateNodeWithScanner<knopEndCode>(pnodeRet->ichLim);
        end->ichLim = end->ichMin;
        AddToNodeList(&pnodeLambda->sxFnc.pnodeBody, &lastNodeRef, end);


        pnodeLambda->sxFnc.SetHasReferenceableBuiltInArguments(false);
    }
}
