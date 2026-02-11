takeit_(obj, sflag)
integer obj;
integer sflag;
{

    logical ret_val;


    integer x;
    integer odo2;


    ret_val = FALSE_;

    if (obj == 0 || obj > star_1.strbit) {
	goto L4000;
    }

    odo2 = objcts_1.odesc2[obj - 1];

    x = objcts_1.ocan[obj - 1];

    if (x == 0 || (sflag & VFBIT) == 0) {
	goto L500;
    }
    if ((objcts_1.oflag2[x - 1] & OPENBT) != 0) {
	goto L500;
    }
    rspsub_(566, odo2);

    return ret_val;

L500:
    if ((sflag & VRBIT) == 0) {
	goto L1000;
    }
    if ((sflag & VTBIT) == 0) {
	goto L2000;
    }


    if (schlst_(0, 0, play_1.here, 0, 0, obj) <= 0) {
	goto L4000;
    }


    if ((objcts_1.oflag1[obj - 1] & TAKEBT) != 0 && (
	    objcts_1.oflag2[obj - 1] & TRYBT) == 0) {
	goto L3000;
    }


    if ((sflag & VCBIT) == 0) {
	goto L4000;
    }
    rspsub_(445, odo2);
    return ret_val;


L2000:
    if ((sflag & VCBIT) == 0) {
	goto L4000;
    }
L1000:
    if (schlst_(0, 0, play_1.here, 0, 0, obj) <= 0) {
	goto L4000;
    }
    rspsub_(665, odo2);
    return ret_val;


L3000:
    if (obj != advs_1.avehic[play_1.winner - 1]) {
	goto L3500;
    }

    rspeak_(672);
    return ret_val;

L3500:
    if (x != 0 && objcts_1.oadv[x - 1] == play_1.winner || weight_(0, obj,
	     play_1.winner) + objcts_1.osize[obj - 1] <= state_1.mxload) {
	goto L3700;
    }
    rspeak_(558);

    return ret_val;

L3700:
    newsta_(obj, 559, 0, 0, play_1.winner);

    objcts_1.oflag2[obj - 1] |= TCHBT;
    scrupd_(objcts_1.ofval[obj - 1]);
    objcts_1.ofval[obj - 1] = 0;

L4000:
    ret_val = TRUE_;

    return ret_val;

}
