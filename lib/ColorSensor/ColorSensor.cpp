#include "ColorSensor.h"
#include "Arduino.h"

ColorSensor::ColorSensor(int Rpin, int Gpin, int Bpin, int readerPin, const int (&thresholdsRGB)[3][3]): 
light(Rpin, Gpin, Bpin),
reader(readerPin) {
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            thresholds[i][j] = thresholdsRGB[i][j];
        
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < colorNum; j++)
            mined[i][j] = 0;
        colorArray[i] = 0;
        readValue[i] = 0;
        copyedColorArray[i] = 0;
        
    }
}

int ColorSensor::readValueRed(){
    int value = 0;
    for (size_t i = 0; i < 3; i++){
        light.writeRed(1);
        delay(1);
        value += reader.read();
        delay(1);
        light.writeRed(0);
    }
}

int ColorSensor::readValueGreen(){
    int value = 0;
    for (size_t i = 0; i < 3; i++){
        light.writeGreen(1);
        delay(1);
        value += reader.read();
        delay(1);
        light.writeGreen(0);
    }
}

int ColorSensor::readValueBlue(){
    int value = 0;
    for (size_t i = 0; i < 3; i++){
        light.writeBlue(1);
        delay(1);
        value += reader.read();
        delay(1);
        light.writeBlue(0);
    }
}

char ColorSensor::read(){
    readValue[0] = readValueRed();
    readValue[1] = readValueGreen();
    readValue[2] = readValueBlue();

    int tmp = 0, loopCount = 0;

    for(int i = 0; i  < colorNum; i++)
        for(int j = 0; j < 3; j++)
            mined[i][j] = thresholds[i][j] - readValue[j];

    for(int i = 0; i  < colorNum; i++)
        for(int j = 0; j < 3; j++)
            mined[i][j] = abs(mined[i][j]);
    for(int i = 0; i  < colorNum; i++)
        colorArray[i] = mined[i][0] + mined[i][1] + mined[i][2];

	for (int i = 0; i < colorNum; i++)
		copyedColorArray[i] = colorArray[i];    

    for (int i = 0; i < colorNum; i++)
        for (int j = i + 1; j < colorNum; j++)
            if (copyedColorArray[i] > copyedColorArray[j]){
                tmp = copyedColorArray[i];
                copyedColorArray[i] = copyedColorArray[j];
                copyedColorArray[j] = tmp;
            }

    while ((copyedColorArray[0] != colorArray[loopCount]) && loopCount < colorNum)
        loopCount += 1;

    if (loopCount == 0)
        return G;

    else if (loopCount == 1)
        return W;

    else   //LoopCount == 2
        return Bl;
}