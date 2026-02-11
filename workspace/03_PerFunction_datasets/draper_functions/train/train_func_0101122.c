DestroyCnxns (CNet* nets) {
    for (CNet* nw = nets->First(); nw != nets->End(); nw = nw->Next()) {
        CCnxn* cnxn = nw->Cnxn();
        CSolverInfo* lbinfo = cnxn->_lbConn->_csinfo;
        CSolverInfo* rtinfo = cnxn->_rtConn->_csinfo;
        delete lbinfo;
        delete rtinfo;
        cnxn->_lbConn->_csinfo = nil;
        cnxn->_rtConn->_csinfo = nil;
    }
}
