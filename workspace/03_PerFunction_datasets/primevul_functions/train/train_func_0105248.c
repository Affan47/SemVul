void CLASS setSonyBodyFeatures (unsigned id) {

  if (
      (id == 257) ||
      (id == 269) ||
      (id == 340) ||
      (id == 318) ||
      (id == 311) ||
      (id == 306) ||
      (id == 298) ||
      (id == 299) ||
      (id == 310) ||
      (id == 294)
      )
    {
      imgdata.lens.makernotes.CameraFormat = FF;
    }
  else
    {
      imgdata.lens.makernotes.CameraFormat = APSC;
    }

  if (

      (id == 302) ||
      (id == 306) ||
      (id == 311) ||
      (id == 312) ||
      (id == 313) ||
      (id == 318) ||
      (id == 339) ||
      (id == 340) ||
      (id == 346)	||

      (id == 278) ||
      (id == 279) ||
      (id == 284) ||
      (id == 288) ||
      (id == 289) ||
      (id == 290) ||
      (id == 293) ||
      (id == 295) ||
      (id == 296) ||
      (id == 299) ||
      (id == 300) ||
      (id == 305) ||
      (id == 307)
      )
    {
      imgdata.lens.makernotes.CameraMount = Sony_E;
    }

  else if (

           (id == 256) ||
           (id == 257) ||
           (id == 258) ||
           (id == 259) ||
           (id == 260) ||
           (id == 261) ||
           (id == 262) ||
           (id == 263) ||
           (id == 264) ||
           (id == 265) ||
           (id == 266) ||
           (id == 269) ||
           (id == 270) ||
           (id == 273) ||
           (id == 274) ||
           (id == 275) ||
           (id == 282) ||
           (id == 283)	||

           (id == 280) ||
           (id == 281) ||
           (id == 285) ||
           (id == 286) ||
           (id == 287) ||
           (id == 291) ||
           (id == 292) ||
           (id == 294) ||
           (id == 303)	||

           (id == 319)
           )
    {
      imgdata.lens.makernotes.CameraMount = Minolta_A;
    }

  else if (
           (id == 002) ||
           (id == 297) ||
           (id == 298) ||
           (id == 308) ||
           (id == 309) ||
           (id == 310) ||
           (id == 317)
           )
    {
      imgdata.lens.makernotes.CameraMount = FixedLens;
      imgdata.lens.makernotes.LensMount = FixedLens;
    }
  return;
}
