apetag_read (apetag *mem_cnt, char *filename,int flag)
{
    FILE *fp;

    if (mem_cnt==NULL) {
        PRINT_ERR(">apetaglib>READ>FATAL>apetag_init()\n");
        return ATL_NOINIT;
    }

    fp = fopen (filename, "rb");
    if (fp == NULL)
        return ATL_FOPEN;

    apetag_read_fp (mem_cnt, fp, filename,flag);

    fclose (fp);

    return 0;
}
