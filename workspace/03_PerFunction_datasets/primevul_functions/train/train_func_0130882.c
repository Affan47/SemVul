intrusive_ptr<Expression> ExpressionNary::optimize() {
    uint32_t constOperandCount = 0;

    for (auto& operand : vpOperand) {
        operand = operand->optimize();
        if (dynamic_cast<ExpressionConstant*>(operand.get())) {
            ++constOperandCount;
        }
    }


    if (constOperandCount == vpOperand.size()) {
        return intrusive_ptr<Expression>(
            ExpressionConstant::create(getExpressionContext(), evaluate(Document())));
    }


    if (isAssociative()) {
        ExpressionVector constExpressions;
        ExpressionVector optimizedOperands;
        for (size_t i = 0; i < vpOperand.size();) {
            intrusive_ptr<Expression> operand = vpOperand[i];


            if (dynamic_cast<ExpressionConstant*>(operand.get())) {
                constExpressions.push_back(operand);
                ++i;
                continue;
            }


            ExpressionNary* nary = dynamic_cast<ExpressionNary*>(operand.get());
            if (nary && str::equals(nary->getOpName(), getOpName()) && nary->isAssociative()) {
                invariant(!nary->vpOperand.empty());
                vpOperand[i] = std::move(nary->vpOperand[0]);
                vpOperand.insert(
                    vpOperand.begin() + i + 1, nary->vpOperand.begin() + 1, nary->vpOperand.end());
                continue;
            }


            if (!isCommutative()) {
                if (constExpressions.size() > 1) {
                    ExpressionVector vpOperandSave = std::move(vpOperand);
                    vpOperand = std::move(constExpressions);
                    optimizedOperands.emplace_back(
                        ExpressionConstant::create(getExpressionContext(), evaluate(Document())));
                    vpOperand = std::move(vpOperandSave);
                } else {
                    optimizedOperands.insert(
                        optimizedOperands.end(), constExpressions.begin(), constExpressions.end());
                }
                constExpressions.clear();
            }
            optimizedOperands.push_back(operand);
            ++i;
        }

        if (constExpressions.size() > 1) {
            vpOperand = std::move(constExpressions);
            optimizedOperands.emplace_back(
                ExpressionConstant::create(getExpressionContext(), evaluate(Document())));
        } else {
            optimizedOperands.insert(
                optimizedOperands.end(), constExpressions.begin(), constExpressions.end());
        }

        vpOperand = std::move(optimizedOperands);
    }
    return this;
}
