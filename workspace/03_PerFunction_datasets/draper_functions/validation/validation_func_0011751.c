setGivenEnvVars(const char *envvarsData) {
	string envvars = Base64::decode(envvarsData);
	const char *key = envvars.data();
	const char *end = envvars.data() + envvars.size();

	while (key < end) {
		const char *keyEnd = (const char *) memchr(key, '\0', end - key);
		if (keyEnd != NULL) {
			const char *value = keyEnd + 1;
			if (value < end) {
				const char *valueEnd = (const char *) memchr(value, '\0', end - value);
				if (valueEnd != NULL) {
					setenv(key, value, 1);
					key = valueEnd + 1;
				} else {
					break;
				}
			} else {
				break;
			}
		} else {
			break;
		}
	}
}
