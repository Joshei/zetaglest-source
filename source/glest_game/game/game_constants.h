//
//      game_constants.h: game setup menu as it appears to
//      to the host
//
//      This file is part of ZetaGlest <https://github.com/ZetaGlest>
//
//      Copyright (C) 2018  The ZetaGlest team
//
//      ZetaGlest is a fork of MegaGlest <https://megaglest.org>
//
//      This program is free software: you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation, either version 3 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef _GLEST_GAME_GAMECONSTANTS_H_
#   define _GLEST_GAME_GAMECONSTANTS_H_

#   include <cassert>
#   include <stdio.h>
#   include "vec.h"
#   include <map>
#   include <string>
#   include "conversion.h"
#   include <stdexcept>

using namespace
  Shared::Graphics;
using namespace
  std;
using namespace
  Shared::Util;

namespace
  Glest
{
  namespace
    Game
  {

    template <
      typename
      T >
      class
      EnumParser
    {
    private:
      typedef
        map <
        string,
        T >
        enumMapType;
      typedef typename
        enumMapType::const_iterator
        enumMapTypeIter;
      EnumParser ();

      enumMapType
        enumMap;

    public:

      static T
      getEnum (const string & value)
      {
        static
          EnumParser <
          T >
          parser;
        enumMapTypeIter
          iValue = parser.enumMap.find (value);
        if (iValue == parser.enumMap.end ())
          {
            throw
            std::runtime_error ("unknown enum lookup [" + value + "]");
          }
        return
          iValue->
          second;
      }
      static string
      getString (const T & value)
      {
        static
          EnumParser <
          T >
          parser;
        for (enumMapTypeIter iValue = parser.enumMap.begin ();
             iValue != parser.enumMap.end (); ++iValue)
          {
            if (iValue->second == value)
              {
                return iValue->first;
              }
          }
        throw
        std::runtime_error ("unknown enum lookup [" + intToStr (value) + "]");
      }
      static int
      getCount ()
      {
        static
          EnumParser <
          T >
          parser;
        return parser.enumMap.size ();
      }
    };

// =====================================================
//      class GameConstants
// =====================================================

    const Vec4f
    BLACK (0.0f, 0.0f, 0.0f, 1.0f);
    const Vec4f
    RED (1.0f, 0.0f, 0.0f, 1.0f);
    const Vec4f
    GREEN (0.0f, 1.0f, 0.0f, 1.0f);
    const Vec4f
    BLUE (0.0f, 0.0f, 1.0f, 1.0f);
    const Vec4f
    GLASS (1.0f, 1.0f, 1.0f, 0.3f);
    const Vec4f
    CYAN (0.0f, 1.0f, 1.0f, 1.0f);
    const Vec4f
    YELLOW (1.0f, 1.0f, 0.0f, 1.0f);
    const Vec4f
    MAGENTA (1.0f, 0.0f, 1.0f, 1.0f);
    const Vec4f
    WHITE (1.0f, 1.0f, 1.0f, 1.0f);
    const Vec4f
    ORANGE (1.0f, 0.7f, 0.0f, 1.0f);

    enum PathFinderType
    {
      pfBasic
    };

    enum TravelState
    {
      tsArrived,
      tsMoving,
      tsBlocked,
      tsImpossible
    };

    enum ControlType
    {
      ctClosed,
      ctCpuEasy,
      ctCpu,
      ctCpuUltra,
      ctCpuMega,
      ctNetwork,
      ctNetworkUnassigned,
      ctHuman,

      ctNetworkCpuEasy,
      ctNetworkCpu,
      ctNetworkCpuUltra,
      ctNetworkCpuMega
    };

    enum NetworkRole
    {
      nrServer,
      nrClient,
      nrIdle
    };

    enum FactionPersonalityType
    {
      fpt_Normal,
      fpt_Observer,

      fpt_EndCount
    };

    enum MasterServerGameStatusType
    {
      game_status_waiting_for_players = 0,
      game_status_waiting_for_start = 1,
      game_status_in_progress = 2,
      game_status_finished = 3
    };

    class
      GameConstants
    {
    public:
      static const int
        specialFactions = fpt_EndCount - 1;
      static const int
        maxPlayers = 10;
      static const int
        serverPort = 61357;
      static const int
        serverAdminPort = 61355;
      static int
        updateFps;
      static int
        cameraFps;

      static int
        networkFramePeriod;
      static const int
        networkPingInterval = 5;
      static const int
        networkSmoothInterval = 30;
      static const int
        maxClientConnectHandshakeSecs = 10;

      static const int
        cellScale = 2;
      static const int
        clusterSize = 16;

      static const char *
        folder_path_maps;
      static const char *
        folder_path_scenarios;
      static const char *
        folder_path_techs;
      static const char *
        folder_path_tilesets;
      static const char *
        folder_path_tutorials;

      static const char *
        NETWORK_SLOT_UNCONNECTED_SLOTNAME;
      static const char *
        NETWORK_SLOT_CLOSED_SLOTNAME;

      static const char *
        folder_path_screenshots;

      static const char *
        OBSERVER_SLOTNAME;
      static const char *
        RANDOMFACTION_SLOTNAME;

      static const char *
        steamCacheInstanceKey;
      static const char *
        preCacheThreadCacheLookupKey;
      static const char *
        playerTextureCacheLookupKey;
      static const char *
        ircClientCacheLookupKey;
      static const char *
        factionPreviewTextureCacheLookupKey;
      static const char *
        characterMenuScreenPositionListCacheLookupKey;
      static const char *
        pathCacheLookupKey;
      static const char *
        path_data_CacheLookupKey;
      static const char *
        path_ini_CacheLookupKey;
      static const char *
        path_logs_CacheLookupKey;

      static const char *
        application_name;

      static const char *
        saveNetworkGameFileServerCompressed;
      static const char *
        saveNetworkGameFileServer;
      static const char *
        saveNetworkGameFileClientCompressed;
      static const char *
        saveNetworkGameFileClient;
      static const char *
        saveGameFileDefault;
      static const char *
        saveGameFileAutoTestDefault;
      static const char *
        saveGameFilePattern;

      // VC++ Chokes on init of non integral static types
      static const float
        normalMultiplier;
      static const float
        easyMultiplier;
      static const float
        ultraMultiplier;
      static const float
        megaMultiplier;
      //

      static const char *
        LOADING_SCREEN_FILE;
      static const char *
        LOADING_SCREEN_FILE_FILTER;
      static const char *
        PREVIEW_SCREEN_FILE;
      static const char *
        PREVIEW_SCREEN_FILE_FILTER;
      static const char *
        HUD_SCREEN_FILE;
      static const char *
        HUD_SCREEN_FILE_FILTER;
    };

    enum PathType
    {
      ptMaps,
      ptScenarios,
      ptTechs,
      ptTilesets,
      ptTutorials
    };

    struct CardinalDir
    {
    public:
      enum Enum
      {
          NORTH,
          EAST,
          SOUTH,
          WEST,
      COUNT };

      CardinalDir ():
      value (NORTH)
      {
      }
      explicit
      CardinalDir (Enum v):
      value (v)
      {
      }
      explicit
      CardinalDir (int v)
      {
        assertDirValid (v);
        value = static_cast < Enum > (v);
      }
      operator
      Enum () const
      {
        return
          value;
      }
      int
      asInt () const
      {
        return (int)
          value;
      }

      static void
      assertDirValid (int v)
      {
        assert (v >= 0 && v < 4);
      }
      void
      operator++ ()
      {
        value = static_cast < Enum > ((value + 1) % 4);
      }
      void
      operator-- ()
      {                         // mod with negative numbers is a 'grey area', hence the +3 rather than -1
        value = static_cast < Enum > ((value + 3) % 4);
      }

    private:
      Enum value;
    };

}}                              //end namespace

#endif
