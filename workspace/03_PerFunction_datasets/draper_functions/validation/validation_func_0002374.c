gl_ui_cmd_file_print (GtkAction *action,
                      glWindow  *window)
{
        glPrintOpDialog         *op;
        GtkPrintOperationResult  result;

        gl_debug (DEBUG_COMMANDS, "START");

        g_return_if_fail (action && GTK_IS_ACTION(action));
        g_return_if_fail (window && GL_IS_WINDOW(window));

        op = gl_print_op_dialog_new (GL_VIEW(window->view)->label);

        if (window->print_settings)
        {
                gl_print_op_set_settings (GL_PRINT_OP (op), window->print_settings);
        }

        result = gtk_print_operation_run (GTK_PRINT_OPERATION (op),
                                          GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG,
                                          GTK_WINDOW (window),
                                          NULL);

        if ( result == GTK_PRINT_OPERATION_RESULT_APPLY )
        {
                gl_print_op_free_settings (window->print_settings);
                window->print_settings = gl_print_op_get_settings (GL_PRINT_OP (op));
        }

        gl_debug (DEBUG_COMMANDS, "END");
}
