sort(stmt_ty *that)
{
    stmt_compound_ty *this;
    size_t          j;

    trace(("compound::sort()\n{\n"));
    this = (stmt_compound_ty *)that;


    for (j = 0; j < this->nlines; ++j)
        stmt_sort(this->line[j]);


    j = 0;
    while (j < this->nlines)
    {
        stmt_ty         *sp;
        size_t          k;
        size_t          m;


        sp = this->line[j];
        if (!sp->mdef.nstrings)
        {
            ++j;
            continue;
        }


        for (k = 0; k < j && !intersect(&this->line[k]->ref, &sp->mdef); ++k)
            ;
        if (k >= j)
        {
            ++j;
            continue;
        }


        for (m = j; m > k; --m)
            this->line[m] = this->line[m - 1];
        this->line[k] = sp;
        j = 0;


    }
    trace(("}\n"));
}
