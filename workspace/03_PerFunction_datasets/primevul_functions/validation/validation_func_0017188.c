MatchExpression::ExpressionOptimizerFunc InMatchExpression::getOptimizer() const {
    return [](std::unique_ptr<MatchExpression> expression) -> std::unique_ptr<MatchExpression> {


        auto& regexList = static_cast<InMatchExpression&>(*expression)._regexes;
        auto& equalitySet = static_cast<InMatchExpression&>(*expression)._equalitySet;
        auto collator = static_cast<InMatchExpression&>(*expression).getCollator();
        if (regexList.size() == 1 && equalitySet.empty()) {

            auto& childRe = regexList.front();
            invariant(!childRe->getTag());

            auto simplifiedExpression = stdx::make_unique<RegexMatchExpression>(
                expression->path(), childRe->getString(), childRe->getFlags());
            if (expression->getTag()) {
                simplifiedExpression->setTag(expression->getTag()->clone());
            }
            return std::move(simplifiedExpression);
        } else if (equalitySet.size() == 1 && regexList.empty()) {

            auto simplifiedExpression = stdx::make_unique<EqualityMatchExpression>(
                expression->path(), *(equalitySet.begin()));
            simplifiedExpression->setCollator(collator);
            if (expression->getTag()) {
                simplifiedExpression->setTag(expression->getTag()->clone());
            }

            return std::move(simplifiedExpression);
        }

        return expression;
    };
}
