gsb_file_save_currency_link_part ( gulong iterator,
                        gulong *length_calculated,
                        gchar **file_content )
{
    GSList *list_tmp;

    list_tmp = gsb_data_currency_link_get_currency_link_list ();

    while ( list_tmp )
    {
    gchar *new_string;
    gint link_number;
    gchar *change_rate;
    gchar *strdate;

    link_number = gsb_data_currency_link_get_no_currency_link (list_tmp -> data);


    change_rate = gsb_real_safe_real_to_string (
                        gsb_data_currency_link_get_change_rate ( link_number ), -1 );


    strdate = gsb_format_gdate_safe ( gsb_data_currency_link_get_modified_date ( link_number ) );


    new_string = g_markup_printf_escaped (
                        "\t<Currency_link Nb=\"%d\" Cu1=\"%d\" Cu2=\"%d\" Ex=\"%s\" "
                        "Modified_date=\"%s\" Fl=\"%d\" />\n",
                        link_number,
                        gsb_data_currency_link_get_first_currency ( link_number ),
                        gsb_data_currency_link_get_second_currency (link_number),
                        my_safe_null_str ( change_rate ),
                        strdate,
                        gsb_data_currency_link_get_fixed_link ( link_number ) );

    g_free ( change_rate );
    g_free ( strdate );


    iterator = gsb_file_save_append_part ( iterator,
                        length_calculated,
                        file_content,
                        new_string );
    list_tmp = list_tmp -> next;
    }
    return iterator;
}
