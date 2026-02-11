print_canon_makervalue(struct ifd_entry *entry_ptr,int make, int model,
                    char *prefix)
{
    int noteversion = 0;

    noteversion = getnoteversion();

    if(entry_ptr && (PRINT_VALUE))
    {
        switch(noteversion)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                print_canon1_makervalue(entry_ptr,make,model,prefix);
                canon1_interpret_value(entry_ptr);
                break;
            default:
                print_value(entry_ptr,PREFIX);
                break;
        }
    }
}
