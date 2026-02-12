extractDirNameStatic(const StaticString &path) {
	if (path.empty()) {
		return StaticString(".", 1);
	}

	const char *data = path.data();
	const char *end = path.data() + path.size();


	while (end > data && end[-1] == '/') {
		end--;
	}
	if (end == data) {

		return StaticString("/", 1);
	}


	end--;
	while (end > data && *end != '/') {
		end--;
	}
	if (end == data) {
		if (*data == '/') {

			return StaticString("/", 1);
		} else {

			return StaticString(".", 1);
		}
	} else {


		while (end >= data && *end == '/') {
			end--;
		}
		if (end < data) {

			return StaticString("/", 1);
		} else {
			return StaticString(data, end - data + 1);
		}
	}
}
