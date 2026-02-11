show_ifd (ExifContent *content)
{
        ExifEntry *e;
        unsigned int i;

        for (i = 0; i < content->count; i++) {
                e = content->entries[i];
                printf ("%-20.20s", exif_tag_get_name (e->tag));
                printf ("|");
#ifdef HAVE_LIBEXIF_LOG
		{char b[1024];
		printf ("%-59.59s", exif_entry_get_value (e, b, sizeof (b)));
		}
#else
                printf ("%-59.59s", exif_entry_get_value (e));
#endif
                printf ("\n");
        }
}
