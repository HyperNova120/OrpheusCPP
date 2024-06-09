#pragma once
#include <dpp/dpp.h>

void handleGuildMemberAdd(const dpp::guild_member_add_t &event);
void handleGuildMemberRemove(const dpp::guild_member_remove_t &event);
void handleGuildMemberUpdate(const dpp::guild_member_update_t &event);

void handleMessageCreate(const dpp::message_create_t &event);
void handleMessageDelete(const dpp::message_delete_t &event);
void handleMessageUpdate(const dpp::message_update_t &event);


void handleSlashCMD_Ping(const dpp::slashcommand_t &event);
void handleSlashCMD_Say(const dpp::slashcommand_t &event);
void handleSlashCMD_Dm(dpp::cluster &bot, const dpp::slashcommand_t &event);
void handleSlashCMD_Jail(dpp::cluster &bot, const dpp::slashcommand_t &event);

//Register config

void handleSlashCMD_RegisterJailChannel(dpp::cluster &bot, const dpp::slashcommand_t &event);
void handleSlashCMD_RegisterJailRole(dpp::cluster &bot, const dpp::slashcommand_t &event);