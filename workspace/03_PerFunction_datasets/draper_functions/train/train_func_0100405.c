gnc_date_edit_set_time (GNCDateEdit *gde, time64 the_time)
{
    g_return_if_fail (gde != NULL);
    g_return_if_fail (GNC_IS_DATE_EDIT (gde));


    gde->initial_time = the_time;

    g_object_set (G_OBJECT (gde), "time", the_time, NULL);
}
