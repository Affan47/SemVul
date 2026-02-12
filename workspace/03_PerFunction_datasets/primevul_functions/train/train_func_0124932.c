static bool scsi_handle_rw_error(SCSIDiskReq *r, int ret, bool acct_failed)
{
    bool is_read = (r->req.cmd.mode == SCSI_XFER_FROM_DEV);
    SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, r->req.dev);
    SCSIDiskClass *sdc = (SCSIDiskClass *) object_get_class(OBJECT(s));
    SCSISense sense = SENSE_CODE(NO_SENSE);
    int error = 0;
    bool req_has_sense = false;
    BlockErrorAction action;
    int status;

    if (ret < 0) {
        status = scsi_sense_from_errno(-ret, &sense);
        error = -ret;
    } else {

        status = ret;
        if (status == CHECK_CONDITION) {
            req_has_sense = true;
            error = scsi_sense_buf_to_errno(r->req.sense, sizeof(r->req.sense));
        } else {
            error = EINVAL;
        }
    }


    if (req_has_sense &&
        scsi_sense_buf_is_guest_recoverable(r->req.sense, sizeof(r->req.sense))) {
        action = BLOCK_ERROR_ACTION_REPORT;
        acct_failed = false;
    } else {
        action = blk_get_error_action(s->qdev.conf.blk, is_read, error);
        blk_error_action(s->qdev.conf.blk, action, is_read, error);
    }

    switch (action) {
    case BLOCK_ERROR_ACTION_REPORT:
        if (acct_failed) {
            block_acct_failed(blk_get_stats(s->qdev.conf.blk), &r->acct);
        }
        if (req_has_sense) {
            sdc->update_sense(&r->req);
        } else if (status == CHECK_CONDITION) {
            scsi_req_build_sense(&r->req, sense);
        }
        scsi_req_complete(&r->req, status);
        return true;

    case BLOCK_ERROR_ACTION_IGNORE:
        return false;

    case BLOCK_ERROR_ACTION_STOP:
        scsi_req_retry(&r->req);
        return true;

    default:
        g_assert_not_reached();
    }
}
