module.exports = [
  {
    "type": "heading",
    "defaultValue": "UMPIRECLOCK Configuration",
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Global",
      },
			{
        "type": "toggle",
        "messageKey": "VibesEnabled",
        "label": "Enable vibration",
				"description": "If disabled, all other vibration settings are ignored.",
        "defaultValue": true,
      },
      {
        "type": "toggle",
        "messageKey": "VibesOnNotificationsEnabled",
        "label": "Enable vibration on notifications",
				"description": "If disabled, all custom vibration settings for notifications (except expired timer) are ignored.",
        "defaultValue": true,
      },
			{
				"type": "select",
				"messageKey": "VibesOnTimerExpiredPatternIndex",
				"label": 'Vibration pattern when timer expires, reaching 0"',
				"description": "Not affected by the 'Enable vibration on notifications' setting.",
				"defaultValue": "2",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short + Long",
						"value": "4" 
					},
					{ 
						"label": "Long + Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
		],
	},
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Buttons",
      },
			{
				"type": "select",
				"messageKey": "VibesOnButtonPressedPatternIndex",
				"label": "Vibration pattern on pressing a button",
				"description": "If set to 'Off', vibration settings for starting a timer are still active.",
				"defaultValue": "0",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short + Long",
						"value": "4" 
					},
					{ 
						"label": "Long + Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "select",
				"messageKey": "VibesOnButtonStartsTimeoutDefaultTimerPatternIndex",
				"label": 'Vibration pattern on pressing a button to start the timout timer (60")',
				"description": "If set to 'Off', a vibration for pressing a button may occur.",
				"defaultValue": "1",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short + Long",
						"value": "4" 
					},
					{ 
						"label": "Long + Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "select",
				"messageKey": "VibesOnButtonStartsTimeoutShortTimerPatternIndex",
				"label": 'Vibration pattern on pressing a button to start the short timeout timer (30")',
				"description": "If set to 'Off', a vibration for pressing a button may occur.",
				"defaultValue": "3",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short - Long",
						"value": "4" 
					},
					{ 
						"label": "Long - Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "select",
				"messageKey": "VibesOnButtonStartsIntermissionTimerPatternIndex",
				"label": 'Vibration pattern on pressing a button to start the intermission timer (60")',
				"description": "If set to 'Off', a vibration for pressing a button may occur.",
				"defaultValue": "3",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short - Long",
						"value": "4" 
					},
					{ 
						"label": "Long - Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Notification 1"
      },
			{
				"type": "slider",
				"messageKey": "Notification_1_Second",
				"label": "The second this notification should occur.",
				"min": 0,
				"max": 64,
				"step": 1,
				"defaultValue": 10,
			},
      {
        "type": "toggle",
        "messageKey": "Notification_1_OnTimeoutDefaultTimerEnabled",
        "label": 'Enable this notification for timeout timer (60").',
        "defaultValue": true,
      },
      {
        "type": "toggle",
        "messageKey": "Notification_1_OnTimeoutShortTimerEnabled",
        "label": 'Enable this notification for short timeout timer (30").',
        "defaultValue": true,
      },
      {
        "type": "toggle",
        "messageKey": "Notification_1_OnIntermissionTimerEnabled",
        "label": 'Enable this notification for intermission timer (60").',
        "defaultValue": true,
      },
			{
				"type": "select",
				"messageKey": "Notification_1_VibePatternIndex",
				"label": "Vibration pattern for this notification",
				"defaultValue": "3",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short - Long",
						"value": "4" 
					},
					{ 
						"label": "Long - Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "input",
				"messageKey": "Notification_1_StateMessage",
				"label": "State message for this notification",
				"description": "If left empty, the state message is not changed when this notification occurs.",
				"defaultValue": '10" TILL READY!',
				"attributes": {
					"placeholder": "eg: WARNING!",
					"limit": 20
				}
			},
		],
	},
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Notification 2"
      },
			{
				"type": "slider",
				"messageKey": "Notification_2_Second",
				"label": "The second this notification should occur.",
				"min": 0,
				"max": 64,
				"step": 1,
				"defaultValue": 0,
			},
      {
        "type": "toggle",
        "messageKey": "Notification_2_OnTimeoutDefaultTimerEnabled",
        "label": 'Enable this notification for timeout timer (60").',
        "defaultValue": false,
      },
      {
        "type": "toggle",
        "messageKey": "Notification_2_OnTimeoutShortTimerEnabled",
        "label": 'Enable this notification for short timeout timer (30").',
        "defaultValue": false,
      },
      {
        "type": "toggle",
        "messageKey": "Notification_2_OnIntermissionTimerEnabled",
        "label": 'Enable this notification for intermission timer (60").',
        "defaultValue": false,
      },
			{
				"type": "select",
				"messageKey": "Notification_2_VibePatternIndex",
				"label": "Vibration pattern for this notification",
				"defaultValue": "0",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short - Long",
						"value": "4" 
					},
					{ 
						"label": "Long - Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "input",
				"messageKey": "Notification_2_StateMessage",
				"label": "State message for this notification",
				"description": "If left empty, the state message is not changed when this notification occurs.",
				"attributes": {
					"placeholder": "eg: WARNING!",
					"limit": 20
				}
			},
		],
	},
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Notification 3"
      },
			{
				"type": "slider",
				"messageKey": "Notification_3_Second",
				"label": "The second this notification should occur.",
				"min": 0,
				"max": 64,
				"step": 1,
				"defaultValue": 0,
			},
      {
        "type": "toggle",
        "messageKey": "Notification_3_OnTimeoutDefaultTimerEnabled",
        "label": 'Enable this notification for timeout timer (60").',
        "defaultValue": false,
      },
      {
        "type": "toggle",
        "messageKey": "Notification_3_OnTimeoutShortTimerEnabled",
        "label": 'Enable this notification for short timeout timer (30").',
        "defaultValue": false,
      },
      {
        "type": "toggle",
        "messageKey": "Notification_3_OnIntermissionTimerEnabled",
        "label": 'Enable this notification for intermission timer (60").',
        "defaultValue": false,
      },
			{
				"type": "select",
				"messageKey": "Notification_3_VibePatternIndex",
				"label": "Vibration pattern for this notification",
				"defaultValue": "0",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short - Long",
						"value": "4" 
					},
					{ 
						"label": "Long - Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "input",
				"messageKey": "Notification_3_StateMessage",
				"label": "State message for this notification",
				"description": "If left empty, the state message is not changed when this notification occurs.",
				"attributes": {
					"placeholder": "eg: WARNING!",
					"limit": 20
				}
			},
		],
	},
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  },
];