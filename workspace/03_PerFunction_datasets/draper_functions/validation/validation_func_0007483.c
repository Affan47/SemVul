auto_lens_button_toggle(GtkToggleButton *button,
                                    UFObject *lensfunAuto)
{
    if (gtk_toggle_button_get_active(button)) {
        if (ufstring_is_equal(lensfunAuto, "yes"))
            ufobject_set_string(lensfunAuto, "no");
        else
            ufobject_set_string(lensfunAuto, "yes");
        gtk_toggle_button_set_active(button, FALSE);
    }
}
