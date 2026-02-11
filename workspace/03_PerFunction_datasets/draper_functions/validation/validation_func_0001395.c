mime_type_of(const String* file_name) {
	return mime_type_of(file_name?file_name->taint_cstr(String::L_FILE_SPEC):0);
}
