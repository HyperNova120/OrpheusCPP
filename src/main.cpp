#include <stdio.h>
#include <dpp/dpp.h>
#include <fmt/core.h>
#include "main.h"
#include "JsonReader.h"
#include "HandleEvents.h"
#include <vector>

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
        event.reply(std::string("ping ") + eventUsr.username);
    }
    else if (eventName == "say")
    {
        event.reply(get<string>(event.get_parameter("content")));
    }
}

void handleOnReady(const dpp::ready_t &event)
{
    cout << "creating commands" << endl;
    std::vector<dpp::slashcommand> g_cmdVec;

    // global commands
    dpp::slashcommand pingCMD("ping", "Ping Orpheus", bot.me.id);
    g_cmdVec.push_back(pingCMD);

    dpp::slashcommand sayCMD("say", "Make Orpheus say something", bot.me.id);
    sayCMD.add_option(dpp::command_option(dpp::co_string, "content", "Text to say", true));
    g_cmdVec.push_back(sayCMD);

    bot.global_bulk_command_create(g_cmdVec);
}