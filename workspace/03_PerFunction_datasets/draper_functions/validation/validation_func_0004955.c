act123()
{
		NLA = 55;

    if ( !(strcmp(zzbegexpr, "#ifdef")==0 ||
    strcmp(zzbegexpr, "#if")==0 ||
    strcmp(zzbegexpr, "#else")==0 ||
    strcmp(zzbegexpr, "#endif")==0 ||
    strcmp(zzbegexpr, "#ifndef")==0 ||
    strcmp(zzbegexpr, "#define")==0 ||
    strcmp(zzbegexpr, "#pragma")==0 ||
    strcmp(zzbegexpr, "#undef")==0 ||
    strcmp(zzbegexpr, "#import")==0 ||
    strcmp(zzbegexpr, "#line")==0 ||
    strcmp(zzbegexpr, "#include")==0 ||
    strcmp(zzbegexpr, "#error")==0) )
    {
      static char buf[100];
      sprintf(buf, "%s_ast", zzbegexpr+1);
      						list_add(&CurAstLabelsInActions, mystrdup(zzbegexpr+1));
      zzreplstr(buf);
      chkGTFlag();
    }
    zzmore();
	}
