PyFFFont_randomText(PyObject *self, PyObject *args) {
    FontViewBase *fv = ((PyFF_Font *) self)->fv;
    char *script=NULL, *lang=NULL, *txt;
    uint32 stag, ltag=0;
    PyObject *ret;

    if ( !PyArg_ParseTuple(args,"s|s",&script, &lang ))
return( NULL );
    stag = StrToTag(script,NULL);
    if ( lang!=NULL ) {
	ltag = StrToTag(lang,NULL);
	txt = RandomParaFromScriptLang(stag,ltag,fv->sf,NULL);
    } else
	txt = RandomParaFromScript(stag,&ltag,fv->sf);
    ret = Py_BuildValue("s",txt);
    free(txt);
return( ret );
}
