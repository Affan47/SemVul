filename()
    const
{
    trace(("output_to_wide::filename(this = %08lX)\n{\n", (long)this));
    nstring result = deeper->filename();
    trace(("return \"%s\";\n", result.c_str()));
    trace(("}\n"));
    return result;
}
