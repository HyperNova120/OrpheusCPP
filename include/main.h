#pragma once
#include <dpp/dpp.h>

extern dpp::cluster bot;

void handleSlashCMD(const dpp::slashcommand_t &event );

void handleOnReady(const dpp::ready_t &event);

void hookEvents();