#pragma once
#include <dpp/dpp.h>


struct GuildConfigs {
    dpp::snowflake JailRole_ID;
    dpp::snowflake JailAppealRole_ID;
    dpp::snowflake JailChannel_ID;
};


GuildConfigs getGuildConfigs(dpp::snowflake guildID);
dpp::snowflake getGuildJailRoleID(dpp::snowflake guildID);
dpp::snowflake getGuildJailAppealRoleID(dpp::snowflake guildID);
dpp::snowflake getGuildJailChannelID(dpp::snowflake guildID);

bool setGuildJailRoleID(dpp::snowflake guildID, dpp::snowflake JailRoleID);
bool setGuildJailAppealRoleID(dpp::snowflake guildID, dpp::snowflake JailAppealRoleID);
bool setGuildJailChannelID(dpp::snowflake guildID, dpp::snowflake JailChannelID);