Value DocumentSourceGroup::expandId(const Value& val) {

    if (_idFieldNames.empty())
        return val;


    if (_idFieldNames.size() == 1)
        return Value(DOC(_idFieldNames[0] << val));


    const vector<Value>& vals = val.getArray();
    invariant(_idFieldNames.size() == vals.size());
    MutableDocument md(vals.size());
    for (size_t i = 0; i < vals.size(); i++) {
        md[_idFieldNames[i]] = vals[i];
    }
    return md.freezeToValue();
}
