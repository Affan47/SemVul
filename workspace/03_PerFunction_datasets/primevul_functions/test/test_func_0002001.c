bool IsNumericType(const DataType dtype) {
  static const gtl::FlatSet<DataType>* const kRealNumberTypes =
      CHECK_NOTNULL((new gtl::FlatSet<DataType>{

          DT_BFLOAT16,
          DT_HALF,
          DT_FLOAT,
          DT_DOUBLE,

          DT_INT8,
          DT_INT16,
          DT_INT32,
          DT_INT64,
          DT_UINT8,
          DT_UINT16,
          DT_UINT32,
          DT_UINT64,

          DT_QINT8,
          DT_QUINT8,
          DT_QINT16,
          DT_QUINT16,
          DT_QINT32,

          DT_BOOL,
      }));
  return kRealNumberTypes->find(dtype) != kRealNumberTypes->end();
}
