db_DS_equal_p( database_DS db1, database_DS db2)
{
   int i;

   if ((db1->n_data == db2->n_data) && (db1->n_atts == db2->n_atts)) {
      for (i=0; i<db1->n_atts; i++)
	 if (att_DS_equal_p( db1->att_info[i], db2->att_info[i]) == FALSE)
	    return(FALSE);
      return(TRUE);
   }
   return(FALSE);
}
