#pragma once
#include <dpp/dpp.h>


struct GuildConfigs {
    GuildConfigs();
    dpp::snowflake JailRole_ID;
    dpp::snowflake JailChannel_ID;
};


GuildConfigs *getGuildConfigs(dpp::snowflake guildID);
dpp::snowflake getGuildJailRoleID(dpp::snowflake guildID);
dpp::snowflake getGuildJailChannelID(dpp::snowflake guildID);

bool setGuildJailRoleID(dpp::snowflake guildID, dpp::snowflake JailRoleID);
bool setGuildJailChannelID(dpp::snowflake guildID, dpp::snowflake JailChannelID);