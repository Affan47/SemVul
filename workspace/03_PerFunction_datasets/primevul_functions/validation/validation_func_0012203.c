intrusive_ptr<Expression> ExpressionMap::parse(ExpressionContext* const expCtx,
                                               BSONElement expr,
                                               const VariablesParseState& vpsIn) {
    verify(expr.fieldNameStringData() == "$map");

    uassert(16878, "$map only supports an object as its argument", expr.type() == Object);


    BSONElement inputElem;
    BSONElement asElem;
    BSONElement inElem;
    const BSONObj args = expr.embeddedObject();
    BSONForEach(arg, args) {
        if (arg.fieldNameStringData() == "input") {
            inputElem = arg;
        } else if (arg.fieldNameStringData() == "as") {
            asElem = arg;
        } else if (arg.fieldNameStringData() == "in") {
            inElem = arg;
        } else {
            uasserted(16879,
                      str::stream() << "Unrecognized parameter to $map: " << arg.fieldName());
        }
    }

    uassert(16880, "Missing 'input' parameter to $map", !inputElem.eoo());
    uassert(16882, "Missing 'in' parameter to $map", !inElem.eoo());


    intrusive_ptr<Expression> input =
        parseOperand(expCtx, inputElem, vpsIn);


    VariablesParseState vpsSub(vpsIn);


    auto varName = asElem.eoo() ? "this" : asElem.str();

    Variables::validateNameForUserWrite(varName);
    Variables::Id varId = vpsSub.defineVariable(varName);


    intrusive_ptr<Expression> in =
        parseOperand(expCtx, inElem, vpsSub);

    return new ExpressionMap(expCtx, varName, varId, input, in);
}
