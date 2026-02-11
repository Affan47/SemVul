log() const {
  register FXfloat scale=sqrtf(x*x+y*y+z*z);
  register FXfloat theta=atan2f(scale,w);
  FXQuatf result(x,y,z,0.0f);
  if(scale>0.0f){
    scale=theta/scale;
    result.x*=scale;
    result.y*=scale;
    result.z*=scale;
    }
  return result;
  }
