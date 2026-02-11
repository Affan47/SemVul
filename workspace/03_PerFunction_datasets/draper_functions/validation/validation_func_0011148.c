GK_delete_key(float pos, float precis, int justone)
{
    Keylist *k, *next;
    int cnt;

    for (cnt = 0, k = Keys; k;) {
	next = k->next;

	if (k->pos >= pos - precis && k->pos <= pos + precis) {
	    cnt++;
	    _remove_key(k);
	    free(k);
	    if (justone) {
		break;
	    }
	}

	k = next;
    }

    GK_update_frames();
    return (cnt);
}
