callback(json_type type, json_pull *jp, void *state) {
	int *level = state;

	if (type == JSON_ARRAY) {
		printf("[\n");
		(*level)++;
		indent(*level);
	} else if (type == JSON_HASH) {
		printf("{\n");
		(*level)++;
		indent(*level);
	} else if (type == JSON_COMMA) {
		printf(",\n");
		indent(*level);
	} else if (type == JSON_COLON) {
		printf(" : ");
	}
}
