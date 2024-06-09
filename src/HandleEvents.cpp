#include "HandleEvents.h"
#include "Logger.h"
#include "GuildConfigHandler.h"

void handleGuildMemberAdd(const dpp::guild_member_add_t &event) {};

void handleGuildMemberRemove(const dpp::guild_member_remove_t &event) {};

void handleGuildMemberUpdate(const dpp::guild_member_update_t &event) {};

void handleMessageCreate(const dpp::message_create_t &event)
{
    if (event.msg.author.is_bot())
    {
        return;
    }
    logDebugInfo(event.msg.content + " Author:" + event.msg.author.username);
};

void handleMessageDelete(const dpp::message_delete_t &event) {};

void handleMessageUpdate(const dpp::message_update_t &event)
{
    if (event.msg.author.is_bot())
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

void handleSlashCMD_Jail(dpp::cluster &bot, const dpp::slashcommand_t &event) {};


//register config

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