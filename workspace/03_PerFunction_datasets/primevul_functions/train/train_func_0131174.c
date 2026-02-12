intrusive_ptr<Expression> ExpressionOr::optimize() {

    intrusive_ptr<Expression> pE(ExpressionNary::optimize());


    ExpressionOr* pOr = dynamic_cast<ExpressionOr*>(pE.get());
    if (!pOr)
        return pE;


    const size_t n = pOr->vpOperand.size();

    verify(n > 0);
    intrusive_ptr<Expression> pLast(pOr->vpOperand[n - 1]);
    const ExpressionConstant* pConst = dynamic_cast<ExpressionConstant*>(pLast.get());
    if (!pConst)
        return pE;


    bool last = pConst->getValue().coerceToBool();
    if (last) {
        intrusive_ptr<ExpressionConstant> pFinal(
            ExpressionConstant::create(getExpressionContext(), Value(true)));
        return pFinal;
    }


    if (n == 2) {
        intrusive_ptr<Expression> pFinal(
            ExpressionCoerceToBool::create(getExpressionContext(), pOr->vpOperand[0]));
        return pFinal;
    }


    pOr->vpOperand.resize(n - 1);
    return pE;
}
