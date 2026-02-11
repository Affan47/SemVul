ET_Set_Displayed_File_List (GList *ETFileList)
{
    GList *l = NULL;

    ETCore->ETFileDisplayedList = g_list_first(ETFileList);


    ETCore->ETFileDisplayedList_Length = ET_Displayed_File_List_Get_Length();
    ETCore->ETFileDisplayedList_TotalSize     = 0;
    ETCore->ETFileDisplayedList_TotalDuration = 0;


    for (l = ETCore->ETFileDisplayedList; l != NULL; l = g_list_next (l))
    {
        ETCore->ETFileDisplayedList_TotalSize += ((ET_File_Info *)((ET_File *)l->data)->ETFileInfo)->size;
        ETCore->ETFileDisplayedList_TotalDuration += ((ET_File_Info *)((ET_File *)l->data)->ETFileInfo)->duration;
    }


    ET_Sort_Displayed_File_List(SORTING_FILE_MODE);


    ET_Displayed_File_List_Number();

    return TRUE;
}
