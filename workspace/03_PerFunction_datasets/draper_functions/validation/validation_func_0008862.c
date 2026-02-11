takePieceAt(const Chess::Square& square)
{
	int index = squareIndex(square);
	if (index == -1)
		return 0;

	GraphicsPiece* piece = m_squares.at(index);
	if (piece == 0)
		return 0;

	m_squares[index] = 0;
	piece->setParentItem(0);
	piece->setContainer(0);

	return piece;
}
