int RemoveSectionType(int SectionType)
{
    int a;
    int retval = FALSE;
    for (a=0;a<SectionsRead-1;a++){
        if (Sections[a].Type == SectionType){

            free (Sections[a].Data);

            memmove(Sections+a, Sections+a+1, sizeof(Section_t) * (SectionsRead-a));
            SectionsRead -= 1;
            a -= 1;
            retval = TRUE;
        }
    }
    return retval;
}
