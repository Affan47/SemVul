deleteAttribute(int i)
{
    if ((!d)||(i<0)||(i>=d->nAttribute)) return;
    d->nAttribute--;
    XMLAttribute *p=d->pAttribute+i;
    free((void*)p->lpszName);
    if (p->lpszValue) free((void*)p->lpszValue);
    if (d->nAttribute) memmove(p,p+1,(d->nAttribute-i)*sizeof(XMLAttribute)); else { free(p); d->pAttribute=NULL; }
}
