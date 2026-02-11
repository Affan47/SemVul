tiltEffect(uint8_t buffer[][3], bool reset)
{
  static int pitchid, rollid, thrust=-1;


  if (reset)
    {
        int i;
        for (i=0; i<NBR_LEDS; i++) {
            buffer[i][0] = 0;
            buffer[i][1] = 0;
            buffer[i][2] = 0;
        }
    }


  if (thrust<0) {

    pitchid = logGetVarId("stabilizer", "pitch");
    rollid = logGetVarId("stabilizer", "roll");
    thrust = logGetVarId("stabilizer", "thrust");
  } else {
    const int led_middle = 10;
    float pitch = -1*logGetFloat(pitchid);
    float roll  = -1*logGetFloat(rollid);

    pitch = (pitch>20)?20:(pitch<-20)?-20:pitch;
    roll = (roll>20)?20:(roll<-20)?-20:roll;

    pitch=SIGN(pitch)*pitch*pitch;
    roll*=SIGN(roll)*roll;

    buffer[11][0] = LIMIT(led_middle + pitch);
    buffer[0][0] = LIMIT(led_middle + pitch);
    buffer[1][0] = LIMIT(led_middle + pitch);

    buffer[2][2] = LIMIT(led_middle - roll);
    buffer[3][2] = LIMIT(led_middle - roll);
    buffer[4][2] = LIMIT(led_middle - roll);

    buffer[5][0] = LIMIT(led_middle - pitch);
    buffer[6][0] = LIMIT(led_middle - pitch);
    buffer[7][0] = LIMIT(led_middle - pitch);

    buffer[8][2] = LIMIT(led_middle + roll);
    buffer[9][2] = LIMIT(led_middle + roll);
    buffer[10][2] = LIMIT(led_middle + roll);
  }
}
