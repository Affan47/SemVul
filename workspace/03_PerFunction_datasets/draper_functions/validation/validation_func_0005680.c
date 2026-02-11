fixLitText(t)
Text t; {
    String   s = textToStr(t);
    char     p[MAX_FIXLIT];
    Int      i;
    for(i = 0;i < MAX_FIXLIT-2 && *s;s++) {
      p[i++] = *s;
      if (*s == '\\') {
	p[i++] = '\\';
      }
    }
    if (i < MAX_FIXLIT-2) {
      p[i] = 0;
    } else {
	ERRMSG(0) "storage space exhausted for internal literal string"
	EEND;
    }
    return (findText(p));
}
