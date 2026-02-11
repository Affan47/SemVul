equal(ExecState *exec, JSValue *v1, JSValue *v2)
{
    JSType t1 = v1->type();
    JSType t2 = v2->type();

    if (t1 != t2) {
        if (t1 == UndefinedType)
            t1 = NullType;
        if (t2 == UndefinedType)
            t2 = NullType;

        if (t1 == BooleanType)
            t1 = NumberType;
        if (t2 == BooleanType)
            t2 = NumberType;

        if (t1 == NumberType && t2 == StringType) {

        } else if (t1 == StringType && t2 == NumberType)
            t1 = NumberType;

        else {
            if ((t1 == StringType || t1 == NumberType) && t2 >= ObjectType)
                return equal(exec, v1, v2->toPrimitive(exec));
            if (t1 == NullType && t2 == ObjectType)
                return static_cast<JSObject *>(v2)->masqueradeAsUndefined();
            if (t1 >= ObjectType && (t2 == StringType || t2 == NumberType))
                return equal(exec, v1->toPrimitive(exec), v2);
            if (t1 == ObjectType && t2 == NullType)
                return static_cast<JSObject *>(v1)->masqueradeAsUndefined();
            if (t1 != t2)
                return false;
        }
    }

    if (t1 == UndefinedType || t1 == NullType)
        return true;

    if (t1 == NumberType) {
        double d1 = v1->toNumber(exec);
        double d2 = v2->toNumber(exec);
        return d1 == d2;
    }

    if (t1 == StringType)
        return v1->toString(exec) == v2->toString(exec);

    if (t1 == BooleanType)
        return v1->toBoolean(exec) == v2->toBoolean(exec);


    return v1 == v2;
}
