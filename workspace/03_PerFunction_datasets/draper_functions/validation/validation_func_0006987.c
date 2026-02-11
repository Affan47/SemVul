isscalar(const SymbolKeyType& id) const
{
    Object::PtrType pobj;
    if (imp->getobjectforget(id, imp->symbols, pobj))
        return false;
    return pobj->gettype() == Object::type_scalar;
}
