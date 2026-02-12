ParseNode* Parser::CopyPnode(ParseNode *pnode) {
    if (pnode==NULL)
        return NULL;
    switch (pnode->nop) {

    case knopName: {
      ParseNode* nameNode=CreateNameNode(pnode->sxPid.pid,pnode->ichMin,pnode->ichLim);
      nameNode->sxPid.sym=pnode->sxPid.sym;
      return nameNode;
    }

  case knopInt:
    return pnode;

  case knopFlt:
    return pnode;

  case knopStr:
    return pnode;

  case knopRegExp:
    return pnode;
    break;

  case knopThis:
    return CreateNodeT<knopThis>(pnode->ichMin,pnode->ichLim);

  case knopNull:
    return pnode;

  case knopFalse:
    {
      ParseNode* ret = CreateNodeT<knopFalse>(pnode->ichMin, pnode->ichLim);
      ret->location = pnode->location;
      return ret;
    }

  case knopTrue:
    {
        ParseNode* ret = CreateNodeT<knopTrue>(pnode->ichMin, pnode->ichLim);
        ret->location = pnode->location;
        return ret;
    }

  case knopEmpty:
    return CreateNodeT<knopEmpty>(pnode->ichMin,pnode->ichLim);


  case knopNot:
  case knopNeg:
  case knopPos:
  case knopLogNot:
  case knopEllipsis:
  case knopIncPost:
  case knopDecPost:
  case knopIncPre:
  case knopDecPre:
  case knopTypeof:
  case knopVoid:
  case knopDelete:
    return CreateUniNode(pnode->nop,CopyPnode(pnode->sxUni.pnode1),pnode->ichMin,pnode->ichLim);


  case knopArray:
  case knopObject:

    Assert(false);
    break;


  case knopAdd:
  case knopSub:
  case knopMul:
  case knopExpo:
  case knopDiv:
  case knopMod:
  case knopOr:
  case knopXor:
  case knopAnd:
  case knopEq:
  case knopNe:
  case knopLt:
  case knopLe:
  case knopGe:
  case knopGt:
  case knopEqv:
  case knopIn:
  case knopInstOf:
  case knopNEqv:
  case knopComma:
  case knopLogOr:
  case knopLogAnd:
  case knopLsh:
  case knopRsh:
  case knopRs2:

  case knopAsg:

  case knopDot:

  case knopAsgAdd:

  case knopAsgSub:

  case knopAsgMul:

  case knopAsgExpo:

  case knopAsgDiv:

  case knopAsgMod:

  case knopAsgAnd:

  case knopAsgXor:

  case knopAsgOr:

  case knopAsgLsh:

  case knopAsgRsh:

  case knopAsgRs2:

  case knopMember:
  case knopMemberShort:


  case knopIndex:
  case knopList:
    return CreateBinNode(pnode->nop,CopyPnode(pnode->sxBin.pnode1),
                         CopyPnode(pnode->sxBin.pnode2),pnode->ichMin,pnode->ichLim);


  case knopNew:
  case knopCall:
    return CreateCallNode(pnode->nop,CopyPnode(pnode->sxCall.pnodeTarget),
                         CopyPnode(pnode->sxCall.pnodeArgs),pnode->ichMin,pnode->ichLim);

  case knopQmark:
    return CreateTriNode(pnode->nop,CopyPnode(pnode->sxTri.pnode1),
                         CopyPnode(pnode->sxTri.pnode2),CopyPnode(pnode->sxTri.pnode3),
                         pnode->ichMin,pnode->ichLim);


    case knopVarDecl: {
      ParseNode* copyNode=CreateNodeT<knopVarDecl>(pnode->ichMin,pnode->ichLim);
      copyNode->sxVar.pnodeInit=CopyPnode(pnode->sxVar.pnodeInit);
      copyNode->sxVar.sym=pnode->sxVar.sym;

      Assert(pnode->sxVar.pnodeNext==NULL);
      copyNode->sxVar.pnodeNext=NULL;
      return copyNode;
    }


  case knopFncDecl:
  case knopProg:
    Assert(false);
    break;

  case knopEndCode:
    break;

  case knopDebugger:
    break;

    case knopFor: {
      ParseNode* copyNode=CreateNodeT<knopFor>(pnode->ichMin,pnode->ichLim);
      copyNode->sxFor.pnodeInverted=NULL;
      copyNode->sxFor.pnodeInit=CopyPnode(pnode->sxFor.pnodeInit);
      copyNode->sxFor.pnodeCond=CopyPnode(pnode->sxFor.pnodeCond);
      copyNode->sxFor.pnodeIncr=CopyPnode(pnode->sxFor.pnodeIncr);
      copyNode->sxFor.pnodeBody=CopyPnode(pnode->sxFor.pnodeBody);
      return copyNode;
    }

  case knopIf:
    Assert(false);
    break;

  case knopWhile:
    Assert(false);
    break;

  case knopDoWhile:
    Assert(false);
    break;

  case knopForIn:
    Assert(false);
    break;
  case knopForOf:
    Assert(false);
    break;

  case knopReturn: {
    ParseNode* copyNode=CreateNodeT<knopReturn>(pnode->ichMin,pnode->ichLim);
    copyNode->sxReturn.pnodeExpr=CopyPnode(pnode->sxReturn.pnodeExpr);
    return copyNode;
  }

  case knopBlock: {
    ParseNode* copyNode=CreateBlockNode(pnode->ichMin,pnode->ichLim,pnode->sxBlock.blockType);
    if (pnode->grfpn & PNodeFlags::fpnSyntheticNode) {


        copyNode->grfpn |= PNodeFlags::fpnSyntheticNode;
    }
    copyNode->sxBlock.pnodeStmt=CopyPnode(pnode->sxBlock.pnodeStmt);
    return copyNode;
  }

  case knopWith:
    Assert(false);
    break;

  case knopBreak:
    Assert(false);
    break;

  case knopContinue:
    Assert(false);
    break;

  case knopLabel:
    Assert(false);
    break;

  case knopSwitch:
    Assert(false);
    break;

  case knopCase:
    Assert(false);
    break;

  case knopTryFinally:
    Assert(false);
    break;
  case knopFinally:
    Assert(false);
    break;

  case knopCatch:
    Assert(false);
    break;

  case knopTryCatch:
    Assert(false);
    break;

  case knopTry:
    Assert(false);
    break;

  case knopThrow:
    Assert(false);
    break;
  default:
    Assert(false);
    break;
    }
    return NULL;
}
