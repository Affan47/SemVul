gen_key (const gchar *component,
         const gchar *part,
         DTFormatKind kind)
{
	const gchar *kind_str = NULL;

	g_return_val_if_fail (component != NULL, NULL);
	g_return_val_if_fail (*component != 0, NULL);

	switch (kind) {
	case DTFormatKindDate:
		kind_str = "Date";
		break;
	case DTFormatKindTime:
		kind_str = "Time";
		break;
	case DTFormatKindDateTime:
		kind_str = "DateTime";
		break;
	case DTFormatKindShortDate:
		kind_str = "ShortDate";
		break;
	}

	return g_strconcat (component, (part && *part) ? "-" : "", part && *part ? part : "", "-", kind_str, NULL);
}
