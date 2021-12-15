#include "camera_view.h"

CameraView::CameraView(const CameraView& other) {
    for (int row = 0; row < matrixSize; ++row) {
        this->mapMatrix[row] = other.getMapRow(row);
        this->coinsMatrix[row] = other.getCoinsRow(row);
    }
}

CameraView CameraView::operator = (const CameraView& other) {
    for (int row = 0; row < matrixSize; ++row)  {
        this->mapMatrix[row] = other.getMapRow(row);
        this->coinsMatrix[row] = other.getCoinsRow(row);
    }
    return *this;
}

void CameraView::setPosition(Point p, bool value) {
    if (value == true) {
        byte mask = 1 << p.y; // zero everywhere exept one position
        mapMatrix[p.x] |= mask;
    }
    else {
        byte mask = ((1 << matrixSize) - 1) ^ (1 << p.y); // one everywhere exept one position
        mapMatrix[p.x] &= mask;
    }
}

byte CameraView::getColumn(byte* bytesMatrix, int index) {
    byte mask = 1 << index;
    byte answer = 0;

    for (int i = 0; i < matrixSize; ++i) {
        byte byteValue = (bytesMatrix[i] & mask);
        answer <<= 1;
        if (byteValue != 0)
            answer |= 1;
    }

    return answer;
}

void CameraView::setColumn(byte* bytesMatrix, int index, byte value) {
    byte setMask = 1 << index;                                  // zero everywhere exept on index
    byte unsetMask = ((1 << matrixSize) - 1) ^ (1 << index);    // one everywhere exept on index

    for (int i = 0; i < matrixSize; ++i) {
        byte byteValue = value & (1 << (matrixSize - i - 1));
        if (byteValue != 0)
            bytesMatrix[i] |= setMask;
        else
            bytesMatrix[i] &= unsetMask;
    }
}

void CameraView::appendColumn(byte mapValue, byte coinsValue) {
    for (int col = matrixSize - 1; col > 0; --col) {
        setColumn(mapMatrix, col, getColumn(mapMatrix, col - 1));
        setColumn(coinsMatrix, col, getColumn(coinsMatrix, col - 1));
    }

    setColumn(mapMatrix, 0, mapValue);
    setColumn(coinsMatrix, 0, coinsValue);
}

void CameraView::prependColumn(byte mapValue, byte coinsValue) {
    for (int col = 0; col < matrixSize - 1; ++col) {
        setColumn(mapMatrix, col, getColumn(mapMatrix, col + 1));
        setColumn(coinsMatrix, col, getColumn(coinsMatrix, col + 1));
    }

    setColumn(mapMatrix, matrixSize - 1, mapValue);
    setColumn(coinsMatrix, matrixSize - 1, coinsValue);
}

void CameraView::changeCoinsState() {
    for (int row = 0; row < matrixSize; ++row)
        mapMatrix[row] ^= coinsMatrix[row];
}

bool CameraView::hasObstacle(Point p) {
    bool pointValue = (mapMatrix[p.x] >> p.y) & 1;
    return pointValue;
}