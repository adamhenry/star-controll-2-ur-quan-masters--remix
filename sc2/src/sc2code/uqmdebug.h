/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#if !defined(_DEBUG_H) && (defined(DEBUG) || defined(USE_DEBUG_KEY))
#define _DEBUG_H

#include "clock.h"
#include "planets/planets.h"
#include "races.h"
#include "libs/compiler.h"

#include <stdio.h>


// If set to true, interactive routines that are called (indirectly) in debug
// functions are a no-op.
extern BOOLEAN disableInteractivity;

// If a function is assigned to this, it will be called from the main loop.
extern void (* volatile debugHook) (void);


// Called when the debug key (symbol 'Debug' in the keys.cfg) is pressed.
void debugKeyPressed (void);

// Forward time to the next event. If skipHEE is set, the event named
// HYPERSPACE_ENCOUNTER_EVENT, which normally occurs every game day,
// is skipped.
void forwardToNextEvent (BOOLEAN skipHEE);
// Generate a list of all events in the event queue.
void dumpEvents (FILE *out);
// Describe one event.
void dumpEvent (FILE *out, EVENTPTR eventPtr);
// Get the name of one event.
const char *eventName (BYTE func_index);

// Give the flagship a decent equipment for debugging.
void equipShip (void);

// Show all active spheres of influence.
void showSpheres (void);

// Make the ships of all races available for building at the shipyard.
void activateAllShips (void);

// Move the Flagship to the destination of the autopilot.
// Should only be called from HS/QS.
// It can be called from debugHook directly after entering HS/QS though.
void doInstantMove (void);


// Call a function for all stars.
void forAllStars (void (*callback) (STAR_DESC *, void *), void *arg);
// Call a function for all planets in a star system.
void forAllPlanets (STAR_DESC *star, SOLARSYS_STATE *system,
		void (*callback) (STAR_DESC *, SOLARSYS_STATE *, PLANET_DESC *,
		void *), void *arg);
// Call a function for all moons of a planet.
void forAllMoons (STAR_DESC *star, SOLARSYS_STATE *system, PLANET_DESC *planet,
		void (*callback) (STAR_DESC *, SOLARSYS_STATE *, PLANET_DESC *,
		PLANET_DESC *, void *), void *arg);

// Argument to UniverseRecurse()
typedef struct
{
	void (*systemFunc) (const STAR_DESC *star, const SOLARSYS_STATE *system,
			void *arg);
	void (*planetFunc) (const PLANET_DESC *planet, void *arg);
	void (*moonFunc) (const PLANET_DESC *moon, void *arg);
	void *arg;
} UniverseRecurseArg;
// Recurse through all systems, planets, and moons in the universe.
void UniverseRecurse (UniverseRecurseArg *universeRecurseArg);

// Describe the entire universe.
void dumpUniverse (FILE *out);
// Describe the entire universe, output to a file "./PlanetInfo".
void dumpUniverseToFile (void);
// Describe one star system.
void dumpSystem (FILE *out, const STAR_DESC *star,
		const SOLARSYS_STATE *system);
// Get a star color as a string.
const char *bodyColorString (BYTE col);
// Get a star type as a string.
const char *starTypeString (BYTE type);
// Get a string describing special presence in the star system.
const char *starPresenceString (BYTE index);
// Get a list describing all planets in a star.
void dumpPlanets (FILE *out, const STAR_DESC *star);
// Describe one planet.
void dumpPlanet(FILE *out, const PLANET_DESC *planet);
// Describe one moon.
void dumpMoon (FILE *out, const PLANET_DESC *moon);
// Calculate the total value of all minerals on a world.
COUNT calculateMineralValue (const SOLARSYS_STATE *system,
		const PLANET_DESC *world);
// Determine how much of each mineral type is present on a world
void generateMineralIndex(const SOLARSYS_STATE *system,
		const PLANET_DESC *world, COUNT minerals[]);
// Calculate the total value of all bio on a world.
COUNT calculateBioValue (const SOLARSYS_STATE *system,
		const PLANET_DESC *world);
// Determine how much of each mineral type is present on a world
void generateBioIndex(const SOLARSYS_STATE *system,
		const PLANET_DESC *world, COUNT bio[]);


// Call a function for all planet types.
void forAllPlanetTypes (void (*callBack) (int, const PlanetFrame *,
		void *), void *arg);
// Describe one planet type.
void dumpPlanetType(FILE *out, int index, const PlanetFrame *planetFrame);
// Generate a list of all planet types.
void dumpPlanetTypes(FILE *out);
// Get a string describing a planet type.
const char *planetTypeString (int typeIndex);
// Get a string describing the size of a type of planet.
const char *worldSizeString (BYTE size);
// Get a string describing a planet type map generation algoritm.
const char *worldGenAlgoString (BYTE algo);
// Get a string describing the severity of a tectonics on a type of planet.
const char *tectonicsString (BYTE tectonics);
// Get a string describing the atmospheric pressure on a type of planet.
const char *atmosphereString (BYTE atmosphere);
// Get a string describing the density of a type of planet.
const char *densityString (BYTE density);

// Get a string describing the quality of a deposit.
const char *depositQualityString (BYTE quality);


// Find a player ship. Setting which to BAD_GUY is only meaningful in battle.
STARSHIPPTR findPlayerShip(ELEMENT_FLAGS which);

// Resets the crew of the first player (the bottom one) to its maximum.
void resetCrewBattle(void);

// Resets the energy of the first player (the bottom one) to its maximum.
void resetEnergyBattle(void);


// Move instantly across hyperspace/quasispace.
extern BOOLEAN instantMove;

// To add some day:
// - a function to fast forward the game clock to a specifiable time.

#endif  /* _DEBUG_H */

