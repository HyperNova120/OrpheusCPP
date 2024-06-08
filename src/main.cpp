#include <stdio.h>
#include <dpp/dpp.h>
#include <fmt/core.h>
#include "main.h"
#include "JsonReader.h"
#include "HandleEvents.h"
#include "Logger.h"
#include <vector>
#include <string>

using namespace std;

dpp::cluster bot(getBot_Token());

int main()
{
    bot.on_log(dpp::utility::cout_logger());
    hookEvents();
    bot.start(dpp::st_wait);
}

void hookEvents()
{
    bot.on_slashcommand(handleSlashCMD);

    bot.on_ready(handleOnReady);

    bot.on_guild_member_add(handleGuildMemberAdd);
    bot.on_guild_member_remove(handleGuildMemberRemove);
    bot.on_guild_member_update(handleGuildMemberUpdate);
}

void handleSlashCMD(const dpp::slashcommand_t &event)
{
    string eventName = event.command.get_command_name();
    dpp::user eventUsr = event.command.get_issuing_user();
    if (eventName == "ping")
    {
        event.reply(dpp::message(std::string("ping ") + eventUsr.username).set_flags(dpp::m_ephemeral));
    }
    else if (eventName == "say")
    {
        event.reply(get<string>(event.get_parameter("content")));
    }
    else if (eventName == "dm")
    {
        dpp::snowflake user = std::get<dpp::snowflake>(event.get_parameter("user"));

        bot.direct_message_create(user, std::get<string>(event.get_parameter("content")), [event, user](const dpp::confirmation_callback_t &callback)
                                  {
            if (callback.is_error())
            {
                event.reply(dpp::message("Failed to send DM").set_flags(dpp::m_ephemeral));
            } else {
                event.reply(dpp::message("DM sent").set_flags(dpp::m_ephemeral));} });
    }
}

void handleOnReady(const dpp::ready_t &event)
{
    logDebugInfo("creating global commands");
    std::vector<dpp::slashcommand> g_cmdVec;

    // global commands
    dpp::slashcommand pingCMD("ping", "Ping Orpheus", bot.me.id);
    g_cmdVec.push_back(pingCMD);

    dpp::slashcommand sayCMD("say", "Make Orpheus say something", bot.me.id);
    sayCMD.add_option(dpp::command_option(dpp::co_string, "content", "Text to say", true));
    g_cmdVec.push_back(sayCMD);

    dpp::slashcommand dmCMD("dm", "Make orpheus dm a user", bot.me.id);
    dmCMD.add_option(dpp::command_option(dpp::co_mentionable, "user", "User to dm", true));
    dmCMD.add_option(dpp::command_option(dpp::co_string, "content", "Message", true));
    g_cmdVec.push_back(dmCMD);

    bot.global_bulk_command_create(g_cmdVec);
}