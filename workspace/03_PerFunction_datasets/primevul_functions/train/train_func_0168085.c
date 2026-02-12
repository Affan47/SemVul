extract_group_icon_cursor_resource(WinLibrary *fi, WinResource *wr, char *lang,
                                   int *ressize, bool is_icon)
{
	Win32CursorIconDir *icondir;
	Win32CursorIconFileDir *fileicondir;
	char *memory;
	int c, size, offset, skipped;


	icondir = (Win32CursorIconDir *) get_resource_entry(fi, wr, &size);
	if (icondir == NULL) {

		return NULL;
	}


	RETURN_IF_BAD_POINTER(NULL, icondir->count);
	skipped = 0;
	for (c = 0 ; c < icondir->count ; c++) {
		int level;
	    	int iconsize;
		char name[14];
		WinResource *fwr;

		RETURN_IF_BAD_POINTER(NULL, icondir->entries[c]);


		snprintf(name, sizeof(name)/sizeof(char), "-%d", icondir->entries[c].res_id);
		fwr = find_resource(fi, (is_icon ? "-3" : "-1"), name, lang, &level);
		if (fwr == NULL) {
			warn(_("%s: could not find `%s' in `%s' resource."),
			 	fi->name, &name[1], (is_icon ? "group_icon" : "group_cursor"));
			return NULL;
		}

		if (get_resource_entry(fi, fwr, &iconsize) != NULL) {
		    if (iconsize == 0) {
			warn(_("%s: icon resource `%s' is empty, skipping"), fi->name, name);
			skipped++;
			continue;
		    }
		    if (iconsize != icondir->entries[c].bytes_in_res) {
			warn(_("%s: mismatch of size in icon resource `%s' and group (%d vs %d)"), fi->name, name, iconsize, icondir->entries[c].bytes_in_res);
		    }
		    size += iconsize < icondir->entries[c].bytes_in_res ? icondir->entries[c].bytes_in_res : iconsize;


		    if (!is_icon)
			size -= sizeof(uint16_t)*2;
		}
	}
	offset = sizeof(Win32CursorIconFileDir) + (icondir->count-skipped) * sizeof(Win32CursorIconFileDirEntry);
	size += offset;
	*ressize = size;


	memory = xmalloc(size);
	fileicondir = (Win32CursorIconFileDir *) memory;


	fileicondir->reserved = icondir->reserved;
	fileicondir->type = icondir->type;
	fileicondir->count = icondir->count - skipped;


	skipped = 0;
	for (c = 0 ; c < icondir->count ; c++) {
		int level;
		char name[14];
		WinResource *fwr;
		char *data;


		snprintf(name, sizeof(name)/sizeof(char), "-%d", icondir->entries[c].res_id);
		fwr = find_resource(fi, (is_icon ? "-3" : "-1"), name, lang, &level);
		if (fwr == NULL) {
			warn(_("%s: could not find `%s' in `%s' resource."),
			 	fi->name, &name[1], (is_icon ? "group_icon" : "group_cursor"));
			return NULL;
		}


		data = get_resource_entry(fi, fwr, &size);
		if (data == NULL) {

			return NULL;
		}
    	    	if (size == 0) {
		    skipped++;
		    continue;
		}


		memcpy(&fileicondir->entries[c-skipped], &icondir->entries[c],
			sizeof(Win32CursorIconFileDirEntry)-sizeof(uint32_t));


		if (!is_icon) {
			fileicondir->entries[c-skipped].width = icondir->entries[c].res_info.cursor.width;
			fileicondir->entries[c-skipped].height = icondir->entries[c].res_info.cursor.height / 2;
			fileicondir->entries[c-skipped].color_count = 0;
			fileicondir->entries[c-skipped].reserved = 0;
		}


		fileicondir->entries[c-skipped].dib_offset = offset;


		if (size > icondir->entries[c-skipped].bytes_in_res)
			size = icondir->entries[c-skipped].bytes_in_res;
		if (is_icon) {
			memcpy(&memory[offset], data, size);
		} else if (size >= sizeof(uint16_t)*2) {
			fileicondir->entries[c-skipped].hotspot_x = ((uint16_t *) data)[0];
			fileicondir->entries[c-skipped].hotspot_y = ((uint16_t *) data)[1];
			memcpy(&memory[offset], data+sizeof(uint16_t)*2,
				   size-sizeof(uint16_t)*2);
			offset -= sizeof(uint16_t)*2;
		}


		offset += icondir->entries[c].bytes_in_res;
	}

	return (void *) memory;
}
