lk_playlist_fid_read(uint32_t fid)
{
    playlist *pl;

    if (fid==0) return NULL;

    pl=malloc(sizeof(playlist));
    if(pl){
        pl->fid=fid;
        if(lk_properties_get_property(pl->fid, "playlist")){
            pl->length=lk_playlist_unescape(
                lk_properties_get_property(pl->fid, "playlist"),
                &pl->playlist);
        }else{
            free(pl);
            pl=lk_playlist_create(lk_properties_get_property(fid, "title"));
            pl->fid=fid;
        }
        pl->name=strdup(lk_properties_get_property(fid, "title"));
        return pl;
    }else return NULL;
}
