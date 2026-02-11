checkScalar()
{
    if (!type->isscalar() && type->toBasetype() != Type::terror)
        error("'%s' is not a scalar, it is a %s", toChars(), type->toChars());
    rvalue();
}
