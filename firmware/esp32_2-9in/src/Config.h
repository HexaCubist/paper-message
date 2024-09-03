#pragma once

#include <stdint.h> 

static constexpr uint16_t input_buffer_pixels = 800; // may affect performance

static constexpr uint16_t max_row_width = 1872; // for up to 7.8" display 1872x1404
static constexpr uint16_t max_palette_pixels = 256; // for depth <= 8

static constexpr const char* rsb_host = "rsb.nz";
static constexpr const char* path = "/api/";
static constexpr const char* pagesEndpoint = "/pages/";
static constexpr const char* fp_rawcontent = "EF:A9:7B:6E:EB:B2:31:B9:9B:2E:13:16:D8:A6:D8:42:4F:83:57:7E";  // SHA-1 as of 24 Aug 2024

static constexpr int display_width = 296;
static constexpr int display_height = 128;


static constexpr int BUTTON_INPUT = 4; // GPIO4 (P4)

