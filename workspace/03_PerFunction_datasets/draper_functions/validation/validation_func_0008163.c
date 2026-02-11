xmlRelaxNGGetElements(xmlRelaxNGParserCtxtPtr ctxt,
                      xmlRelaxNGDefinePtr def, int eora)
{
    xmlRelaxNGDefinePtr *ret = NULL, parent, cur, tmp;
    int len = 0;
    int max = 0;


    if (ctxt->nbErrors != 0)
        return (NULL);

    parent = NULL;
    cur = def;
    while (cur != NULL) {
        if (((eora == 0) && ((cur->type == XML_RELAXNG_ELEMENT) ||
                             (cur->type == XML_RELAXNG_TEXT))) ||
            ((eora == 1) && (cur->type == XML_RELAXNG_ATTRIBUTE))) {
            if (ret == NULL) {
                max = 10;
                ret = (xmlRelaxNGDefinePtr *)
                    xmlMalloc((max + 1) * sizeof(xmlRelaxNGDefinePtr));
                if (ret == NULL) {
                    xmlRngPErrMemory(ctxt, "getting element list\n");
                    return (NULL);
                }
            } else if (max <= len) {
                xmlRelaxNGDefinePtr *temp;

                max *= 2;
                temp = xmlRealloc(ret,
                               (max + 1) * sizeof(xmlRelaxNGDefinePtr));
                if (temp == NULL) {
                    xmlRngPErrMemory(ctxt, "getting element list\n");
                    xmlFree(ret);
                    return (NULL);
                }
                ret = temp;
            }
            ret[len++] = cur;
            ret[len] = NULL;
        } else if ((cur->type == XML_RELAXNG_CHOICE) ||
                   (cur->type == XML_RELAXNG_INTERLEAVE) ||
                   (cur->type == XML_RELAXNG_GROUP) ||
                   (cur->type == XML_RELAXNG_ONEORMORE) ||
                   (cur->type == XML_RELAXNG_ZEROORMORE) ||
                   (cur->type == XML_RELAXNG_OPTIONAL) ||
                   (cur->type == XML_RELAXNG_PARENTREF) ||
                   (cur->type == XML_RELAXNG_REF) ||
                   (cur->type == XML_RELAXNG_DEF) ||
                   (cur->type == XML_RELAXNG_EXTERNALREF)) {


            if (cur->content != NULL) {
                parent = cur;
                cur = cur->content;
                tmp = cur;
                while (tmp != NULL) {
                    tmp->parent = parent;
                    tmp = tmp->next;
                }
                continue;
            }
        }
        if (cur == def)
            break;
        if (cur->next != NULL) {
            cur = cur->next;
            continue;
        }
        do {
            cur = cur->parent;
            if (cur == NULL)
                break;
            if (cur == def)
                return (ret);
            if (cur->next != NULL) {
                cur = cur->next;
                break;
            }
        } while (cur != NULL);
    }
    return (ret);
}
