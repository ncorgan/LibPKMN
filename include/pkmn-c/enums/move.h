/*
 * Copyright (c) 2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef PKMN_C_ENUMS_MOVE_H
#define PKMN_C_ENUMS_MOVE_H

enum pkmn_move
{
    PKMN_MOVE_NONE = 0,
    PKMN_MOVE_POUND = 1,
    PKMN_MOVE_KARATE_CHOP = 2,
    PKMN_MOVE_DOUBLE_SLAP = 3,
    PKMN_MOVE_COMET_PUNCH = 4,
    PKMN_MOVE_MEGA_PUNCH = 5,
    PKMN_MOVE_PAY_DAY = 6,
    PKMN_MOVE_FIRE_PUNCH = 7,
    PKMN_MOVE_ICE_PUNCH = 8,
    PKMN_MOVE_THUNDER_PUNCH = 9,
    PKMN_MOVE_SCRATCH = 10,
    PKMN_MOVE_VICE_GRIP = 11,
    PKMN_MOVE_GUILLOTINE = 12,
    PKMN_MOVE_RAZOR_WIND = 13,
    PKMN_MOVE_SWORDS_DANCE = 14,
    PKMN_MOVE_CUT = 15,
    PKMN_MOVE_GUST = 16,
    PKMN_MOVE_WING_ATTACK = 17,
    PKMN_MOVE_WHIRLWIND = 18,
    PKMN_MOVE_FLY = 19,
    PKMN_MOVE_BIND = 20,
    PKMN_MOVE_SLAM = 21,
    PKMN_MOVE_VINE_WHIP = 22,
    PKMN_MOVE_STOMP = 23,
    PKMN_MOVE_DOUBLE_KICK = 24,
    PKMN_MOVE_MEGA_KICK = 25,
    PKMN_MOVE_JUMP_KICK = 26,
    PKMN_MOVE_ROLLING_KICK = 27,
    PKMN_MOVE_SAND_ATTACK = 28,
    PKMN_MOVE_HEADBUTT = 29,
    PKMN_MOVE_HORN_ATTACK = 30,
    PKMN_MOVE_FURY_ATTACK = 31,
    PKMN_MOVE_HORN_DRILL = 32,
    PKMN_MOVE_TACKLE = 33,
    PKMN_MOVE_BODY_SLAM = 34,
    PKMN_MOVE_WRAP = 35,
    PKMN_MOVE_TAKE_DOWN = 36,
    PKMN_MOVE_THRASH = 37,
    PKMN_MOVE_DOUBLE_EDGE = 38,
    PKMN_MOVE_TAIL_WHIP = 39,
    PKMN_MOVE_POISON_STING = 40,
    PKMN_MOVE_TWINEEDLE = 41,
    PKMN_MOVE_PIN_MISSILE = 42,
    PKMN_MOVE_LEER = 43,
    PKMN_MOVE_BITE = 44,
    PKMN_MOVE_GROWL = 45,
    PKMN_MOVE_ROAR = 46,
    PKMN_MOVE_SING_MOVE = 47,
    PKMN_MOVE_SUPERSONIC = 48,
    PKMN_MOVE_SONIC_BOOM = 49,
    PKMN_MOVE_DISABLE = 50,
    PKMN_MOVE_ACID = 51,
    PKMN_MOVE_EMBER = 52,
    PKMN_MOVE_FLAMETHROWER = 53,
    PKMN_MOVE_MIST = 54,
    PKMN_MOVE_WATER_GUN = 55,
    PKMN_MOVE_HYDRO_PUMP = 56,
    PKMN_MOVE_SURF = 57,
    PKMN_MOVE_ICE_BEAM = 58,
    PKMN_MOVE_BLIZZARD = 59,
    PKMN_MOVE_PSYBEAM = 60,
    PKMN_MOVE_BUBBLE_BEAM = 61,
    PKMN_MOVE_AURORA_BEAM = 62,
    PKMN_MOVE_HYPER_BEAM = 63,
    PKMN_MOVE_PECK = 64,
    PKMN_MOVE_DRILL_PECK = 65,
    PKMN_MOVE_SUBMISSION = 66,
    PKMN_MOVE_LOW_KICK = 67,
    PKMN_MOVE_COUNTER = 68,
    PKMN_MOVE_SEISMIC_TOSS = 69,
    PKMN_MOVE_STRENGTH = 70,
    PKMN_MOVE_ABSORB = 71,
    PKMN_MOVE_MEGA_DRAIN = 72,
    PKMN_MOVE_LEECH_SEED = 73,
    PKMN_MOVE_GROWTH = 74,
    PKMN_MOVE_RAZOR_LEAF = 75,
    PKMN_MOVE_SOLAR_BEAM = 76,
    PKMN_MOVE_POISON_POWDER = 77,
    PKMN_MOVE_STUN_SPORE = 78,
    PKMN_MOVE_SLEEP_POWDER = 79,
    PKMN_MOVE_PETAL_DANCE = 80,
    PKMN_MOVE_STRING_SHOT = 81,
    PKMN_MOVE_DRAGON_RAGE = 82,
    PKMN_MOVE_FIRE_SPIN = 83,
    PKMN_MOVE_THUNDER_SHOCK = 84,
    PKMN_MOVE_THUNDERBOLT = 85,
    PKMN_MOVE_THUNDER_WAVE = 86,
    PKMN_MOVE_THUNDER = 87,
    PKMN_MOVE_ROCK_THROW = 88,
    PKMN_MOVE_EARTHQUAKE = 89,
    PKMN_MOVE_FISSURE = 90,
    PKMN_MOVE_DIG = 91,
    PKMN_MOVE_TOXIC = 92,
    PKMN_MOVE_CONFUSION = 93,
    PKMN_MOVE_PSYCHIC = 94,
    PKMN_MOVE_HYPNOSIS = 95,
    PKMN_MOVE_MEDITATE = 96,
    PKMN_MOVE_AGILITY = 97,
    PKMN_MOVE_QUICK_ATTACK = 98,
    PKMN_MOVE_RAGE = 99,
    PKMN_MOVE_TELEPORT = 100,
    PKMN_MOVE_NIGHT_SHADE = 101,
    PKMN_MOVE_MIMIC = 102,
    PKMN_MOVE_SCREECH = 103,
    PKMN_MOVE_DOUBLE_TEAM = 104,
    PKMN_MOVE_RECOVER = 105,
    PKMN_MOVE_HARDEN = 106,
    PKMN_MOVE_MINIMIZE = 107,
    PKMN_MOVE_SMOKESCREEN = 108,
    PKMN_MOVE_CONFUSE_RAY = 109,
    PKMN_MOVE_WITHDRAW = 110,
    PKMN_MOVE_DEFENSE_CURL = 111,
    PKMN_MOVE_BARRIER = 112,
    PKMN_MOVE_LIGHT_SCREEN = 113,
    PKMN_MOVE_HAZE = 114,
    PKMN_MOVE_REFLECT = 115,
    PKMN_MOVE_FOCUS_ENERGY = 116,
    PKMN_MOVE_BIDE = 117,
    PKMN_MOVE_METRONOME = 118,
    PKMN_MOVE_MIRROR_MOVE = 119,
    PKMN_MOVE_SELF_DESTRUCT = 120,
    PKMN_MOVE_EGG_BOMB = 121,
    PKMN_MOVE_LICK = 122,
    PKMN_MOVE_SMOG = 123,
    PKMN_MOVE_SLUDGE = 124,
    PKMN_MOVE_BONE_CLUB = 125,
    PKMN_MOVE_FIRE_BLAST = 126,
    PKMN_MOVE_WATERFALL = 127,
    PKMN_MOVE_CLAMP = 128,
    PKMN_MOVE_SWIFT = 129,
    PKMN_MOVE_SKULL_BASH = 130,
    PKMN_MOVE_SPIKE_CANNON = 131,
    PKMN_MOVE_CONSTRICT = 132,
    PKMN_MOVE_AMNESIA = 133,
    PKMN_MOVE_KINESIS = 134,
    PKMN_MOVE_SOFT_BOILED = 135,
    PKMN_MOVE_HIGH_JUMP_KICK = 136,
    PKMN_MOVE_GLARE = 137,
    PKMN_MOVE_DREAM_EATER = 138,
    PKMN_MOVE_POISON_GAS = 139,
    PKMN_MOVE_BARRAGE = 140,
    PKMN_MOVE_LEECH_LIFE = 141,
    PKMN_MOVE_LOVELY_KISS = 142,
    PKMN_MOVE_SKY_ATTACK = 143,
    PKMN_MOVE_TRANSFORM = 144,
    PKMN_MOVE_BUBBLE = 145,
    PKMN_MOVE_DIZZY_PUNCH = 146,
    PKMN_MOVE_SPORE = 147,
    PKMN_MOVE_FLASH = 148,
    PKMN_MOVE_PSYWAVE = 149,
    PKMN_MOVE_SPLASH = 150,
    PKMN_MOVE_ACID_ARMOR = 151,
    PKMN_MOVE_CRABHAMMER = 152,
    PKMN_MOVE_EXPLOSION = 153,
    PKMN_MOVE_FURY_SWIPES = 154,
    PKMN_MOVE_BONEMERANG = 155,
    PKMN_MOVE_REST = 156,
    PKMN_MOVE_ROCK_SLIDE = 157,
    PKMN_MOVE_HYPER_FANG = 158,
    PKMN_MOVE_SHARPEN = 159,
    PKMN_MOVE_CONVERSION = 160,
    PKMN_MOVE_TRI_ATTACK = 161,
    PKMN_MOVE_SUPER_FANG = 162,
    PKMN_MOVE_SLASH = 163,
    PKMN_MOVE_SUBSTITUTE = 164,
    PKMN_MOVE_STRUGGLE = 165,
    PKMN_MOVE_SKETCH = 166,
    PKMN_MOVE_TRIPLE_KICK = 167,
    PKMN_MOVE_THIEF = 168,
    PKMN_MOVE_SPIDER_WEB = 169,
    PKMN_MOVE_MIND_READER = 170,
    PKMN_MOVE_NIGHTMARE = 171,
    PKMN_MOVE_FLAME_WHEEL = 172,
    PKMN_MOVE_SNORE = 173,
    PKMN_MOVE_CURSE = 174,
    PKMN_MOVE_FLAIL = 175,
    PKMN_MOVE_CONVERSION_2 = 176,
    PKMN_MOVE_AEROBLAST = 177,
    PKMN_MOVE_COTTON_SPORE = 178,
    PKMN_MOVE_REVERSAL = 179,
    PKMN_MOVE_SPITE = 180,
    PKMN_MOVE_POWDER_SNOW = 181,
    PKMN_MOVE_PROTECT = 182,
    PKMN_MOVE_MACH_PUNCH = 183,
    PKMN_MOVE_SCARY_FACE = 184,
    PKMN_MOVE_FEINT_ATTACK = 185,
    PKMN_MOVE_SWEET_KISS = 186,
    PKMN_MOVE_BELLY_DRUM = 187,
    PKMN_MOVE_SLUDGE_BOMB = 188,
    PKMN_MOVE_MUD_SLAP = 189,
    PKMN_MOVE_OCTAZOOKA = 190,
    PKMN_MOVE_SPIKES = 191,
    PKMN_MOVE_ZAP_CANNON = 192,
    PKMN_MOVE_FORESIGHT = 193,
    PKMN_MOVE_DESTINY_BOND = 194,
    PKMN_MOVE_PERISH_SONG = 195,
    PKMN_MOVE_ICY_WIND = 196,
    PKMN_MOVE_DETECT = 197,
    PKMN_MOVE_BONE_RUSH = 198,
    PKMN_MOVE_LOCK_ON = 199,
    PKMN_MOVE_OUTRAGE = 200,
    PKMN_MOVE_SANDSTORM = 201,
    PKMN_MOVE_GIGA_DRAIN = 202,
    PKMN_MOVE_ENDURE = 203,
    PKMN_MOVE_CHARM = 204,
    PKMN_MOVE_ROLLOUT = 205,
    PKMN_MOVE_FALSE_SWIPE = 206,
    PKMN_MOVE_SWAGGER = 207,
    PKMN_MOVE_MILK_DRINK = 208,
    PKMN_MOVE_SPARK = 209,
    PKMN_MOVE_FURY_CUTTER = 210,
    PKMN_MOVE_STEEL_WING = 211,
    PKMN_MOVE_MEAN_LOOK = 212,
    PKMN_MOVE_ATTRACT = 213,
    PKMN_MOVE_SLEEP_TALK = 214,
    PKMN_MOVE_HEAL_BELL = 215,
    PKMN_MOVE_RETURN = 216,
    PKMN_MOVE_PRESENT = 217,
    PKMN_MOVE_FRUSTRATION = 218,
    PKMN_MOVE_SAFEGUARD = 219,
    PKMN_MOVE_PAIN_SPLIT = 220,
    PKMN_MOVE_SACRED_FIRE = 221,
    PKMN_MOVE_MAGNITUDE = 222,
    PKMN_MOVE_DYNAMIC_PUNCH = 223,
    PKMN_MOVE_MEGAHORN = 224,
    PKMN_MOVE_DRAGON_BREATH = 225,
    PKMN_MOVE_BATON_PASS = 226,
    PKMN_MOVE_ENCORE = 227,
    PKMN_MOVE_PURSUIT = 228,
    PKMN_MOVE_RAPID_SPIN = 229,
    PKMN_MOVE_SWEET_SCENT = 230,
    PKMN_MOVE_IRON_TAIL = 231,
    PKMN_MOVE_METAL_CLAW = 232,
    PKMN_MOVE_VITAL_THROW = 233,
    PKMN_MOVE_MORNING_SUN = 234,
    PKMN_MOVE_SYNTHESIS = 235,
    PKMN_MOVE_MOONLIGHT = 236,
    PKMN_MOVE_HIDDEN_POWER = 237,
    PKMN_MOVE_CROSS_CHOP = 238,
    PKMN_MOVE_TWISTER = 239,
    PKMN_MOVE_RAIN_DANCE = 240,
    PKMN_MOVE_SUNNY_DAY = 241,
    PKMN_MOVE_CRUNCH = 242,
    PKMN_MOVE_MIRROR_COAT = 243,
    PKMN_MOVE_PSYCH_UP = 244,
    PKMN_MOVE_EXTREME_SPEED = 245,
    PKMN_MOVE_ANCIENT_POWER = 246,
    PKMN_MOVE_SHADOW_BALL = 247,
    PKMN_MOVE_FUTURE_SIGHT = 248,
    PKMN_MOVE_ROCK_SMASH = 249,
    PKMN_MOVE_WHIRLPOOL = 250,
    PKMN_MOVE_BEAT_UP = 251,
    PKMN_MOVE_FAKE_OUT = 252,
    PKMN_MOVE_UPROAR = 253,
    PKMN_MOVE_STOCKPILE = 254,
    PKMN_MOVE_SPIT_UP = 255,
    PKMN_MOVE_SWALLOW = 256,
    PKMN_MOVE_HEAT_WAVE = 257,
    PKMN_MOVE_HAIL = 258,
    PKMN_MOVE_TORMENT = 259,
    PKMN_MOVE_FLATTER = 260,
    PKMN_MOVE_WILL_O_WISP = 261,
    PKMN_MOVE_MEMENTO = 262,
    PKMN_MOVE_FACADE = 263,
    PKMN_MOVE_FOCUS_PUNCH = 264,
    PKMN_MOVE_SMELLING_SALTS = 265,
    PKMN_MOVE_FOLLOW_ME = 266,
    PKMN_MOVE_NATURE_POWER = 267,
    PKMN_MOVE_CHARGE = 268,
    PKMN_MOVE_TAUNT = 269,
    PKMN_MOVE_HELPING_HAND = 270,
    PKMN_MOVE_TRICK = 271,
    PKMN_MOVE_ROLE_PLAY = 272,
    PKMN_MOVE_WISH = 273,
    PKMN_MOVE_ASSIST = 274,
    PKMN_MOVE_INGRAIN = 275,
    PKMN_MOVE_SUPERPOWER = 276,
    PKMN_MOVE_MAGIC_COAT = 277,
    PKMN_MOVE_RECYCLE = 278,
    PKMN_MOVE_REVENGE = 279,
    PKMN_MOVE_BRICK_BREAK = 280,
    PKMN_MOVE_YAWN = 281,
    PKMN_MOVE_KNOCK_OFF = 282,
    PKMN_MOVE_ENDEAVOR = 283,
    PKMN_MOVE_ERUPTION = 284,
    PKMN_MOVE_SKILL_SWAP = 285,
    PKMN_MOVE_IMPRISON = 286,
    PKMN_MOVE_REFRESH = 287,
    PKMN_MOVE_GRUDGE = 288,
    PKMN_MOVE_SNATCH = 289,
    PKMN_MOVE_SECRET_POWER = 290,
    PKMN_MOVE_DIVE = 291,
    PKMN_MOVE_ARM_THRUST = 292,
    PKMN_MOVE_CAMOUFLAGE = 293,
    PKMN_MOVE_TAIL_GLOW = 294,
    PKMN_MOVE_LUSTER_PURGE = 295,
    PKMN_MOVE_MIST_BALL = 296,
    PKMN_MOVE_FEATHER_DANCE = 297,
    PKMN_MOVE_TEETER_DANCE = 298,
    PKMN_MOVE_BLAZE_KICK = 299,
    PKMN_MOVE_MUD_SPORT = 300,
    PKMN_MOVE_ICE_BALL = 301,
    PKMN_MOVE_NEEDLE_ARM = 302,
    PKMN_MOVE_SLACK_OFF = 303,
    PKMN_MOVE_HYPER_VOICE = 304,
    PKMN_MOVE_POISON_FANG = 305,
    PKMN_MOVE_CRUSH_CLAW = 306,
    PKMN_MOVE_BLAST_BURN = 307,
    PKMN_MOVE_HYDRO_CANNON = 308,
    PKMN_MOVE_METEOR_MASH = 309,
    PKMN_MOVE_ASTONISH = 310,
    PKMN_MOVE_WEATHER_BALL = 311,
    PKMN_MOVE_AROMATHERAPY = 312,
    PKMN_MOVE_FAKE_TEARS = 313,
    PKMN_MOVE_AIR_CUTTER = 314,
    PKMN_MOVE_OVERHEAT = 315,
    PKMN_MOVE_ODOR_SLEUTH = 316,
    PKMN_MOVE_ROCK_TOMB = 317,
    PKMN_MOVE_SILVER_WIND = 318,
    PKMN_MOVE_METAL_SOUND = 319,
    PKMN_MOVE_GRASS_WHISTLE = 320,
    PKMN_MOVE_TICKLE = 321,
    PKMN_MOVE_COSMIC_POWER = 322,
    PKMN_MOVE_WATER_SPOUT = 323,
    PKMN_MOVE_SIGNAL_BEAM = 324,
    PKMN_MOVE_SHADOW_PUNCH = 325,
    PKMN_MOVE_EXTRASENSORY = 326,
    PKMN_MOVE_SKY_UPPERCUT = 327,
    PKMN_MOVE_SAND_TOMB = 328,
    PKMN_MOVE_SHEER_COLD = 329,
    PKMN_MOVE_MUDDY_WATER = 330,
    PKMN_MOVE_BULLET_SEED = 331,
    PKMN_MOVE_AERIAL_ACE = 332,
    PKMN_MOVE_ICICLE_SPEAR = 333,
    PKMN_MOVE_IRON_DEFENSE = 334,
    PKMN_MOVE_BLOCK = 335,
    PKMN_MOVE_HOWL = 336,
    PKMN_MOVE_DRAGON_CLAW = 337,
    PKMN_MOVE_FRENZY_PLANT = 338,
    PKMN_MOVE_BULK_UP = 339,
    PKMN_MOVE_BOUNCE = 340,
    PKMN_MOVE_MUD_SHOT = 341,
    PKMN_MOVE_POISON_TAIL = 342,
    PKMN_MOVE_COVET = 343,
    PKMN_MOVE_VOLT_TACKLE = 344,
    PKMN_MOVE_MAGICAL_LEAF = 345,
    PKMN_MOVE_WATER_SPORT = 346,
    PKMN_MOVE_CALM_MIND = 347,
    PKMN_MOVE_LEAF_BLADE = 348,
    PKMN_MOVE_DRAGON_DANCE = 349,
    PKMN_MOVE_ROCK_BLAST = 350,
    PKMN_MOVE_SHOCK_WAVE = 351,
    PKMN_MOVE_WATER_PULSE = 352,
    PKMN_MOVE_DOOM_DESIRE = 353,
    PKMN_MOVE_PSYCHO_BOOST = 354,
    PKMN_MOVE_ROOST = 355,
    PKMN_MOVE_GRAVITY = 356,
    PKMN_MOVE_MIRACLE_EYE = 357,
    PKMN_MOVE_WAKE_UP_SLAP = 358,
    PKMN_MOVE_HAMMER_ARM = 359,
    PKMN_MOVE_GYRO_BALL = 360,
    PKMN_MOVE_HEALING_WISH = 361,
    PKMN_MOVE_BRINE = 362,
    PKMN_MOVE_NATURAL_GIFT = 363,
    PKMN_MOVE_FEINT = 364,
    PKMN_MOVE_PLUCK = 365,
    PKMN_MOVE_TAILWIND = 366,
    PKMN_MOVE_ACUPRESSURE = 367,
    PKMN_MOVE_METAL_BURST = 368,
    PKMN_MOVE_U_TURN = 369,
    PKMN_MOVE_CLOSE_COMBAT = 370,
    PKMN_MOVE_PAYBACK = 371,
    PKMN_MOVE_ASSURANCE = 372,
    PKMN_MOVE_EMBARGO = 373,
    PKMN_MOVE_FLING = 374,
    PKMN_MOVE_PSYCHO_SHIFT = 375,
    PKMN_MOVE_TRUMP_CARD = 376,
    PKMN_MOVE_HEAL_BLOCK = 377,
    PKMN_MOVE_WRING_OUT = 378,
    PKMN_MOVE_POWER_TRICK = 379,
    PKMN_MOVE_GASTRO_ACID = 380,
    PKMN_MOVE_LUCKY_CHANT = 381,
    PKMN_MOVE_ME_FIRST = 382,
    PKMN_MOVE_COPYCAT = 383,
    PKMN_MOVE_POWER_SWAP = 384,
    PKMN_MOVE_GUARD_SWAP = 385,
    PKMN_MOVE_PUNISHMENT = 386,
    PKMN_MOVE_LAST_RESORT = 387,
    PKMN_MOVE_WORRY_SEED = 388,
    PKMN_MOVE_SUCKER_PUNCH = 389,
    PKMN_MOVE_TOXIC_SPIKES = 390,
    PKMN_MOVE_HEART_SWAP = 391,
    PKMN_MOVE_AQUA_RING = 392,
    PKMN_MOVE_MAGNET_RISE = 393,
    PKMN_MOVE_FLARE_BLITZ = 394,
    PKMN_MOVE_FORCE_PALM = 395,
    PKMN_MOVE_AURA_SPHERE = 396,
    PKMN_MOVE_ROCK_POLISH = 397,
    PKMN_MOVE_POISON_JAB = 398,
    PKMN_MOVE_DARK_PULSE = 399,
    PKMN_MOVE_NIGHT_SLASH = 400,
    PKMN_MOVE_AQUA_TAIL = 401,
    PKMN_MOVE_SEED_BOMB = 402,
    PKMN_MOVE_AIR_SLASH = 403,
    PKMN_MOVE_X_SCISSOR = 404,
    PKMN_MOVE_BUG_BUZZ = 405,
    PKMN_MOVE_DRAGON_PULSE = 406,
    PKMN_MOVE_DRAGON_RUSH = 407,
    PKMN_MOVE_POWER_GEM = 408,
    PKMN_MOVE_DRAIN_PUNCH = 409,
    PKMN_MOVE_VACUUM_WAVE = 410,
    PKMN_MOVE_FOCUS_BLAST = 411,
    PKMN_MOVE_ENERGY_BALL = 412,
    PKMN_MOVE_BRAVE_BIRD = 413,
    PKMN_MOVE_EARTH_POWER = 414,
    PKMN_MOVE_SWITCHEROO = 415,
    PKMN_MOVE_GIGA_IMPACT = 416,
    PKMN_MOVE_NASTY_PLOT = 417,
    PKMN_MOVE_BULLET_PUNCH = 418,
    PKMN_MOVE_AVALANCHE = 419,
    PKMN_MOVE_ICE_SHARD = 420,
    PKMN_MOVE_SHADOW_CLAW = 421,
    PKMN_MOVE_THUNDER_FANG = 422,
    PKMN_MOVE_ICE_FANG = 423,
    PKMN_MOVE_FIRE_FANG = 424,
    PKMN_MOVE_SHADOW_SNEAK = 425,
    PKMN_MOVE_MUD_BOMB = 426,
    PKMN_MOVE_PSYCHO_CUT = 427,
    PKMN_MOVE_ZEN_HEADBUTT = 428,
    PKMN_MOVE_MIRROR_SHOT = 429,
    PKMN_MOVE_FLASH_CANNON = 430,
    PKMN_MOVE_ROCK_CLIMB = 431,
    PKMN_MOVE_DEFOG = 432,
    PKMN_MOVE_TRICK_ROOM = 433,
    PKMN_MOVE_DRACO_METEOR = 434,
    PKMN_MOVE_DISCHARGE = 435,
    PKMN_MOVE_LAVA_PLUME = 436,
    PKMN_MOVE_LEAF_STORM = 437,
    PKMN_MOVE_POWER_WHIP = 438,
    PKMN_MOVE_ROCK_WRECKER = 439,
    PKMN_MOVE_CROSS_POISON = 440,
    PKMN_MOVE_GUNK_SHOT = 441,
    PKMN_MOVE_IRON_HEAD = 442,
    PKMN_MOVE_MAGNET_BOMB = 443,
    PKMN_MOVE_STONE_EDGE = 444,
    PKMN_MOVE_CAPTIVATE = 445,
    PKMN_MOVE_STEALTH_ROCK = 446,
    PKMN_MOVE_GRASS_KNOT = 447,
    PKMN_MOVE_CHATTER = 448,
    PKMN_MOVE_JUDGMENT = 449,
    PKMN_MOVE_BUG_BITE = 450,
    PKMN_MOVE_CHARGE_BEAM = 451,
    PKMN_MOVE_WOOD_HAMMER = 452,
    PKMN_MOVE_AQUA_JET = 453,
    PKMN_MOVE_ATTACK_ORDER = 454,
    PKMN_MOVE_DEFEND_ORDER = 455,
    PKMN_MOVE_HEAL_ORDER = 456,
    PKMN_MOVE_HEAD_SMASH = 457,
    PKMN_MOVE_DOUBLE_HIT = 458,
    PKMN_MOVE_ROAR_OF_TIME = 459,
    PKMN_MOVE_SPACIAL_REND = 460,
    PKMN_MOVE_LUNAR_DANCE = 461,
    PKMN_MOVE_CRUSH_GRIP = 462,
    PKMN_MOVE_MAGMA_STORM = 463,
    PKMN_MOVE_DARK_VOID = 464,
    PKMN_MOVE_SEED_FLARE = 465,
    PKMN_MOVE_OMINOUS_WIND = 466,
    PKMN_MOVE_SHADOW_FORCE = 467,
    PKMN_MOVE_HONE_CLAWS = 468,
    PKMN_MOVE_WIDE_GUARD = 469,
    PKMN_MOVE_GUARD_SPLIT = 470,
    PKMN_MOVE_POWER_SPLIT = 471,
    PKMN_MOVE_WONDER_ROOM = 472,
    PKMN_MOVE_PSYSHOCK = 473,
    PKMN_MOVE_VENOSHOCK = 474,
    PKMN_MOVE_AUTOTOMIZE = 475,
    PKMN_MOVE_RAGE_POWDER = 476,
    PKMN_MOVE_TELEKINESIS = 477,
    PKMN_MOVE_MAGIC_ROOM = 478,
    PKMN_MOVE_SMACK_DOWN = 479,
    PKMN_MOVE_STORM_THROW = 480,
    PKMN_MOVE_FLAME_BURST = 481,
    PKMN_MOVE_SLUDGE_WAVE = 482,
    PKMN_MOVE_QUIVER_DANCE = 483,
    PKMN_MOVE_HEAVY_SLAM = 484,
    PKMN_MOVE_SYNCHRONOISE = 485,
    PKMN_MOVE_ELECTRO_BALL = 486,
    PKMN_MOVE_SOAK = 487,
    PKMN_MOVE_FLAME_CHARGE = 488,
    PKMN_MOVE_COIL = 489,
    PKMN_MOVE_LOW_SWEEP = 490,
    PKMN_MOVE_ACID_SPRAY = 491,
    PKMN_MOVE_FOUL_PLAY = 492,
    PKMN_MOVE_SIMPLE_BEAM = 493,
    PKMN_MOVE_ENTRAINMENT = 494,
    PKMN_MOVE_AFTER_YOU = 495,
    PKMN_MOVE_ROUND = 496,
    PKMN_MOVE_ECHOED_VOICE = 497,
    PKMN_MOVE_CHIP_AWAY = 498,
    PKMN_MOVE_CLEAR_SMOG = 499,
    PKMN_MOVE_STORED_POWER = 500,
    PKMN_MOVE_QUICK_GUARD = 501,
    PKMN_MOVE_ALLY_SWITCH = 502,
    PKMN_MOVE_SCALD = 503,
    PKMN_MOVE_SHELL_SMASH = 504,
    PKMN_MOVE_HEAL_PULSE = 505,
    PKMN_MOVE_HEX = 506,
    PKMN_MOVE_SKY_DROP = 507,
    PKMN_MOVE_SHIFT_GEAR = 508,
    PKMN_MOVE_CIRCLE_THROW = 509,
    PKMN_MOVE_INCINERATE = 510,
    PKMN_MOVE_QUASH = 511,
    PKMN_MOVE_ACROBATICS = 512,
    PKMN_MOVE_REFLECT_TYPE = 513,
    PKMN_MOVE_RETALIATE = 514,
    PKMN_MOVE_FINAL_GAMBIT = 515,
    PKMN_MOVE_BESTOW = 516,
    PKMN_MOVE_INFERNO = 517,
    PKMN_MOVE_WATER_PLEDGE = 518,
    PKMN_MOVE_FIRE_PLEDGE = 519,
    PKMN_MOVE_GRASS_PLEDGE = 520,
    PKMN_MOVE_VOLT_SWITCH = 521,
    PKMN_MOVE_STRUGGLE_BUG = 522,
    PKMN_MOVE_BULLDOZE = 523,
    PKMN_MOVE_FROST_BREATH = 524,
    PKMN_MOVE_DRAGON_TAIL = 525,
    PKMN_MOVE_WORK_UP = 526,
    PKMN_MOVE_ELECTROWEB = 527,
    PKMN_MOVE_WILD_CHARGE = 528,
    PKMN_MOVE_DRILL_RUN = 529,
    PKMN_MOVE_DUAL_CHOP = 530,
    PKMN_MOVE_HEART_STAMP = 531,
    PKMN_MOVE_HORN_LEECH = 532,
    PKMN_MOVE_SACRED_SWORD = 533,
    PKMN_MOVE_RAZOR_SHELL = 534,
    PKMN_MOVE_HEAT_CRASH = 535,
    PKMN_MOVE_LEAF_TORNADO = 536,
    PKMN_MOVE_STEAMROLLER = 537,
    PKMN_MOVE_COTTON_GUARD = 538,
    PKMN_MOVE_NIGHT_DAZE = 539,
    PKMN_MOVE_PSYSTRIKE = 540,
    PKMN_MOVE_TAIL_SLAP = 541,
    PKMN_MOVE_HURRICANE = 542,
    PKMN_MOVE_HEAD_CHARGE = 543,
    PKMN_MOVE_GEAR_GRIND = 544,
    PKMN_MOVE_SEARING_SHOT = 545,
    PKMN_MOVE_TECHNO_BLAST = 546,
    PKMN_MOVE_RELIC_SONG = 547,
    PKMN_MOVE_SECRET_SWORD = 548,
    PKMN_MOVE_GLACIATE = 549,
    PKMN_MOVE_BOLT_STRIKE = 550,
    PKMN_MOVE_BLUE_FLARE = 551,
    PKMN_MOVE_FIERY_DANCE = 552,
    PKMN_MOVE_FREEZE_SHOCK = 553,
    PKMN_MOVE_ICE_BURN = 554,
    PKMN_MOVE_SNARL = 555,
    PKMN_MOVE_ICICLE_CRASH = 556,
    PKMN_MOVE_V_CREATE = 557,
    PKMN_MOVE_FUSION_FLARE = 558,
    PKMN_MOVE_FUSION_BOLT = 559,
    PKMN_MOVE_FLYING_PRESS = 560,
    PKMN_MOVE_MAT_BLOCK = 561,
    PKMN_MOVE_BELCH = 562,
    PKMN_MOVE_ROTOTILLER = 563,
    PKMN_MOVE_STICKY_WEB = 564,
    PKMN_MOVE_FELL_STINGER = 565,
    PKMN_MOVE_PHANTOM_FORCE = 566,
    PKMN_MOVE_TRICK_OR_TREAT = 567,
    PKMN_MOVE_NOBLE_ROAR = 568,
    PKMN_MOVE_ION_DELUGE = 569,
    PKMN_MOVE_PARABOLIC_CHARGE = 570,
    PKMN_MOVE_FORESTS_CURSE = 571,
    PKMN_MOVE_PETAL_BLIZZARD = 572,
    PKMN_MOVE_FREEZE_DRY = 573,
    PKMN_MOVE_DISARMING_VOICE = 574,
    PKMN_MOVE_PARTING_SHOT = 575,
    PKMN_MOVE_TOPSY_TURVY = 576,
    PKMN_MOVE_DRAINING_KISS = 577,
    PKMN_MOVE_CRAFTY_SHIELD = 578,
    PKMN_MOVE_FLOWER_SHIELD = 579,
    PKMN_MOVE_GRASSY_TERRAIN = 580,
    PKMN_MOVE_MISTY_TERRAIN = 581,
    PKMN_MOVE_ELECTRIFY = 582,
    PKMN_MOVE_PLAY_ROUGH = 583,
    PKMN_MOVE_FAIRY_WIND = 584,
    PKMN_MOVE_MOONBLAST = 585,
    PKMN_MOVE_BOOMBURST = 586,
    PKMN_MOVE_FAIRY_LOCK = 587,
    PKMN_MOVE_KINGS_SHIELD = 588,
    PKMN_MOVE_PLAY_NICE = 589,
    PKMN_MOVE_CONFIDE = 590,
    PKMN_MOVE_DIAMOND_STORM = 591,
    PKMN_MOVE_STEAM_ERUPTION = 592,
    PKMN_MOVE_HYPERSPACE_HOLE = 593,
    PKMN_MOVE_WATER_SHURIKEN = 594,
    PKMN_MOVE_MYSTICAL_FIRE = 595,
    PKMN_MOVE_SPIKY_SHIELD = 596,
    PKMN_MOVE_AROMATIC_MIST = 597,
    PKMN_MOVE_EERIE_IMPULSE = 598,
    PKMN_MOVE_VENOM_DRENCH = 599,
    PKMN_MOVE_POWDER = 600,
    PKMN_MOVE_GEOMANCY = 601,
    PKMN_MOVE_MAGNETIC_FLUX = 602,
    PKMN_MOVE_HAPPY_HOUR = 603,
    PKMN_MOVE_ELECTRIC_TERRAIN = 604,
    PKMN_MOVE_DAZZLING_GLEAM = 605,
    PKMN_MOVE_CELEBRATE = 606,
    PKMN_MOVE_HOLD_HANDS = 607,
    PKMN_MOVE_BABY_DOLL_EYES = 608,
    PKMN_MOVE_NUZZLE = 609,
    PKMN_MOVE_HOLD_BACK = 610,
    PKMN_MOVE_INFESTATION = 611,
    PKMN_MOVE_POWER_UP_PUNCH = 612,
    PKMN_MOVE_OBLIVION_WING = 613,
    PKMN_MOVE_THOUSAND_ARROWS = 614,
    PKMN_MOVE_THOUSAND_WAVES = 615,
    PKMN_MOVE_LANDS_WRATH = 616,
    PKMN_MOVE_LIGHT_OF_RUIN = 617,
    PKMN_MOVE_ORIGIN_PULSE = 618,
    PKMN_MOVE_PRECIPICE_BLADES = 619,
    PKMN_MOVE_DRAGON_ASCENT = 620,
    PKMN_MOVE_HYPERSPACE_FURY = 621,
    PKMN_MOVE_SHADOW_RUSH = 10001,
    PKMN_MOVE_SHADOW_BLAST = 10002,
    PKMN_MOVE_SHADOW_BLITZ = 10003,
    PKMN_MOVE_SHADOW_BOLT = 10004,
    PKMN_MOVE_SHADOW_BREAK = 10005,
    PKMN_MOVE_SHADOW_CHILL = 10006,
    PKMN_MOVE_SHADOW_END = 10007,
    PKMN_MOVE_SHADOW_FIRE = 10008,
    PKMN_MOVE_SHADOW_RAVE = 10009,
    PKMN_MOVE_SHADOW_STORM = 10010,
    PKMN_MOVE_SHADOW_WAVE = 10011,
    PKMN_MOVE_SHADOW_DOWN = 10012,
    PKMN_MOVE_SHADOW_HALF = 10013,
    PKMN_MOVE_SHADOW_HOLD = 10014,
    PKMN_MOVE_SHADOW_MIST = 10015,
    PKMN_MOVE_SHADOW_PANIC = 10016,
    PKMN_MOVE_SHADOW_SHED = 10017,
    PKMN_MOVE_SHADOW_SKY = 10018,
    PKMN_MOVE_INVALID = 30000,
};

#endif /* PKMN_C_ENUMS_MOVE_H */
