buildCGetRSP(T_DIMSE_C_GetRSP * e, DcmDataset * obj)
{
    OFCondition cond = buildCommonRSP(obj, DIMSE_C_GET_RSP,
        e->MessageIDBeingRespondedTo,
	e->DataSetType, e->DimseStatus); RET(cond);


    if (e->opts & O_GET_AFFECTEDSOPCLASSUID) {
        cond = addString(obj, DCM_AffectedSOPClassUID,
            e->AffectedSOPClassUID, OFFalse); RET(cond);
    }
    if (e->opts & O_GET_NUMBEROFREMAININGSUBOPERATIONS) {
        cond = addUS(obj, DCM_NumberOfRemainingSubOperations,
            e->NumberOfRemainingSubOperations); RET(cond);
    }
    if (e->opts & O_GET_NUMBEROFCOMPLETEDSUBOPERATIONS) {
        cond = addUS(obj, DCM_NumberOfCompletedSubOperations,
            e->NumberOfCompletedSubOperations); RET(cond);
    }
    if (e->opts & O_GET_NUMBEROFFAILEDSUBOPERATIONS) {
        cond = addUS(obj, DCM_NumberOfFailedSubOperations,
            e->NumberOfFailedSubOperations); RET(cond);
    }
    if (e->opts & O_GET_NUMBEROFWARNINGSUBOPERATIONS) {
        cond = addUS(obj, DCM_NumberOfWarningSubOperations,
            e->NumberOfWarningSubOperations); RET(cond);
    }
    return cond;
}
