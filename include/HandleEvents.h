#pragma once
#include <dpp/dpp.h>

void handleGuildMemberAdd(const dpp::guild_member_add_t &event);
void handleGuildMemberRemove(const dpp::guild_member_remove_t &event);
void handleGuildMemberUpdate(const dpp::guild_member_update_t &event);
