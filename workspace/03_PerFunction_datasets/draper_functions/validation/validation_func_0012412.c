reset(bool all)
{
	d->reset();
	d->noopTimer.stop();


	delete d->ss;
	d->ss = 0;


	delete d->sasl;
	d->sasl = 0;


	if(d->mode == Client) {


		if(d->bs) {
			d->bs->close();
			d->bs = 0;
		}
		d->conn->done();


		d->client.reset();
	}

	else {
		if(d->tls)
			d->tls->reset();

		if(d->bs) {
			d->bs->close();
			d->bs = 0;
		}

		d->srv.reset();
	}

	if(all) {
		while (!d->in.isEmpty()) {
			delete d->in.takeFirst();
		}
	}
}
