cx_fabric_find_arg_type(cx_fabric_arg_t * arg_type_list, char *arg)
{
	int i, ip0, ip1, ip2, ip3;
	int mac0, mac1, mac2, mac3, mac4, mac5;
	int ls0, ls1;
	int val;
	int ret;

	errno = 0;


	i = 0;
	while (arg_type_list[i].keyword != NULL) {
		if ((strlen(arg) == strlen(arg_type_list[i].keyword)) &&
		    !strncasecmp(arg, arg_type_list[i].keyword,
				 strlen(arg_type_list[i].keyword))) {
			return arg_type_list[i].arg_type;
		}
		i++;
	}


	if ((sscanf(arg, "%02x:%02x:%02x:%02x:%02x:%02x",
		    &mac0, &mac1, &mac2, &mac3, &mac4, &mac5)) == 6) {
		return Cx_Fabric_Arg_Value_MAC_Address;
	}

	if ((sscanf(arg, "%d.%d.%d.%d", &ip0, &ip1, &ip2, &ip3)) == 4) {
		return Cx_Fabric_Arg_Value_IPV4_Address;
	}

	if ((sscanf(arg, "%d.%d", &ls0, &ls1)) == 2) {
		return Cx_Fabric_Arg_Value_Scalar;
	}


	if (isalpha(arg[0])) {

		return Cx_Fabric_Arg_Value_String;
	}

	val = strtol(arg, NULL, 10);
	if (errno == 0) {
		return Cx_Fabric_Arg_Value_Scalar;
	}

	return Cx_Fabric_Arg_Invalid;
}
