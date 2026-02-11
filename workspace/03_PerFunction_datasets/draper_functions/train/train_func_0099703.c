giraffe_table_save(GiTable *self, const cxchar *filename)
{

    if (filename == NULL) {
        return 1;
    }

    if (self) {

        cxint code;

        cpl_table *table = giraffe_table_get(self);
        cpl_propertylist *plist = giraffe_table_get_properties(self);


        if (cpl_propertylist_is_empty(plist)) {
            plist = NULL;
        }

        plist = cpl_propertylist_duplicate(plist);


        cpl_propertylist_erase_regexp(plist, "^CRPIX[0-9]$", 0);
        cpl_propertylist_erase_regexp(plist, "^CRVAL[0-9]$", 0);
        cpl_propertylist_erase_regexp(plist, "^CDELT[0-9]$", 0);
        cpl_propertylist_erase_regexp(plist, "^CTYPE[0-9]$", 0);


        code = cpl_table_save(table, plist, plist, filename, CPL_IO_CREATE);

        if (code != CPL_ERROR_NONE) {
            cpl_propertylist_delete(plist);
            plist = NULL;

            return 1;
        }

        cpl_propertylist_delete(plist);
        plist = NULL;

    }

    return 0;

}
