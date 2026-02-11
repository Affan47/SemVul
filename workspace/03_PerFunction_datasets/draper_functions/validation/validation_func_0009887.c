set_isNull(fType type)
{
	is_null = true;
	field_type = type;
	str_value = "";
	if (type == ft_Blob)
		set_asBlob(NULL, 0);
}
