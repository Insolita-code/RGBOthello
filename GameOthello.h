/*
*File: GameOthello.h
*Author: Olavi Viitanen, Rauno Vesti, Mikko Uutela
*Description: Include file for GameOthello.cpp
*/


#ifndef GAMEOTHELLO_H
#define GAMEOTHELLO_H

void initOthelloBoard();
void cursorToDefaultPosition();
void moveCursorUp();
void moveCursorDown();
void moveCursorRight();
void moveCursorLeft();
int getCursorX();
int getCursorY();
int checkIfEmptySquare(int xAxis, int yAxis);
int checkIfPlacementValid(int xAxis, int yAxis, int playerTurn);
int checkIfAnyValidPlacements(int playerTurn);
void captureDisks(int xAxis, int yAxis, int playerTurn, int validDirections);
int placeDisk(int xAxis, int yAxis, int playerTurn);
int countPlayer1Score();
int countPlayer2Score();

#endif /* GAMEOTHELLO_H */