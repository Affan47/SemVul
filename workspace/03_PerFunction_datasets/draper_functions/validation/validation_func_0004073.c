newJob(fxStr& jobid, fxStr& groupid, fxStr& emsg)
{
    if (command("JNEW") == COMPLETE) {
        if (code == 200) {


            u_int l = 0;
            if (extract(l, "jobid:", jobid, "JNEW", emsg) &&
                    extract(l, "groupid:", groupid, "JNEW", emsg)) {


                jobid.resize(jobid.skip(0, "0123456789"));
                groupid.resize(groupid.skip(0, "0123456789"));
                curjob = jobid;
                return true;
            }
        } else {
            unexpectedResponse(emsg);
        }
    } else {
        emsg = lastResponse;
    }
    return false;
}
