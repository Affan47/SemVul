gmlc_mysql_query_next_record(GmlcMysqlQuery * pGmlcMysqlQry) {
	GArray * arRecordValue = NULL;
	GError * oErr = NULL;
	MYSQL_ROW pCurrRow;
	gchar * pcConverted = NULL;
	gulong * arlSizes = NULL;
	gsize szConverted = 0;
	int i = 0;

	g_return_val_if_fail(pGmlcMysqlQry != NULL, FALSE);

	if (pGmlcMysqlQry->pMysqlResult == NULL) {
		if (pGmlcMysqlQry->bNoRecord) {
			gmlc_mysql_query_read_error(pGmlcMysqlQry, TRUE);
			return NULL;
		}

		pGmlcMysqlQry->pMysqlResult = mysql_use_result(pGmlcMysqlQry->pMysqlLink);

		if (pGmlcMysqlQry->pMysqlResult == NULL) {
			gmlc_mysql_query_read_error(pGmlcMysqlQry, FALSE);
			g_printerr("gmlc_mysql_query_next_record - mysql_use_result - Failed\nQuery : '%s'\nError: (%d) %s\n", pGmlcMysqlQry->pcQuery, pGmlcMysqlQry->iErrCode, pGmlcMysqlQry->pcErrMsg);
			return NULL;
		}

		pGmlcMysqlQry->pMysqlHeaders = mysql_fetch_fields(pGmlcMysqlQry->pMysqlResult);
		if (pGmlcMysqlQry->pMysqlHeaders == NULL) {
			gmlc_mysql_query_read_error(pGmlcMysqlQry, FALSE);
			g_printerr("gmlc_mysql_query_execute - mysql_fetch_fields - Failed to query : '%s'\nError: (%d) %s\n", pGmlcMysqlQry->pcQuery, pGmlcMysqlQry->iErrCode, pGmlcMysqlQry->pcErrMsg);
		}

		pGmlcMysqlQry->bNoRecord = FALSE;
	}

	pCurrRow = mysql_fetch_row(pGmlcMysqlQry->pMysqlResult);
	if (pCurrRow == NULL) {
		gmlc_mysql_query_read_error(pGmlcMysqlQry, FALSE);
		if (pGmlcMysqlQry->iErrCode != 0) {
			g_printerr("gmlc_mysql_query_next_record - mysql_fetch_row - Failed\nQuery : '%s'\nError: (%d) %s\n", pGmlcMysqlQry->pcQuery, pGmlcMysqlQry->iErrCode, pGmlcMysqlQry->pcErrMsg);
		}
		return NULL;
	}

	arlSizes = mysql_fetch_lengths(pGmlcMysqlQry->pMysqlResult);
	if (pCurrRow == NULL) {
		gmlc_mysql_query_read_error(pGmlcMysqlQry, FALSE);
		g_printerr("gmlc_mysql_query_next_record - mysql_fetch_lengths - Failed\nQuery : '%s'\nError: (%d) %s\n", pGmlcMysqlQry->pcQuery, pGmlcMysqlQry->iErrCode, pGmlcMysqlQry->pcErrMsg);
		return NULL;
	}

	arRecordValue = g_array_sized_new (FALSE, TRUE, sizeof (gchar *), pGmlcMysqlQry->iNbField);

	for(i = 0; i < pGmlcMysqlQry->iNbField; i++) {
		if (pCurrRow[i] != NULL) {
			pcConverted = NULL;
			if (pGmlcMysqlQry->pcSrvCharset != NULL && pGmlcMysqlQry->pMysqlHeaders[i].charsetnr != 63) {
				pcConverted = g_convert(pCurrRow[i], arlSizes[i], "utf8", pGmlcMysqlQry->pcSrvCharset, NULL, &szConverted, &oErr);
				g_print("Convert (%d - %s -> utf8) : '%s' -> '%s'\n", pGmlcMysqlQry->pMysqlHeaders[i].charsetnr, pGmlcMysqlQry->pcSrvCharset, pCurrRow[i], pcConverted);
				if (pcConverted == NULL) {
					pcConverted = g_strdup("Binary BLOB");
				}
			} else {
				pcConverted = g_strndup(pCurrRow[i], arlSizes[i]);
				g_print("NO Convert (%d) : '%s' -> '%s'\n", pGmlcMysqlQry->pMysqlHeaders[i].charsetnr, pCurrRow[i], pcConverted);
			}

		} else {
			pcConverted = g_strdup("NULL");
		}

		g_array_append_val (arRecordValue, pcConverted);
	}

	return arRecordValue;
}
