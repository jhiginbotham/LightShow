#include "LedStrip.h"
#include "PaletteDefinitions.h"

#define SECONDS_PER_PALETTE 10

extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
extern const uint8_t gGradientPaletteCount;

uint8_t gCurrentPaletteNumber = 0;

CRGBPalette16 gCurrentPalette( CRGB::Black);
CRGBPalette16 gTargetPalette( gGradientPalettes[0] );

LedStrip topStrip(210, 3);
LedStrip bottomStrip(207, 5);

void setup() {
	delay(3000);
}

void loop()
{
	EVERY_N_SECONDS( SECONDS_PER_PALETTE ) {
		gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPaletteCount);
		gTargetPalette = gGradientPalettes[ gCurrentPaletteNumber ];
	}
	
	EVERY_N_MILLISECONDS(40) {
		nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 16);
	}
	
	topStrip.RainbowWithGlitter();
	bottomStrip.ColorWaves(gCurrentPalette);
}

const TProgmemRGBGradientPalettePtr gGradientPalettes[] = {
	shyviolet_gp,
	snodraegon_gp,
	spellbound_gp,
	springbird_gp,
	tashangel_gp,
	titannightfall_gp,
	trove_gp,
	beautifuldreams_gp,
	aquamarinemermaid_gp,
	butterflytalker_gp,
	carousel_gp,
	cloud_gp,
	fairygarden_gp,
	hangonfatboy_gp,
	liahlah2_gp,
	mistressnight_gp,
	otis_gp,
	pinkchampagne_gp,
	pinkfairyrose_gp,
	purplefly_gp,
	Sunset_Real_gp,
	es_rivendell_15_gp,
	es_ocean_breeze_036_gp,
	rgi_15_gp,
	retro2_16_gp,
	Analogous_1_gp,
	es_pinksplash_08_gp,
	Coral_reef_gp,
	es_ocean_breeze_068_gp,
	es_pinksplash_07_gp,
	es_vintage_01_gp,
	departure_gp,
	es_landscape_64_gp,
	es_landscape_33_gp,
	rainbowsherbet_gp,
	gr65_hult_gp,
	gr64_hult_gp,
	GMT_drywet_gp,
	ib_jul01_gp,
	es_vintage_57_gp,
	ib15_gp,
	Fuschia_7_gp,
	es_emerald_dragon_08_gp,
	lava_gp,
	fire_gp,
	Colorfull_gp,
	Magenta_Evening_gp,
	Pink_Purple_gp,
	es_autumn_19_gp,
	BlacK_Blue_Magenta_White_gp,
	BlacK_Magenta_Red_gp,
	BlacK_Red_Magenta_Yellow_gp,
	Blue_Cyan_Yellow_gp 
};

const uint8_t gGradientPaletteCount = sizeof( gGradientPalettes) / sizeof( TProgmemRGBGradientPalettePtr );