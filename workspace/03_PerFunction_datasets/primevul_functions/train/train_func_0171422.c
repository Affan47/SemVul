int handler::update_first_row(const uchar *new_data)
{
  int error;
  if (likely(!(error= ha_rnd_init(1))))
  {
    int end_error;
    if (likely(!(error= ha_rnd_next(table->record[1]))))
    {


      if (memcmp(new_data, table->record[1], table->s->reclength))
        error= update_row(table->record[1], new_data);
    }
    end_error= ha_rnd_end();
    if (likely(!error))
      error= end_error;

    DBUG_ASSERT(!end_error || error != 0);
  }
  return error;
}
