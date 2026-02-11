ET_Remove_File_From_File_List (ET_File *ETFile)
{
    GList *ETFileList = NULL;
    GList *ETFileDisplayedList = NULL;


    ETCore->ETFileDisplayedList_TotalSize     -= ((ET_File_Info *)ETFile->ETFileInfo)->size;
    ETCore->ETFileDisplayedList_TotalDuration -= ((ET_File_Info *)ETFile->ETFileInfo)->duration;


    ETFileDisplayedList = g_list_find(g_list_first(ETCore->ETFileDisplayedList),ETFile);
    ETFileList          = g_list_find(g_list_first(ETCore->ETFileList),ETFile);


    if (ETCore->ETFileDisplayedList == ETFileDisplayedList)
    {
        if (ETFileList->next)
            ETCore->ETFileDisplayedList = ETFileDisplayedList->next;
        else if (ETFileList->prev)
            ETCore->ETFileDisplayedList = ETFileDisplayedList->prev;
        else
            ETCore->ETFileDisplayedList = NULL;
    }

    if (ETCore->ETFileDisplayed == ETFile)
    {
        if (ETCore->ETFileDisplayedList)
            ETCore->ETFileDisplayed = (ET_File *)ETCore->ETFileDisplayedList->data;
        else
            ETCore->ETFileDisplayed = (ET_File *)NULL;
    }


    ETCore->ETFileList = g_list_first(g_list_remove_link(g_list_first(ETCore->ETFileList),ETFileList));


    ET_Remove_File_From_Artist_Album_List(ETFile);


    if ( (ETFileDisplayedList = g_list_find(ETCore->ETFileDisplayedList,ETFile)) )
    {
        ETCore->ETFileDisplayedList = g_list_first(g_list_remove_link(g_list_first(ETCore->ETFileDisplayedList),ETFileDisplayedList));
    }


    ET_Free_File_List_Item(ETFile);
    if (ETFileList)
        g_list_free(ETFileList);
    if (ETFileDisplayedList)
        g_list_free(ETFileDisplayedList);


    ET_Displayed_File_List_Get_Length();


    ET_Displayed_File_List_Number();


    if (ETCore->ETFileDisplayedList)
    {
        if (ETCore->ETFileDisplayed)
        {
            ET_Displayed_File_List_By_Etfile(ETCore->ETFileDisplayed);
        }else if (ETCore->ETFileDisplayedList->data)
        {

            ET_Displayed_File_List_By_Etfile((ET_File *)ETCore->ETFileDisplayedList->data);
        }
    }else
    {

        Clear_File_Entry_Field();
        Clear_Header_Fields();
        Clear_Tag_Entry_Fields();
        gtk_label_set_text(GTK_LABEL(FileIndex),"0/0:");
        Update_Command_Buttons_Sensivity();
    }

    return TRUE;
}
