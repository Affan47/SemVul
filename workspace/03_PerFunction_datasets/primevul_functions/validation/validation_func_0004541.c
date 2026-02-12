Section_t * CreateSection(int SectionType, unsigned char * Data, int Size)
{
    Section_t * NewSection;
    int a;
    int NewIndex;

    NewIndex = 0;
    if (SectionType == M_EXIF){

    }else{
        for (;NewIndex < 3;NewIndex++){
            if (Sections[NewIndex].Type == M_JFIF) continue;
            if (Sections[NewIndex].Type == M_EXIF) continue;
            break;
        }
    }

    if (SectionsRead < NewIndex){
        ErrFatal("Too few sections!");
    }

    CheckSectionsAllocated();
    for (a=SectionsRead;a>NewIndex;a--){
        Sections[a] = Sections[a-1];
    }
    SectionsRead += 1;

    NewSection = Sections+NewIndex;

    NewSection->Type = SectionType;
    NewSection->Size = Size;
    NewSection->Data = Data;

    return NewSection;
}
