#include "camera_view.h"

CameraView CameraView::operator = (const CameraView& other) {
    for (int row = 0; row < matrixSize; ++row) 
        this->matrixByte[row] = other.getRow(row);
    return *this;
}

void CameraView::setPosition(Point p, bool value) {
    if (value == true) {
        byte mask = 1 << p.y; // zero everywhere exept one position
        matrixByte[p.x] |= mask;
    }
    else {
        byte mask = ((1 << matrixSize) - 1) ^ (1 << p.y); // one everywhere exept one position
        matrixByte[p.x] &= mask;
    }
}

byte CameraView::getColumn(int index) {
    byte mask = 1 << index;
    byte answer = 0;

    for (int i = 0; i < matrixSize; ++i) {
        byte byteValue = (matrixByte[i] & mask);
        answer <<= 1;
        if (byteValue != 0)
            answer |= 1;
    }

    return answer;
}

void CameraView::setColumn(int index, byte value) {
    byte setMask = 1 << index;                                  // zero everywhere exept on index
    byte unsetMask = ((1 << matrixSize) - 1) ^ (1 << index);    // one everywhere exept on index

    for (int i = 0; i < matrixSize; ++i) {
        byte byteValue = value & (1 << (matrixSize - i - 1));
        if (byteValue != 0)
            matrixByte[i] |= setMask;
        else
            matrixByte[i] &= unsetMask;
    }
}

void CameraView::appendColumn(byte value) {
    for (int col = matrixSize - 1; col > 0; --col)
        setColumn(col, getColumn(col - 1));
    setColumn(0, value);
}

void CameraView::prependColumn(byte value) {
    for (int col = 0; col < matrixSize - 1; ++col)
        setColumn(col, getColumn(col + 1));
    setColumn(matrixSize - 1, value);
}

bool CameraView::hasObstacle(Point p) {
    bool pointValue = (matrixByte[p.x] >> p.y) & 1;
    return pointValue;
}