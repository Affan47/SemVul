intrusive_ptr<ExpressionFieldPath> ExpressionFieldPath::parse(
    const boost::intrusive_ptr<ExpressionContext>& expCtx,
    const string& raw,
    const VariablesParseState& vps) {
    uassert(16873,
            str::stream() << "FieldPath '" << raw << "' doesn't start with $",
            raw.c_str()[0] == '$');

    uassert(16872,
            str::stream() << "'$' by itself is not a valid FieldPath",
            raw.size() >= 2);

    if (raw[1] == '$') {
        const StringData rawSD = raw;
        const StringData fieldPath = rawSD.substr(2);
        const StringData varName = fieldPath.substr(0, fieldPath.find('.'));
        Variables::uassertValidNameForUserRead(varName);
        return new ExpressionFieldPath(expCtx, fieldPath.toString(), vps.getVariable(varName));
    } else {
        return new ExpressionFieldPath(expCtx,
                                       "CURRENT." + raw.substr(1),
                                       vps.getVariable("CURRENT"));
    }
}
