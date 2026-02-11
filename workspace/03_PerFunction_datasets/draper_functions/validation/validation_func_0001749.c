AddRow(unsigned rowId, DataStructures::List<Cell> &initialCellValues)
{
	Row *newRow = RakNet::OP_NEW<Row>( _FILE_AND_LINE_ );
	unsigned rowIndex;
	for (rowIndex=0; rowIndex < columns.Size(); rowIndex++)
	{
		if (rowIndex < initialCellValues.Size() && initialCellValues[rowIndex].isEmpty==false)
		{
			Table::Cell *c;
			c = RakNet::OP_NEW<Table::Cell>(_FILE_AND_LINE_);
			c->SetByType(initialCellValues[rowIndex].i,initialCellValues[rowIndex].c,initialCellValues[rowIndex].ptr,columns[rowIndex].columnType);
			newRow->cells.Insert(c, _FILE_AND_LINE_ );
		}
		else
			newRow->cells.Insert(RakNet::OP_NEW<Table::Cell>(_FILE_AND_LINE_), _FILE_AND_LINE_ );
	}
	rows.Insert(rowId, newRow);
	return newRow;
}
