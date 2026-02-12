intrusive_ptr<Expression> ExpressionFilter::parse(ExpressionContext* const expCtx,
                                                  BSONElement expr,
                                                  const VariablesParseState& vpsIn) {
    verify(expr.fieldNameStringData() == "$filter");

    uassert(28646, "$filter only supports an object as its argument", expr.type() == Object);


    BSONElement inputElem;
    BSONElement asElem;
    BSONElement condElem;
    for (auto elem : expr.Obj()) {
        if (elem.fieldNameStringData() == "input") {
            inputElem = elem;
        } else if (elem.fieldNameStringData() == "as") {
            asElem = elem;
        } else if (elem.fieldNameStringData() == "cond") {
            condElem = elem;
        } else {
            uasserted(28647,
                      str::stream() << "Unrecognized parameter to $filter: " << elem.fieldName());
        }
    }

    uassert(28648, "Missing 'input' parameter to $filter", !inputElem.eoo());
    uassert(28650, "Missing 'cond' parameter to $filter", !condElem.eoo());


    intrusive_ptr<Expression> input = parseOperand(expCtx, inputElem, vpsIn);


    VariablesParseState vpsSub(vpsIn);


    auto varName = asElem.eoo() ? "this" : asElem.str();

    Variables::validateNameForUserWrite(varName);
    Variables::Id varId = vpsSub.defineVariable(varName);


    intrusive_ptr<Expression> cond = parseOperand(expCtx, condElem, vpsSub);

    return new ExpressionFilter(
        expCtx, std::move(varName), varId, std::move(input), std::move(cond));
}
