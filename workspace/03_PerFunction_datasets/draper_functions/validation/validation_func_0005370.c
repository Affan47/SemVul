add_delta_def(Type1Font *output, int dict, PermString name, const Cff::Font *font, Cff::DictOperator op)
{
    Vector<double> vec;
    if (font->dict_value(op, vec)) {
	for (int i = 1; i < vec.size(); i++)
	    vec[i] += vec[i - 1];
	StringAccum sa;
	for (int i = 0; i < vec.size(); i++)
	    sa << (i ? ' ' : '[') << vec[i];
	sa << ']';
	output->add_definition(dict, Type1Definition::make_literal(name, sa.take_string(), (dict == Type1Font::dP ? "|-" : "readonly def")));
    }
}
