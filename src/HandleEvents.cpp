#include "HandleEvents.h"
#include "Logger.h"
#include "GuildConfigHandler.h"

void handleGuildMemberAdd(const dpp::guild_member_add_t &event) {};

void handleGuildMemberRemove(const dpp::guild_member_remove_t &event) {};

void handleGuildMemberUpdate(const dpp::guild_member_update_t &event) {};

void handleMessageCreate(dpp::cluster &bot, const dpp::message_create_t &event)
{
    logDebugInfo("Author:" + event.msg.author.username + " \"" + event.msg.content + "\"");
    if (event.msg.author.is_bot() || event.msg.is_dm())
    {
        return;
    }

    dpp::snowflake guildID = event.msg.guild_id;
    dpp::snowflake userID = event.msg.author.id;
    dpp::guild_member guildMember = bot.guild_get_member_sync(guildID, userID);

    if (event.msg.channel_id == getGuildJailChannelID(event.msg.guild_id) && doesMemberContainRole(guildMember, getGuildJailRoleID(guildID)))
    {
        logDebugInfo("Author:" + event.msg.author.username + " Sent Message From Jail");
    }
};

bool doesMemberContainRole(dpp::guild_member member, dpp::snowflake roleID)
{
    for (dpp::snowflake role : member.get_roles())
    {
        if (role == roleID)
        {
            return true;
        }
    }
    return false;
};

void handleMessageDelete(const dpp::message_delete_t &event) {};

void handleMessageUpdate(const dpp::message_update_t &event)
{
    if (event.msg.author.is_bot() || event.msg.is_dm())
    {
        return;
    }
};

// Slash Commands
void handleSlashCMD_Ping(const dpp::slashcommand_t &event)
{
    event.reply(dpp::message(std::string("ping ") + event.command.get_issuing_user().username).set_flags(dpp::m_ephemeral));
};

void handleSlashCMD_Say(const dpp::slashcommand_t &event)
{
    event.reply(std::get<std::string>(event.get_parameter("content")));
};

void handleSlashCMD_Dm(dpp::cluster &bot, const dpp::slashcommand_t &event)
{
    dpp::snowflake user = std::get<dpp::snowflake>(event.get_parameter("user"));

    bot.direct_message_create(user, std::get<std::string>(event.get_parameter("content")), [event, user](const dpp::confirmation_callback_t &callback)
                              {
            if (callback.is_error())
            {
                event.reply(dpp::message("Failed to send DM").set_flags(dpp::m_ephemeral));
                logDebugInfo("Failed To Send DM");
            } else 
            {
                event.reply(dpp::message("DM sent").set_flags(dpp::m_ephemeral));
            } });
};

void handleSlashCMD_Jail(dpp::cluster &bot, const dpp::slashcommand_t &event)
{
    try
    {
        dpp::snowflake guildID = event.command.get_guild().id;
        dpp::snowflake jailRoleID = getGuildJailRoleID(guildID);
        dpp::snowflake jailAppealRoleID = getGuildJailAppealRoleID(guildID);
        dpp::snowflake userToJail = std::get<dpp::snowflake>(event.get_parameter("user"));
        bot.guild_member_add_role_sync(guildID, userToJail, jailRoleID);
        bot.guild_member_add_role_sync(guildID, userToJail, jailAppealRoleID);
        event.reply(dpp::message("Gave User Jail Role").set_flags(dpp::m_ephemeral));
    }
    catch (std::exception e)
    {
        event.reply(dpp::message("Failed To Give User Jail Role").set_flags(dpp::m_ephemeral));
    }
};

void handleSlashCMD_Free(dpp::cluster &bot, const dpp::slashcommand_t &event)
{
    try
    {
        dpp::snowflake guildID = event.command.get_guild().id;
        dpp::snowflake jailRoleID = getGuildJailRoleID(guildID);
        dpp::snowflake jailAppealRoleID = getGuildJailAppealRoleID(guildID);
        dpp::snowflake userToJail = std::get<dpp::snowflake>(event.get_parameter("user"));
        bot.guild_member_remove_role_sync(guildID, userToJail, jailRoleID);
        bot.guild_member_remove_role_sync(guildID, userToJail, jailAppealRoleID);
        event.reply(dpp::message("Freed User").set_flags(dpp::m_ephemeral));
    }
    catch (std::exception e)
    {
        event.reply(dpp::message("Failed To Free User").set_flags(dpp::m_ephemeral));
    }
};

// register config

void handleSlashCMD_RegisterJailChannel(dpp::cluster &bot, const dpp::slashcommand_t &event)
{
    if (setGuildJailChannelID(event.command.get_guild().id, std::get<dpp::snowflake>(event.get_parameter("channel"))))
    {
        event.reply(dpp::message("Set Jail Channel").set_flags(dpp::m_ephemeral));
    }
    else
    {
        event.reply(dpp::message("Failed To Jail Channel").set_flags(dpp::m_ephemeral));
    }
};

void handleSlashCMD_RegisterJailRole(dpp::cluster &bot, const dpp::slashcommand_t &event)
{
    if (setGuildJailRoleID(event.command.get_guild().id, std::get<dpp::snowflake>(event.get_parameter("role"))))
    {
        event.reply(dpp::message("Set Jail Role").set_flags(dpp::m_ephemeral));
    }
    else
    {
        event.reply(dpp::message("Failed To Jail Role").set_flags(dpp::m_ephemeral));
    }
};

void handleSlashCMD_RegisterJailAppealRole(dpp::cluster &bot, const dpp::slashcommand_t &event)
{
    if (setGuildJailAppealRoleID(event.command.get_guild().id, std::get<dpp::snowflake>(event.get_parameter("role"))))
    {
        event.reply(dpp::message("Set Appeal Role").set_flags(dpp::m_ephemeral));
    }
    else
    {
        event.reply(dpp::message("Failed To Appeal Role").set_flags(dpp::m_ephemeral));
    }
};