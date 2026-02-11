gravityLight(uint8_t buffer[][3], bool reset)
{
  static int pitchid, rollid;
  static bool isInitialized = false;

  if (!isInitialized) {
    pitchid = logGetVarId("stabilizer", "pitch");
    rollid = logGetVarId("stabilizer", "roll");
    isInitialized = true;
  }

  float pitch = logGetFloat(pitchid);
  float roll = logGetFloat(rollid);

  float angle = gravityLightCalculateAngle(pitch, roll);
  float led_index = NBR_LEDS * angle / (2 * (float) M_PI);
  int intensity = LIMIT(sqrtf(pitch * pitch + roll * roll));
  gravityLightRender(buffer, led_index, intensity);
}
