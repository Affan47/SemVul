translate_response(int response) {
        static const char *const response_table[] = {
                [-GTK_RESPONSE_NONE] = NULL,
                [-GTK_RESPONSE_REJECT] = "dialog-cancel",
                [-GTK_RESPONSE_DELETE_EVENT] = "dialog-cancel",
                [-GTK_RESPONSE_ACCEPT] = "dialog-ok",
                [-GTK_RESPONSE_OK] = "dialog-ok",
                [-GTK_RESPONSE_CANCEL] = "dialog-cancel",
                [-GTK_RESPONSE_CLOSE] = "dialog-ok",
                [-GTK_RESPONSE_YES] = "dialog-ok",
                [-GTK_RESPONSE_NO] = "dialog-cancel",
                [-GTK_RESPONSE_APPLY] = "dialog-ok",
                [-GTK_RESPONSE_HELP] = NULL,
        };

        if (response >= 0)
                return NULL;

        if ((unsigned) -response >= G_N_ELEMENTS(response_table))
                return NULL;

        return response_table[-response];
}
