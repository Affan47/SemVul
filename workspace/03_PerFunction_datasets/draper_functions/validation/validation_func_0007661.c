deepCopy() const
{
    if (!d) return XMLNode::emptyXMLNode;
    XMLNode x(NULL,stringDup(d->lpszName),d->isDeclaration);
    XMLNodeData *p=x.d;
    int n=d->nAttribute;
    if (n)
    {
        p->nAttribute=n; p->pAttribute=OFreinterpret_cast(XMLAttribute*, malloc(n*sizeof(XMLAttribute)));
        while (n--)
        {
            p->pAttribute[n].lpszName=stringDup(d->pAttribute[n].lpszName);
            p->pAttribute[n].lpszValue=stringDup(d->pAttribute[n].lpszValue);
        }
    }
    if (d->pOrder)
    {
        n=OFstatic_cast(int, (d->nChild+d->nText+d->nClear)*sizeof(int)); p->pOrder=OFreinterpret_cast(int*, malloc(n)); memcpy(p->pOrder,d->pOrder,n);
    }
    n=d->nText;
    if (n)
    {
        p->nText=n; p->pText=OFreinterpret_cast(XMLCSTR*, malloc(n*sizeof(XMLCSTR)));
        while(n--) p->pText[n]=stringDup(d->pText[n]);
    }
    n=d->nClear;
    if (n)
    {
        p->nClear=n; p->pClear=OFreinterpret_cast(XMLClear*, malloc(n*sizeof(XMLClear)));
        while (n--)
        {
            p->pClear[n].lpszCloseTag=d->pClear[n].lpszCloseTag;
            p->pClear[n].lpszOpenTag=d->pClear[n].lpszOpenTag;
            p->pClear[n].lpszValue=stringDup(d->pClear[n].lpszValue);
        }
    }
    n=d->nChild;
    if (n)
    {
        p->nChild=n; p->pChild=OFreinterpret_cast(XMLNode*, malloc(n*sizeof(XMLNode)));
        while (n--)
        {
            p->pChild[n].d=NULL;
            p->pChild[n]=d->pChild[n].deepCopy();
            p->pChild[n].d->pParent=p;
        }
    }
    return x;
}
