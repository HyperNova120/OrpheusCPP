#include "GuildConfigHandler.h"
#include "Logger.h"

std::map<dpp::snowflake, GuildConfigs> GuildConfigs_VEC;

GuildConfigs getGuildConfigs(dpp::snowflake guildID)
{
    if (GuildConfigs_VEC.find(guildID) == GuildConfigs_VEC.end())
    {
        logDebugInfo("getGuildConfigs SERVER NOT RECOGNIZED, CREATING ENTRY");
        GuildConfigs temp = GuildConfigs();
        GuildConfigs_VEC.insert(std::pair<dpp::snowflake, GuildConfigs>(guildID, temp));
    }
    else
    {
        logDebugInfo("getGuildConfigs SERVER RECOGNIZED, RETURNING ENTRY");
    }
    return GuildConfigs_VEC.at(guildID);
};

dpp::snowflake getGuildJailRoleID(dpp::snowflake guildID)
{
    logDebugInfo("getGuildJailRoleID:" + guildID.str());
    return getGuildConfigs(guildID).JailRole_ID;
};

dpp::snowflake getGuildJailAppealRoleID(dpp::snowflake guildID)
{
    logDebugInfo("getGuildJailAppealRoleID:" + guildID.str());
    return getGuildConfigs(guildID).JailAppealRole_ID;
};

dpp::snowflake getGuildJailChannelID(dpp::snowflake guildID)
{
    logDebugInfo("getGuildJailChannelID:" + guildID.str());
    return getGuildConfigs(guildID).JailChannel_ID;
};

bool setGuildJailRoleID(dpp::snowflake guildID, dpp::snowflake JailRoleID)
{
    try
    {
        GuildConfigs temp = getGuildConfigs(guildID);
        temp.JailRole_ID = JailRoleID;
        GuildConfigs_VEC.erase(guildID);
        GuildConfigs_VEC.insert(std::pair<dpp::snowflake, GuildConfigs>(guildID, temp));
        logDebugInfo("setGuildJailRoleID: SERVER ID:" + guildID.str() + std::string(" ROLE ID:") + JailRoleID.str());
        return true;
    }
    catch (std::exception e)
    {
        logErrorInfo("setGuildJailRoleID: ERROR");
        return false;
    }
};

bool setGuildJailAppealRoleID(dpp::snowflake guildID, dpp::snowflake JailAppealRoleID)
{
    try
    {
        GuildConfigs temp = getGuildConfigs(guildID);
        temp.JailAppealRole_ID = JailAppealRoleID;
        GuildConfigs_VEC.erase(guildID);
        GuildConfigs_VEC.insert(std::pair<dpp::snowflake, GuildConfigs>(guildID, temp));
        logDebugInfo("setGuildJailAppealRoleID: SERVER ID:" + guildID.str() + std::string(" ROLE ID:") + JailAppealRoleID.str());
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
        GuildConfigs temp = getGuildConfigs(guildID);
        temp.JailChannel_ID = JailChannelID;
        GuildConfigs_VEC.erase(guildID);
        GuildConfigs_VEC.insert(std::pair<dpp::snowflake, GuildConfigs>(guildID, temp));
        logDebugInfo("setGuildJailChannelID: SERVER ID:" + guildID.str() + std::string(" CHANNEl ID:") + JailChannelID.str());
        return true;
    }
    catch (std::exception e)
    {
        logErrorInfo("setGuildJailChannelID: ERROR");
        return false;
    }
};