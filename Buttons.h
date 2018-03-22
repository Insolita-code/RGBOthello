/*
*File: Buttons.h
*Author: Olavi Viitanen, Rauno Vesti, Mikko Uutela
*Description: Include file for Buttons.cpp
*/

#ifndef BUTTONS_H
#define BUTTONS_H

int DetectLeftButtonPress();
int DetectDownButtonPress();
int DetectRightButtonPress();
int DetectUpButtonPress();
int DetectSelectButtonPress();
int DetectStartButtonPress();
int DetectStartButtonHold();

void clearLeftButtonPress();
void clearDownButtonPress();
void clearRightButtonPress();
void clearUpButtonPress();
void clearSelectButtonPress();
void clearStartButtonPress();
void clearStartButtonHold();

#endif /* BUTTONS_H */