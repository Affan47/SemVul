keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Escape:
	e->ignore();
	break;
    case Qt::Key_Backspace:
    case Qt::Key_Delete:
    case 0x7f:
	if (e->modifiers() & (Qt::ControlModifier | Qt::AltModifier))
	    e->ignore();
	else if (m_Length) {
	    m_Password[--m_Length] = '\000';
	    showPass();
	}
	break;
    default:
	const unsigned char ke = e->text().toLocal8Bit()[0];
	if (ke >= 32) {
	    insert(e->text());
	} else
	    e->ignore();
	break;
    }
}
