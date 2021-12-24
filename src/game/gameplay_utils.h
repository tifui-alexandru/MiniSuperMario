#ifndef GAMEPLAY_UTILS_H
#define GAMEPLAY_UTILS_H

/*
    Contains textures used in the game
*/

// column textures for the game
const static byte gameFloor = B00000001;
const static byte hole = B00000000;

const static byte wallHeight1 = B00000011;
const static byte wallHeight2 = B00000111;
const static byte wallHeight3 = B00001111;
const static byte wallHeight4 = B00011111;

const static byte endWall = B11111111;

// coins textures
const static byte coinTypes = 6;

const static byte noCoin = B00000000;

const static byte coinCol1 = B00000010;
const static byte coinCol2 = B00000100;
const static byte coinCol3 = B00001000;
const static byte coinCol4 = B00010000;
const static byte coinCol5 = B00100000;


struct TexturesProbability {
    TexturesProbability(float p1 = 0, float p2 = 0, float p3 = 0) : floorProb(p1), holeProb(p2), wallProb(p3) {}
    
    float floorProb, holeProb, wallProb;

    byte generateTexture() {
        byte randomNumber = random(100);

        float currentProb = floorProb;
        if (randomNumber <= currentProb * 100)
            return gameFloor;
        
        currentProb += holeProb;
        if (randomNumber <= currentProb * 100)
            return hole;

        byte wallHeight = random(1, 5);

        if (wallHeight == 1) 
            return wallHeight1;
        if (wallHeight == 2) 
            return wallHeight2;
        if (wallHeight == 3) 
            return wallHeight3;
        if (wallHeight == 4) 
            return wallHeight4;
    }
};

#endif