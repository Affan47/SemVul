intrusive_ptr<Expression> ExpressionAnd::optimize() {

    intrusive_ptr<Expression> pE(ExpressionNary::optimize());


    ExpressionAnd* pAnd = dynamic_cast<ExpressionAnd*>(pE.get());
    if (!pAnd)
        return pE;


    const size_t n = pAnd->vpOperand.size();

    verify(n > 0);
    intrusive_ptr<Expression> pLast(pAnd->vpOperand[n - 1]);
    const ExpressionConstant* pConst = dynamic_cast<ExpressionConstant*>(pLast.get());
    if (!pConst)
        return pE;


    bool last = pConst->getValue().coerceToBool();
    if (!last) {
        intrusive_ptr<ExpressionConstant> pFinal(
            ExpressionConstant::create(getExpressionContext(), Value(false)));
        return pFinal;
    }


    if (n == 2) {
        intrusive_ptr<Expression> pFinal(
            ExpressionCoerceToBool::create(getExpressionContext(), pAnd->vpOperand[0]));
        return pFinal;
    }


    pAnd->vpOperand.resize(n - 1);
    return pE;
}
