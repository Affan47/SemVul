rotate(double roll, double pitch, double yaw) {

    for (unsigned int i=0; i<points.size(); i++) {
      points[i].rotate_IP(roll, pitch, yaw);
    }
  }
