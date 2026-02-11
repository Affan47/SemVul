slotPercent(KJob *job, unsigned long percent)
{
    qulonglong bytesTotal = job->totalAmount(KJob::Bytes);
    qulonglong bytesProcessed = bytesTotal * (percent / 100);
    if (operation() == QNetworkAccessManager::PutOperation ||
        operation() == QNetworkAccessManager::PostOperation) {
        emit uploadProgress(bytesProcessed, bytesTotal);
        return;
    }
    emit downloadProgress(bytesProcessed, bytesTotal);
}
