xml_free_album_browse(struct album_browse* album)
{
    struct album_browse* next_album = album;
    for (struct album_browse* a = next_album; next_album; a = next_album) {
        xml_free_track(a->tracks);
        next_album = a->next;
        free(a);
    }
}
