check_opt_strings(
    char_u	*val,
    char	**values,
    int		list)
{
    return opt_strings_flags(val, values, NULL, list);
}
