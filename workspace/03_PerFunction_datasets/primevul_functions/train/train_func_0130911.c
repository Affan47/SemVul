intrusive_ptr<Expression> ExpressionFilter::parse(
    const boost::intrusive_ptr<ExpressionContext>& expCtx,
    BSONElement expr,
    const VariablesParseState& vpsIn) {
    verify(str::equals(expr.fieldName(), "$filter"));

    uassert(28646, "$filter only supports an object as its argument", expr.type() == Object);


    BSONElement inputElem;
    BSONElement asElem;
    BSONElement condElem;
    for (auto elem : expr.Obj()) {
        if (str::equals(elem.fieldName(), "input")) {
            inputElem = elem;
        } else if (str::equals(elem.fieldName(), "as")) {
            asElem = elem;
        } else if (str::equals(elem.fieldName(), "cond")) {
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

    Variables::uassertValidNameForUserWrite(varName);
    Variables::Id varId = vpsSub.defineVariable(varName);


    intrusive_ptr<Expression> cond = parseOperand(expCtx, condElem, vpsSub);

    return new ExpressionFilter(
        expCtx, std::move(varName), varId, std::move(input), std::move(cond));
}
