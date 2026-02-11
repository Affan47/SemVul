ET_Remove_File_From_Artist_Album_List (ET_File *ETFile)
{
    GList *ArtistList;
    GList *AlbumList;
    GList *etfilelist;
    ET_File *etfile;


    ArtistList = ETCore->ETArtistAlbumFileList;
    while (ArtistList && ETFile)
    {
        AlbumList = g_list_first((GList *)ArtistList->data);
        while (AlbumList)
        {
            etfilelist = g_list_first((GList *)AlbumList->data);
            while (etfilelist)
            {
                etfile = (ET_File *)etfilelist->data;
                if (ETFile == etfile)
                {
                    etfilelist = g_list_remove(etfilelist,ETFile);
                    if (etfilelist)
                    {
                        AlbumList->data = (gpointer) g_list_first(etfilelist);
                    }else
                    {
                        AlbumList = g_list_remove(AlbumList,AlbumList->data);
                        if (AlbumList)
                        {
                            ArtistList->data = (gpointer) g_list_first(AlbumList);
                        }else
                        {
                            ETCore->ETArtistAlbumFileList = g_list_remove(ArtistList,ArtistList->data);
                            if (ETCore->ETArtistAlbumFileList)
                                ETCore->ETArtistAlbumFileList = g_list_first(ETCore->ETArtistAlbumFileList);
                            return TRUE;
                        }
                        return TRUE;
                    }
                    return TRUE;
                }
                etfilelist = etfilelist->next;
            }
            AlbumList = AlbumList->next;
        }
        ArtistList = ArtistList->next;
    }
    return FALSE;
}
