#include <pebble.h>
#include "settings.h"

uint32_t vibeSegementsShort[] = { VIBE_SHORT };
static const VibePattern VIBE_PATTERN_SHORT = { .durations = vibeSegementsShort, .num_segments = ARRAY_LENGTH(vibeSegementsShort) };
uint32_t vibeSegementsLong[] = { VIBE_LONG };
static const VibePattern VIBE_PATTERN_LONG = { .durations = vibeSegementsLong, .num_segments = ARRAY_LENGTH(vibeSegementsLong) };
uint32_t vibeSegementsShortShort[] = { VIBE_SHORT, VIBE_PAUSE, VIBE_SHORT };
static const VibePattern VIBE_PATTERN_SHORT_SHORT = { .durations = vibeSegementsShortShort, .num_segments = ARRAY_LENGTH(vibeSegementsShortShort) };
uint32_t vibeSegementsShortLong[] = { VIBE_SHORT, VIBE_PAUSE, VIBE_LONG };
static const VibePattern VIBE_PATTERN_SHORT_LONG = { .durations = vibeSegementsShortLong, .num_segments = ARRAY_LENGTH(vibeSegementsShortLong) };
uint32_t vibeSegementsLongShort[] = { VIBE_LONG, VIBE_PAUSE, VIBE_SHORT };
static const VibePattern VIBE_PATTERN_LONG_SHORT = { .durations = vibeSegementsLongShort, .num_segments = ARRAY_LENGTH(vibeSegementsLongShort) };
uint32_t vibeSegementsLongLong[] = { VIBE_LONG, VIBE_PAUSE, VIBE_LONG };
static const VibePattern VIBE_PATTERN_LONG_LONG = { .durations = vibeSegementsLongLong, .num_segments = ARRAY_LENGTH(vibeSegementsLongLong) };
uint32_t vibeSegementsShortShortShort[] = { VIBE_SHORT, VIBE_PAUSE, VIBE_SHORT, VIBE_PAUSE, VIBE_SHORT };
static const VibePattern VIBE_PATTERN_SHORT_SHORT_SHORT = { .durations = vibeSegementsShortShortShort, .num_segments = ARRAY_LENGTH(vibeSegementsShortShortShort) };
//uint32_t vibeSegementsVeryLong[] = { 600 };
//static const VibePattern VIBE_PATTERN_VERY_LONG = { .durations = vibeSegementsVeryLong, .num_segments = ARRAY_LENGTH(vibeSegementsVeryLong) };

																							// 0	// 1									// 2								// 3											// 4											// 5											// 6											// 7
static const VibePattern *VIBE_PATTERNS[] = { NULL, &VIBE_PATTERN_SHORT, &VIBE_PATTERN_LONG, &VIBE_PATTERN_SHORT_SHORT, &VIBE_PATTERN_SHORT_LONG, &VIBE_PATTERN_LONG_SHORT, &VIBE_PATTERN_LONG_LONG, &VIBE_PATTERN_SHORT_SHORT_SHORT };

static ClaySettings settings = { VIBE_ENABLED_DEFAULT,
																VIBE_ON_NOTIFICATION_ENABLED_DEFAULT,
																VIBE_ON_TIMER_EXPIRED_PATTERN_INDEX_DEFAULT,
																VIBE_OFF_PATTERN_INDEX,
																VIBE_ON_BUTTON_STARTS_TIMEOUT_DEFAULT_TIMER_PATTERN_INDEX_DEFAULT,
																VIBE_ON_BUTTON_STARTS_TIMEOUT_SHORT_TIMER_PATTERN_INDEX_DEFAULT,
																VIBE_ON_BUTTON_STARTS_INTERMISSION_TIMER_PATTERN_INDEX_DEFAULT,
																// Notifications [second, onDefaultTimeoutTimerEnabled, onDefaultShortTimerEnabled, onIntermissionTimerEnabled, vibePatternIndex, stateMessage]
																{ { 10, true, true, true, 3, "10\" TILL READY!" },
																  { 0, false, false, false, 0, "" },
																	{ 0, false, false, false, 0, "" }
																}
															 };
const int settingsVersionCurrent = 1;

// TODO: add version to storage and migrate storage data if necessary
// https://developer.pebble.com/guides/events-and-services/persistent-storage/

// TODO: add settings for motion sensor (enable / disable, vibration pattern on starting timeout / intermission timer)

// Read settings from persistent storage
static void loadSettings(void) {
	if(persist_exists(SETTINGS_KEY)) {
		persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
		for(int i = 0; i < NOTIFICATION_MAX; i++) {
			settings.notifications[i].stateMessage = malloc(NOTIFICATION_MSG_MAX_LEN + 1);
			persist_read_string(SETTINGS_KEY_NOTIFICATION_MSG_START + i, settings.notifications[i].stateMessage, NOTIFICATION_MSG_MAX_LEN);
		}
	}
}

// Delete the settings from persistent storage
static void deleteSettings(void) {
	if(persist_exists(SETTINGS_KEY)) {
		persist_delete(SETTINGS_KEY);
		for(int i = 0; i < NOTIFICATION_MAX; i++) {
			persist_delete(SETTINGS_KEY_NOTIFICATION_MSG_START + i);
		}
	}
}

// Save the settings to persistent storage
static void saveSettings(void) {
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
	for(int i = 0; i < NOTIFICATION_MAX; i++) {
		persist_write_string(SETTINGS_KEY_NOTIFICATION_MSG_START + i, settings.notifications[i].stateMessage);
	}
	persist_write_int(SETTINGS_KEY_VERSION, settingsVersionCurrent);
}

// Handle the response from AppMessage
static void inboxReceivedHandler(DictionaryIterator *iter, void *context) {
	// Handle global section
	Tuple *vibesEnabled = dict_find(iter, MESSAGE_KEY_VibesEnabled);
	if(vibesEnabled) {
		settings.vibesEnabled = vibesEnabled->value->int32 == 1;
	}
	Tuple *vibesOnNotificationsEnabled = dict_find(iter, MESSAGE_KEY_VibesOnNotificationsEnabled);
	if(vibesOnNotificationsEnabled) {
		settings.vibesOnNotificationsEnabled = vibesOnNotificationsEnabled->value->int32 == 1;
	}
	Tuple *vibesOnTimerExpiredPatternIndex = dict_find(iter, MESSAGE_KEY_VibesOnTimerExpiredPatternIndex);
	if(vibesOnTimerExpiredPatternIndex) {
		settings.vibesOnTimerExpiredPatternIndex = atoi(vibesOnTimerExpiredPatternIndex->value->cstring);
	}
	
	// Handle button section
	Tuple *vibesOnButtonPressedPatternIndex = dict_find(iter, MESSAGE_KEY_VibesOnButtonPressedPatternIndex);
	if(vibesOnButtonPressedPatternIndex) {
		settings.vibesOnButtonPressedPatternIndex = atoi(vibesOnButtonPressedPatternIndex->value->cstring);
	}
	Tuple *vibesOnButtonStartsTimeoutDefaultTimerPatternIndex = dict_find(iter, MESSAGE_KEY_VibesOnButtonStartsTimeoutDefaultTimerPatternIndex);
	if(vibesOnButtonStartsTimeoutDefaultTimerPatternIndex) {
		settings.vibesOnButtonStartsTimeoutDefaultTimerPatternIndex = atoi(vibesOnButtonStartsTimeoutDefaultTimerPatternIndex->value->cstring);
	}
	Tuple *vibesOnButtonStartsTimeoutShortTimerPatternIndex = dict_find(iter, MESSAGE_KEY_VibesOnButtonStartsTimeoutShortTimerPatternIndex);
	if(vibesOnButtonStartsTimeoutShortTimerPatternIndex) {
		settings.vibesOnButtonStartsTimeoutShortTimerPatternIndex = atoi(vibesOnButtonStartsTimeoutShortTimerPatternIndex->value->cstring);
	}
	Tuple *vibesOnButtonStartsIntermissionTimerPatternIndex = dict_find(iter, MESSAGE_KEY_VibesOnButtonStartsIntermissionTimerPatternIndex);
	if(vibesOnButtonStartsIntermissionTimerPatternIndex) {
		settings.vibesOnButtonStartsIntermissionTimerPatternIndex = atoi(vibesOnButtonStartsIntermissionTimerPatternIndex->value->cstring);
	}
	
	// Handle notification sections
	Tuple *notification_1_Second = dict_find(iter, MESSAGE_KEY_Notification_1_Second);
	if(notification_1_Second) {
		settings.notifications[0].second = notification_1_Second->value->int32;
	}
	Tuple *notification_1_OnTimeoutDefaultTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_1_OnTimeoutDefaultTimerEnabled);
	if(notification_1_OnTimeoutDefaultTimerEnabled) {
		settings.notifications[0].onTimeoutDefaultTimerEnabled = notification_1_OnTimeoutDefaultTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_1_OnTimeoutShortTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_1_OnTimeoutShortTimerEnabled);
	if(notification_1_OnTimeoutShortTimerEnabled) {
		settings.notifications[0].onTimeoutShortTimerEnabled = notification_1_OnTimeoutShortTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_1_OnIntermissionTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_1_OnIntermissionTimerEnabled);
	if(notification_1_OnIntermissionTimerEnabled) {
		settings.notifications[0].onIntermissionTimerEnabled = notification_1_OnIntermissionTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_1_VibePatternIndex = dict_find(iter, MESSAGE_KEY_Notification_1_VibePatternIndex);
	if(notification_1_VibePatternIndex) {
		settings.notifications[0].vibePatternIndex = atoi(notification_1_VibePatternIndex->value->cstring);
	}
	Tuple *notification_1_StateMessage = dict_find(iter, MESSAGE_KEY_Notification_1_StateMessage);
	if(notification_1_StateMessage) {
		settings.notifications[0].stateMessage = notification_1_StateMessage->value->cstring;
	}

	Tuple *notification_2_Second = dict_find(iter, MESSAGE_KEY_Notification_2_Second);
	if(notification_2_Second) {
		settings.notifications[1].second = notification_2_Second->value->int32;
	}
	Tuple *notification_2_OnTimeoutDefaultTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_2_OnTimeoutDefaultTimerEnabled);
	if(notification_2_OnTimeoutDefaultTimerEnabled) {
		settings.notifications[1].onTimeoutDefaultTimerEnabled = notification_2_OnTimeoutDefaultTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_2_OnTimeoutShortTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_2_OnTimeoutShortTimerEnabled);
	if(notification_2_OnTimeoutShortTimerEnabled) {
		settings.notifications[1].onTimeoutShortTimerEnabled = notification_2_OnTimeoutShortTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_2_OnIntermissionTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_2_OnIntermissionTimerEnabled);
	if(notification_2_OnIntermissionTimerEnabled) {
		settings.notifications[1].onIntermissionTimerEnabled = notification_2_OnIntermissionTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_2_VibePatternIndex = dict_find(iter, MESSAGE_KEY_Notification_2_VibePatternIndex);
	if(notification_2_VibePatternIndex) {
		settings.notifications[1].vibePatternIndex = atoi(notification_2_VibePatternIndex->value->cstring);
	}
	Tuple *notification_2_StateMessage = dict_find(iter, MESSAGE_KEY_Notification_2_StateMessage);
	if(notification_2_StateMessage) {
		settings.notifications[1].stateMessage = notification_2_StateMessage->value->cstring;
	}
	
	Tuple *notification_3_Second = dict_find(iter, MESSAGE_KEY_Notification_3_Second);
	if(notification_3_Second) {
		settings.notifications[2].second = notification_3_Second->value->int32;
	}
	Tuple *notification_3_OnTimeoutDefaultTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_3_OnTimeoutDefaultTimerEnabled);
	if(notification_3_OnTimeoutDefaultTimerEnabled) {
		settings.notifications[2].onTimeoutDefaultTimerEnabled = notification_3_OnTimeoutDefaultTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_3_OnTimeoutShortTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_3_OnTimeoutShortTimerEnabled);
	if(notification_3_OnTimeoutShortTimerEnabled) {
		settings.notifications[2].onTimeoutShortTimerEnabled = notification_3_OnTimeoutShortTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_3_OnIntermissionTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_3_OnIntermissionTimerEnabled);
	if(notification_3_OnIntermissionTimerEnabled) {
		settings.notifications[2].onIntermissionTimerEnabled = notification_3_OnIntermissionTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_3_VibePatternIndex = dict_find(iter, MESSAGE_KEY_Notification_3_VibePatternIndex);
	if(notification_3_VibePatternIndex) {
		settings.notifications[2].vibePatternIndex = atoi(notification_3_VibePatternIndex->value->cstring);
	}
	Tuple *notification_3_StateMessage = dict_find(iter, MESSAGE_KEY_Notification_3_StateMessage);
	if(notification_3_StateMessage) {
		settings.notifications[2].stateMessage = notification_3_StateMessage->value->cstring;
	}

  // Save the new settings to persistent storage
  saveSettings();
}

void initSettings(void) {
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "init settings");
	loadSettings();

	// Listen for AppMessages
	app_message_register_inbox_received(inboxReceivedHandler);
	app_message_open(512, 512);
}

bool isVibesEnabled(void) {
	return settings.vibesEnabled;
}

bool invertVibesEnabled(void) {
	settings.vibesEnabled = !settings.vibesEnabled;
	saveSettings();
	return settings.vibesEnabled;
}

bool isVibesOnNotificationsEnabled(void) {
	return (settings.vibesEnabled && settings.vibesOnNotificationsEnabled);
}

const VibePattern *getVibesOnTimerExpiredPattern(void) {
	if(settings.vibesEnabled) {
		return VIBE_PATTERNS[settings.vibesOnTimerExpiredPatternIndex];
	}
	return NULL;
}

const VibePattern *getOnButtonPressedVibePattern(void) {
	if(settings.vibesEnabled) {
		return VIBE_PATTERNS[settings.vibesOnButtonPressedPatternIndex];
	}
	return NULL;
}

bool invertVibesOnButtonPressedEnabled(void) {
	if(settings.vibesOnButtonPressedPatternIndex > VIBE_OFF_PATTERN_INDEX) {
		settings.vibesOnButtonPressedPatternIndex = VIBE_OFF_PATTERN_INDEX;
	} else {
		settings.vibesOnButtonPressedPatternIndex = VIBE_DEFAULT_INDEX;
	}
	saveSettings();
	return (settings.vibesOnButtonPressedPatternIndex > VIBE_OFF_PATTERN_INDEX);
}

const VibePattern *getOnButtonStartsTimeoutDefaultTimerVibePattern(void) {
	if(settings.vibesEnabled) {
		if(settings.vibesOnButtonStartsTimeoutDefaultTimerPatternIndex > VIBE_OFF_PATTERN_INDEX) {
			return VIBE_PATTERNS[settings.vibesOnButtonStartsTimeoutDefaultTimerPatternIndex];
		}
	}
	return VIBE_PATTERNS[settings.vibesOnButtonPressedPatternIndex];
}

const VibePattern *getOnButtonStartsTimeoutShortTimerVibePattern(void) {
	if(settings.vibesEnabled) {
		if(settings.vibesOnButtonStartsTimeoutShortTimerPatternIndex > VIBE_OFF_PATTERN_INDEX) {
			return VIBE_PATTERNS[settings.vibesOnButtonStartsTimeoutShortTimerPatternIndex];
		}
	}
	return VIBE_PATTERNS[settings.vibesOnButtonPressedPatternIndex];
}

const VibePattern *getOnButtonStartsIntermissionTimerVibePattern(void) {
	if(settings.vibesEnabled) {
		if(settings.vibesOnButtonStartsIntermissionTimerPatternIndex > VIBE_OFF_PATTERN_INDEX) {
			return VIBE_PATTERNS[settings.vibesOnButtonStartsIntermissionTimerPatternIndex];
		}
	}
	return VIBE_PATTERNS[settings.vibesOnButtonPressedPatternIndex];
}

const Notification *getTimeoutNotification(int second, bool isShortTimer) {
	for(int i = 0; i < NOTIFICATION_MAX; i++) {
		if(settings.notifications[i].second == second && ((!isShortTimer && settings.notifications[i].onTimeoutDefaultTimerEnabled) || (isShortTimer && settings.notifications[i].onTimeoutShortTimerEnabled))) {
			return &settings.notifications[i];
		}
	}
	return NULL;
}

const Notification *getIntermissionNotification(int second) {
	for(int i = 0; i < NOTIFICATION_MAX; i++) {
		if(settings.notifications[i].second == second && settings.notifications[i].onIntermissionTimerEnabled) {
			return &settings.notifications[i];
		}
	}
	return NULL;
}

const VibePattern *getVibesNotificationPattern(const Notification *notification) {
	if(notification != NULL && settings.vibesEnabled && settings.vibesOnNotificationsEnabled) {
		return VIBE_PATTERNS[notification->vibePatternIndex];
	}
	return NULL;
}

char *getNotificationStateMessage(const Notification *notification) {
	if(notification != NULL) {
		return notification->stateMessage;
	}
	return NULL;
}

int getButtonPressedLongDuration(void) {
	return BUTTON_LONG_PRESSED_DURATION_DEFAULT;
}

GColor getBackgroundColor(void) {
	return COLOR_BGCOLOR_DEFAULT;
}

GColor getForegroundColor(void) {
	return COLOR_FORECOLOR_DEFAULT;
}

char *getStateMessageVibesOn(void) {
	return STATE_MSG_VIBRATION_ON;
}

char *getStateMessageVibesOff(void) {
	return STATE_MSG_VIBRATION_OFF;
}

char *getStateMessageVibesOnButtonPressedOn(void) {
	return STATE_MSG_VIBRATION_BUTTON_ON;
}

char *getStateMessageVibesOnButtonPressedOff(void) {
	return STATE_MSG_VIBRATION_BUTTON_OFF;
}
