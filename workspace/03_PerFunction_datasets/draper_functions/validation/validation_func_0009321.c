sprep(void)
{
    char *p1,*p2,*s;
    int i,l,thislang;

    modcnt=0;
    s=getenv("slist"); if(s==NULL) return;
    l=strlen(s); if(l<0 || l>100*MAX_LINELEN) return;
    mlist=xmalloc(l+16); ovlstrcpy(mlist,s);
    for(p1=find_word_start(mlist); *p1 && modcnt<MAX_MODULES; p1=find_word_start(p2)) {
    p2=find_word_end(p1);
    l=p2-p1; if(*p2) *p2++=0;
    for(i=0;i<langcnt;i++) if(strncasecmp(lang[i],p1,2)==0) break;
    if(i<langcnt) thislang=i; else continue;
    mod[modcnt].name=p1;
    mod[modcnt].langs[0]=thislang;
    mod[modcnt].langcnt=1;
    modcnt++;
    }
}
