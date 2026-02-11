xmlrpc_read_double(xmlrpc_env *         const envP,
                   const xmlrpc_value * const valueP,
                   xmlrpc_double *      const doubleValueP) {

    validateType(envP, valueP, XMLRPC_TYPE_DOUBLE);
    if (!envP->fault_occurred)
        *doubleValueP = valueP->_value.d;

}
