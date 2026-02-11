readResponseHeader(const QHttpResponseHeader &responseHeader)
{
    if (responseHeader.statusCode() != 200) {
        QMessageBox::information(this, tr("HTTP"),
                                 tr("Download failed: %1.")
                                 .arg(responseHeader.reasonPhrase()));
        httpRequestAborted = true;
        progressDialog->hide();
        http->abort();
        return;
    }
}
