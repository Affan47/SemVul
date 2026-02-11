xmlSecKeyDataNameXmlWrite(xmlSecKeyDataId id, xmlSecKeyPtr key, xmlNodePtr node, xmlSecKeyInfoCtxPtr keyInfoCtx) {
    const xmlChar* name;

    xmlSecAssert2(id == xmlSecKeyDataNameId, -1);
    xmlSecAssert2(key != NULL, -1);
    xmlSecAssert2(node != NULL, -1);
    xmlSecAssert2(keyInfoCtx != NULL, -1);
    xmlSecAssert2(keyInfoCtx->mode == xmlSecKeyInfoModeWrite, -1);

    name = xmlSecKeyGetName(key);
    if(name != NULL) {
            xmlSecNodeEncodeAndSetContent(node, name);
    }
    return(0);
}
