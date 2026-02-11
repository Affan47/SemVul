is_array_func (pIIR_FunctionDeclaration f, pVAUL_NamedAssocElem a)
{
    return f->return_type && f->return_type->is(IR_ARRAY_TYPE)
	&& f->interface_declarations == NULL && a != NULL;
}
