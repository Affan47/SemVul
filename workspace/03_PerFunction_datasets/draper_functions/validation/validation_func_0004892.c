print_minolta_makervalue(struct ifd_entry *entry_ptr,int make, int model,
                                                            char *prefix)
{
    int noteversion = 0;

    noteversion = getnoteversion();

    if(entry_ptr && (PRINT_VALUE))
    {
        switch(noteversion)
        {
            case 1:
                print_minolta1_makervalue(entry_ptr,make,model,prefix);
                minolta1_interpret_value(entry_ptr,model);
                break;
            default:
                print_value(entry_ptr,PREFIX);
                break;
        }
    }
}
