FreeAuditTimer(void)
{
    if (auditTimer != NULL) {

        TimerForce(auditTimer);
        TimerFree(auditTimer);
        auditTimer = NULL;
    }
}
