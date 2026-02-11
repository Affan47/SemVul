phone_number_from_string (const gchar *normal,
                          const gchar *default_region)
{
	EPhoneNumber *number = NULL;


	if (normal && e_phone_number_is_supported ())
		number = e_phone_number_from_string (normal, default_region, NULL);

	return number;
}
