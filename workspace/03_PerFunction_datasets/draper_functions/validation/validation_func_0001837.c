element(output::pointer ofp, const char *name, string_ty *value)
{
    element(ofp, name, nstring(value));
}
