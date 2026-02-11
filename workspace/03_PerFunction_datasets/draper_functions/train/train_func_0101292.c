nxt_motor_record(nxt_t *nxt,int motor,double t,nxt_motor_record_callback callback,void *data) {
  struct timeval tv, starttv;
  int rot;
  int err;
  double time = 0;
  int capacity = 256;
  int fill_counter = 0;

  nxt_motor_stop(nxt, motor, 0);
  gettimeofday(&starttv,NULL);
  while (1) {

    rot = nxt_motor_get_rotation_count(nxt, motor);
    err = nxt_error(nxt);
    if (err != 0)
      break;
    gettimeofday(&tv,NULL);
    time = tv.tv_sec - starttv.tv_sec + (tv.tv_usec - starttv.tv_usec) * 1e-6;
    if (time > t)
      break;
    callback(time,rot,data);
  }
}
