void php_filter_url(PHP_INPUT_FILTER_PARAM_DECL)
{


	const unsigned char allowed_list[] = LOWALPHA HIALPHA DIGIT SAFE EXTRA NATIONAL PUNCTUATION RESERVED;
	filter_map     map;

	filter_map_init(&map);
	filter_map_update(&map, 1, allowed_list);
	filter_map_apply(value, &map);
}
