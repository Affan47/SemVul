get_enemy_surfaces_data(char *DataPointer)
{
	char *SurfacePointer;
	char *EndOfSurfaceData;
	int SurfaceIndex = 0;

#define ENEMY_SURFACES_SECTION_BEGIN_STRING "*** Start of Enemy Surfaces Section: ***"
#define ENEMY_SURFACES_SECTION_END_STRING "*** End of Enemy Surfaces Section: ***"
#define NEW_SURFACE_BEGIN_STRING "** Start of new surface specification subsection **"

#define SURFACES_FILE_NAME_BEGIN_STRING "PrefixToFilename=\""
#define SURFACES_WALK_ANI_SPEED_BEGIN_STRING "droid_walk_animation_speed_factor="
#define SURFACES_ATTACK_ANI_SPEED_BEGIN_STRING "droid_attack_animation_speed_factor="
#define SURFACES_GETHIT_ANI_SPEED_BEGIN_STRING "droid_gethit_animation_speed_factor="
#define SURFACES_DEATH_ANI_SPEED_BEGIN_STRING "droid_death_animation_speed_factor="
#define SURFACES_STAND_ANI_SPEED_BEGIN_STRING "droid_stand_animation_speed_factor="


	EndOfSurfaceData = LocateStringInData(DataPointer, ENEMY_SURFACES_SECTION_END_STRING);

 	DebugPrintf(1, "\n\nStarting to read surfaces data...\n\n");

	SurfacePointer = DataPointer;

	while ((SurfacePointer = strstr(SurfacePointer, NEW_SURFACE_BEGIN_STRING)) != NULL) {
		if (SurfaceIndex >= ENEMY_ROTATION_MODELS_AVAILABLE) {
			ErrorMessage(__FUNCTION__, "enemy_surfaces.dat specifies more surfaces than ENEMY_ROTATION_MODELS_AVAILABLE (%d) allows.", PLEASE_INFORM, IS_FATAL, ENEMY_ROTATION_MODELS_AVAILABLE);
		}

 		DebugPrintf(1, "\n\nFound another surface specification entry!  Lets add that to the others!");
		SurfacePointer++;

		PrefixToFilename[SurfaceIndex] = ReadAndMallocStringFromData(SurfacePointer, SURFACES_FILE_NAME_BEGIN_STRING, "\"");

		ReadValueFromStringWithDefault(SurfacePointer, SURFACES_WALK_ANI_SPEED_BEGIN_STRING,
			"%d", "0", &(droid_walk_animation_speed_factor[SurfaceIndex]), EndOfSurfaceData);
		ReadValueFromStringWithDefault(SurfacePointer, SURFACES_ATTACK_ANI_SPEED_BEGIN_STRING,
			"%d", "0", &(droid_attack_animation_speed_factor[SurfaceIndex]), EndOfSurfaceData);
		ReadValueFromStringWithDefault(SurfacePointer, SURFACES_GETHIT_ANI_SPEED_BEGIN_STRING,
			"%d", "0", &(droid_gethit_animation_speed_factor[SurfaceIndex]), EndOfSurfaceData);
		ReadValueFromStringWithDefault(SurfacePointer, SURFACES_DEATH_ANI_SPEED_BEGIN_STRING,
			"%d", "0", &(droid_death_animation_speed_factor[SurfaceIndex]), EndOfSurfaceData);
		ReadValueFromStringWithDefault(SurfacePointer, SURFACES_STAND_ANI_SPEED_BEGIN_STRING,
			"%d", "0", &(droid_stand_animation_speed_factor[SurfaceIndex]), EndOfSurfaceData);

		SurfaceIndex++;
	}

 	DebugPrintf(1, "\nEnd of get_enemy_surfaces_data ( char* DataPointer ) reached.");
}
