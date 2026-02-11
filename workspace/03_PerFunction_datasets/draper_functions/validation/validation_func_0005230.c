dichl_add(cdichl *d, u64 key1, u64 key2, char *str)
{
    cdichlitem *item, *lnew, *last;
    int len;

    if (d==NULL || !str)
    {   errprintf("invalid parameters\n");
        return -1;
    }
    len=strlen(str);


    lnew=malloc(sizeof(cdichlitem));
    if (!lnew)
    {   errprintf("malloc(%ld) failed: out of memory\n", (long)sizeof(cdichlitem));
        return -1;
    }
    memset(lnew, 0, sizeof(cdichlitem));
    lnew->str=malloc(len+1);
    if (!lnew->str)
    {
        free(lnew);
        errprintf("malloc(%ld) failed: out of memory\n", (long)len+1);
        return -1;
    }

    memcpy(lnew->str, str, len+1);
    lnew->key1=key1;
    lnew->key2=key2;
    lnew->next=NULL;


    if (d->head==NULL)
    {
        d->head=lnew;
    }
    else
    {
        for (item=d->head; item!=NULL; item=item->next)
        {
            last=item;
            if (item->key1==key1 && item->key2==key2)
            {   errprintf("dichl_add_internal(): item with key1=%ld and key2=%ld is already in dico\n", (long)item->key1, (long)item->key2);
                return -1;
            }
        }
        last->next=lnew;
    }

    return 0;
}
