get_element(Value& aself, const String& aname) {

	if(Property* prop=ffields.get(aname)) {
		if(prop->getter)
			return new VJunction(aself, prop->getter, true );

		if(prop->setter){
			if(Value *result=get_default_getter(aself, aname))
				return result;
			throw Exception(PARSER_RUNTIME,	0, "this property has no getter method (@GET_%s[])", aname.cstr());
		}


		return prop->value;
	}


	if(Value* result=VStateless_class::get_element(aself, aname))
		return result;


	return get_default_getter(aself, aname);
}
