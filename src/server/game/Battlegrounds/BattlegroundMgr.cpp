/*
 * Copyright (C) 2005 - 2012 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008 - 2012 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2010 - 2012 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "gamePCH.h"
#include "Common.h"
#include "ObjectMgr.h"
#include "World.h"
#include "WorldPacket.h"

#include "ArenaTeam.h"
#include "BattlegroundMgr.h"
#include "BattlegroundAV.h"
#include "BattlegroundAB.h"
#include "BattlegroundEY.h"
#include "BattlegroundWS.h"
#include "BattlegroundNA.h"
#include "BattlegroundBE.h"
#include "BattlegroundAA.h"
#include "BattlegroundRL.h"
#include "BattlegroundSA.h"
#include "BattlegroundDS.h"
#include "BattlegroundRV.h"
#include "BattlegroundIC.h"
#include "BattlegroundBG.h"
#include "BattlegroundTP.h"
#include "BattlegroundRB.h"
#include "Chat.h"
#include "Map.h"
#include "MapInstanced.h"
#include "MapManager.h"
#include "Player.h"
#include "GameEventMgr.h"
#include "SharedDefines.h"
#include "Formulas.h"
#include "DisableMgr.h"

/*********************************************************/
/***            BATTLEGROUND MANAGER                   ***/
/*********************************************************/

BattlegroundMgr::BattlegroundMgr () :
        m_AutoDistributionTimeChecker(0), m_ArenaTesting(false)
{
    for (uint32 i = BATTLEGROUND_TYPE_NONE; i < MAX_BATTLEGROUND_TYPE_ID; i++)
        m_Battlegrounds[i].clear();
    m_NextRatingDiscardUpdate = sWorld->getIntConfig(CONFIG_ARENA_RATING_DISCARD_TIMER);
    m_Testing = false;
}

BattlegroundMgr::~BattlegroundMgr ()
{
    DeleteAllBattlegrounds();
}

void BattlegroundMgr::DeleteAllBattlegrounds ()
{
    for (uint32 i = BATTLEGROUND_TYPE_NONE; i < MAX_BATTLEGROUND_TYPE_ID; ++i)
    {
        for (BattlegroundSet::iterator itr = m_Battlegrounds[i].begin(); itr != m_Battlegrounds[i].end();)
        {
            Battleground * bg = itr->second;
            m_Battlegrounds[i].erase(itr++);
            if (!m_ClientBattlegroundIds[i][bg->GetBracketId()].empty())
                m_ClientBattlegroundIds[i][bg->GetBracketId()].erase(bg->GetClientInstanceID());
            delete bg;
        }
    }

    // destroy template battlegrounds that listed only in queues (other already terminated)
    for (uint32 bgTypeId = 0; bgTypeId < MAX_BATTLEGROUND_TYPE_ID; ++bgTypeId)
    {
        // ~Battleground call unregistring BG from queue
        while (!BGFreeSlotQueue[bgTypeId].empty())
            delete BGFreeSlotQueue[bgTypeId].front();
    }
}

// used to update running battlegrounds, and delete finished ones
void BattlegroundMgr::Update (uint32 diff)
{
    BattlegroundSet::iterator itr, next;
    for (uint32 i = BATTLEGROUND_TYPE_NONE; i < MAX_BATTLEGROUND_TYPE_ID; ++i)
    {
        itr = m_Battlegrounds[i].begin();
        // skip updating battleground template
        if (itr != m_Battlegrounds[i].end())
            ++itr;
        for (; itr != m_Battlegrounds[i].end(); itr = next)
        {
            next = itr;
            ++next;
            itr->second->Update(diff);
            // use the SetDeleteThis variable
            // direct deletion caused crashes
            if (itr->second->m_SetDeleteThis)
            {
                Battleground * bg = itr->second;
                m_Battlegrounds[i].erase(itr);
                if (!m_ClientBattlegroundIds[i][bg->GetBracketId()].empty())
                    m_ClientBattlegroundIds[i][bg->GetBracketId()].erase(bg->GetClientInstanceID());
                delete bg;
            }
        }
    }

    // update scheduled queues
    if (!m_QueueUpdateScheduler.empty())
    {
        std::vector<uint64> scheduled;
        {
            //copy vector and clear the other
            scheduled = std::vector < uint64 > (m_QueueUpdateScheduler);
            m_QueueUpdateScheduler.clear();
            //release lock
        }

        for (uint8 i = 0; i < scheduled.size(); i++)
        {
            uint32 arenaMMRating = scheduled[i] >> 32;
            uint8 arenaType = scheduled[i] >> 24 & 255;
            BattlegroundQueueTypeId bgQueueTypeId = BattlegroundQueueTypeId(scheduled[i] >> 16 & 255);
            BattlegroundTypeId bgTypeId = BattlegroundTypeId((scheduled[i] >> 8) & 255);
            BattlegroundBracketId bracket_id = BattlegroundBracketId(scheduled[i] & 255);
            m_BattlegroundQueues[bgQueueTypeId].Update(bgTypeId, bracket_id, arenaType, arenaMMRating > 0, arenaMMRating);
        }
    }

    // if rating difference counts, maybe force-update queues
    if (sWorld->getIntConfig(CONFIG_ARENA_MAX_RATING_DIFFERENCE) && sWorld->getIntConfig(CONFIG_ARENA_RATING_DISCARD_TIMER))
    {
        // it's time to force update
        if (m_NextRatingDiscardUpdate < diff)
        {
            // forced update for rated arenas (scan all, but skipped non rated)
            sLog->outDebug(LOG_FILTER_BATTLEGROUND, "BattlegroundMgr: UPDATING ARENA QUEUES");
            for (int qtype = BATTLEGROUND_QUEUE_2v2; qtype <= BATTLEGROUND_QUEUE_5v5; ++qtype)
                for (int bracket = BG_BRACKET_ID_FIRST; bracket < MAX_BATTLEGROUND_BRACKETS; ++bracket)
                    m_BattlegroundQueues[qtype].Update(BATTLEGROUND_AA, BattlegroundBracketId(bracket), BattlegroundMgr::BGArenaType(BattlegroundQueueTypeId(qtype)), true, 0);

            m_NextRatingDiscardUpdate = sWorld->getIntConfig(CONFIG_ARENA_RATING_DISCARD_TIMER);
        }
        else
            m_NextRatingDiscardUpdate -= diff;
    }
    if (sWorld->getBoolConfig(CONFIG_ARENA_AUTO_DISTRIBUTE_POINTS))
    {
        if (m_AutoDistributionTimeChecker < diff)
        {
            if (time(NULL) > m_NextAutoDistributionTime)
            {
                DistributeArenaPoints();
                m_NextAutoDistributionTime = m_NextAutoDistributionTime + BATTLEGROUND_ARENA_POINT_DISTRIBUTION_DAY * sWorld->getIntConfig(CONFIG_ARENA_AUTO_DISTRIBUTE_INTERVAL_DAYS);
                sWorld->setWorldState(WS_ARENA_DISTRIBUTION_TIME, uint64(m_NextAutoDistributionTime));
            }
            m_AutoDistributionTimeChecker = 600000;          // check 10 minutes
        }
        else
            m_AutoDistributionTimeChecker -= diff;
    }
}

void BattlegroundMgr::BuildBattlegroundStatusPacket (WorldPacket *data, Battleground *bg, uint8 QueueSlot, uint8 StatusID, uint32 Time1, uint32 Time2, uint8 arenatype, uint8 uiFrame)
{
    if (!bg)
        StatusID = STATUS_NONE;

    switch (StatusID)
    {
    case STATUS_NONE:
    {
        // STATUS1 resets clients' BG Info
        data->Initialize(SMSG_BATTLEFIELD_STATUS1, 4);
        *data << uint32(QueueSlot);          // queue id (0...1)
    }
        break;
    case STATUS_WAIT_QUEUE:
    {
        // The client will set STATUS_WAIT_QUEUE at BGInfo once it receives this packet
        data->Initialize(SMSG_JOINED_BATTLEGROUND_QUEUE, (1 + 1 + 4 + 4 + 4 + 1 + 8 + 1 + 4));
        *data << uint8(0x20);          // packed flag, seems to be always 0x20 for non-rated non-arena bgs
        *data << uint8(bg->GetMaxLevel());          // max level
        *data << uint32(Time1);          // avg wait time
        *data << uint32(QueueSlot);          // queueSlot
        *data << uint32(bg->GetClientInstanceID());          // instanceid
        *data << uint8(bg->GetMinLevel());          // lowest level (seems to be set to 0 even though its not 0 sometimes O.O)

        // packed uint64 (seems to be BG GUID)
        *data << uint32(bg->GetTypeID());          // BGTypeID
        *data << uint32(arenatype);          // On retail 0x101F is sent here, but we need this value to be returned in PORT opcode
        // end

        *data << uint8(0);          // teamsize, 0 if not arena
        *data << uint32(Time2);          // time in queue
    }
        break;
    case STATUS_WAIT_JOIN:
    {
        // The client will set STATUS_WAIT_JOIN at BGInfo once it receives this packet
        data->Initialize(SMSG_BATTLEFIELD_STATUS3, (1 + 1 + 4 + 8 + 4 + 1 + 4 + 4 + 1));
        *data << uint8(bg->isRated() ? 128 : 0);          // isarena?
        *data << uint8(bg->GetMinLevel());
        *data << uint32(bg->GetClientInstanceID());          // instance id

        *data << uint32(bg->GetTypeID());          // BGTypeID
        *data << uint32(arenatype);

        *data << uint32(QueueSlot);          // queueslot
        *data << uint8(arenatype);          // teamsize (0 if not arena)
        *data << uint32(Time1);          // port expiration time

        if (bg->GetTypeID() != BATTLEGROUND_RB)
            *data << uint32(bg->GetMapId());          // mapid
        else
            *data << uint32(0);

        *data << uint8(bg->GetMaxLevel());          // highestLevel
    }
        break;
    case STATUS_IN_PROGRESS:
    {
        data->Initialize(SMSG_BATTLEFIELD_STATUS2, 100);
        *data << uint8(bg->isRated() ? 128 : 0);
        *data << uint32(Time2);          // Time since started
        *data << uint32(QueueSlot);          // queueslot
        *data << uint32(bg->GetMapId());          // MapID

        // This is bg guid
        *data << uint32(bg->GetTypeID());          // BGTypeID
        *data << uint16(0);
        *data << uint8(0x10);          // High guid
        *data << uint8(0x1F);          // High guid
        // end

        *data << uint32(Time1);          // Time until BG closed
        *data << uint8(arenatype);          // teamsize (0 if not arena)
        *data << uint8(bg->GetMaxLevel());
        *data << uint32(bg->GetClientInstanceID());          // instanceid
        *data << uint8(bg->GetMinLevel());
    }
        break;
    case STATUS_WAIT_LEAVE:
    {
        // Not used...
        data->Initialize(SMSG_BATTLEFIELD_STATUS4, (1 + 4 + 1 + 1 + 1 + 4 + 1 + 4 + 1 + 4 + 1 + 8 + 1));
        *data << uint8(0);          // flag
        *data << uint32(Time1);          //
        *data << uint8(bg->GetMinLevel());          // lowestLevel
        *data << uint8(0);
        *data << uint8(0);
        *data << uint32(QueueSlot);          // queueSlot
        *data << uint8(bg->GetMaxLevel());          // highestLevel
        *data << uint32(Time2);          //
        *data << uint8(0);          // teamsize (0 if not arena)
        *data << uint32(bg->GetClientInstanceID());          // instanceid
        *data << uint8(0);

        // This is bg guid
        *data << uint32(bg->GetTypeID());          // BGTypeID
        *data << uint16(0);
        *data << uint8(0x10);          // High guid
        *data << uint8(0x1F);          // High guid
        // end

        *data << uint8(0);
    }
        break;
    }
}

void BattlegroundMgr::BuildPvpLogDataPacket (WorldPacket *data, Battleground *bg)
{
    uint8 type = (bg->isArena() ? 128 + 64 : 0);
    if (bg->GetStatus() == STATUS_WAIT_LEAVE)
        type |= 32;

    // last check on 4.0.6
    data->Initialize(MSG_PVP_LOG_DATA, (1 + 1 + 4 + 40 * bg->GetPlayerScoresSize()));
    *data << uint8(type);          // flags

    if ((type & 64) != 0)          // arena
    {
        for (int8 i = 1; i >= 0; --i)
        {
            uint32 at_id = bg->m_ArenaTeamIds[i];
            ArenaTeam* at = sObjectMgr->GetArenaTeamById(at_id);
            if (at)
                *data << at->GetName();
            else
                *data << uint8(0);
        }
    }
    if ((type & 128) != 0)
    {
        // it seems this must be according to BG_WINNER_A/H and _NOT_ BG_TEAM_A/H
        for (int8 i = 1; i >= 0; --i)
        {
            uint32 pointsLost = bg->m_ArenaTeamRatingChanges[i] < 0 ? abs(bg->m_ArenaTeamRatingChanges[i]) : 0;
            uint32 pointsGained = bg->m_ArenaTeamRatingChanges[i] > 0 ? bg->m_ArenaTeamRatingChanges[i] : 0;
            uint32 MatchmakerRating = bg->m_ArenaTeamMMR[i];

            *data << uint32(pointsLost);          // Rating Lost
            *data << uint32(pointsGained);          // Rating gained
            *data << uint32(MatchmakerRating);          // Matchmaking Value
            sLog->outDebug(LOG_FILTER_BATTLEGROUND, "rating change: %d", bg->m_ArenaTeamRatingChanges[i]);
        }
    }

    size_t wpos = data->wpos();
    uint32 scoreCount = 0;
    *data << uint32(scoreCount);          // placeholder
    if (int8(type * 4) < 0)          // when battle is over
    {
        *data << uint8(bg->GetWinner());          // who win
    }

    uint32 flagCounter = 0;
    uint8 updateFlags;
    Battleground::BattlegroundScoreMap::const_iterator itr2 = bg->GetPlayerScoresBegin();
    for (Battleground::BattlegroundScoreMap::const_iterator itr = itr2; itr != bg->GetPlayerScoresEnd();)
    {
        itr2 = itr++;
        if (!bg->IsPlayerInBattleground(itr2->first))
        {
            sLog->outError("Player " UI64FMTD " has scoreboard entry for battleground %u but is not in battleground!", itr->first, bg->GetTypeID(true));
            continue;
        }
        Player *plr = sObjectMgr->GetPlayer(itr2->first);
        uint32 team = bg->GetPlayerTeam(itr2->first);
        if (!team && plr)
            team = plr->GetBGTeam();

        if (flagCounter % 2 == 0)
        {
            // set all flags except team
            updateFlags = 255 - 32 - 2;
            if (team == ALLIANCE)
            {
                updateFlags |= 32;
            }
        }
        else
        {
            if (team == ALLIANCE)
            {
                updateFlags |= 2;
            }
            *data << uint8(updateFlags);
        }

        flagCounter++;
    }
    if (flagCounter > 0 && flagCounter % 2 != 0)
    {
        // uneven number of players so need to send last field
        *data << uint8(updateFlags);
    }

    itr2 = bg->GetPlayerScoresBegin();
    for (Battleground::BattlegroundScoreMap::const_iterator itr = itr2; itr != bg->GetPlayerScoresEnd();)
    {
        itr2 = itr++;
        if (!bg->IsPlayerInBattleground(itr2->first))
        {
            sLog->outError("Player " UI64FMTD " has scoreboard entry for battleground %u but is not in battleground!", itr->first, bg->GetTypeID(true));
            continue;
        }
        *data << uint32(itr2->second->DamageDone);          // damage done
        *data << uint32(0);          //unk, enabled by flag
        size_t extraFields = data->wpos();
        *data << uint32(0);          // count of extra fields
                                     // next 3 fields enabled by flag
        *data << uint32(itr2->second->HonorableKills);
        *data << uint32(itr2->second->BonusHonor);
        *data << uint32(itr2->second->Deaths);

        *data << uint64(itr2->first);
        *data << uint32(itr2->second->KillingBlows);

        switch (bg->GetTypeID(true))
        // battleground specific things
        {
        case BATTLEGROUND_RB:
            switch (bg->GetMapId())
            {
            case 489:
                data->put(extraFields, 2);          // count of next fields
                *data << uint32(((BattlegroundWGScore*) (itr2->second))->FlagCaptures);          // flag captures
                *data << uint32(((BattlegroundWGScore*) (itr2->second))->FlagReturns);          // flag returns
                break;
            case 566:
                data->put(extraFields, 1);          // count of next fields
                *data << uint32(((BattlegroundEYScore*) (itr2->second))->FlagCaptures);          // flag captures
                break;
            case 529:
                data->put(extraFields, 1);          // count of next fields
                *data << uint32(((BattlegroundABScore*) (itr2->second))->BasesAssaulted);          // bases asssulted
                *data << uint32(((BattlegroundABScore*) (itr2->second))->BasesDefended);          // bases defended
                break;
            case 30:
                data->put(extraFields, 5);          // count of next fields
                *data << uint32(((BattlegroundAVScore*) (itr2->second))->GraveyardsAssaulted);          // GraveyardsAssaulted
                *data << uint32(((BattlegroundAVScore*) (itr2->second))->GraveyardsDefended);          // GraveyardsDefended
                *data << uint32(((BattlegroundAVScore*) (itr2->second))->TowersAssaulted);          // TowersAssaulted
                *data << uint32(((BattlegroundAVScore*) (itr2->second))->TowersDefended);          // TowersDefended
                *data << uint32(((BattlegroundAVScore*) (itr2->second))->MinesCaptured);          // MinesCaptured
                break;
            case 607:
                data->put(extraFields, 2);          // count of next fields
                *data << uint32(((BattlegroundSAScore*) (itr2->second))->demolishers_destroyed);
                *data << uint32(((BattlegroundSAScore*) (itr2->second))->gates_destroyed);
                break;
            case 628:
                data->put(extraFields, 2);          // count of next fields
                *data << uint32(((BattlegroundICScore*) (itr2->second))->BasesAssaulted);          // bases asssulted
                *data << uint32(((BattlegroundICScore*) (itr2->second))->BasesDefended);          // bases defended
                break;
            case 726:
                data->put(extraFields, 2);          // count of next fields
                *data << uint32(((BattlegroundTPScore*) (itr2->second))->FlagCaptures);          // flag captures
                *data << uint32(((BattlegroundTPScore*) (itr2->second))->FlagReturns);          // flag returns
                break;
            case 761:
                data->put(extraFields, 2);          // count of next fields
                *data << uint32(((BattlegroundBGScore*) (itr2->second))->BasesAssaulted);          // bases asssulted
                *data << uint32(((BattlegroundBGScore*) (itr2->second))->BasesDefended);          // bases defended
                break;
            default:
                data->put(extraFields, 0);          // count of next fields
                break;
            }
            break;
        case BATTLEGROUND_AV:
            data->put(extraFields, 5);          // count of next fields
            *data << uint32(((BattlegroundAVScore*) (itr2->second))->GraveyardsAssaulted);          // GraveyardsAssaulted
            *data << uint32(((BattlegroundAVScore*) (itr2->second))->GraveyardsDefended);          // GraveyardsDefended
            *data << uint32(((BattlegroundAVScore*) (itr2->second))->TowersAssaulted);          // TowersAssaulted
            *data << uint32(((BattlegroundAVScore*) (itr2->second))->TowersDefended);          // TowersDefended
            *data << uint32(((BattlegroundAVScore*) (itr2->second))->MinesCaptured);          // MinesCaptured
            break;
        case BATTLEGROUND_WS:
            data->put(extraFields, 2);          // count of next fields
            *data << uint32(((BattlegroundWGScore*) (itr2->second))->FlagCaptures);          // flag captures
            *data << uint32(((BattlegroundWGScore*) (itr2->second))->FlagReturns);          // flag returns
            break;
        case BATTLEGROUND_AB:
            data->put(extraFields, 2);          // count of next fields
            *data << uint32(((BattlegroundABScore*) (itr2->second))->BasesAssaulted);          // bases asssulted
            *data << uint32(((BattlegroundABScore*) (itr2->second))->BasesDefended);          // bases defended
            break;
        case BATTLEGROUND_EY:
            data->put(extraFields, 1);          // count of next fields
            *data << uint32(((BattlegroundEYScore*) (itr2->second))->FlagCaptures);          // flag captures
            break;
        case BATTLEGROUND_SA:
            data->put(extraFields, 2);          // count of next fields
            *data << uint32(((BattlegroundSAScore*) (itr2->second))->demolishers_destroyed);
            *data << uint32(((BattlegroundSAScore*) (itr2->second))->gates_destroyed);
            break;
        case BATTLEGROUND_IC:
            data->put(extraFields, 2);          // count of next fields
            *data << uint32(((BattlegroundICScore*) (itr2->second))->BasesAssaulted);          // bases asssulted
            *data << uint32(((BattlegroundICScore*) (itr2->second))->BasesDefended);          // bases defended
            break;
        case BATTLEGROUND_TP:          // Twin Peaks
            data->put(extraFields, 2);          // count of next fields
            *data << uint32(((BattlegroundTPScore*) (itr2->second))->FlagCaptures);          // flag captures
            *data << uint32(((BattlegroundTPScore*) (itr2->second))->FlagReturns);          // flag returns
            break;
        case BATTLEGROUND_BG:          // Battle of Gilneas
            data->put(extraFields, 2);          // count of next fields
            *data << uint32(((BattlegroundBGScore*) (itr2->second))->BasesAssaulted);          // bases asssulted
            *data << uint32(((BattlegroundBGScore*) (itr2->second))->BasesDefended);          // bases defended
            break;
        case BATTLEGROUND_NA:
        case BATTLEGROUND_BE:
        case BATTLEGROUND_AA:
        case BATTLEGROUND_RL:
        case BATTLEGROUND_DS:          // wotlk
        case BATTLEGROUND_RV:          // wotlk
            data->put(extraFields, 0);          // count of next fields
            break;
        default:
            sLog->outDebug(LOG_FILTER_NETWORKIO, "Unhandled MSG_PVP_LOG_DATA for BG id %u", bg->GetTypeID());
            data->put(extraFields, 0);          // count of next fields
            break;
        }

        *data << uint32(0);          // unk, enabled by flag
        *data << uint32(itr2->second->HealingDone);          // healing done

        // should never happen
        if (++scoreCount >= bg->GetMaxPlayers() && itr != bg->GetPlayerScoresEnd())
        {
            sLog->outError("Battleground %u scoreboard has more entries (%u) than allowed players in this bg (%u)", bg->GetTypeID(true), bg->GetPlayerScoresSize(), bg->GetMaxPlayers());
            break;
        }
    }

    data->put(wpos, scoreCount);
}

void BattlegroundMgr::BuildGroupJoinedBattlegroundPacket (WorldPacket *data, GroupJoinBattlegroundResult result)
{
    data->Initialize(SMSG_GROUP_JOINED_BATTLEGROUND, 4);
    *data << uint32(-1);          // QueueSlot
    *data << uint32(result);
    *data << uint64(0);          // player guid
    *data << uint64(0);          // unk, could be bg guid, but it wasnt checked
}

void BattlegroundMgr::BuildUpdateWorldStatePacket (WorldPacket *data, uint32 field, uint32 value)
{
    data->Initialize(SMSG_UPDATE_WORLD_STATE, 4 + 4);
    *data << uint32(field);
    *data << uint32(value);
}

void BattlegroundMgr::BuildPlaySoundPacket (WorldPacket *data, uint32 soundid)
{
    data->Initialize(SMSG_PLAY_SOUND, 4);
    *data << uint32(soundid);
}

void BattlegroundMgr::BuildPlayerLeftBattlegroundPacket (WorldPacket *data, const uint64& guid)
{
    data->Initialize(SMSG_BATTLEGROUND_PLAYER_LEFT, 8);
    *data << uint64(guid);
}

void BattlegroundMgr::BuildPlayerJoinedBattlegroundPacket (WorldPacket *data, Player *plr)
{
    data->Initialize(SMSG_BATTLEGROUND_PLAYER_JOINED, 8);
    *data << uint64(plr->GetGUID());
}

Battleground * BattlegroundMgr::GetBattlegroundThroughClientInstance (uint32 instanceId, BattlegroundTypeId bgTypeId)
{
    //cause at HandleBattlegroundJoinOpcode the clients sends the instanceid he gets from
    //SMSG_BATTLEFIELD_LIST we need to find the battleground with this clientinstance-id
    Battleground* bg = GetBattlegroundTemplate(bgTypeId);
    if (!bg)
        return NULL;

    if (bg->isArena())
        return GetBattleground(instanceId, bgTypeId);

    for (BattlegroundSet::iterator itr = m_Battlegrounds[bgTypeId].begin(); itr != m_Battlegrounds[bgTypeId].end(); ++itr)
    {
        if (itr->second->GetClientInstanceID() == instanceId)
            return itr->second;
    }
    return NULL;
}

Battleground * BattlegroundMgr::GetBattleground (uint32 InstanceID, BattlegroundTypeId bgTypeId)
{
    if (!InstanceID)
        return NULL;
    //search if needed
    BattlegroundSet::iterator itr;
    if (bgTypeId == BATTLEGROUND_TYPE_NONE)
    {
        for (uint32 i = BATTLEGROUND_AV; i < MAX_BATTLEGROUND_TYPE_ID; i++)
        {
            itr = m_Battlegrounds[i].find(InstanceID);
            if (itr != m_Battlegrounds[i].end())
                return itr->second;
        }
        return NULL;
    }
    itr = m_Battlegrounds[bgTypeId].find(InstanceID);
    return ((itr != m_Battlegrounds[bgTypeId].end()) ? itr->second : NULL);
}

Battleground * BattlegroundMgr::GetBattlegroundTemplate (BattlegroundTypeId bgTypeId)
{
    //map is sorted and we can be sure that lowest instance id has only BG template
    return m_Battlegrounds[bgTypeId].empty() ? NULL : m_Battlegrounds[bgTypeId].begin()->second;
}

uint32 BattlegroundMgr::CreateClientVisibleInstanceId (BattlegroundTypeId bgTypeId, BattlegroundBracketId bracket_id)
{
    if (IsArenaType(bgTypeId))
        return 0;          //arenas don't have client-instanceids

    // we create here an instanceid, which is just for
    // displaying this to the client and without any other use..
    // the client-instanceIds are unique for each battleground-type
    // the instance-id just needs to be as low as possible, beginning with 1
    // the following works, because std::set is default ordered with "<"
    // the optimalization would be to use as bitmask std::vector<uint32> - but that would only make code unreadable
    uint32 lastId = 0;
    for (std::set<uint32>::iterator itr = m_ClientBattlegroundIds[bgTypeId][bracket_id].begin(); itr != m_ClientBattlegroundIds[bgTypeId][bracket_id].end();)
    {
        if ((++lastId) != *itr)          //if there is a gap between the ids, we will break..
            break;
        lastId = *itr;
    }
    m_ClientBattlegroundIds[bgTypeId][bracket_id].insert(lastId + 1);
    return lastId + 1;
}

// create a new battleground that will really be used to play
Battleground * BattlegroundMgr::CreateNewBattleground (BattlegroundTypeId bgTypeId, PvPDifficultyEntry const* bracketEntry, uint8 arenaType, bool isRated)
{
    // get the template BG
    Battleground *bg_template = GetBattlegroundTemplate(bgTypeId);
    BattlegroundSelectionWeightMap *selectionWeights = NULL;

    if (!bg_template)
    {
        sLog->outError("Battleground: CreateNewBattleground - bg template not found for %u", bgTypeId);
        return NULL;
    }
    bool isRandom = false;

    if (bg_template->isArena())
        selectionWeights = &m_ArenaSelectionWeights;
    else if (bgTypeId == BATTLEGROUND_RB)
    {
        selectionWeights = &m_BGSelectionWeights;
        isRandom = true;
    }

    if (selectionWeights)
    {
        if (!selectionWeights->size())
            return NULL;
        uint32 Weight = 0;
        uint32 selectedWeight = 0;
        bgTypeId = BATTLEGROUND_TYPE_NONE;
        // Get sum of all weights
        for (BattlegroundSelectionWeightMap::const_iterator it = selectionWeights->begin(); it != selectionWeights->end(); ++it)
            Weight += it->second;
        if (!Weight)
            return NULL;
        // Select a random value
        selectedWeight = urand(0, Weight - 1);

        // Select the correct bg (if we have in DB A(10), B(20), C(10), D(15) --> [0---A---9|10---B---29|30---C---39|40---D---54])
        Weight = 0;
        for (BattlegroundSelectionWeightMap::const_iterator it = selectionWeights->begin(); it != selectionWeights->end(); ++it)
        {
            Weight += it->second;
            if (selectedWeight < Weight)
            {
                bgTypeId = it->first;
                break;
            }
        }
        bg_template = GetBattlegroundTemplate(bgTypeId);
        if (!bg_template)
        {
            sLog->outError("Battleground: CreateNewBattleground - bg template not found for %u", bgTypeId);
            return NULL;
        }
    }

    Battleground *bg = NULL;
    // create a copy of the BG template
    switch (bgTypeId)
    {
    case BATTLEGROUND_AV:
        bg = new BattlegroundAV(*(BattlegroundAV*) bg_template);
        break;
    case BATTLEGROUND_WS:
        bg = new BattlegroundWS(*(BattlegroundWS*) bg_template);
        break;
    case BATTLEGROUND_AB:
        bg = new BattlegroundAB(*(BattlegroundAB*) bg_template);
        break;
    case BATTLEGROUND_NA:
        bg = new BattlegroundNA(*(BattlegroundNA*) bg_template);
        break;
    case BATTLEGROUND_BE:
        bg = new BattlegroundBE(*(BattlegroundBE*) bg_template);
        break;
    case BATTLEGROUND_AA:
        bg = new BattlegroundAA(*(BattlegroundAA*) bg_template);
        break;
    case BATTLEGROUND_EY:
        bg = new BattlegroundEY(*(BattlegroundEY*) bg_template);
        break;
    case BATTLEGROUND_RL:
        bg = new BattlegroundRL(*(BattlegroundRL*) bg_template);
        break;
    case BATTLEGROUND_SA:
        bg = new BattlegroundSA(*(BattlegroundSA*) bg_template);
        break;
    case BATTLEGROUND_DS:
        bg = new BattlegroundDS(*(BattlegroundDS*) bg_template);
        break;
    case BATTLEGROUND_RV:
        bg = new BattlegroundRV(*(BattlegroundRV*) bg_template);
        break;
    case BATTLEGROUND_IC:
        bg = new BattlegroundIC(*(BattlegroundIC*) bg_template);
        break;
    case BATTLEGROUND_TP:
        bg = new BattlegroundTP(*(BattlegroundTP*) bg_template);
        break;
    case BATTLEGROUND_BG:
        bg = new BattlegroundBG(*(BattlegroundBG*) bg_template);
        break;
    case BATTLEGROUND_RB:
        bg = new BattlegroundRB(*(BattlegroundRB*) bg_template);
        break;
    default:
        //error, but it is handled few lines above
        return 0;
    }

    // set battelground difficulty before initialization
    bg->SetBracket(bracketEntry);

    // generate a new instance id
    bg->SetInstanceID(sMapMgr->GenerateInstanceId());          // set instance id
    bg->SetClientInstanceID(CreateClientVisibleInstanceId(isRandom ? BATTLEGROUND_RB : bgTypeId, bracketEntry->GetBracketId()));

    // reset the new bg (set status to status_wait_queue from status_none)
    bg->Reset();

    // start the joining of the bg
    bg->SetStatus(STATUS_WAIT_JOIN);
    bg->SetArenaType(arenaType);
    bg->SetRated(isRated);
    bg->SetRandom(isRandom);
    bg->SetTypeID(isRandom ? BATTLEGROUND_RB : bgTypeId);
    bg->SetRandomTypeID(bgTypeId);

    return bg;
}

// used to create the BG templates
uint32 BattlegroundMgr::CreateBattleground (BattlegroundTypeId bgTypeId, bool IsArena, uint32 MinPlayersPerTeam, uint32 MaxPlayersPerTeam, uint32 LevelMin, uint32 LevelMax, const char* BattlegroundName, uint32 MapID, float Team1StartLocX, float Team1StartLocY, float Team1StartLocZ, float Team1StartLocO, float Team2StartLocX, float Team2StartLocY, float Team2StartLocZ, float Team2StartLocO, uint32 scriptId)
{
    // Create the BG
    Battleground *bg = NULL;
    switch (bgTypeId)
    {
    case BATTLEGROUND_AV:
        bg = new BattlegroundAV;
        break;
    case BATTLEGROUND_WS:
        bg = new BattlegroundWS;
        break;
    case BATTLEGROUND_AB:
        bg = new BattlegroundAB;
        break;
    case BATTLEGROUND_NA:
        bg = new BattlegroundNA;
        break;
    case BATTLEGROUND_BE:
        bg = new BattlegroundBE;
        break;
    case BATTLEGROUND_AA:
        bg = new BattlegroundAA;
        break;
    case BATTLEGROUND_EY:
        bg = new BattlegroundEY;
        break;
    case BATTLEGROUND_RL:
        bg = new BattlegroundRL;
        break;
    case BATTLEGROUND_SA:
        bg = new BattlegroundSA;
        break;
    case BATTLEGROUND_DS:
        bg = new BattlegroundDS;
        break;
    case BATTLEGROUND_RV:
        bg = new BattlegroundRV;
        break;
    case BATTLEGROUND_IC:
        bg = new BattlegroundIC;
        break;
    case BATTLEGROUND_TP:
        bg = new BattlegroundTP;
        break;
    case BATTLEGROUND_BG:
        bg = new BattlegroundBG;
        break;
    case BATTLEGROUND_RB:
        bg = new BattlegroundRB;
        break;
    default:
        bg = new Battleground;
        break;
    }

    bg->SetMapId(MapID);
    bg->SetTypeID(bgTypeId);
    bg->SetInstanceID(0);
    bg->SetArenaorBGType(IsArena);
    bg->SetMinPlayersPerTeam(MinPlayersPerTeam);
    bg->SetMaxPlayersPerTeam(MaxPlayersPerTeam);
    bg->SetMinPlayers(MinPlayersPerTeam * 2);
    bg->SetMaxPlayers(MaxPlayersPerTeam * 2);
    bg->SetName(BattlegroundName);
    bg->SetTeamStartLoc(ALLIANCE, Team1StartLocX, Team1StartLocY, Team1StartLocZ, Team1StartLocO);
    bg->SetTeamStartLoc(HORDE, Team2StartLocX, Team2StartLocY, Team2StartLocZ, Team2StartLocO);
    bg->SetLevelRange(LevelMin, LevelMax);
    bg->SetScriptId(scriptId);

    // add bg to update list
    AddBattleground(bg->GetInstanceID(), bg->GetTypeID(), bg);

    // return some not-null value, bgTypeId is good enough for me
    return bgTypeId;
}

void BattlegroundMgr::CreateInitialBattlegrounds ()
{
    uint32 oldMSTime = getMSTime();

    float AStartLoc[4];
    float HStartLoc[4];
    uint32 MaxPlayersPerTeam, MinPlayersPerTeam, MinLvl, MaxLvl, start1, start2;
    uint8 selectionWeight;
    BattlemasterListEntry const *bl;
    WorldSafeLocsEntry const *start;
    bool IsArena;
    uint32 scriptId = 0;

    //                                                       0   1                 2                 3      4      5                6              7             8           9      10
    QueryResult result = WorldDatabase.Query("SELECT id, MinPlayersPerTeam, MaxPlayersPerTeam, MinLvl, MaxLvl, AllianceStartLoc, AllianceStartO, HordeStartLoc, HordeStartO, Weight, ScriptName FROM battleground_template");

    if (!result)
    {
        sLog->outErrorDb(">> Loaded 0 battlegrounds. DB table `battleground_template` is empty.");
        sLog->outString();
        return;
    }

    uint32 count = 0;

    do
    {
        Field *fields = result->Fetch();
        uint32 bgTypeID_ = fields[0].GetUInt32();
        if (sDisableMgr->IsDisabledFor(DISABLE_TYPE_BATTLEGROUND, bgTypeID_, NULL))
            continue;

        // can be overwrite by values from DB
        bl = sBattlemasterListStore.LookupEntry(bgTypeID_);
        if (!bl)
        {
            sLog->outError("Battleground ID %u not found in BattlemasterList.dbc. Battleground not created.", bgTypeID_);
            continue;
        }

        BattlegroundTypeId bgTypeID = BattlegroundTypeId(bgTypeID_);

        IsArena = (bl->MapType == TYPE_ARENA);
        MinPlayersPerTeam = fields[1].GetUInt32();
        MaxPlayersPerTeam = fields[2].GetUInt32();
        MinLvl = fields[3].GetUInt32();
        MaxLvl = fields[4].GetUInt32();
        //check values from DB
        if (MaxPlayersPerTeam == 0 || MinPlayersPerTeam == 0 || MinPlayersPerTeam > MaxPlayersPerTeam)
        {
            MinPlayersPerTeam = 0;          // by default now expected strong full bg requirement
            MaxPlayersPerTeam = 40;
        }
        if (MinLvl == 0 || MaxLvl == 0 || MinLvl > MaxLvl)
        {
            //TO-DO: FIX ME
            MinLvl = 0;          //bl->minlvl;
            MaxLvl = 80;          //bl->maxlvl;
        }

        start1 = fields[5].GetUInt32();

        start = sWorldSafeLocsStore.LookupEntry(start1);
        if (start)
        {
            AStartLoc[0] = start->x;
            AStartLoc[1] = start->y;
            AStartLoc[2] = start->z;
            AStartLoc[3] = fields[6].GetFloat();
        }
        else if (bgTypeID == BATTLEGROUND_AA || bgTypeID == BATTLEGROUND_RB)
        {
            AStartLoc[0] = 0;
            AStartLoc[1] = 0;
            AStartLoc[2] = 0;
            AStartLoc[3] = fields[6].GetFloat();
        }
        else
        {
            sLog->outErrorDb("Table `battleground_template` for id %u have non-existed WorldSafeLocs.dbc id %u in field `AllianceStartLoc`. BG not created.", bgTypeID, start1);
            continue;
        }

        start2 = fields[7].GetUInt32();

        start = sWorldSafeLocsStore.LookupEntry(start2);
        if (start)
        {
            HStartLoc[0] = start->x;
            HStartLoc[1] = start->y;
            HStartLoc[2] = start->z;
            HStartLoc[3] = fields[8].GetFloat();
        }
        else if (bgTypeID == BATTLEGROUND_AA || bgTypeID == BATTLEGROUND_RB)
        {
            HStartLoc[0] = 0;
            HStartLoc[1] = 0;
            HStartLoc[2] = 0;
            HStartLoc[3] = fields[8].GetFloat();
        }
        else
        {
            sLog->outErrorDb("Table `battleground_template` for id %u have non-existed WorldSafeLocs.dbc id %u in field `HordeStartLoc`. BG not created.", bgTypeID, start2);
            continue;
        }

        selectionWeight = fields[9].GetUInt8();
        scriptId = sObjectMgr->GetScriptId(fields[10].GetCString());
        //sLog->outDetail("Creating battleground %s, %u-%u", bl->name[sWorld->GetDBClang()], MinLvl, MaxLvl);
        if (!CreateBattleground(bgTypeID, IsArena, MinPlayersPerTeam, MaxPlayersPerTeam, MinLvl, MaxLvl, bl->name, bl->mapid[0], AStartLoc[0], AStartLoc[1], AStartLoc[2], AStartLoc[3], HStartLoc[0], HStartLoc[1], HStartLoc[2], HStartLoc[3], scriptId))
            continue;

        if (IsArena)
        {
            if (bgTypeID != BATTLEGROUND_AA)
                m_ArenaSelectionWeights[bgTypeID] = selectionWeight;
        }
        else if (bgTypeID != BATTLEGROUND_RB)
            m_BGSelectionWeights[bgTypeID] = selectionWeight;
        ++count;
    }
    while (result->NextRow());

    sLog->outString(">> Loaded %u battlegrounds in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

void BattlegroundMgr::InitAutomaticArenaPointDistribution ()
{
    if (!sWorld->getBoolConfig(CONFIG_ARENA_AUTO_DISTRIBUTE_POINTS))
        return;

    time_t wstime = time_t(sWorld->getWorldState(WS_ARENA_DISTRIBUTION_TIME));
    time_t curtime = time(NULL);
    sLog->outDebug(LOG_FILTER_BATTLEGROUND, "Initializing Automatic Arena Point Distribution");
    if (wstime < curtime)
    {
        m_NextAutoDistributionTime = curtime;          // reset will be called in the next update
        sLog->outDebug(LOG_FILTER_BATTLEGROUND, "Battleground: Next arena point distribution time in the past, reseting it now.");
    }
    else
        m_NextAutoDistributionTime = wstime;
    sLog->outDebug(LOG_FILTER_BATTLEGROUND, "Automatic Arena Point Distribution initialized.");
}

void BattlegroundMgr::DistributeArenaPoints ()
{
    // used to distribute arena points based on last week's stats
    sWorld->SendWorldText(LANG_DIST_ARENA_POINTS_START);

    sWorld->SendWorldText(LANG_DIST_ARENA_POINTS_ONLINE_START);

    //temporary structure for storing maximum points to add values for all players
            std::map<uint32, uint32> PlayerPoints;

    //at first update all points for all team members
    for (ObjectMgr::ArenaTeamMap::iterator team_itr = sObjectMgr->GetArenaTeamMapBegin(); team_itr != sObjectMgr->GetArenaTeamMapEnd(); ++team_itr)
    if (ArenaTeam * at = team_itr->second)
    at->UpdateArenaPointsHelper(PlayerPoints);

    PlayerPoints.clear();

    sWorld->SendWorldText(LANG_DIST_ARENA_POINTS_ONLINE_END);

    sWorld->SendWorldText(LANG_DIST_ARENA_POINTS_TEAM_START);
    for (ObjectMgr::ArenaTeamMap::iterator titr = sObjectMgr->GetArenaTeamMapBegin(); titr != sObjectMgr->GetArenaTeamMapEnd(); ++titr)
    {
        if (ArenaTeam * at = titr->second)
        {
            at->FinishWeek();          // set played this week etc values to 0 in memory, too
            at->SaveToDB();// save changes
            at->NotifyStatsChanged();// notify the players of the changes
        }
    }

    sWorld->SendWorldText(LANG_DIST_ARENA_POINTS_TEAM_END);

    sWorld->SendWorldText(LANG_DIST_ARENA_POINTS_END);
}

void BattlegroundMgr::BuildBattlegroundListPacket (WorldPacket *data, const uint64& guid, Player* plr, BattlegroundTypeId bgTypeId)
{
    if (!plr)
        return;

    uint32 win_kills = plr->GetRandomWinner() ? BG_REWARD_WINNER_HONOR_LAST : BG_REWARD_WINNER_HONOR_FIRST;
    uint32 win_arena = plr->GetRandomWinner() ? BG_REWARD_WINNER_ARENA_LAST : BG_REWARD_WINNER_ARENA_FIRST;
    uint32 lose_kills = plr->GetRandomWinner() ? BG_REWARD_LOSER_HONOR_LAST : BG_REWARD_LOSER_HONOR_FIRST;

    win_kills = Trinity::Honor::hk_honor_at_level(plr->getLevel(), (float) win_kills);
    lose_kills = Trinity::Honor::hk_honor_at_level(plr->getLevel(), (float) lose_kills);

    data->Initialize(SMSG_BATTLEFIELD_LIST);

    *data << uint8(0x2);          // unk flags 1 << 7, 1 << 6, 1 << 5
    *data << uint8(0x31);          // unk
    *data << uint32(win_kills);          // Call to arms win honor bonus
    *data << uint64(guid);          // battlemaster guid?
    *data << uint32(win_kills);          // random BG win honor bonus
    *data << uint8(0x2D);          // unk
    *data << uint32(lose_kills);          // Call to arms lose honor bonus
    *data << uint32(win_arena);          // Call to arms win conquest bonus
    *data << uint32(win_arena);          // random BG win conquest bonus
    *data << uint32(0);          // unk

    *data << uint32(0);          // count of uints appended to the end
    *data << uint32(lose_kills);          // random BG lose honor bonus
}

void BattlegroundMgr::SendToBattleground (Player *pl, uint32 instanceId, BattlegroundTypeId bgTypeId)
{
    Battleground *bg = GetBattleground(instanceId, bgTypeId);
    if (bg)
    {
        uint32 mapid = bg->GetMapId();
        float x, y, z, O;
        uint32 team = pl->GetBGTeam();
        if (team == 0)
            team = pl->GetTeam();
        bg->GetTeamStartLoc(team, x, y, z, O);

        sLog->outDetail("BATTLEGROUND: Sending %s to map %u, X %f, Y %f, Z %f, O %f", pl->GetName(), mapid, x, y, z, O);
        pl->TeleportTo(mapid, x, y, z, O);
    }
    else
    {
        sLog->outError("player %u trying to port to non-existent bg instance %u", pl->GetGUIDLow(), instanceId);
    }
}

void BattlegroundMgr::SendAreaSpiritHealerQueryOpcode (Player *pl, Battleground *bg, const uint64& guid)
{
    WorldPacket data(SMSG_AREA_SPIRIT_HEALER_TIME, 12);
    uint32 time_ = 30000 - bg->GetLastResurrectTime();          // resurrect every 30 seconds
    if (time_ == uint32(-1))
        time_ = 0;
    data << guid << time_;
    pl->GetSession()->SendPacket(&data);
}

bool BattlegroundMgr::IsArenaType (BattlegroundTypeId bgTypeId)
{
    return (bgTypeId == BATTLEGROUND_AA || bgTypeId == BATTLEGROUND_BE || bgTypeId == BATTLEGROUND_NA || bgTypeId == BATTLEGROUND_DS || bgTypeId == BATTLEGROUND_RV || bgTypeId == BATTLEGROUND_RL || bgTypeId == BATTLEGROUND_DS);
}

BattlegroundQueueTypeId BattlegroundMgr::BGQueueTypeId (BattlegroundTypeId bgTypeId, uint8 arenaType)
{
    switch (bgTypeId)
    {
    case BATTLEGROUND_WS:
        return BATTLEGROUND_QUEUE_WS;
    case BATTLEGROUND_AB:
        return BATTLEGROUND_QUEUE_AB;
    case BATTLEGROUND_AV:
        return BATTLEGROUND_QUEUE_AV;
    case BATTLEGROUND_EY:
        return BATTLEGROUND_QUEUE_EY;
    case BATTLEGROUND_SA:
        return BATTLEGROUND_QUEUE_SA;
    case BATTLEGROUND_IC:
        return BATTLEGROUND_QUEUE_IC;
    case BATTLEGROUND_TP:
        return BATTLEGROUND_QUEUE_TP;
    case BATTLEGROUND_BG:
        return BATTLEGROUND_QUEUE_BG;
    case BATTLEGROUND_RB:
        return BATTLEGROUND_QUEUE_RB;
    case BATTLEGROUND_AA:
    case BATTLEGROUND_NA:
    case BATTLEGROUND_RL:
    case BATTLEGROUND_BE:
    case BATTLEGROUND_DS:
    case BATTLEGROUND_RV:
        switch (arenaType)
        {
        case ARENA_TYPE_2v2:
            return BATTLEGROUND_QUEUE_2v2;
        case ARENA_TYPE_3v3:
            return BATTLEGROUND_QUEUE_3v3;
        case ARENA_TYPE_5v5:
            return BATTLEGROUND_QUEUE_5v5;
        default:
            return BATTLEGROUND_QUEUE_NONE;
        }
    default:
        return BATTLEGROUND_QUEUE_NONE;
    }
}

BattlegroundTypeId BattlegroundMgr::BGTemplateId (BattlegroundQueueTypeId bgQueueTypeId)
{
    switch (bgQueueTypeId)
    {
    case BATTLEGROUND_QUEUE_WS:
        return BATTLEGROUND_WS;
    case BATTLEGROUND_QUEUE_AB:
        return BATTLEGROUND_AB;
    case BATTLEGROUND_QUEUE_AV:
        return BATTLEGROUND_AV;
    case BATTLEGROUND_QUEUE_EY:
        return BATTLEGROUND_EY;
    case BATTLEGROUND_QUEUE_SA:
        return BATTLEGROUND_SA;
    case BATTLEGROUND_QUEUE_IC:
        return BATTLEGROUND_IC;
    case BATTLEGROUND_QUEUE_TP:
        return BATTLEGROUND_TP;
    case BATTLEGROUND_QUEUE_BG:
        return BATTLEGROUND_BG;
    case BATTLEGROUND_QUEUE_RB:
        return BATTLEGROUND_RB;
    case BATTLEGROUND_QUEUE_2v2:
    case BATTLEGROUND_QUEUE_3v3:
    case BATTLEGROUND_QUEUE_5v5:
        return BATTLEGROUND_AA;
    default:
        return BattlegroundTypeId(0);          // used for unknown template (it existed and do nothing)
    }
}

uint8 BattlegroundMgr::BGArenaType (BattlegroundQueueTypeId bgQueueTypeId)
{
    switch (bgQueueTypeId)
    {
    case BATTLEGROUND_QUEUE_2v2:
        return ARENA_TYPE_2v2;
    case BATTLEGROUND_QUEUE_3v3:
        return ARENA_TYPE_3v3;
    case BATTLEGROUND_QUEUE_5v5:
        return ARENA_TYPE_5v5;
    default:
        return 0;
    }
}

void BattlegroundMgr::ToggleTesting ()
{
    m_Testing = !m_Testing;
    if (m_Testing)
        sWorld->SendWorldText(LANG_DEBUG_BG_ON);
    else
        sWorld->SendWorldText(LANG_DEBUG_BG_OFF);
}

void BattlegroundMgr::ToggleArenaTesting ()
{
    m_ArenaTesting = !m_ArenaTesting;
    if (m_ArenaTesting)
        sWorld->SendWorldText(LANG_DEBUG_ARENA_ON);
    else
        sWorld->SendWorldText(LANG_DEBUG_ARENA_OFF);
}

void BattlegroundMgr::SetHolidayWeekends (uint32 mask)
{
    for (uint32 bgtype = 1; bgtype < MAX_BATTLEGROUND_TYPE_ID; ++bgtype)
    {
        if (Battleground * bg = GetBattlegroundTemplate(BattlegroundTypeId(bgtype)))
        {
            bg->SetHoliday(mask & (1 << bgtype));
        }
    }
}

void BattlegroundMgr::ScheduleQueueUpdate (uint32 arenaMatchmakerRating, uint8 arenaType, BattlegroundQueueTypeId bgQueueTypeId, BattlegroundTypeId bgTypeId, BattlegroundBracketId bracket_id)
{
    //This method must be atomic, TODO add mutex
    //we will use only 1 number created of bgTypeId and bracket_id
    uint64 schedule_id = ((uint64) arenaMatchmakerRating << 32) | (arenaType << 24) | (bgQueueTypeId << 16) | (bgTypeId << 8) | bracket_id;
    bool found = false;
    for (uint8 i = 0; i < m_QueueUpdateScheduler.size(); i++)
    {
        if (m_QueueUpdateScheduler[i] == schedule_id)
        {
            found = true;
            break;
        }
    }
    if (!found)
        m_QueueUpdateScheduler.push_back(schedule_id);
}

uint32 BattlegroundMgr::GetMaxRatingDifference () const
{
    // this is for stupid people who can't use brain and set max rating difference to 0
    uint32 diff = sWorld->getIntConfig(CONFIG_ARENA_MAX_RATING_DIFFERENCE);
    if (diff == 0)
        diff = 5000;
    return diff;
}

uint32 BattlegroundMgr::GetRatingDiscardTimer () const
{
    return sWorld->getIntConfig(CONFIG_ARENA_RATING_DISCARD_TIMER);
}

uint32 BattlegroundMgr::GetPrematureFinishTime () const
{
    return sWorld->getIntConfig(CONFIG_BATTLEGROUND_PREMATURE_FINISH_TIMER);
}

HolidayIds BattlegroundMgr::BGTypeToWeekendHolidayId (BattlegroundTypeId bgTypeId)
{
    switch (bgTypeId)
    {
    case BATTLEGROUND_AV:
        return HOLIDAY_CALL_TO_ARMS_AV;
    case BATTLEGROUND_EY:
        return HOLIDAY_CALL_TO_ARMS_EY;
    case BATTLEGROUND_WS:
        return HOLIDAY_CALL_TO_ARMS_WS;
    case BATTLEGROUND_SA:
        return HOLIDAY_CALL_TO_ARMS_SA;
    case BATTLEGROUND_AB:
        return HOLIDAY_CALL_TO_ARMS_AB;
    case BATTLEGROUND_IC:
        return HOLIDAY_CALL_TO_ARMS_IC;
    case BATTLEGROUND_TP:
        return HOLIDAY_CALL_TO_ARMS_TP;
    case BATTLEGROUND_BG:
        return HOLIDAY_CALL_TO_ARMS_BG;
    default:
        return HOLIDAY_NONE;
    }
}

BattlegroundTypeId BattlegroundMgr::WeekendHolidayIdToBGType (HolidayIds holiday)
{
    switch (holiday)
    {
    case HOLIDAY_CALL_TO_ARMS_AV:
        return BATTLEGROUND_AV;
    case HOLIDAY_CALL_TO_ARMS_EY:
        return BATTLEGROUND_EY;
    case HOLIDAY_CALL_TO_ARMS_WS:
        return BATTLEGROUND_WS;
    case HOLIDAY_CALL_TO_ARMS_SA:
        return BATTLEGROUND_SA;
    case HOLIDAY_CALL_TO_ARMS_AB:
        return BATTLEGROUND_AB;
    case HOLIDAY_CALL_TO_ARMS_IC:
        return BATTLEGROUND_IC;
    case HOLIDAY_CALL_TO_ARMS_TP:
        return BATTLEGROUND_TP;
    case HOLIDAY_CALL_TO_ARMS_BG:
        return BATTLEGROUND_BG;
    default:
        return BATTLEGROUND_TYPE_NONE;
    }
}

bool BattlegroundMgr::IsBGWeekend (BattlegroundTypeId bgTypeId)
{
    return IsHolidayActive(BGTypeToWeekendHolidayId(bgTypeId));
}

void BattlegroundMgr::DoCompleteAchievement (uint32 achievement, Player * player)
{
    AchievementEntry const* AE = GetAchievementStore()->LookupEntry(achievement);

    if (!player)
    {
        //Map::PlayerList const &PlayerList = this->GetPlayers();
        //GroupsQueueType::iterator group = SelectedGroups.begin();

        //if (!PlayerList.isEmpty())
        //for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
        //    for (GroupsQueueType::iterator itr = group; itr != SelectedGroups.end(); ++itr)
        //        if (Player *pPlayer = itr->getSource())
        //            pPlayer->CompletedAchievement(AE);
    }
    else
    {
        player->CompletedAchievement(AE);
    }
}
