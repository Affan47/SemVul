imagetype (usershape_t *us)
{
    char header[HDRLEN];
    char line[200];
    int i;

    if (us->f && fread(header, 1, HDRLEN, us->f) == HDRLEN) {
        for (i = 0; i < sizeof(knowntypes) / sizeof(knowntype_t); i++) {
	    if (!memcmp (header, knowntypes[i].template, knowntypes[i].size)) {
	        us->stringtype = knowntypes[i].stringtype;
		us->type = knowntypes[i].type;
		if (us->type == FT_XML) {

		    while (fgets(line, sizeof(line), us->f) != NULL) {
		        if (!memcmp(line, SVG_MAGIC, sizeof(SVG_MAGIC)-1)) {
    			    us->stringtype = "svg";
			    return (us->type = FT_SVG);
		        }
		    }
		}
	    	else if (us->type == FT_RIFF) {

		    if (!memcmp(header+8, WEBP_MAGIC, sizeof(WEBP_MAGIC)-1)) {
    			us->stringtype = "webp";
			return (us->type = FT_WEBP);
		    }
		}
		return us->type;
	    }
        }
    }

    us->stringtype = "(lib)";
    us->type = FT_NULL;

    return FT_NULL;
}
