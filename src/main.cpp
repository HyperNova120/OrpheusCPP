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
/*
       [x]- !say
       [x]-!dm
       []-rand gif
       [x]-!send

       []-!join
       []-!leave

       []-!play
       []-!pause
       []-!stop

       []-!on
       []-!off
       []-!dnd
*/

dpp::cluster bot(getBot_Token(), dpp::i_default_intents | dpp::i_message_content);

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

    dpp::cluster *pbot = &bot;

    bot.on_message_create([pbot](dpp::message_create_t msgCT)
                          { handleMessageCreate(*pbot, msgCT); }); // bot.on_message_create([&bot](...) { handleMessageCreate(bot, ...) });
    bot.on_message_delete(handleMessageDelete);
    bot.on_message_update(handleMessageUpdate);
}

void handleSlashCMD(const dpp::slashcommand_t &event)
{
    string eventName = event.command.get_command_name();
    dpp::user eventUsr = event.command.get_issuing_user();
    if (eventName == "ping")
    {
        handleSlashCMD_Ping(event);
    }
    else if (eventName == "say")
    {
        handleSlashCMD_Say(event);
    }
    else if (eventName == "dm")
    {
        handleSlashCMD_Dm(bot, event);
    }
    else if (eventName == "jail")
    {
        handleSlashCMD_Jail(bot, event);
    }
    else if (eventName == "free")
    {
        handleSlashCMD_Free(bot, event);
    }
    else if (eventName == "set_jail_appeal_channel")
    {
        handleSlashCMD_RegisterJailChannel(bot, event);
    }
    else if (eventName == "set_jail_role")
    {
        handleSlashCMD_RegisterJailRole(bot, event);
    }
    else if (eventName == "set_jail_appeal_role")
    {
        handleSlashCMD_RegisterJailAppealRole(bot, event);
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
    dmCMD.add_option(dpp::command_option(dpp::co_user, "user", "User to dm", true));
    dmCMD.add_option(dpp::command_option(dpp::co_string, "content", "Message", true));
    g_cmdVec.push_back(dmCMD);

    dpp::slashcommand jailCMD("jail", "Send A User to Server Jail", bot.me.id);
    jailCMD.add_option(dpp::command_option(dpp::co_user, "user", "User to Jail", true));
    // jailCMD.default_member_permissions = 0;
    g_cmdVec.push_back(jailCMD);

    dpp::slashcommand freeCMD("free", "Free A User From Server Jail", bot.me.id);
    freeCMD.add_option(dpp::command_option(dpp::co_user, "user", "User to Free", true));
    // jailCMD.default_member_permissions = 0;
    g_cmdVec.push_back(freeCMD);

    dpp::slashcommand registerJailIdCMD("set_jail_appeal_channel", "Set Channel for jail appeal", bot.me.id);
    registerJailIdCMD.add_option(dpp::command_option(dpp::co_channel, "channel", "Appeal Channel", true));
    // registerJailIdCMD.default_member_permissions = 0;
    g_cmdVec.push_back(registerJailIdCMD);

    dpp::slashcommand registerJailRoleIdCMD("set_jail_role", "Set Role for jail", bot.me.id);
    registerJailRoleIdCMD.add_option(dpp::command_option(dpp::co_role, "role", "Jail Role", true));
    // registerJailRoleIdCMD.default_member_permissions = 0;
    g_cmdVec.push_back(registerJailRoleIdCMD);

    dpp::slashcommand registerJailAppealRoleIdCMD("set_jail_appeal_role", "Set appeal Role for jail", bot.me.id);
    registerJailAppealRoleIdCMD.add_option(dpp::command_option(dpp::co_role, "role", "appeal Role", true));
    // registerJailRoleIdCMD.default_member_permissions = 0;
    g_cmdVec.push_back(registerJailAppealRoleIdCMD);

    bot.global_bulk_command_create(g_cmdVec);
}