endNonTransactionalAccess() {


        DEBUG << "TransactionalStore::endNonTransactionalAccess" << endl;
        m_mutex.unlock();
    }
