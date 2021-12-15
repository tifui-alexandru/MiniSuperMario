// column textures for the game

static const byte noWallTypes = 5;

static byte wallType[noWallTypes] = {
    B00000001,
    B00000011,
    B00000111,
    B00001111,
    B00011111
};

static byte endWall = B11111111;
static byte hole = B00000000;

// coins textures
static byte noCoin = B00000000;

static byte coinCol1 = B00000010;
static byte coinCol2 = B00000100;
static byte coinCol3 = B00001000;
static byte coinCol4 = B00010000;
static byte coinCol5 = B00100000;