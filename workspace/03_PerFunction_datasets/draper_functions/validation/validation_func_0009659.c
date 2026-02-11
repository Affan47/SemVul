pconf_file_template_free(void *that)
{
    pconf_file_template_ty *this_thing;

    this_thing = (pconf_file_template_ty *)that;
    if (!this_thing)
	return;
    this_thing->reference_count--;
    assert(this_thing->reference_count >= 0);
    if (this_thing->reference_count > 0)
	return;
    trace(("pconf_file_template_free(this_thing = %08lX)\n{\n", (long)this_thing));
    if (this_thing->errpos)
    {
	str_free(this_thing->errpos);
	this_thing->errpos = 0;
    }
    pconf_file_template_pattern_list_free(this_thing->pattern);
    str_free(this_thing->body);
    str_free(this_thing->body_command);
    mem_free(this_thing);
    trace(("}\n"));
}
