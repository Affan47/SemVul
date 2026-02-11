main(int argc, char *argv[])
{

    fl_initialize(&argc, argv, "FormDemo", 0, 0);

    create_form_cl();
    strcpy(dbname, "rgb.txt");

    if (load_browser(dbname))
	fl_set_object_label(dbobj, dbname);
    else
	fl_set_object_label(dbobj, "None");


    cl->size_range(cl->w(),cl->h(),2*cl->w(),2*cl->h());


    fl_show_form(cl, FL_PLACE_FREE, 1, "RGB Browser");


    while (fl_do_forms())
	;
    return 0;
}
