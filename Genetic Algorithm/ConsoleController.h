#pragma once
#include <windows.h> 
#include <iostream>
#include <chrono>
#include <string>
#include <vector>  
#include <stdlib.h>  
#include <time.h>  
#include <stdio.h>

using namespace std;

void Console_gotoXY(int x, int y);

void Console_Resize(int x, int y);

void Console_Clear();

void Console_FontSize(int a, int b);

void Console_ColoredTEXT(string m_word, int m_color);

void Console_RainbowWrite(string m_word);
