make_anon_element(const Lexeme &what, const char *decl_pos2,
			  ElementClassT *type, const String &conf)
{
    return make_element(anon_element_name(type->name()), what, decl_pos2, type, conf);
}
