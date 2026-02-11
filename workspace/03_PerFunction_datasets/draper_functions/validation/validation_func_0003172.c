FindGradient(const std::string& widgettype, const std::string& objectname, const std::string& name) {
	THEME_OBJECT* object = FindObject(widgettype, objectname);

	if(object == NULL) {
		return NULL;
	}

	return object->FindGradient(name);
}
