generateEvalCode(CompileState* comp)
{
    Node* cand = expr->nodeInsideAllParens();
    ASSERT(cand->isLocation());
    LocationNode* loc = static_cast<LocationNode*>(cand);

    OpValue funVal, thisVal;
    loc->generateRefFunc(comp, &funVal, &thisVal);
    args->generateEvalArguments(comp);

    OpValue out;
    CodeGen::emitOp(comp, Op_FunctionCall, &out, &funVal, &thisVal);
    return out;
}
