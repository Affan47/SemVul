editIndent()
{
	QPointer<IndentDialog> indentDialog = new IndentDialog(this, tr("Indent"));
	if (!indentDialog->exec())
	{
		delete indentDialog;
		return;
	}

	const QString insertString = indentDialog->insertChar();
	const int numOfInserts = indentDialog->numOfInserts();
	delete indentDialog;

	bool go = true;
	QTextCursor textCursor = m_tikzEditor->textCursor();
	if (textCursor.hasSelection())
	{
		textCursor.beginEditBlock();
		const int start = textCursor.selectionStart();
		int end = textCursor.selectionEnd();
		textCursor.setPosition(start, QTextCursor::MoveAnchor);
		textCursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
		while (textCursor.position() < end && go)
		{
			for (int i = 0; i < numOfInserts; ++i)
				textCursor.insertText(insertString);
			end++;
			go = textCursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
		}
		textCursor.endEditBlock();
	}
	else
	{
		textCursor.beginEditBlock();
		textCursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
		for (int i = 0; i < numOfInserts; ++i)
			textCursor.insertText(insertString);
		textCursor.endEditBlock();
	}
}
