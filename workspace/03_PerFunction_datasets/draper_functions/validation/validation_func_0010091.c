set_attribute(const std::string &name, const std::string &value)
{
	if (impl)
	{
		for(int i = 0; i < (int)impl->attributes.get_length(); ++i)
			if (impl->attributes.item(i).to_attr().get_name() == name)
			{
				impl->attributes.item(i).to_attr().set_value(value);
				return;
			}

		CL_DomAttr attr(get_owner_document(), name);
		impl->attributes.set_named_item(attr);
		attr.impl->node_value = value;
	}
}
