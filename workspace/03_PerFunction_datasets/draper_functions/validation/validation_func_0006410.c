gncInvoiceRegister (void)
{
    static QofParam params[] =
    {
        { INVOICE_ID,        QOF_TYPE_STRING,  (QofAccessFunc)gncInvoiceGetID,     (QofSetterFunc)gncInvoiceSetID },
        { INVOICE_OWNER,     GNC_ID_OWNER,     (QofAccessFunc)gncInvoiceGetOwner, NULL },
        { INVOICE_OPENED,    QOF_TYPE_DATE,    (QofAccessFunc)gncInvoiceGetDateOpened, (QofSetterFunc)gncInvoiceSetDateOpened },
        { INVOICE_DUE,       QOF_TYPE_DATE,    (QofAccessFunc)gncInvoiceGetDateDue, NULL },
        { INVOICE_POSTED,    QOF_TYPE_DATE,    (QofAccessFunc)gncInvoiceGetDatePosted, (QofSetterFunc)gncInvoiceSetDatePosted },
        { INVOICE_IS_POSTED, QOF_TYPE_BOOLEAN, (QofAccessFunc)gncInvoiceIsPosted, NULL },
        { INVOICE_IS_PAID,   QOF_TYPE_BOOLEAN, (QofAccessFunc)gncInvoiceIsPaid,    NULL },
        { INVOICE_BILLINGID, QOF_TYPE_STRING,  (QofAccessFunc)gncInvoiceGetBillingID, (QofSetterFunc)gncInvoiceSetBillingID },
        { INVOICE_NOTES,     QOF_TYPE_STRING,  (QofAccessFunc)gncInvoiceGetNotes,   (QofSetterFunc)gncInvoiceSetNotes },
        { INVOICE_ACC,       GNC_ID_ACCOUNT,   (QofAccessFunc)gncInvoiceGetPostedAcc, (QofSetterFunc)gncInvoiceSetPostedAcc },
        { INVOICE_POST_TXN,  GNC_ID_TRANS,     (QofAccessFunc)gncInvoiceGetPostedTxn, (QofSetterFunc)gncInvoiceSetPostedTxn },
        { INVOICE_POST_LOT,  GNC_ID_LOT,       (QofAccessFunc)gncInvoiceGetPostedLot, NULL },
        { INVOICE_TYPE,      QOF_TYPE_INT32,   (QofAccessFunc)gncInvoiceGetType,    NULL },
        { INVOICE_TYPE_STRING, QOF_TYPE_STRING, (QofAccessFunc)gncInvoiceGetTypeString,    NULL },
        { INVOICE_TERMS,     GNC_ID_BILLTERM,  (QofAccessFunc)gncInvoiceGetTerms,   (QofSetterFunc)gncInvoiceSetTerms },
        { INVOICE_BILLTO,    GNC_ID_OWNER,     (QofAccessFunc)gncInvoiceGetBillTo, NULL  },
        { INVOICE_ENTRIES,   QOF_TYPE_COLLECT, (QofAccessFunc)qofInvoiceGetEntries, (QofSetterFunc)qofInvoiceSetEntries },
        { INVOICE_JOB,       GNC_ID_JOB,       (QofAccessFunc)qofInvoiceGetJob,     (QofSetterFunc)qofInvoiceSetJob },
        { QOF_PARAM_ACTIVE,  QOF_TYPE_BOOLEAN, (QofAccessFunc)gncInvoiceGetActive, (QofSetterFunc)gncInvoiceSetActive },
        { INVOICE_IS_CN,     QOF_TYPE_BOOLEAN, (QofAccessFunc)gncInvoiceGetIsCreditNote, (QofSetterFunc)gncInvoiceSetIsCreditNote },
        { QOF_PARAM_BOOK,    QOF_ID_BOOK,      (QofAccessFunc)qof_instance_get_book, NULL },
        { QOF_PARAM_GUID,    QOF_TYPE_GUID,    (QofAccessFunc)qof_instance_get_guid, NULL },
        { NULL },
    };

    qof_class_register (_GNC_MOD_NAME, (QofSortFunc)gncInvoiceCompare, params);
    reg_lot ();
    reg_txn ();


    if (0)
    {
        qofInvoiceSetEntries(NULL, NULL);
        qofInvoiceGetEntries(NULL);
        qofInvoiceSetOwner(NULL, NULL);
        qofInvoiceGetOwner(NULL);
        qofInvoiceSetBillTo(NULL, NULL);
        qofInvoiceGetBillTo(NULL);
    }
    if (!qof_choice_create(GNC_ID_INVOICE))
    {
        return FALSE;
    }
    return qof_object_register (&gncInvoiceDesc);
}
