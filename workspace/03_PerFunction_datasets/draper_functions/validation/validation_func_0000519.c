handle_features_command(String *args, int offset)
{
    struct feature *f;

    if (args->len > offset) {
	for (f = features; f->name; f++) {
	    if (cstrcmp(f->name, args->data + offset) == 0)
		return *f->flag ? shareval(val_one) : shareval(val_zero);
	}
	return shareval(val_zero);
    } else {
	oputline(CS(featurestr));
	return shareval(val_one);
    }
}
