gretl_xml_put_matrix (const gretl_matrix *m, const char *name,
			   FILE *fp)
{
    int i, j;

    if (m == NULL) {
	return;
    }

    if (name == NULL) {
	fprintf(fp, "<gretl-matrix rows=\"%d\" cols=\"%d\"\n",
		m->rows, m->cols);
    } else {
	fprintf(fp, "<gretl-matrix name=\"%s\" rows=\"%d\" cols=\"%d\"",
		name, m->rows, m->cols);
    }

    if (gretl_matrix_is_dated(m)) {
	int mt1 = gretl_matrix_get_t1(m);
	int mt2 = gretl_matrix_get_t2(m);

	fprintf(fp, " t1=\"%d\" t2=\"%d\"", mt1, mt2);
    }

    fputs(">\n", fp);

    for (i=0; i<m->rows; i++) {
	for (j=0; j<m->cols; j++) {
	    fprintf(fp, "%.15g ", gretl_matrix_get(m, i, j));
	}
	fputc('\n', fp);
    }

    fputs("</gretl-matrix>\n", fp);
}
