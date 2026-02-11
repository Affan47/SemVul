loan_info_calc_update_cb( GtkWidget *w, gpointer user_data )
{
    LoanAssistantData *ldd = user_data;
    GDate start, now;
    int i, totalVal, total, remain;

    g_date_clear( &start, 1 );
    g_date_clear( &now, 1 );
    gnc_gdate_set_time64( &start, gnc_date_edit_get_date( ldd->prmStartDateGDE ) );
    gnc_gdate_set_time64( &now, gnc_time (NULL) );
    for ( i = 0; g_date_compare( &start, &now ) < 0; i++ )
    {
        g_date_add_months( &start, 1 );
    }


    {
        gchar *valueStr = gtk_editable_get_chars( GTK_EDITABLE(ldd->prmLengthSpin),
                          0, -1 );
        totalVal = strtol( valueStr, NULL, 10 );
        g_free( valueStr );
    }
    total = totalVal
            * ( gtk_combo_box_get_active( ldd->prmLengthType )
                == 1 ? 12 : 1 );
    remain = total - i;
    gtk_spin_button_set_value( ldd->prmRemainSpin, remain );
    gtk_widget_show( GTK_WIDGET(ldd->prmRemainSpin) );
}
