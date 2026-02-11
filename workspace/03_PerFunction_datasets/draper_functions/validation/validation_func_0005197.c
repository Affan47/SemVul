G3d_keyGetString(struct Key_Value *keys, const char *key, char **returnStr)
{
    char *str;

    if ((str = G_find_key_value(key, keys)) == NULL) {
	G3d_error("G3d_keyGetString: cannot find field %s in key structure",
		  key);
	return 0;
    }

    G_strip(str);
    *returnStr = G_store(str);
    return 1;
}
