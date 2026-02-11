decode_json_object(json_string *injson){

	if(injson == NULL || injson->offset == NULL) return NULL;

	json_value *out = apr_palloc(injson->mpool,sizeof(json_value));
	out->value.object = apr_hash_make(injson->mpool);
	out->type = JSON_OBJECT;

	injson->offset++;
	while(isspace(*injson->offset)) injson->offset++;

	if(*(injson->offset) == '}') {
		injson->offset++;
		return out;
	}


	while(isspace(*injson->offset)) injson->offset++;
	if(*(injson->offset) != '"') return NULL;
	json_value *name = decode_json_string(injson);
	if(name == NULL) return NULL;
	while(isspace(*injson->offset)) injson->offset++;
	if(*(injson->offset) != ':') return NULL;
	injson->offset++;
	while(isspace(*injson->offset)) injson->offset++;
	json_value *value = decode_json_value(injson);
	if(value == NULL) return NULL;
	apr_hash_set(out->value.object,name->value.string,APR_HASH_KEY_STRING,value);

	while(*(injson->offset) != '\0' && *(injson->offset) != '}') {
		while(isspace(*injson->offset)) injson->offset++;
		if(*(injson->offset) == '}')  {
			goto object_closure;
		} else if (*(injson->offset) == ',') {
			injson->offset++;
			while(isspace(*injson->offset)) injson->offset++;
			if(*(injson->offset) != '"') return NULL;
			json_value *name = decode_json_string(injson);
			if(name == NULL) return NULL;
			while(isspace(*injson->offset)) injson->offset++;
			if(*(injson->offset) != ':') return NULL;
			injson->offset++;
			while(isspace(*injson->offset)) injson->offset++;
			json_value *value = decode_json_value(injson);
			if(value == NULL) return NULL;
			apr_hash_set(out->value.object,name->value.string,APR_HASH_KEY_STRING,value);
		} else {
			return NULL;
		}
	}
object_closure:
		if(*(injson->offset) !='}') return NULL;
		injson->offset++;
	return out;
}
