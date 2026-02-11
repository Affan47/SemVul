eventFilter(QObject *object, QEvent *event)
{
    KTextEdit *editor = qobject_cast<KTextEdit*>(object);
    if (!editor)
        return false;

    switch (event->type())
    {
    case QEvent::KeyPress:
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key())
        {
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            emit commitData(editor);
            emit closeEditor(editor, NoHint);
            return true;

        case Qt::Key_Enter:
        case Qt::Key_Return: {
            const QString text = editor->toPlainText();
            if (text.isEmpty() || (text == QLatin1String(".")) || (text == QLatin1String("..")))
                return true;

            emit commitData(editor);
            emit closeEditor(editor, SubmitModelCache);
            return true;
        }

        case Qt::Key_Escape:
            emit closeEditor(editor, RevertModelCache);
            return true;

        default:
            return false;
        }
    }

    case QEvent::FocusOut:
    {
        const QWidget *w = QApplication::activePopupWidget();
        if (!w || w->parent() != editor)
        {
            emit commitData(editor);
            emit closeEditor(editor, NoHint);
            return true;
        }
        else
            return false;
    }

    default:
        return false;
    }
}
