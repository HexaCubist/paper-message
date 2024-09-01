#pragma once
#include <Arduino.h>
#include <DisplayController.h>
#include <FetchBMP.h>
#include <Config.h>
#include <WifiController.h>
#include <WiFiClientSecure.h>
#include <UserInfo.h>
#include <images/download.h>

// As of writing, takes up 2/3 of the heap
// 4736 bytes per page
constexpr uint8_t MAX_PAGES = 15;

void initialiseImageLoader();

bool downloadAllImages(UserInfo *userInfo, uint8_t page_num, uint8_t page_count);

bool openImage(UserInfo *userInfo, uint8_t page_num);