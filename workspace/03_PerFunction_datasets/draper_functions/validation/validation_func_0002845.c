cal_set_time(GtkWidget *cal, MarginType type, time_t timet) {
    GtkBuilder *cal_xml;
    GtkCalendar *calendar = NULL;
    GtkSpinButton *hour = NULL;
    GtkSpinButton *min = NULL;
    GtkToggleButton *no_margin = NULL;

    cal_xml = _get_calendar_xml(cal);

    switch (type) {
    case LOWER_MARGIN:
        calendar = GTK_CALENDAR (gtkpod_builder_xml_get_widget (cal_xml, "lower_cal"));
        hour = GTK_SPIN_BUTTON (gtkpod_builder_xml_get_widget (cal_xml, "lower_hours"));
        min = GTK_SPIN_BUTTON (gtkpod_builder_xml_get_widget (cal_xml, "lower_minutes"));
        no_margin = GTK_TOGGLE_BUTTON (gtkpod_builder_xml_get_widget (cal_xml, "no_lower_margin"));
        break;
    case UPPER_MARGIN:
        calendar = GTK_CALENDAR (gtkpod_builder_xml_get_widget (cal_xml, "upper_cal"));
        hour = GTK_SPIN_BUTTON (gtkpod_builder_xml_get_widget (cal_xml, "upper_hours"));
        min = GTK_SPIN_BUTTON (gtkpod_builder_xml_get_widget (cal_xml, "upper_minutes"));
        no_margin = GTK_TOGGLE_BUTTON (gtkpod_builder_xml_get_widget (cal_xml, "no_upper_margin"));
        break;
    }
    cal_set_time_widgets(calendar, hour, min, no_margin, timet);
}
