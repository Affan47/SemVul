haveComposite(bool for_real) {
    if (for_real) {
        Display *disp = FbTk::App::instance()->display();
        int major_opcode, first_event, first_error;

        return (XQueryExtension(disp, "Composite",
                               &major_opcode,
                               &first_event, &first_error) == True);
    } else {
        if (!s_init)
            init();

        return s_composite;
    }
}
