#include "GuildConfigHandler.h"
#include "Logger.h"

std::map<dpp::snowflake, GuildConfigs> *GuildConfigs_VEC;

GuildConfigs *getGuildConfigs(dpp::snowflake guildID)
{
    if (!GuildConfigs_VEC->contains(guildID))
    {
        logDebugInfo("getGuildConfigs SERVER NOT RECOGNIZED, CREATING ENTRY");
        GuildConfigs temp = GuildConfigs();
        GuildConfigs_VEC->insert(std::pair<dpp::snowflake, GuildConfigs>(guildID, temp));
    }
    return &GuildConfigs_VEC->at(guildID);
};

dpp::snowflake getGuildJailRoleID(dpp::snowflake guildID)
{
    logDebugInfo("getGuildJailRoleID:" + guildID.str());
    return getGuildConfigs(guildID)->JailRole_ID;
};

dpp::snowflake getGuildJailChannelID(dpp::snowflake guildID)
{
    logDebugInfo("getGuildJailChannelID:" + guildID.str());
    return getGuildConfigs(guildID)->JailChannel_ID;
};

bool setGuildJailRoleID(dpp::snowflake guildID, dpp::snowflake JailRoleID)
{
    try
    {
        logDebugInfo("setGuildJailRoleID: SERVER ID:" + guildID.str() + std::string(" ROLE ID:") + JailRoleID.str());
        getGuildConfigs(guildID)->JailRole_ID = JailRoleID;
        return true;
    }
    catch (std::exception e)
    {
        logErrorInfo("setGuildJailRoleID: ERROR");
        return false;
    }
};

bool setGuildJailChannelID(dpp::snowflake guildID, dpp::snowflake JailChannelID)
{
    try
    {
        logDebugInfo("setGuildJailChannelID: SERVER ID:" + guildID.str() + std::string(" CHANNEl ID:") + JailChannelID.str());
        getGuildConfigs(guildID)->JailChannel_ID = JailChannelID;
        return true;
    }
    catch (std::exception e)
    {
        logErrorInfo("setGuildJailChannelID: ERROR");
        return false;
    }
};