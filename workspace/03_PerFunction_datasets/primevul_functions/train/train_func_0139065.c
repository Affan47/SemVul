base160next_sql(sqlite3_context * hContext,
                int argc,
                sqlite3_value ** argv)
{
        int                         i;
        int                         len;
        char *             pTab;
        char *             pBase160 = strdup((const char *)sqlite3_value_text(argv[0]));
        char *             pStart = pBase160;


        if (pBase160 != NULL &&
            (len = strlen(pBase160)) >= 4 &&
            len % 4 == 0) {

                if (pBase160 == NULL) {

                        sqlite3_result_null(hContext);
                        return;
                }

                pBase160 += strlen(pBase160) - 1;


                for (i = 0; i < 4; i++) {


                        pTab = strchr(base160tab, *pBase160);


                        if (pTab < base160tab + sizeof(base160tab) - 1) {


                                *pBase160 = *++pTab;
                                break;
                        } else {


                                *pBase160-- = base160tab[0];
                        }
                }

                sqlite3_result_text(hContext,
                                    pStart,
                                    strlen(pStart),
                                    free);
        } else {
                sqlite3_result_value(hContext, argv[0]);
                if (pBase160 != NULL) {
                        free(pBase160);
                }
        }
}
