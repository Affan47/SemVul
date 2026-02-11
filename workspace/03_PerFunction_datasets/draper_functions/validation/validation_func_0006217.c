do_duplication( int32_t pos_1, int32_t pos_2, int32_t pos_3 )

{
  char* duplicate_segment = NULL;
  int32_t seg_length;

  if ( pos_1 < pos_2 )
  {


    seg_length = pos_2 - pos_1;
    duplicate_segment = new char[seg_length+1];
    memcpy( duplicate_segment, &_data[pos_1], seg_length );
    duplicate_segment[seg_length] = '\0';
  }
  else
  {


    int32_t tmp1_len = _length - pos_1;
    int32_t tmp2_len = pos_2;
    seg_length = tmp1_len + tmp2_len;
    duplicate_segment = new char[seg_length+1];
    memcpy( duplicate_segment, &_data[pos_1], tmp1_len );
    memcpy( &duplicate_segment[tmp1_len], _data, tmp2_len );
    duplicate_segment[seg_length] = '\0';
  }


  ae_list<ae_rna*>** duplicated_promoters = new ae_list<ae_rna*>*[2];
  duplicated_promoters[LEADING] = new ae_list<ae_rna*>();
  duplicated_promoters[LAGGING] = new ae_list<ae_rna*>();
  _gen_unit->duplicate_promoters_included_in( pos_1, pos_2, duplicated_promoters );

  _gen_unit->remove_promoters_around( pos_3 );

  insert( pos_3, duplicate_segment, seg_length );

  if ( _length >= PROM_SIZE )
  {
    if ( _length - seg_length < PROM_SIZE )
    {


      _gen_unit->locate_promoters();
    }
    else
    {
      _gen_unit->move_all_promoters_after( pos_3, seg_length );

      _gen_unit->insert_promoters_at( duplicated_promoters, pos_3 );

      _gen_unit->look_for_new_promoters_around( pos_3 );
      _gen_unit->look_for_new_promoters_around( pos_3 + seg_length );
    }
  }


  delete [] duplicate_segment;

  delete duplicated_promoters[LEADING];
  delete duplicated_promoters[LAGGING];
  delete [] duplicated_promoters;

  return true;
}
