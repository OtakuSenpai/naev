/*
 * See Licensing and Copyright notice in naev.h
 */



#ifndef OUTFIT_H
#  define OUTFIT_H


#include "opengl.h"
#include "sound.h"


/*
 * properties
 */
#define outfit_isProp(o,p)          ((o)->properties & p) /**< Checks an outfit for property. */
/* property flags */
#define OUTFIT_PROP_WEAP_SECONDARY  (1<<0) /**< Is a secondary weapon? */


/**
 * @enum OutfitType
 *
 * @brief Different types of existing outfits.
 *
 * Outfits are organized by the order here 
 */
typedef enum OutfitType_ {
   OUTFIT_TYPE_NULL, /**< Null type. */
   OUTFIT_TYPE_BOLT, /**< @todo Fixed bolt cannon. */
   OUTFIT_TYPE_BEAM, /**< Fixed beam cannon. */
   OUTFIT_TYPE_TURRET_BOLT, /**< @todo Rotary bolt turret. */
   OUTFIT_TYPE_TURRET_BEAM, /**< Rotary beam turret. */
   OUTFIT_TYPE_MISSILE_DUMB, /**< Dumb missile launcher. */
   OUTFIT_TYPE_MISSILE_DUMB_AMMO, /**< Dumb missile ammo. */
   OUTFIT_TYPE_MISSILE_SEEK, /**< Seeker missile launcher. */
   OUTFIT_TYPE_MISSILE_SEEK_AMMO, /**< Seeker missile ammo. */
   OUTFIT_TYPE_MISSILE_SEEK_SMART, /**< ATM equivalent to SEEK */
   OUTFIT_TYPE_MISSILE_SEEK_SMART_AMMO, /** ATM equivalent to SEEK_AMMO */
   OUTFIT_TYPE_MISSILE_SWARM, /**< @todo Swarm missile launcher. */
   OUTFIT_TYPE_MISSILE_SWARM_AMMO, /**< @todo Swarm missile ammo. */
   OUTFIT_TYPE_MISSILE_SWARM_SMART, /**< @todo same as SWARM */
   OUTFIT_TYPE_MISSILE_SWARM_SMART_AMMO, /**< @todo same as SWARM_AMMO */
   OUTFIT_TYPE_MODIFCATION, /**< Modifies the ship base features. */
   OUTFIT_TYPE_AFTERBURNER, /**< Gives the ship afterburn capability. */
   OUTFIT_TYPE_JAMMER, /**< Used to nullify seeker missiles. */
   OUTFIT_TYPE_MAP, /**< Gives the player more knowledge about systems. */
   OUTFIT_TYPE_SENTINEL /**< indicates last type */
} OutfitType;


/**
 * @enum DamageType
 *
 * @brief Different types of damage.
 */
typedef enum DamageType_ {
   DAMAGE_TYPE_NULL, /**< NULL */
   DAMAGE_TYPE_ENERGY, /**< Energy-based weapons. */
   DAMAGE_TYPE_KINETIC, /**< Physic impact weapons. */
   DAMAGE_TYPE_ION, /**< Ion-based weapons. */
   DAMAGE_TYPE_RADIATION /**< Radioactive weapons. */
} DamageType;


/**
 * @struct OutfitBoltData
 *
 * @brief Represents the particular properties of a bolt weapon.
 */
typedef struct OutfitBoltData_ {
   unsigned int delay; /**< delay between shots */
   double speed; /**< how fast it goes (not applicable to beam) */
   double range; /**< how far it goes */
   double accuracy; /**< desviation accuracy */
   double energy; /**< energy usage */
   DamageType dtype; /**< damage type */
   double damage; /**< damage */

   glTexture* gfx_space; /**< graphic */
   int sound; /**< sound to play */
   int spfx; /**< special effect on hit */
} OutfitBoltData;

/**
 * @struct OutfitBeamData
 *
 * @brief Represents the particular properties of a beam weapon.
 */
typedef struct OutfitBeamData_ {
   double range; /**< how far it goes */
   glColour colour; /**< beam colour */
   double energy; /**< energy it drains */
   double dtype; /**< damage type */
   double damage; /**< damage */
} OutfitBeamData;

/**
 * @struct OutfitLauncherData
 *
 * @brief Represents a particular missile launcher.
 *
 * The properties of the weapon are highly dependent on the ammunition.
 */
typedef struct OutfitLauncherData_ {
   unsigned int delay; /**< delay between shots */
   char *ammo; /**< the ammo to use */
} OutfitLauncherData;

/**
 * @struct OutfitAmmoData
 *
 * @brief Represents ammunition for a launcher.
 */
typedef struct OutfitAmmoData_ {
   double duration; /**< How long the ammo lives. */
   double lockon; /**< time it takes to lock on the target */
   double resist; /**< lowers chance of jamming by this amount */

   double speed; /**< maximum speed */
   double turn; /**< turn velocity */
   double thrust; /**< acceleration */
   double energy; /**< energy usage */
   DamageType dtype; /**< damage type */
   double damage; /**< damage */

   glTexture* gfx_space; /**< graphic */
   int sound; /**< sound to play */
   int spfx; /**< special effect on hit */
} OutfitAmmoData;

/**
 * @struct OutfitModificationData
 *
 * @brief Represents a ship modification.
 *
 * These modify the ship's basic properties when equipped on a pilot.
 */
typedef struct OutfitModificationData_ {
   /* movement */
   double thrust; /**< Maximum thrust modifier. */
   double turn; /**< Maximum turn modifier. */
   double speed; /**< Maximum speed modifier. */

   /* health */
   double armour; /**< Maximum armour modifier. */
   double armour_regen; /**< Armour regeneration modifier. */
   double shield; /**< Maximum shield modifier. */
   double shield_regen; /**< Shield regeneration modifier. */
   double energy; /**< Maximum energy modifier. */
   double energy_regen; /**< Energy regeneration modifier. */
   double fuel; /**< Maximum fuel modifier. */

   /* misc */
   int cargo; /**< Cargo space modifier. */
} OutfitModificationData;

/**
 * @struct OutfitAfterburnerData
 *
 * @brief Represents an afterburner.
 */
typedef struct OutfitAfterburnerData_ {
   double rumble; /**< percent of rumble */
   int sound; /**< sound of the afterburner */
   double thrust_perc; /**< % of thrust increase based on ship base. */
   double thrust_abs; /**< Fixed absolute thrust increase. */
   double speed_perc; /**< % of speed to increase based on ship base. */
   double speed_abs; /**< Fixed absolute speed increase. */
   double energy; /**< Energy usage while active */
} OutfitAfterburnerData;

/**
 * @struct OutfitMapData
 *
 * @brief Represents a map, is not actually stored on a ship but put into the nav system.
 *
 * Basically just marks an amount of systems when the player buys it as known.
 */
typedef struct OutfitMapData_ {
   double radius; /**< Number of jumps to add all systems within. */
} OutfitMapData;

/**
 * @struct OutfitJammerData
 *
 * @brief Represents a jammer.
 */
typedef struct OutfitJammerData_ {
   double range; /**< Range it starts to do effect */
   double chance; /**< Chance of it nullifying the missile */
   double energy; /**< Energy it uses to run */
} OutfitJammerData;

/**
 * @struct Outfit
 *
 * @brief A ship outfit, depends radically on the type.
 */
typedef struct Outfit_ {
   char* name; /**< Name of the outfit. */

   /* general specs */
   int max; /**< Maximum amount one can own. */
   int tech; /**< Tech needed to sell it. */
   int mass; /**< How much weapon capacity is needed. */

   /* store stuff */
   unsigned int price; /**< Base sell price. */
   char* description; /**< Store description. */

   glTexture* gfx_store; /**< Store graphic. */

   unsigned int properties; /**< Properties stored bitwise. */

   /* Type dependent */
   OutfitType type; /**< Type of the outfit. */
   union {
      OutfitBoltData blt; /**< BOLT */
      OutfitBeamData bem; /**< BEAM */
      OutfitLauncherData lau; /**< MISSILE */
      OutfitAmmoData amm; /**< AMMO */
      OutfitModificationData mod; /**< MODIFICATION */
      OutfitAfterburnerData afb; /**< AFTERBURNER */
      OutfitJammerData jam; /**< JAMMER */
      OutfitMapData map; /**< MAP */
   } u; /**< Holds the type-based outfit data. */
} Outfit;


/*
 * misc
 */
void outfit_calcDamage( double *dshield, double *darmour, double *knockback,
      DamageType dtype, double dmg );


/*
 * get
 */
Outfit* outfit_get( const char* name );
char** outfit_getTech( int *n, const int *tech, const int techmax );
/* outfit types */
int outfit_isWeapon( const Outfit* o );
int outfit_isLauncher( const Outfit* o );
int outfit_isAmmo( const Outfit* o );
int outfit_isTurret( const Outfit* o );
int outfit_isMod( const Outfit* o );
int outfit_isAfterburner( const Outfit* o );
int outfit_isMap( const Outfit* o );
int outfit_isJammer( const Outfit* o );
const char* outfit_getType( const Outfit* o );
const char* outfit_getTypeBroad( const Outfit* o );

/*
 * get data from outfit
 */
glTexture* outfit_gfx( const Outfit* o );
int outfit_spfx( const Outfit* o );
double outfit_damage( const Outfit* o );
DamageType outfit_damageType( const Outfit* o );
int outfit_delay( const Outfit* o );
double outfit_energy( const Outfit* o );
double outfit_range( const Outfit* o );
double outfit_speed( const Outfit* o );
int outfit_isSeeker( const Outfit* o );

/*
 * loading/freeing outfit stack
 */
int outfit_load (void);
void outfit_free (void);


#endif /* OUTFIT_H */
