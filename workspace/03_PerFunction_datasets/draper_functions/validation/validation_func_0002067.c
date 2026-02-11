pointerArithBoolCond(const Token *tok)
{
    if (!tok)
        return;
    if (Token::Match(tok, "&&|%oror%")) {
        pointerArithBoolCond(tok->astOperand1());
        pointerArithBoolCond(tok->astOperand2());
        return;
    }
    if (tok->str() != "+")
        return;

    if (tok->astOperand1() &&
        tok->astOperand1()->isName() &&
        tok->astOperand1()->variable() &&
        tok->astOperand1()->variable()->isPointer() &&
        tok->astOperand2()->isNumber())
        pointerArithBoolError(tok);
}
