/*
 * Copyright (c) 2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef PKMN_C_ENUMS_SPECIES_H
#define PKMN_C_ENUMS_SPECIES_H

#include <pkmn-c/config.h>
#include <pkmn-c/error.h>

#include <stdlib.h>

enum pkmn_species
{
    PKMN_SPECIES_NONE = 0,
    PKMN_SPECIES_BULBASAUR = 1,
    PKMN_SPECIES_IVYSAUR = 2,
    PKMN_SPECIES_VENUSAUR = 3,
    PKMN_SPECIES_CHARMANDER = 4,
    PKMN_SPECIES_CHARMELEON = 5,
    PKMN_SPECIES_CHARIZARD = 6,
    PKMN_SPECIES_SQUIRTLE = 7,
    PKMN_SPECIES_WARTORTLE = 8,
    PKMN_SPECIES_BLASTOISE = 9,
    PKMN_SPECIES_CATERPIE = 10,
    PKMN_SPECIES_METAPOD = 11,
    PKMN_SPECIES_BUTTERFREE = 12,
    PKMN_SPECIES_WEEDLE = 13,
    PKMN_SPECIES_KAKUNA = 14,
    PKMN_SPECIES_BEEDRILL = 15,
    PKMN_SPECIES_PIDGEY = 16,
    PKMN_SPECIES_PIDGEOTTO = 17,
    PKMN_SPECIES_PIDGEOT = 18,
    PKMN_SPECIES_RATTATA = 19,
    PKMN_SPECIES_RATICATE = 20,
    PKMN_SPECIES_SPEAROW = 21,
    PKMN_SPECIES_FEAROW = 22,
    PKMN_SPECIES_EKANS = 23,
    PKMN_SPECIES_ARBOK = 24,
    PKMN_SPECIES_PIKACHU = 25,
    PKMN_SPECIES_RAICHU = 26,
    PKMN_SPECIES_SANDSHREW = 27,
    PKMN_SPECIES_SANDSLASH = 28,
    PKMN_SPECIES_NIDORAN_F = 29,
    PKMN_SPECIES_NIDORINA = 30,
    PKMN_SPECIES_NIDOQUEEN = 31,
    PKMN_SPECIES_NIDORAN_M = 32,
    PKMN_SPECIES_NIDORINO = 33,
    PKMN_SPECIES_NIDOKING = 34,
    PKMN_SPECIES_CLEFAIRY = 35,
    PKMN_SPECIES_CLEFABLE = 36,
    PKMN_SPECIES_VULPIX = 37,
    PKMN_SPECIES_NINETALES = 38,
    PKMN_SPECIES_JIGGLYPUFF = 39,
    PKMN_SPECIES_WIGGLYTUFF = 40,
    PKMN_SPECIES_ZUBAT = 41,
    PKMN_SPECIES_GOLBAT = 42,
    PKMN_SPECIES_ODDISH = 43,
    PKMN_SPECIES_GLOOM = 44,
    PKMN_SPECIES_VILEPLUME = 45,
    PKMN_SPECIES_PARAS = 46,
    PKMN_SPECIES_PARASECT = 47,
    PKMN_SPECIES_VENONAT = 48,
    PKMN_SPECIES_VENOMOTH = 49,
    PKMN_SPECIES_DIGLETT = 50,
    PKMN_SPECIES_DUGTRIO = 51,
    PKMN_SPECIES_MEOWTH = 52,
    PKMN_SPECIES_PERSIAN = 53,
    PKMN_SPECIES_PSYDUCK = 54,
    PKMN_SPECIES_GOLDUCK = 55,
    PKMN_SPECIES_MANKEY = 56,
    PKMN_SPECIES_PRIMEAPE = 57,
    PKMN_SPECIES_GROWLITHE = 58,
    PKMN_SPECIES_ARCANINE = 59,
    PKMN_SPECIES_POLIWAG = 60,
    PKMN_SPECIES_POLIWHIRL = 61,
    PKMN_SPECIES_POLIWRATH = 62,
    PKMN_SPECIES_ABRA = 63,
    PKMN_SPECIES_KADABRA = 64,
    PKMN_SPECIES_ALAKAZAM = 65,
    PKMN_SPECIES_MACHOP = 66,
    PKMN_SPECIES_MACHOKE = 67,
    PKMN_SPECIES_MACHAMP = 68,
    PKMN_SPECIES_BELLSPROUT = 69,
    PKMN_SPECIES_WEEPINBELL = 70,
    PKMN_SPECIES_VICTREEBEL = 71,
    PKMN_SPECIES_TENTACOOL = 72,
    PKMN_SPECIES_TENTACRUEL = 73,
    PKMN_SPECIES_GEODUDE = 74,
    PKMN_SPECIES_GRAVELER = 75,
    PKMN_SPECIES_GOLEM = 76,
    PKMN_SPECIES_PONYTA = 77,
    PKMN_SPECIES_RAPIDASH = 78,
    PKMN_SPECIES_SLOWPOKE = 79,
    PKMN_SPECIES_SLOWBRO = 80,
    PKMN_SPECIES_MAGNEMITE = 81,
    PKMN_SPECIES_MAGNETON = 82,
    PKMN_SPECIES_FARFETCHD = 83,
    PKMN_SPECIES_DODUO = 84,
    PKMN_SPECIES_DODRIO = 85,
    PKMN_SPECIES_SEEL = 86,
    PKMN_SPECIES_DEWGONG = 87,
    PKMN_SPECIES_GRIMER = 88,
    PKMN_SPECIES_MUK = 89,
    PKMN_SPECIES_SHELLDER = 90,
    PKMN_SPECIES_CLOYSTER = 91,
    PKMN_SPECIES_GASTLY = 92,
    PKMN_SPECIES_HAUNTER = 93,
    PKMN_SPECIES_GENGAR = 94,
    PKMN_SPECIES_ONIX = 95,
    PKMN_SPECIES_DROWZEE = 96,
    PKMN_SPECIES_HYPNO = 97,
    PKMN_SPECIES_KRABBY = 98,
    PKMN_SPECIES_KINGLER = 99,
    PKMN_SPECIES_VOLTORB = 100,
    PKMN_SPECIES_ELECTRODE = 101,
    PKMN_SPECIES_EXEGGCUTE = 102,
    PKMN_SPECIES_EXEGGUTOR = 103,
    PKMN_SPECIES_CUBONE = 104,
    PKMN_SPECIES_MAROWAK = 105,
    PKMN_SPECIES_HITMONLEE = 106,
    PKMN_SPECIES_HITMONCHAN = 107,
    PKMN_SPECIES_LICKITUNG = 108,
    PKMN_SPECIES_KOFFING = 109,
    PKMN_SPECIES_WEEZING = 110,
    PKMN_SPECIES_RHYHORN = 111,
    PKMN_SPECIES_RHYDON = 112,
    PKMN_SPECIES_CHANSEY = 113,
    PKMN_SPECIES_TANGELA = 114,
    PKMN_SPECIES_KANGASKHAN = 115,
    PKMN_SPECIES_HORSEA = 116,
    PKMN_SPECIES_SEADRA = 117,
    PKMN_SPECIES_GOLDEEN = 118,
    PKMN_SPECIES_SEAKING = 119,
    PKMN_SPECIES_STARYU = 120,
    PKMN_SPECIES_STARMIE = 121,
    PKMN_SPECIES_MR_MIME = 122,
    PKMN_SPECIES_SCYTHER = 123,
    PKMN_SPECIES_JYNX = 124,
    PKMN_SPECIES_ELECTABUZZ = 125,
    PKMN_SPECIES_MAGMAR = 126,
    PKMN_SPECIES_PINSIR = 127,
    PKMN_SPECIES_TAUROS = 128,
    PKMN_SPECIES_MAGIKARP = 129,
    PKMN_SPECIES_GYARADOS = 130,
    PKMN_SPECIES_LAPRAS = 131,
    PKMN_SPECIES_DITTO = 132,
    PKMN_SPECIES_EEVEE = 133,
    PKMN_SPECIES_VAPOREON = 134,
    PKMN_SPECIES_JOLTEON = 135,
    PKMN_SPECIES_FLAREON = 136,
    PKMN_SPECIES_PORYGON = 137,
    PKMN_SPECIES_OMANYTE = 138,
    PKMN_SPECIES_OMASTAR = 139,
    PKMN_SPECIES_KABUTO = 140,
    PKMN_SPECIES_KABUTOPS = 141,
    PKMN_SPECIES_AERODACTYL = 142,
    PKMN_SPECIES_SNORLAX = 143,
    PKMN_SPECIES_ARTICUNO = 144,
    PKMN_SPECIES_ZAPDOS = 145,
    PKMN_SPECIES_MOLTRES = 146,
    PKMN_SPECIES_DRATINI = 147,
    PKMN_SPECIES_DRAGONAIR = 148,
    PKMN_SPECIES_DRAGONITE = 149,
    PKMN_SPECIES_MEWTWO = 150,
    PKMN_SPECIES_MEW = 151,
    PKMN_SPECIES_CHIKORITA = 152,
    PKMN_SPECIES_BAYLEEF = 153,
    PKMN_SPECIES_MEGANIUM = 154,
    PKMN_SPECIES_CYNDAQUIL = 155,
    PKMN_SPECIES_QUILAVA = 156,
    PKMN_SPECIES_TYPHLOSION = 157,
    PKMN_SPECIES_TOTODILE = 158,
    PKMN_SPECIES_CROCONAW = 159,
    PKMN_SPECIES_FERALIGATR = 160,
    PKMN_SPECIES_SENTRET = 161,
    PKMN_SPECIES_FURRET = 162,
    PKMN_SPECIES_HOOTHOOT = 163,
    PKMN_SPECIES_NOCTOWL = 164,
    PKMN_SPECIES_LEDYBA = 165,
    PKMN_SPECIES_LEDIAN = 166,
    PKMN_SPECIES_SPINARAK = 167,
    PKMN_SPECIES_ARIADOS = 168,
    PKMN_SPECIES_CROBAT = 169,
    PKMN_SPECIES_CHINCHOU = 170,
    PKMN_SPECIES_LANTURN = 171,
    PKMN_SPECIES_PICHU = 172,
    PKMN_SPECIES_CLEFFA = 173,
    PKMN_SPECIES_IGGLYBUFF = 174,
    PKMN_SPECIES_TOGEPI = 175,
    PKMN_SPECIES_TOGETIC = 176,
    PKMN_SPECIES_NATU = 177,
    PKMN_SPECIES_XATU = 178,
    PKMN_SPECIES_MAREEP = 179,
    PKMN_SPECIES_FLAAFFY = 180,
    PKMN_SPECIES_AMPHAROS = 181,
    PKMN_SPECIES_BELLOSSOM = 182,
    PKMN_SPECIES_MARILL = 183,
    PKMN_SPECIES_AZUMARILL = 184,
    PKMN_SPECIES_SUDOWOODO = 185,
    PKMN_SPECIES_POLITOED = 186,
    PKMN_SPECIES_HOPPIP = 187,
    PKMN_SPECIES_SKIPLOOM = 188,
    PKMN_SPECIES_JUMPLUFF = 189,
    PKMN_SPECIES_AIPOM = 190,
    PKMN_SPECIES_SUNKERN = 191,
    PKMN_SPECIES_SUNFLORA = 192,
    PKMN_SPECIES_YANMA = 193,
    PKMN_SPECIES_WOOPER = 194,
    PKMN_SPECIES_QUAGSIRE = 195,
    PKMN_SPECIES_ESPEON = 196,
    PKMN_SPECIES_UMBREON = 197,
    PKMN_SPECIES_MURKROW = 198,
    PKMN_SPECIES_SLOWKING = 199,
    PKMN_SPECIES_MISDREAVUS = 200,
    PKMN_SPECIES_UNOWN = 201,
    PKMN_SPECIES_WOBBUFFET = 202,
    PKMN_SPECIES_GIRAFARIG = 203,
    PKMN_SPECIES_PINECO = 204,
    PKMN_SPECIES_FORRETRESS = 205,
    PKMN_SPECIES_DUNSPARCE = 206,
    PKMN_SPECIES_GLIGAR = 207,
    PKMN_SPECIES_STEELIX = 208,
    PKMN_SPECIES_SNUBBULL = 209,
    PKMN_SPECIES_GRANBULL = 210,
    PKMN_SPECIES_QWILFISH = 211,
    PKMN_SPECIES_SCIZOR = 212,
    PKMN_SPECIES_SHUCKLE = 213,
    PKMN_SPECIES_HERACROSS = 214,
    PKMN_SPECIES_SNEASEL = 215,
    PKMN_SPECIES_TEDDIURSA = 216,
    PKMN_SPECIES_URSARING = 217,
    PKMN_SPECIES_SLUGMA = 218,
    PKMN_SPECIES_MAGCARGO = 219,
    PKMN_SPECIES_SWINUB = 220,
    PKMN_SPECIES_PILOSWINE = 221,
    PKMN_SPECIES_CORSOLA = 222,
    PKMN_SPECIES_REMORAID = 223,
    PKMN_SPECIES_OCTILLERY = 224,
    PKMN_SPECIES_DELIBIRD = 225,
    PKMN_SPECIES_MANTINE = 226,
    PKMN_SPECIES_SKARMORY = 227,
    PKMN_SPECIES_HOUNDOUR = 228,
    PKMN_SPECIES_HOUNDOOM = 229,
    PKMN_SPECIES_KINGDRA = 230,
    PKMN_SPECIES_PHANPY = 231,
    PKMN_SPECIES_DONPHAN = 232,
    PKMN_SPECIES_PORYGON2 = 233,
    PKMN_SPECIES_STANTLER = 234,
    PKMN_SPECIES_SMEARGLE = 235,
    PKMN_SPECIES_TYROGUE = 236,
    PKMN_SPECIES_HITMONTOP = 237,
    PKMN_SPECIES_SMOOCHUM = 238,
    PKMN_SPECIES_ELEKID = 239,
    PKMN_SPECIES_MAGBY = 240,
    PKMN_SPECIES_MILTANK = 241,
    PKMN_SPECIES_BLISSEY = 242,
    PKMN_SPECIES_RAIKOU = 243,
    PKMN_SPECIES_ENTEI = 244,
    PKMN_SPECIES_SUICUNE = 245,
    PKMN_SPECIES_LARVITAR = 246,
    PKMN_SPECIES_PUPITAR = 247,
    PKMN_SPECIES_TYRANITAR = 248,
    PKMN_SPECIES_LUGIA = 249,
    PKMN_SPECIES_HO_OH = 250,
    PKMN_SPECIES_CELEBI = 251,
    PKMN_SPECIES_TREECKO = 252,
    PKMN_SPECIES_GROVYLE = 253,
    PKMN_SPECIES_SCEPTILE = 254,
    PKMN_SPECIES_TORCHIC = 255,
    PKMN_SPECIES_COMBUSKEN = 256,
    PKMN_SPECIES_BLAZIKEN = 257,
    PKMN_SPECIES_MUDKIP = 258,
    PKMN_SPECIES_MARSHTOMP = 259,
    PKMN_SPECIES_SWAMPERT = 260,
    PKMN_SPECIES_POOCHYENA = 261,
    PKMN_SPECIES_MIGHTYENA = 262,
    PKMN_SPECIES_ZIGZAGOON = 263,
    PKMN_SPECIES_LINOONE = 264,
    PKMN_SPECIES_WURMPLE = 265,
    PKMN_SPECIES_SILCOON = 266,
    PKMN_SPECIES_BEAUTIFLY = 267,
    PKMN_SPECIES_CASCOON = 268,
    PKMN_SPECIES_DUSTOX = 269,
    PKMN_SPECIES_LOTAD = 270,
    PKMN_SPECIES_LOMBRE = 271,
    PKMN_SPECIES_LUDICOLO = 272,
    PKMN_SPECIES_SEEDOT = 273,
    PKMN_SPECIES_NUZLEAF = 274,
    PKMN_SPECIES_SHIFTRY = 275,
    PKMN_SPECIES_TAILLOW = 276,
    PKMN_SPECIES_SWELLOW = 277,
    PKMN_SPECIES_WINGULL = 278,
    PKMN_SPECIES_PELIPPER = 279,
    PKMN_SPECIES_RALTS = 280,
    PKMN_SPECIES_KIRLIA = 281,
    PKMN_SPECIES_GARDEVOIR = 282,
    PKMN_SPECIES_SURSKIT = 283,
    PKMN_SPECIES_MASQUERAIN = 284,
    PKMN_SPECIES_SHROOMISH = 285,
    PKMN_SPECIES_BRELOOM = 286,
    PKMN_SPECIES_SLAKOTH = 287,
    PKMN_SPECIES_VIGOROTH = 288,
    PKMN_SPECIES_SLAKING = 289,
    PKMN_SPECIES_NINCADA = 290,
    PKMN_SPECIES_NINJASK = 291,
    PKMN_SPECIES_SHEDINJA = 292,
    PKMN_SPECIES_WHISMUR = 293,
    PKMN_SPECIES_LOUDRED = 294,
    PKMN_SPECIES_EXPLOUD = 295,
    PKMN_SPECIES_MAKUHITA = 296,
    PKMN_SPECIES_HARIYAMA = 297,
    PKMN_SPECIES_AZURILL = 298,
    PKMN_SPECIES_NOSEPASS = 299,
    PKMN_SPECIES_SKITTY = 300,
    PKMN_SPECIES_DELCATTY = 301,
    PKMN_SPECIES_SABLEYE = 302,
    PKMN_SPECIES_MAWILE = 303,
    PKMN_SPECIES_ARON = 304,
    PKMN_SPECIES_LAIRON = 305,
    PKMN_SPECIES_AGGRON = 306,
    PKMN_SPECIES_MEDITITE = 307,
    PKMN_SPECIES_MEDICHAM = 308,
    PKMN_SPECIES_ELECTRIKE = 309,
    PKMN_SPECIES_MANECTRIC = 310,
    PKMN_SPECIES_PLUSLE = 311,
    PKMN_SPECIES_MINUN = 312,
    PKMN_SPECIES_VOLBEAT = 313,
    PKMN_SPECIES_ILLUMISE = 314,
    PKMN_SPECIES_ROSELIA = 315,
    PKMN_SPECIES_GULPIN = 316,
    PKMN_SPECIES_SWALOT = 317,
    PKMN_SPECIES_CARVANHA = 318,
    PKMN_SPECIES_SHARPEDO = 319,
    PKMN_SPECIES_WAILMER = 320,
    PKMN_SPECIES_WAILORD = 321,
    PKMN_SPECIES_NUMEL = 322,
    PKMN_SPECIES_CAMERUPT = 323,
    PKMN_SPECIES_TORKOAL = 324,
    PKMN_SPECIES_SPOINK = 325,
    PKMN_SPECIES_GRUMPIG = 326,
    PKMN_SPECIES_SPINDA = 327,
    PKMN_SPECIES_TRAPINCH = 328,
    PKMN_SPECIES_VIBRAVA = 329,
    PKMN_SPECIES_FLYGON = 330,
    PKMN_SPECIES_CACNEA = 331,
    PKMN_SPECIES_CACTURNE = 332,
    PKMN_SPECIES_SWABLU = 333,
    PKMN_SPECIES_ALTARIA = 334,
    PKMN_SPECIES_ZANGOOSE = 335,
    PKMN_SPECIES_SEVIPER = 336,
    PKMN_SPECIES_LUNATONE = 337,
    PKMN_SPECIES_SOLROCK = 338,
    PKMN_SPECIES_BARBOACH = 339,
    PKMN_SPECIES_WHISCASH = 340,
    PKMN_SPECIES_CORPHISH = 341,
    PKMN_SPECIES_CRAWDAUNT = 342,
    PKMN_SPECIES_BALTOY = 343,
    PKMN_SPECIES_CLAYDOL = 344,
    PKMN_SPECIES_LILEEP = 345,
    PKMN_SPECIES_CRADILY = 346,
    PKMN_SPECIES_ANORITH = 347,
    PKMN_SPECIES_ARMALDO = 348,
    PKMN_SPECIES_FEEBAS = 349,
    PKMN_SPECIES_MILOTIC = 350,
    PKMN_SPECIES_CASTFORM = 351,
    PKMN_SPECIES_KECLEON = 352,
    PKMN_SPECIES_SHUPPET = 353,
    PKMN_SPECIES_BANETTE = 354,
    PKMN_SPECIES_DUSKULL = 355,
    PKMN_SPECIES_DUSCLOPS = 356,
    PKMN_SPECIES_TROPIUS = 357,
    PKMN_SPECIES_CHIMECHO = 358,
    PKMN_SPECIES_ABSOL = 359,
    PKMN_SPECIES_WYNAUT = 360,
    PKMN_SPECIES_SNORUNT = 361,
    PKMN_SPECIES_GLALIE = 362,
    PKMN_SPECIES_SPHEAL = 363,
    PKMN_SPECIES_SEALEO = 364,
    PKMN_SPECIES_WALREIN = 365,
    PKMN_SPECIES_CLAMPERL = 366,
    PKMN_SPECIES_HUNTAIL = 367,
    PKMN_SPECIES_GOREBYSS = 368,
    PKMN_SPECIES_RELICANTH = 369,
    PKMN_SPECIES_LUVDISC = 370,
    PKMN_SPECIES_BAGON = 371,
    PKMN_SPECIES_SHELGON = 372,
    PKMN_SPECIES_SALAMENCE = 373,
    PKMN_SPECIES_BELDUM = 374,
    PKMN_SPECIES_METANG = 375,
    PKMN_SPECIES_METAGROSS = 376,
    PKMN_SPECIES_REGIROCK = 377,
    PKMN_SPECIES_REGICE = 378,
    PKMN_SPECIES_REGISTEEL = 379,
    PKMN_SPECIES_LATIAS = 380,
    PKMN_SPECIES_LATIOS = 381,
    PKMN_SPECIES_KYOGRE = 382,
    PKMN_SPECIES_GROUDON = 383,
    PKMN_SPECIES_RAYQUAZA = 384,
    PKMN_SPECIES_JIRACHI = 385,
    PKMN_SPECIES_DEOXYS = 386,
    PKMN_SPECIES_TURTWIG = 387,
    PKMN_SPECIES_GROTLE = 388,
    PKMN_SPECIES_TORTERRA = 389,
    PKMN_SPECIES_CHIMCHAR = 390,
    PKMN_SPECIES_MONFERNO = 391,
    PKMN_SPECIES_INFERNAPE = 392,
    PKMN_SPECIES_PIPLUP = 393,
    PKMN_SPECIES_PRINPLUP = 394,
    PKMN_SPECIES_EMPOLEON = 395,
    PKMN_SPECIES_STARLY = 396,
    PKMN_SPECIES_STARAVIA = 397,
    PKMN_SPECIES_STARAPTOR = 398,
    PKMN_SPECIES_BIDOOF = 399,
    PKMN_SPECIES_BIBAREL = 400,
    PKMN_SPECIES_KRICKETOT = 401,
    PKMN_SPECIES_KRICKETUNE = 402,
    PKMN_SPECIES_SHINX = 403,
    PKMN_SPECIES_LUXIO = 404,
    PKMN_SPECIES_LUXRAY = 405,
    PKMN_SPECIES_BUDEW = 406,
    PKMN_SPECIES_ROSERADE = 407,
    PKMN_SPECIES_CRANIDOS = 408,
    PKMN_SPECIES_RAMPARDOS = 409,
    PKMN_SPECIES_SHIELDON = 410,
    PKMN_SPECIES_BASTIODON = 411,
    PKMN_SPECIES_BURMY = 412,
    PKMN_SPECIES_WORMADAM = 413,
    PKMN_SPECIES_MOTHIM = 414,
    PKMN_SPECIES_COMBEE = 415,
    PKMN_SPECIES_VESPIQUEN = 416,
    PKMN_SPECIES_PACHIRISU = 417,
    PKMN_SPECIES_BUIZEL = 418,
    PKMN_SPECIES_FLOATZEL = 419,
    PKMN_SPECIES_CHERUBI = 420,
    PKMN_SPECIES_CHERRIM = 421,
    PKMN_SPECIES_SHELLOS = 422,
    PKMN_SPECIES_GASTRODON = 423,
    PKMN_SPECIES_AMBIPOM = 424,
    PKMN_SPECIES_DRIFLOON = 425,
    PKMN_SPECIES_DRIFBLIM = 426,
    PKMN_SPECIES_BUNEARY = 427,
    PKMN_SPECIES_LOPUNNY = 428,
    PKMN_SPECIES_MISMAGIUS = 429,
    PKMN_SPECIES_HONCHKROW = 430,
    PKMN_SPECIES_GLAMEOW = 431,
    PKMN_SPECIES_PURUGLY = 432,
    PKMN_SPECIES_CHINGLING = 433,
    PKMN_SPECIES_STUNKY = 434,
    PKMN_SPECIES_SKUNTANK = 435,
    PKMN_SPECIES_BRONZOR = 436,
    PKMN_SPECIES_BRONZONG = 437,
    PKMN_SPECIES_BONSLY = 438,
    PKMN_SPECIES_MIME_JR = 439,
    PKMN_SPECIES_HAPPINY = 440,
    PKMN_SPECIES_CHATOT = 441,
    PKMN_SPECIES_SPIRITOMB = 442,
    PKMN_SPECIES_GIBLE = 443,
    PKMN_SPECIES_GABITE = 444,
    PKMN_SPECIES_GARCHOMP = 445,
    PKMN_SPECIES_MUNCHLAX = 446,
    PKMN_SPECIES_RIOLU = 447,
    PKMN_SPECIES_LUCARIO = 448,
    PKMN_SPECIES_HIPPOPOTAS = 449,
    PKMN_SPECIES_HIPPOWDON = 450,
    PKMN_SPECIES_SKORUPI = 451,
    PKMN_SPECIES_DRAPION = 452,
    PKMN_SPECIES_CROAGUNK = 453,
    PKMN_SPECIES_TOXICROAK = 454,
    PKMN_SPECIES_CARNIVINE = 455,
    PKMN_SPECIES_FINNEON = 456,
    PKMN_SPECIES_LUMINEON = 457,
    PKMN_SPECIES_MANTYKE = 458,
    PKMN_SPECIES_SNOVER = 459,
    PKMN_SPECIES_ABOMASNOW = 460,
    PKMN_SPECIES_WEAVILE = 461,
    PKMN_SPECIES_MAGNEZONE = 462,
    PKMN_SPECIES_LICKILICKY = 463,
    PKMN_SPECIES_RHYPERIOR = 464,
    PKMN_SPECIES_TANGROWTH = 465,
    PKMN_SPECIES_ELECTIVIRE = 466,
    PKMN_SPECIES_MAGMORTAR = 467,
    PKMN_SPECIES_TOGEKISS = 468,
    PKMN_SPECIES_YANMEGA = 469,
    PKMN_SPECIES_LEAFEON = 470,
    PKMN_SPECIES_GLACEON = 471,
    PKMN_SPECIES_GLISCOR = 472,
    PKMN_SPECIES_MAMOSWINE = 473,
    PKMN_SPECIES_PORYGON_Z = 474,
    PKMN_SPECIES_GALLADE = 475,
    PKMN_SPECIES_PROBOPASS = 476,
    PKMN_SPECIES_DUSKNOIR = 477,
    PKMN_SPECIES_FROSLASS = 478,
    PKMN_SPECIES_ROTOM = 479,
    PKMN_SPECIES_UXIE = 480,
    PKMN_SPECIES_MESPRIT = 481,
    PKMN_SPECIES_AZELF = 482,
    PKMN_SPECIES_DIALGA = 483,
    PKMN_SPECIES_PALKIA = 484,
    PKMN_SPECIES_HEATRAN = 485,
    PKMN_SPECIES_REGIGIGAS = 486,
    PKMN_SPECIES_GIRATINA = 487,
    PKMN_SPECIES_CRESSELIA = 488,
    PKMN_SPECIES_PHIONE = 489,
    PKMN_SPECIES_MANAPHY = 490,
    PKMN_SPECIES_DARKRAI = 491,
    PKMN_SPECIES_SHAYMIN = 492,
    PKMN_SPECIES_ARCEUS = 493,
    PKMN_SPECIES_VICTINI = 494,
    PKMN_SPECIES_SNIVY = 495,
    PKMN_SPECIES_SERVINE = 496,
    PKMN_SPECIES_SERPERIOR = 497,
    PKMN_SPECIES_TEPIG = 498,
    PKMN_SPECIES_PIGNITE = 499,
    PKMN_SPECIES_EMBOAR = 500,
    PKMN_SPECIES_OSHAWOTT = 501,
    PKMN_SPECIES_DEWOTT = 502,
    PKMN_SPECIES_SAMUROTT = 503,
    PKMN_SPECIES_PATRAT = 504,
    PKMN_SPECIES_WATCHOG = 505,
    PKMN_SPECIES_LILLIPUP = 506,
    PKMN_SPECIES_HERDIER = 507,
    PKMN_SPECIES_STOUTLAND = 508,
    PKMN_SPECIES_PURRLOIN = 509,
    PKMN_SPECIES_LIEPARD = 510,
    PKMN_SPECIES_PANSAGE = 511,
    PKMN_SPECIES_SIMISAGE = 512,
    PKMN_SPECIES_PANSEAR = 513,
    PKMN_SPECIES_SIMISEAR = 514,
    PKMN_SPECIES_PANPOUR = 515,
    PKMN_SPECIES_SIMIPOUR = 516,
    PKMN_SPECIES_MUNNA = 517,
    PKMN_SPECIES_MUSHARNA = 518,
    PKMN_SPECIES_PIDOVE = 519,
    PKMN_SPECIES_TRANQUILL = 520,
    PKMN_SPECIES_UNFEZANT = 521,
    PKMN_SPECIES_BLITZLE = 522,
    PKMN_SPECIES_ZEBSTRIKA = 523,
    PKMN_SPECIES_ROGGENROLA = 524,
    PKMN_SPECIES_BOLDORE = 525,
    PKMN_SPECIES_GIGALITH = 526,
    PKMN_SPECIES_WOOBAT = 527,
    PKMN_SPECIES_SWOOBAT = 528,
    PKMN_SPECIES_DRILBUR = 529,
    PKMN_SPECIES_EXCADRILL = 530,
    PKMN_SPECIES_AUDINO = 531,
    PKMN_SPECIES_TIMBURR = 532,
    PKMN_SPECIES_GURDURR = 533,
    PKMN_SPECIES_CONKELDURR = 534,
    PKMN_SPECIES_TYMPOLE = 535,
    PKMN_SPECIES_PALPITOAD = 536,
    PKMN_SPECIES_SEISMITOAD = 537,
    PKMN_SPECIES_THROH = 538,
    PKMN_SPECIES_SAWK = 539,
    PKMN_SPECIES_SEWADDLE = 540,
    PKMN_SPECIES_SWADLOON = 541,
    PKMN_SPECIES_LEAVANNY = 542,
    PKMN_SPECIES_VENIPEDE = 543,
    PKMN_SPECIES_WHIRLIPEDE = 544,
    PKMN_SPECIES_SCOLIPEDE = 545,
    PKMN_SPECIES_COTTONEE = 546,
    PKMN_SPECIES_WHIMSICOTT = 547,
    PKMN_SPECIES_PETILIL = 548,
    PKMN_SPECIES_LILLIGANT = 549,
    PKMN_SPECIES_BASCULIN = 550,
    PKMN_SPECIES_SANDILE = 551,
    PKMN_SPECIES_KROKOROK = 552,
    PKMN_SPECIES_KROOKODILE = 553,
    PKMN_SPECIES_DARUMAKA = 554,
    PKMN_SPECIES_DARMANITAN = 555,
    PKMN_SPECIES_MARACTUS = 556,
    PKMN_SPECIES_DWEBBLE = 557,
    PKMN_SPECIES_CRUSTLE = 558,
    PKMN_SPECIES_SCRAGGY = 559,
    PKMN_SPECIES_SCRAFTY = 560,
    PKMN_SPECIES_SIGILYPH = 561,
    PKMN_SPECIES_YAMASK = 562,
    PKMN_SPECIES_COFAGRIGUS = 563,
    PKMN_SPECIES_TIRTOUGA = 564,
    PKMN_SPECIES_CARRACOSTA = 565,
    PKMN_SPECIES_ARCHEN = 566,
    PKMN_SPECIES_ARCHEOPS = 567,
    PKMN_SPECIES_TRUBBISH = 568,
    PKMN_SPECIES_GARBODOR = 569,
    PKMN_SPECIES_ZORUA = 570,
    PKMN_SPECIES_ZOROARK = 571,
    PKMN_SPECIES_MINCCINO = 572,
    PKMN_SPECIES_CINCCINO = 573,
    PKMN_SPECIES_GOTHITA = 574,
    PKMN_SPECIES_GOTHORITA = 575,
    PKMN_SPECIES_GOTHITELLE = 576,
    PKMN_SPECIES_SOLOSIS = 577,
    PKMN_SPECIES_DUOSION = 578,
    PKMN_SPECIES_REUNICLUS = 579,
    PKMN_SPECIES_DUCKLETT = 580,
    PKMN_SPECIES_SWANNA = 581,
    PKMN_SPECIES_VANILLITE = 582,
    PKMN_SPECIES_VANILLISH = 583,
    PKMN_SPECIES_VANILLUXE = 584,
    PKMN_SPECIES_DEERLING = 585,
    PKMN_SPECIES_SAWSBUCK = 586,
    PKMN_SPECIES_EMOLGA = 587,
    PKMN_SPECIES_KARRABLAST = 588,
    PKMN_SPECIES_ESCAVALIER = 589,
    PKMN_SPECIES_FOONGUS = 590,
    PKMN_SPECIES_AMOONGUSS = 591,
    PKMN_SPECIES_FRILLISH = 592,
    PKMN_SPECIES_JELLICENT = 593,
    PKMN_SPECIES_ALOMOMOLA = 594,
    PKMN_SPECIES_JOLTIK = 595,
    PKMN_SPECIES_GALVANTULA = 596,
    PKMN_SPECIES_FERROSEED = 597,
    PKMN_SPECIES_FERROTHORN = 598,
    PKMN_SPECIES_KLINK = 599,
    PKMN_SPECIES_KLANG = 600,
    PKMN_SPECIES_KLINKLANG = 601,
    PKMN_SPECIES_TYNAMO = 602,
    PKMN_SPECIES_EELEKTRIK = 603,
    PKMN_SPECIES_EELEKTROSS = 604,
    PKMN_SPECIES_ELGYEM = 605,
    PKMN_SPECIES_BEHEEYEM = 606,
    PKMN_SPECIES_LITWICK = 607,
    PKMN_SPECIES_LAMPENT = 608,
    PKMN_SPECIES_CHANDELURE = 609,
    PKMN_SPECIES_AXEW = 610,
    PKMN_SPECIES_FRAXURE = 611,
    PKMN_SPECIES_HAXORUS = 612,
    PKMN_SPECIES_CUBCHOO = 613,
    PKMN_SPECIES_BEARTIC = 614,
    PKMN_SPECIES_CRYOGONAL = 615,
    PKMN_SPECIES_SHELMET = 616,
    PKMN_SPECIES_ACCELGOR = 617,
    PKMN_SPECIES_STUNFISK = 618,
    PKMN_SPECIES_MIENFOO = 619,
    PKMN_SPECIES_MIENSHAO = 620,
    PKMN_SPECIES_DRUDDIGON = 621,
    PKMN_SPECIES_GOLETT = 622,
    PKMN_SPECIES_GOLURK = 623,
    PKMN_SPECIES_PAWNIARD = 624,
    PKMN_SPECIES_BISHARP = 625,
    PKMN_SPECIES_BOUFFALANT = 626,
    PKMN_SPECIES_RUFFLET = 627,
    PKMN_SPECIES_BRAVIARY = 628,
    PKMN_SPECIES_VULLABY = 629,
    PKMN_SPECIES_MANDIBUZZ = 630,
    PKMN_SPECIES_HEATMOR = 631,
    PKMN_SPECIES_DURANT = 632,
    PKMN_SPECIES_DEINO = 633,
    PKMN_SPECIES_ZWEILOUS = 634,
    PKMN_SPECIES_HYDREIGON = 635,
    PKMN_SPECIES_LARVESTA = 636,
    PKMN_SPECIES_VOLCARONA = 637,
    PKMN_SPECIES_COBALION = 638,
    PKMN_SPECIES_TERRAKION = 639,
    PKMN_SPECIES_VIRIZION = 640,
    PKMN_SPECIES_TORNADUS = 641,
    PKMN_SPECIES_THUNDURUS = 642,
    PKMN_SPECIES_RESHIRAM = 643,
    PKMN_SPECIES_ZEKROM = 644,
    PKMN_SPECIES_LANDORUS = 645,
    PKMN_SPECIES_KYUREM = 646,
    PKMN_SPECIES_KELDEO = 647,
    PKMN_SPECIES_MELOETTA = 648,
    PKMN_SPECIES_GENESECT = 649,
    PKMN_SPECIES_CHESPIN = 650,
    PKMN_SPECIES_QUILLADIN = 651,
    PKMN_SPECIES_CHESNAUGHT = 652,
    PKMN_SPECIES_FENNEKIN = 653,
    PKMN_SPECIES_BRAIXEN = 654,
    PKMN_SPECIES_DELPHOX = 655,
    PKMN_SPECIES_FROAKIE = 656,
    PKMN_SPECIES_FROGADIER = 657,
    PKMN_SPECIES_GRENINJA = 658,
    PKMN_SPECIES_BUNNELBY = 659,
    PKMN_SPECIES_DIGGERSBY = 660,
    PKMN_SPECIES_FLETCHLING = 661,
    PKMN_SPECIES_FLETCHINDER = 662,
    PKMN_SPECIES_TALONFLAME = 663,
    PKMN_SPECIES_SCATTERBUG = 664,
    PKMN_SPECIES_SPEWPA = 665,
    PKMN_SPECIES_VIVILLON = 666,
    PKMN_SPECIES_LITLEO = 667,
    PKMN_SPECIES_PYROAR = 668,
    PKMN_SPECIES_FLABEBE = 669,
    PKMN_SPECIES_FLOETTE = 670,
    PKMN_SPECIES_FLORGES = 671,
    PKMN_SPECIES_SKIDDO = 672,
    PKMN_SPECIES_GOGOAT = 673,
    PKMN_SPECIES_PANCHAM = 674,
    PKMN_SPECIES_PANGORO = 675,
    PKMN_SPECIES_FURFROU = 676,
    PKMN_SPECIES_ESPURR = 677,
    PKMN_SPECIES_MEOWSTIC = 678,
    PKMN_SPECIES_HONEDGE = 679,
    PKMN_SPECIES_DOUBLADE = 680,
    PKMN_SPECIES_AEGISLASH = 681,
    PKMN_SPECIES_SPRITZEE = 682,
    PKMN_SPECIES_AROMATISSE = 683,
    PKMN_SPECIES_SWIRLIX = 684,
    PKMN_SPECIES_SLURPUFF = 685,
    PKMN_SPECIES_INKAY = 686,
    PKMN_SPECIES_MALAMAR = 687,
    PKMN_SPECIES_BINACLE = 688,
    PKMN_SPECIES_BARBARACLE = 689,
    PKMN_SPECIES_SKRELP = 690,
    PKMN_SPECIES_DRAGALGE = 691,
    PKMN_SPECIES_CLAUNCHER = 692,
    PKMN_SPECIES_CLAWITZER = 693,
    PKMN_SPECIES_HELIOPTILE = 694,
    PKMN_SPECIES_HELIOLISK = 695,
    PKMN_SPECIES_TYRUNT = 696,
    PKMN_SPECIES_TYRANTRUM = 697,
    PKMN_SPECIES_AMAURA = 698,
    PKMN_SPECIES_AURORUS = 699,
    PKMN_SPECIES_SYLVEON = 700,
    PKMN_SPECIES_HAWLUCHA = 701,
    PKMN_SPECIES_DEDENNE = 702,
    PKMN_SPECIES_CARBINK = 703,
    PKMN_SPECIES_GOOMY = 704,
    PKMN_SPECIES_SLIGGOO = 705,
    PKMN_SPECIES_GOODRA = 706,
    PKMN_SPECIES_KLEFKI = 707,
    PKMN_SPECIES_PHANTUMP = 708,
    PKMN_SPECIES_TREVENANT = 709,
    PKMN_SPECIES_PUMPKABOO = 710,
    PKMN_SPECIES_GOURGEIST = 711,
    PKMN_SPECIES_BERGMITE = 712,
    PKMN_SPECIES_AVALUGG = 713,
    PKMN_SPECIES_NOIBAT = 714,
    PKMN_SPECIES_NOIVERN = 715,
    PKMN_SPECIES_XERNEAS = 716,
    PKMN_SPECIES_YVELTAL = 717,
    PKMN_SPECIES_ZYGARDE = 718,
    PKMN_SPECIES_DIANCIE = 719,
    PKMN_SPECIES_HOOPA = 720,
    PKMN_SPECIES_VOLCANION = 721,
    PKMN_SPECIES_INVALID = 30000,
};

struct pkmn_species_enum_list
{
    enum pkmn_species* p_enums;
    size_t length;
};

#ifdef __cplusplus
extern "C" {
#endif

PKMN_C_API enum pkmn_error pkmn_species_enum_list_free(
    struct pkmn_species_enum_list* p_species_enum_list
);

#ifdef __cplusplus
}
#endif

#endif /* PKMN_C_ENUMS_SPECIES_H */
