ateof(FILE *inptr)
{
    int atend = 0;
    if(feof(inptr))
        atend++;
    else if(fgetc(inptr) == -1)
        atend++;
    return(atend);
}
