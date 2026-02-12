int ReadJpegFile(const char * FileName, ReadMode_t ReadMode)
{
    FILE * infile;
    int ret;

    infile = fopen(FileName, "rb");

    if (infile == NULL) {
        fprintf(stderr, "can't open '%s'\n", FileName);
        return FALSE;
    }


    ret = ReadJpegSections(infile, ReadMode);
    if (!ret){
        if (ReadMode == READ_ANY){


            ret = TRUE;
        }else{
            fprintf(stderr,"Not JPEG: %s\n",FileName);
        }
    }

    fclose(infile);

    if (ret == FALSE){
        DiscardData();
    }
    return ret;
}
