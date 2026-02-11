GetColumnsOfNonZeroMatrixElementsInRow(unsigned int, ColumnArray & cols, unsigned int)
{

  cols = ColumnArray(m_Order);
  for( unsigned int i = 0; i < m_Order; i++ )
    {
    cols[i] = i;
    }
}
