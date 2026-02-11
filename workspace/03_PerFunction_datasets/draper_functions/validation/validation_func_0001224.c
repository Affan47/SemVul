trace_SQLSetDescRec (int trace_leave, int retcode,
  SQLHDESC		  DescriptorHandle,
  SQLSMALLINT		  RecNumber,
  SQLSMALLINT		  Type,
  SQLSMALLINT		  SubType,
  SQLLEN		  Length,
  SQLSMALLINT		  Precision,
  SQLSMALLINT		  Scale,
  SQLPOINTER		  Data,
  SQLLEN		* StringLength,
  SQLLEN		* Indicator)
{

  _trace_print_function (en_SetDescRec, trace_leave, retcode);


  _trace_handle (SQL_HANDLE_DESC, DescriptorHandle);
  _trace_smallint (RecNumber);
  _trace_smallint (Type);
  _trace_smallint (SubType);
  _trace_len (Length);
  _trace_smallint (Precision);
  _trace_smallint (Scale);
  _trace_pointer (Data);
  _trace_len_p (StringLength, TRACE_OUTPUT_SUCCESS);
  _trace_len_p (Indicator, TRACE_OUTPUT_SUCCESS);
}
