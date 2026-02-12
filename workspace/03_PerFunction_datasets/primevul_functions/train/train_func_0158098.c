subOpCallback(void *  ,
        T_ASC_Network *aNet, T_ASC_Association **subAssoc)
{

    if (aNet == NULL) return;

    if (*subAssoc == NULL) {

        acceptSubAssoc(aNet, subAssoc);
    } else {

        subOpSCP(subAssoc);
    }
}
