stringalloc(size)
unsigned int size;
{
    if(Stringpool - size <= (char *)(Symbol + symBot))
        faterr(err_memory);
    Stringpool -= size;
    return(Stringpool);
}
