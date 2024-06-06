#include <stdio.h>
#include <dpp/dpp.h>
#include <fmt/core.h>
#include "JsonReader.h"
#include <vector>

using namespace std;

int main()
{
    dpp::cluster bot(getBot_Token());

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([&bot](const dpp::slashcommand_t &event)
                        { handleSlashCMD(event); });

    bot.on_ready([&bot](const dpp::ready_t &event)
                 {
                    if (dpp::run_once<struct register_bot_commands()>)
                    {
                            std::vector<dpp::slashcommand> g_cmdVec;

                            //global commands
                            dpp::slashcommand pingCMD("ping", "ping discord bot", bot.me.id);
                            g_cmdVec.push_back(pingCMD);

                            
                            bot.global_bulk_command_create(g_cmdVec);
                    } });

    bot.start(dpp::st_wait);
}

void handleSlashCMD(const dpp::slashcommand_t &event)
{
}