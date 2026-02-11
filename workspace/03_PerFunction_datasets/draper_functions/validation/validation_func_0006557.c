showType(const Value & v)
{
    switch (v.type) {
        case tInt: return "an integer";
        case tBool: return "a boolean";
        case tString: return "a string";
        case tPath: return "a path";
        case tNull: return "null";
        case tAttrs: return "an attribute set";
        case tList: return "a list";
        case tThunk: return "a thunk";
        case tApp: return "a function application";
        case tLambda: return "a function";
        case tCopy: return "a copy";
        case tBlackhole: return "a black hole";
        case tPrimOp: return "a built-in function";
        case tPrimOpApp: return "a partially applied built-in function";
    }
    abort();
}
