void JOIN_TAB::build_range_rowid_filter_if_needed()
{
  if (rowid_filter && !is_rowid_filter_built)
  {


    Exec_time_tracker *table_tracker= table->file->get_time_tracker();
    Rowid_filter_tracker *rowid_tracker= rowid_filter->get_tracker();
    table->file->set_time_tracker(rowid_tracker->get_time_tracker());
    rowid_tracker->start_tracking();
    if (!rowid_filter->build())
    {
      is_rowid_filter_built= true;
    }
    else
    {
      delete rowid_filter;
      rowid_filter= 0;
    }
    rowid_tracker->stop_tracking();
    table->file->set_time_tracker(table_tracker);
  }
}
