TxnWrap::~TxnWrap() {

    if (this->txn) {
        mdb_txn_abort(txn);
        this->removeFromEnvWrap();
    }
}
