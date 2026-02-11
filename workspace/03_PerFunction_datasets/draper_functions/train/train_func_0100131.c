sfxhash_gfindfirst( SFXHASH * t )
{
    if(t)
    {
        if (t->ghead) t->gnode = t->ghead->gnext;
        else t->gnode = NULL;
        return t->ghead;
    }
    return NULL;
}
