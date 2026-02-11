wi_mutable_string_delete_characters_to_index(wi_mutable_string_t *string, wi_uinteger_t index) {
	WI_RUNTIME_ASSERT_MUTABLE(string);

	wi_mutable_string_delete_characters_in_range(string, wi_make_range(0, index));
}
