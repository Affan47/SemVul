askValue( const QString & value, bool & ok )
{
	return QString::number( QInputDialog::getInteger( 0, "New item", "Enter new number: ", value.toInt(), _min, _max, 1, &ok ) );
}
