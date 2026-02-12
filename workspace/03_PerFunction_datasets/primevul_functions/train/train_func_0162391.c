main(int argc, char **argv)
{


  int result = 0;


  setenv ("LOUIS_TABLEPATH", "", 1);
  ASSERT (lou_getTable ("tables/resolve_table/table_1"));


  ASSERT (!lou_getTable ("table_1"));


  setenv ("LOUIS_TABLEPATH", "tables/resolve_table", 1);
  ASSERT (lou_getTable ("table_1"));


  setenv ("LOUIS_TABLEPATH", "", 1);
  ASSERT (lou_getTable ("tables/resolve_table/table_1,"
			"table_2"));


  ASSERT (!lou_getTable ("tables/resolve_table/table_1,"
			 "table_1.1.1"));


  ASSERT (lou_getTable ("tables/resolve_table/dir_1/table_1.1,"
			"tables/resolve_table/dir_2/table_2.1"));


  setenv ("LOUIS_TABLEPATH", "tables/resolve_table/dir_2", 1);
  ASSERT (lou_getTable ("tables/resolve_table/dir_1/table_1.1,"
			"table_2.1,"
			"table_1.2"));


  setenv ("LOUIS_TABLEPATH", "", 1);
  ASSERT (lou_getTable ("tables/resolve_table/table_1,"
			"dir_1/table_1.1"));


  setenv ("LOUIS_TABLEPATH", "tables/resolve_table/dir_1,"
			     "tables/resolve_table/dir_2", 1);
  ASSERT (lou_getTable ("table_1.2,"
			"table_2.1"));


  setenv ("LOUIS_TABLEPATH", "tables/resolve_table", 1);
  ASSERT (!lou_getTable ("table_1,"
			 "tables/resolve_table/dir_1/table_1.1,"
			 "table_1.2"));


  setenv ("LOUIS_TABLEPATH", "", 1);
  ASSERT (lou_getTable ("tables/resolve_table/table_3"));


  ASSERT (lou_getTable ("tables/resolve_table/dir_1/table_1.3"));


  ASSERT (lou_getTable ("tables/resolve_table/table_4"));


  ASSERT (!lou_getTable ("tables/resolve_table/table_5"));


  setenv ("LOUIS_TABLEPATH", "tables/resolve_table", 1);
  ASSERT (lou_getTable ("tables/resolve_table/table_5"));


  setenv ("LOUIS_TABLEPATH", "tables/resolve_table/dir_1", 1);
  ASSERT (lou_getTable ("tables/resolve_table/table_6"));

  return result;

}
