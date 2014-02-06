LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/IntroLayer.cpp \
                   ../../Classes/Utilities/sqlite3/sqlite3.c \
                   ../../Classes/Utilities/LZDBUtils.cpp \
                   ../../Classes/game_assist/game_audio_manager/GameSounds.cpp \
                   ../../Classes/game_data/game_state/GameData.cpp \
                   ../../Classes/game_data/level_data/Level.cpp \
                   ../../Classes/game_data/level_data/Levels.cpp \
                   ../../Classes/game_data/level_data/LevelParser.cpp \
                   ../../Classes/game_data/scene_data/Chapter.cpp \
                   ../../Classes/game_data/scene_data/Chapters.cpp \
                   ../../Classes/game_data/scene_data/ChpaterParser.cpp \
                   ../../Classes/game_interface/about/About.cpp \
                   ../../Classes/game_interface/chapter_select/ChpaterSelect.cpp \
                   ../../Classes/game_interface/level_selection/LevelSelection.cpp \
                   ../../Classes/game_interface/start/StartGameScene.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
