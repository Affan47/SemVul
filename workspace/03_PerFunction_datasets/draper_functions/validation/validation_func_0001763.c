append_page_setup_section(dstr_t *str, int optset, int comments)
{

    if (comments) {
        _log("\"PageSetup\" section is missing, inserting it.\n");
        dstrcat(str, "%%BeginPageSetup\n");
    }


    _log("Inserting option code into \"PageSetup\" section.\n");
    build_commandline(optset, NULL, 0);
    dstrcat(str, pagesetupprepend->data);


    if (comments)
        dstrcat(str, "%%EndPageSetup\n");
}
