deliver_before_test_cleared(Octstr *before, struct tm now)
{
    long time_data[6];
    long j;

    if (before == NULL)
        return 1;

    initialize_time_item_array(time_data, now);
    if (date_item_compare(before, time_data[0], 0) == 1)
        return 1;
    if (date_item_compare(before, time_data[0], 0) == -1)
        return 0;

    for (j = 5; j < octstr_len(before); j += 3) {
        if (date_item_compare(before, time_data[(j-5)/3 + 1], j) == 1)
            return 1;
        if (date_item_compare(before, time_data[(j-5)/3 + 1], j) == -1)
            return 0;
    }

    return 0;
}
