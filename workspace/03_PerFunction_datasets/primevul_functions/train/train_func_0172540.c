void PrintPnodeWIndent(ParseNode *pnode,int indentAmt) {
    if (pnode==NULL)
        return;

    Output::Print(_u("[%4d, %4d): "), pnode->ichMin, pnode->ichLim);
    switch (pnode->nop) {

  case knopName:
      Indent(indentAmt);
      if (pnode->sxPid.pid!=NULL) {
        Output::Print(_u("id: %s\n"),pnode->sxPid.pid->Psz());
      }
      else {
        Output::Print(_u("name node\n"));
      }
      break;

  case knopInt:
      Indent(indentAmt);
      Output::Print(_u("%d\n"),pnode->sxInt.lw);
      break;

  case knopFlt:
      Indent(indentAmt);
      Output::Print(_u("%lf\n"),pnode->sxFlt.dbl);
      break;

  case knopStr:
      Indent(indentAmt);
      Output::Print(_u("\"%s\"\n"),pnode->sxPid.pid->Psz());
      break;

  case knopRegExp:
      Indent(indentAmt);
      Output::Print(_u("/%x/\n"),pnode->sxPid.regexPattern);
      break;

  case knopThis:
      Indent(indentAmt);
      Output::Print(_u("this\n"));
      break;

  case knopSuper:
      Indent(indentAmt);
      Output::Print(_u("super\n"));
      break;

  case knopNewTarget:
      Indent(indentAmt);
      Output::Print(_u("new.target\n"));
      break;

  case knopNull:
      Indent(indentAmt);
      Output::Print(_u("null\n"));
      break;

  case knopFalse:
      Indent(indentAmt);
      Output::Print(_u("false\n"));
      break;

  case knopTrue:
      Indent(indentAmt);
      Output::Print(_u("true\n"));
      break;

  case knopEmpty:
      Indent(indentAmt);
      Output::Print(_u("empty\n"));
      break;


  case knopNot:
      Indent(indentAmt);
      Output::Print(_u("~\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopNeg:
      Indent(indentAmt);
      Output::Print(_u("U-\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopPos:
      Indent(indentAmt);
      Output::Print(_u("U+\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopLogNot:
      Indent(indentAmt);
      Output::Print(_u("!\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopEllipsis:
      Indent(indentAmt);
      Output::Print(_u("...<expr>\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopIncPost:
      Indent(indentAmt);
      Output::Print(_u("<expr>++\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopDecPost:
      Indent(indentAmt);
      Output::Print(_u("<expr>--\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopIncPre:
      Indent(indentAmt);
      Output::Print(_u("++<expr>\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopDecPre:
      Indent(indentAmt);
      Output::Print(_u("--<expr>\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopTypeof:
      Indent(indentAmt);
      Output::Print(_u("typeof\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopVoid:
      Indent(indentAmt);
      Output::Print(_u("void\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopDelete:
      Indent(indentAmt);
      Output::Print(_u("delete\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;


  case knopArrayPattern:
      Indent(indentAmt);
      Output::Print(_u("Array Pattern\n"));
      PrintPnodeListWIndent(pnode->sxUni.pnode1, indentAmt + INDENT_SIZE);
      break;

  case knopObjectPattern:
      Indent(indentAmt);
      Output::Print(_u("Object Pattern\n"));
      PrintPnodeListWIndent(pnode->sxUni.pnode1, indentAmt + INDENT_SIZE);
      break;

  case knopArray:
      Indent(indentAmt);
      Output::Print(_u("Array Literal\n"));
      PrintPnodeListWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopObject:
      Indent(indentAmt);
      Output::Print(_u("Object Literal\n"));
      PrintPnodeListWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;


  case knopAdd:
      Indent(indentAmt);
      Output::Print(_u("+\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopSub:
      Indent(indentAmt);
      Output::Print(_u("-\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopMul:
      Indent(indentAmt);
      Output::Print(_u("*\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopExpo:
      Indent(indentAmt);
      Output::Print(_u("**\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1, indentAmt + INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2, indentAmt + INDENT_SIZE);
      break;


  case knopDiv:
      Indent(indentAmt);
      Output::Print(_u("/\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopMod:
      Indent(indentAmt);
      Output::Print(_u("%\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopOr:
      Indent(indentAmt);
      Output::Print(_u("|\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopXor:
      Indent(indentAmt);
      Output::Print(_u("^\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopAnd:
      Indent(indentAmt);
      Output::Print(_u("&\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopEq:
      Indent(indentAmt);
      Output::Print(_u("==\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopNe:
      Indent(indentAmt);
      Output::Print(_u("!=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopLt:
      Indent(indentAmt);
      Output::Print(_u("<\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopLe:
      Indent(indentAmt);
      Output::Print(_u("<=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopGe:
      Indent(indentAmt);
      Output::Print(_u(">=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopGt:
      Indent(indentAmt);
      Output::Print(_u(">\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopCall:
      Indent(indentAmt);
      Output::Print(_u("Call\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeListWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopDot:
      Indent(indentAmt);
      Output::Print(_u(".\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopAsg:
      Indent(indentAmt);
      Output::Print(_u("=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopInstOf:
      Indent(indentAmt);
      Output::Print(_u("instanceof\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopIn:
      Indent(indentAmt);
      Output::Print(_u("in\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopEqv:
      Indent(indentAmt);
      Output::Print(_u("===\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopNEqv:
      Indent(indentAmt);
      Output::Print(_u("!==\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopComma:
      Indent(indentAmt);
      Output::Print(_u(",\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopLogOr:
      Indent(indentAmt);
      Output::Print(_u("||\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopLogAnd:
      Indent(indentAmt);
      Output::Print(_u("&&\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopLsh:
      Indent(indentAmt);
      Output::Print(_u("<<\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopRsh:
      Indent(indentAmt);
      Output::Print(_u(">>\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopRs2:
      Indent(indentAmt);
      Output::Print(_u(">>>\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopNew:
      Indent(indentAmt);
      Output::Print(_u("new\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeListWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopIndex:
      Indent(indentAmt);
      Output::Print(_u("[]\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeListWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopQmark:
      Indent(indentAmt);
      Output::Print(_u("?:\n"));
      PrintPnodeWIndent(pnode->sxTri.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxTri.pnode2,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxTri.pnode3,indentAmt+INDENT_SIZE);
      break;

  case knopAsgAdd:
      Indent(indentAmt);
      Output::Print(_u("+=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopAsgSub:
      Indent(indentAmt);
      Output::Print(_u("-=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopAsgMul:
      Indent(indentAmt);
      Output::Print(_u("*=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopAsgExpo:
      Indent(indentAmt);
      Output::Print(_u("**=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1, indentAmt + INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2, indentAmt + INDENT_SIZE);
      break;


  case knopAsgDiv:
      Indent(indentAmt);
      Output::Print(_u("/=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopAsgMod:
      Indent(indentAmt);
      Output::Print(_u("%=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopAsgAnd:
      Indent(indentAmt);
      Output::Print(_u("&=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopAsgXor:
      Indent(indentAmt);
      Output::Print(_u("^=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopAsgOr:
      Indent(indentAmt);
      Output::Print(_u("|=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopAsgLsh:
      Indent(indentAmt);
      Output::Print(_u("<<=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopAsgRsh:
      Indent(indentAmt);
      Output::Print(_u(">>=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopAsgRs2:
      Indent(indentAmt);
      Output::Print(_u(">>>=\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;

  case knopComputedName:
      Indent(indentAmt);
      Output::Print(_u("ComputedProperty\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1, indentAmt + INDENT_SIZE);
      break;


  case knopMember:
  case knopMemberShort:
  case knopObjectPatternMember:
      Indent(indentAmt);
      Output::Print(_u(":\n"));
      PrintPnodeWIndent(pnode->sxBin.pnode1,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxBin.pnode2,indentAmt+INDENT_SIZE);
      break;


  case knopList:
      Indent(indentAmt);
      Output::Print(_u("List\n"));
      PrintPnodeListWIndent(pnode,indentAmt+INDENT_SIZE);
      break;

  case knopVarDecl:
      Indent(indentAmt);
      Output::Print(_u("var %s\n"),pnode->sxVar.pid->Psz());
      if (pnode->sxVar.pnodeInit!=NULL)
          PrintPnodeWIndent(pnode->sxVar.pnodeInit,indentAmt+INDENT_SIZE);
      break;
  case knopConstDecl:
      Indent(indentAmt);
      Output::Print(_u("const %s\n"),pnode->sxVar.pid->Psz());
      if (pnode->sxVar.pnodeInit!=NULL)
          PrintPnodeWIndent(pnode->sxVar.pnodeInit,indentAmt+INDENT_SIZE);
      break;
  case knopLetDecl:
      Indent(indentAmt);
      Output::Print(_u("let %s\n"),pnode->sxVar.pid->Psz());
      if (pnode->sxVar.pnodeInit!=NULL)
          PrintPnodeWIndent(pnode->sxVar.pnodeInit,indentAmt+INDENT_SIZE);
      break;

  case knopFncDecl:
      Indent(indentAmt);
      if (pnode->sxFnc.pid!=NULL)
      {
          Output::Print(_u("fn decl %d nested %d name %s (%d-%d)\n"),pnode->sxFnc.IsDeclaration(),pnode->sxFnc.IsNested(),
              pnode->sxFnc.pid->Psz(), pnode->ichMin, pnode->ichLim);
      }
      else
      {
          Output::Print(_u("fn decl %d nested %d anonymous (%d-%d)\n"),pnode->sxFnc.IsDeclaration(),pnode->sxFnc.IsNested(),pnode->ichMin,pnode->ichLim);
      }
      PrintScopesWIndent(pnode, indentAmt+INDENT_SIZE);
      PrintFormalsWIndent(pnode->sxFnc.pnodeParams, indentAmt + INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxFnc.pnodeRest, indentAmt + INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxFnc.pnodeBody, indentAmt + INDENT_SIZE);
      if (pnode->sxFnc.pnodeBody == nullptr)
      {
          Output::Print(_u("[%4d, %4d): "), pnode->ichMin, pnode->ichLim);
          Indent(indentAmt + INDENT_SIZE);
          Output::Print(_u("<parse deferred body>\n"));
      }
      break;

  case knopProg:
      Indent(indentAmt);
      Output::Print(_u("program\n"));
      PrintScopesWIndent(pnode, indentAmt+INDENT_SIZE);
      PrintPnodeListWIndent(pnode->sxFnc.pnodeBody,indentAmt+INDENT_SIZE);
      break;

  case knopEndCode:
      Indent(indentAmt);
      Output::Print(_u("<endcode>\n"));
      break;

  case knopDebugger:
      Indent(indentAmt);
      Output::Print(_u("<debugger>\n"));
      break;

  case knopFor:
      Indent(indentAmt);
      Output::Print(_u("for\n"));
      PrintScopesWIndent(pnode, indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxFor.pnodeInit,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxFor.pnodeCond,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxFor.pnodeIncr,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxFor.pnodeBody,indentAmt+INDENT_SIZE);
      break;

  case knopIf:
      Indent(indentAmt);
      Output::Print(_u("if\n"));
      PrintPnodeWIndent(pnode->sxIf.pnodeCond,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxIf.pnodeTrue,indentAmt+INDENT_SIZE);
      if (pnode->sxIf.pnodeFalse!=NULL)
          PrintPnodeWIndent(pnode->sxIf.pnodeFalse,indentAmt+INDENT_SIZE);
      break;

  case knopWhile:
      Indent(indentAmt);
      Output::Print(_u("while\n"));
      PrintPnodeWIndent(pnode->sxWhile.pnodeCond,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxWhile.pnodeBody,indentAmt+INDENT_SIZE);
      break;

  case knopDoWhile:
      Indent(indentAmt);
      Output::Print(_u("do\n"));
      PrintPnodeWIndent(pnode->sxWhile.pnodeCond,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxWhile.pnodeBody,indentAmt+INDENT_SIZE);
      break;

  case knopForIn:
      Indent(indentAmt);
      Output::Print(_u("forIn\n"));
      PrintScopesWIndent(pnode, indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxForInOrForOf.pnodeLval,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxForInOrForOf.pnodeObj,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxForInOrForOf.pnodeBody,indentAmt+INDENT_SIZE);
      break;
  case knopForOf:
      Indent(indentAmt);
      Output::Print(_u("forOf\n"));
      PrintScopesWIndent(pnode, indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxForInOrForOf.pnodeLval,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxForInOrForOf.pnodeObj,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxForInOrForOf.pnodeBody,indentAmt+INDENT_SIZE);
      break;

  case knopReturn:
      Indent(indentAmt);
      Output::Print(_u("return\n"));
      if (pnode->sxReturn.pnodeExpr!=NULL)
          PrintPnodeWIndent(pnode->sxReturn.pnodeExpr,indentAmt+INDENT_SIZE);
      break;

  case knopBlock:
      Indent(indentAmt);
      Output::Print(_u("block "));
      if (pnode->grfpn & fpnSyntheticNode)
          Output::Print(_u("synthetic "));
      PrintBlockType(pnode->sxBlock.blockType);
      Output::Print(_u("(%d-%d)\n"),pnode->ichMin,pnode->ichLim);
      PrintScopesWIndent(pnode, indentAmt+INDENT_SIZE);
      if (pnode->sxBlock.pnodeStmt!=NULL)
          PrintPnodeWIndent(pnode->sxBlock.pnodeStmt,indentAmt+INDENT_SIZE);
      break;

  case knopWith:
      Indent(indentAmt);
      Output::Print(_u("with (%d-%d)\n"), pnode->ichMin,pnode->ichLim);
      PrintScopesWIndent(pnode, indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxWith.pnodeObj,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxWith.pnodeBody,indentAmt+INDENT_SIZE);
      break;

  case knopBreak:
      Indent(indentAmt);
      Output::Print(_u("break\n"));

      break;

  case knopContinue:
      Indent(indentAmt);
      Output::Print(_u("continue\n"));

      break;

  case knopLabel:
      Indent(indentAmt);
      Output::Print(_u("label %s"),pnode->sxLabel.pid->Psz());

      break;

  case knopSwitch:
      Indent(indentAmt);
      Output::Print(_u("switch\n"));
      PrintScopesWIndent(pnode, indentAmt+INDENT_SIZE);
      for (ParseNode *pnodeT = pnode->sxSwitch.pnodeCases; NULL != pnodeT;pnodeT = pnodeT->sxCase.pnodeNext) {
          PrintPnodeWIndent(pnodeT,indentAmt+2);
      }
      break;

  case knopCase:
      Indent(indentAmt);
      Output::Print(_u("case\n"));
      PrintPnodeWIndent(pnode->sxCase.pnodeExpr,indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxCase.pnodeBody,indentAmt+INDENT_SIZE);
      break;

  case knopTryFinally:
      PrintPnodeWIndent(pnode->sxTryFinally.pnodeTry,indentAmt);
      PrintPnodeWIndent(pnode->sxTryFinally.pnodeFinally,indentAmt);
      break;
  case knopFinally:
      Indent(indentAmt);
      Output::Print(_u("finally\n"));
      PrintPnodeWIndent(pnode->sxFinally.pnodeBody,indentAmt+INDENT_SIZE);
      break;

  case knopCatch:
      Indent(indentAmt);
      Output::Print(_u("catch (%d-%d)\n"), pnode->ichMin,pnode->ichLim);
      PrintScopesWIndent(pnode, indentAmt+INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxCatch.pnodeParam,indentAmt+INDENT_SIZE);


      PrintPnodeWIndent(pnode->sxCatch.pnodeBody,indentAmt+INDENT_SIZE);
      break;

  case knopTryCatch:
      PrintPnodeWIndent(pnode->sxTryCatch.pnodeTry,indentAmt);
      PrintPnodeWIndent(pnode->sxTryCatch.pnodeCatch,indentAmt);
      break;

  case knopTry:
      Indent(indentAmt);
      Output::Print(_u("try\n"));
      PrintPnodeWIndent(pnode->sxTry.pnodeBody,indentAmt+INDENT_SIZE);
      break;

  case knopThrow:
      Indent(indentAmt);
      Output::Print(_u("throw\n"));
      PrintPnodeWIndent(pnode->sxUni.pnode1,indentAmt+INDENT_SIZE);
      break;

  case knopClassDecl:
      Indent(indentAmt);
      Output::Print(_u("class %s"), pnode->sxClass.pnodeName->sxVar.pid->Psz());
      if (pnode->sxClass.pnodeExtends != nullptr)
      {
          Output::Print(_u(" extends "));
          PrintPnodeWIndent(pnode->sxClass.pnodeExtends, 0);
      }
      else {
          Output::Print(_u("\n"));
      }

      PrintPnodeWIndent(pnode->sxClass.pnodeConstructor,   indentAmt + INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxClass.pnodeMembers,       indentAmt + INDENT_SIZE);
      PrintPnodeWIndent(pnode->sxClass.pnodeStaticMembers, indentAmt + INDENT_SIZE);
      break;
  case knopStrTemplate:
      Indent(indentAmt);
      Output::Print(_u("string template\n"));
      PrintPnodeListWIndent(pnode->sxStrTemplate.pnodeSubstitutionExpressions, indentAmt + INDENT_SIZE);
      break;
  case knopYieldStar:
      Indent(indentAmt);
      Output::Print(_u("yield*\n"));
      PrintPnodeListWIndent(pnode->sxUni.pnode1, indentAmt + INDENT_SIZE);
      break;
  case knopYield:
  case knopYieldLeaf:
      Indent(indentAmt);
      Output::Print(_u("yield\n"));
      PrintPnodeListWIndent(pnode->sxUni.pnode1, indentAmt + INDENT_SIZE);
      break;
  case knopAwait:
      Indent(indentAmt);
      Output::Print(_u("await\n"));
      PrintPnodeListWIndent(pnode->sxUni.pnode1, indentAmt + INDENT_SIZE);
      break;
  case knopExportDefault:
      Indent(indentAmt);
      Output::Print(_u("export default\n"));
      PrintPnodeListWIndent(pnode->sxExportDefault.pnodeExpr, indentAmt + INDENT_SIZE);
      break;
  default:
      Output::Print(_u("unhandled pnode op %d\n"),pnode->nop);
      break;
    }
}
