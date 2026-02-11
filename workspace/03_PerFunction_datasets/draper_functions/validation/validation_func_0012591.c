deleteRegFileContents(VolInfo* volInfo, BkFile* file)
{
    if( file->onImage )
        free( file->pathAndName );


    if(volInfo->bootMediaType != BOOT_MEDIA_NONE &&
       volInfo->bootMediaType == BOOT_MEDIA_NO_EMULATION)
    {
        if(volInfo->bootRecordIsVisible &&
           volInfo->bootRecordOnImage == file)
        {


            bk_delete_boot_record(volInfo);
        }
    }
}
