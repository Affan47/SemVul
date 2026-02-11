fill_values_if_necessary(DbTreeModel& model, int row)
{


  if(m_values_retrieved)
  {

  }
  else
  {


    if((row < (int)model.m_data_model_rows_count) && model.m_gda_datamodel)
    {
      Glib::RefPtr<Gnome::Gda::DataModelIter> iter = model.m_gda_datamodel->create_iter();
      if(iter)
      {
        iter->move_to_row(row);


        const int cols_count = model.m_data_model_columns_count;
        for(int i = 0; i < cols_count; ++i)
        {
          try
          {
            m_db_values[i] = iter->get_value_at(i);
          }
          catch(const Glib::Error& ex)
          {

            std::cerr << G_STRFUNC << ": get_value_at() failed for column=" << i << ", with exception: " << ex.what() << std::endl;
          }


        }


        try
        {
          m_key = iter->get_value_at(model.m_column_index_key);
        }
        catch(const Glib::Error& ex)
        {

          std::cerr << G_STRFUNC << ": get_value_at() failed for model.m_column_index_key=" << model.m_column_index_key << ", with exception: " << ex.what() << std::endl;
        }

        m_extra = false;
        m_removed = false;
      }
    }
    else
    {

      if(m_extra)
      {


      }
      else if(!m_removed)
      {


      }


      const Glib::RefPtr<const Gnome::Gda::DataModel> datamodel = model.m_gda_datamodel;
      for(guint col = 0; col < model.m_data_model_columns_count; ++col)
      {
        if(m_db_values.find(col) == m_db_values.end())
        {
          if(!datamodel)
          {
            m_db_values[col] = Gnome::Gda::Value();
          }
          else
          {
            const Glib::RefPtr<const Gnome::Gda::Column> column = datamodel->describe_column(col);


            const Field::glom_field_type glom_type = Field::get_glom_type_for_gda_type(column->get_g_type());
            m_db_values[col] = Glom::Conversions::get_empty_value(glom_type);
          }
        }
      }
    }

  }

  m_values_retrieved = true;
}
