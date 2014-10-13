#include "fwInternal.h"

static const irr::u32 JOYSTICK_AXIS_HIT_ANGLE = 15;

InputReceiver::InputReceiver( ) :
	m_InputState(0),
	m_JoystickProfile(Hash(""))
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
	{
		m_KeyIsDown[i] = false;
	}
}

InputReceiver::~InputReceiver( )
{
}

bool InputReceiver::OnEvent(const irr::SEvent& event)
{
	char logMsg[kStrLen_Gargantuan] = {'\0'};
	blackbox::BlackBox * pBlackBox = GameEngine::GetInstance()->GetBlackBox();
	std::map<irr::u32,irr::u32>::const_iterator it;

	switch (event.EventType)
	{
		// keyboard
		case irr::EET_KEY_INPUT_EVENT:
		{
			// key down event
			if (!m_KeyIsDown[event.KeyInput.Key] && event.KeyInput.PressedDown)
			{
				it = m_InputProfile.m_InputMapping.find(event.KeyInput.Key);
				if (it != m_InputProfile.m_InputMapping.end())
				{
					snprintf(logMsg, kStrLen_Gargantuan, "key down: %u %c", event.KeyInput.Key, event.KeyInput.Char);
					pBlackBox->Log("DEBUG", 0, logMsg);
					Event evt(it->second);
					FireEvent(&evt);
				}
			}
			// key up state
			else if (m_KeyIsDown[event.KeyInput.Key] && !event.KeyInput.PressedDown)
			{
				it = m_InputProfile.m_InputMapping.find(event.KeyInput.Key);
				if (it != m_InputProfile.m_InputMapping.end())
				{
					snprintf(logMsg, kStrLen_Gargantuan, "key up: %u %c", event.KeyInput.Key, event.KeyInput.Char);
					pBlackBox->Log("DEBUG", 0, logMsg);
					Event evt(it->second + 1);
					FireEvent(&evt);
				}
			}
			m_KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			break;
		}
		// mouse	
		case irr::EET_MOUSE_INPUT_EVENT:
		{
			// I'm adding KEY_KEY_CODES_COUNT here to ensure that the mouse event enums don't conflict with the keyboard ones.
			// .. also, since we did it in the LoadProfile, we'll have to do it here.
			it = m_InputProfile.m_InputMapping.find(event.MouseInput.Event + irr::KEY_KEY_CODES_COUNT);
			if (it != m_InputProfile.m_InputMapping.end())
			{
				snprintf(logMsg, kStrLen_Gargantuan, "mouse event: %u", event.MouseInput.Event);
				pBlackBox->Log("DEBUG", 5, logMsg);
				Event evt(it->second);
				FireEvent(&evt);
			}
			{
				SMouseEvent evt(SMouseEvent::kEvent_MouseInput, &event.MouseInput);
				FireEvent(&evt);
			}
			return false;
			break;
		}
		// joystick
		case irr::EET_JOYSTICK_INPUT_EVENT:
		{
			// detect button up states for the POV hat
			if (event.JoystickEvent.POV == (irr::u16)-1)
			{
				if (CheckInputState(SInputEvent::kEvent_InputUp_Down - SInputEvent::kEvent_Input_First))
				{
					pBlackBox->Log("DEBUG", 0, "joystick pov up: -1");
					UnsetInputState(SInputEvent::kEvent_InputUp_Down - SInputEvent::kEvent_Input_First);
					Event evt(SInputEvent::kEvent_InputUp_Up);
					FireEvent(&evt);
				}
				if (CheckInputState(SInputEvent::kEvent_InputRight_Down - SInputEvent::kEvent_Input_First))
				{
					pBlackBox->Log("DEBUG", 0, "joystick pov up: -1");
					UnsetInputState(SInputEvent::kEvent_InputRight_Down - SInputEvent::kEvent_Input_First);
					Event evt(SInputEvent::kEvent_InputRight_Up);
					FireEvent(&evt);
				}
				if (CheckInputState(SInputEvent::kEvent_InputDown_Down - SInputEvent::kEvent_Input_First))
				{
					pBlackBox->Log("DEBUG", 0, "joystick pov up: -1");
					UnsetInputState(SInputEvent::kEvent_InputDown_Down - SInputEvent::kEvent_Input_First);
					Event evt(SInputEvent::kEvent_InputDown_Up);
					FireEvent(&evt);
				}
				if (CheckInputState(SInputEvent::kEvent_InputLeft_Down - SInputEvent::kEvent_Input_First))
				{
					pBlackBox->Log("DEBUG", 0, "joystick pov up: -1");
					UnsetInputState(SInputEvent::kEvent_InputLeft_Down - SInputEvent::kEvent_Input_First);
					Event evt(SInputEvent::kEvent_InputLeft_Up);
					FireEvent(&evt);
				}
			}
			// detect button down states for the POV hat
			else
			{
				const irr::u16 povDegrees = event.JoystickEvent.POV / 100;
				if (povDegrees < 360)
				{
					unsigned int virtualBtn = 0;
					const unsigned int povHashes[] = { Hash("povhatup"), Hash("povhatright"), Hash("povhatdown"), Hash("povhatleft") };

					if (povDegrees >= 360-JOYSTICK_AXIS_HIT_ANGLE || povDegrees <= 0+JOYSTICK_AXIS_HIT_ANGLE)
					{
						virtualBtn = povHashes[0];
					}
					else if (povDegrees >= 90-JOYSTICK_AXIS_HIT_ANGLE && povDegrees <= 90+JOYSTICK_AXIS_HIT_ANGLE)
					{
						virtualBtn = povHashes[1];
					}
					else if (povDegrees >= 180-JOYSTICK_AXIS_HIT_ANGLE && povDegrees <= 180+JOYSTICK_AXIS_HIT_ANGLE)
					{
						virtualBtn = povHashes[2];
					}
					else if (povDegrees >= 270-JOYSTICK_AXIS_HIT_ANGLE && povDegrees <= 270+JOYSTICK_AXIS_HIT_ANGLE)
					{
						virtualBtn = povHashes[3];
					}

					// if a direction is pressed
					if (virtualBtn)
					{
						for (int i = 0; i < sizeof(povHashes); ++i)
						{
							it = m_InputProfile.m_InputMapping.find(povHashes[i]);
							if (it != m_InputProfile.m_InputMapping.end())
							{
								// unset all other directions
								const irr::u32 index = it->second - SInputEvent::kEvent_Input_First;
								if (povHashes[i] != virtualBtn)
								{
									if (CheckInputState(index))
									{
										snprintf(logMsg, kStrLen_Gargantuan, "pov up: %u (%u)", povDegrees, event.JoystickEvent.POV);
										pBlackBox->Log("DEBUG", 0, logMsg);
										UnsetInputState(index);
										Event evt(it->second + 1);
										FireEvent(&evt);
									}
								}
								// set pressed direction
								else
								{
									if (CheckInputState(index) == 0)
									{
										snprintf(logMsg, kStrLen_Gargantuan, "pov down: %u (%u)", povDegrees, event.JoystickEvent.POV);
										pBlackBox->Log("DEBUG", 0, logMsg);
										SetInputState(index);
										Event evt(it->second);
										FireEvent(&evt);
									}
								}
							}
						}
					}
				}
			}
			
			// joystick buttons
			for (irr::u32 i = 0; i < event.JoystickEvent.NUMBER_OF_BUTTONS; ++i)
			{
				// down state
				if(event.JoystickEvent.IsButtonPressed(i))
				{
					it = m_InputProfile.m_InputMapping.find(i);
					if (it != m_InputProfile.m_InputMapping.end())
					{
						const irr::u32 index = it->second - SInputEvent::kEvent_Input_First;
						if (CheckInputState(index) == 0)
						{
							snprintf(logMsg, kStrLen_Gargantuan, "joystick button down: %u", i);
							pBlackBox->Log("DEBUG", 0, logMsg);
							SetInputState(index);
							Event evt(it->second);
							FireEvent(&evt);
						}
					}
				}
				// up state
				else
				{
					it = m_InputProfile.m_InputMapping.find(i);
					if (it != m_InputProfile.m_InputMapping.end())
					{
						const irr::u32 index = it->second - SInputEvent::kEvent_Input_First;
						if (CheckInputState(index))
						{
							snprintf(logMsg, kStrLen_Gargantuan, "joystick button up: %u", i);
							pBlackBox->Log("DEBUG", 0, logMsg);
							UnsetInputState(index);
							// this only works if the state we are tracking (down) us sequentially before the up state in the enum
							Event evt(it->second + 1);
							FireEvent(&evt);
						}
					}
				}
			}
			float DEAD_ZONE = 0.05f;
			float move = 0;
			for (int i = 0; i < event.JoystickEvent.NUMBER_OF_AXES; ++i)
			{
				move = (float)event.JoystickEvent.Axis[i] / 32767.f;
				if(fabs(move) < DEAD_ZONE)
					move = 0.f;
				//printf("axis %u is %f\n", i, move);
			}
			break;
		}
		case irr::EET_GUI_EVENT:
		{
			if(event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
			{
				SGUIEvent evt(SGUIEvent::kEvent_GUI_ButtonClicked, event.GUIEvent.Caller->getID());
				FireEvent(&evt);
			}
			break;
		}
		default:
		{
			return false;
			break;
		}
	}

	return true;
}

const bool InputReceiver::IsKeyDown(const irr::EKEY_CODE keyCode) const
{
	return m_KeyIsDown[keyCode];
}

void InputReceiver::LoadProfile(const char * filename)
{
	m_InputProfile.m_InputMapping.clear();
	//TODO: Convert these hard coded profiles to a data driven system
	if (m_JoystickProfile == Hash("Controller (XBOX 360 For Windows)"))
	{
		m_InputProfile.m_InputMapping[6] = SInputEvent::kEvent_InputQuit_Down;
		m_InputProfile.m_InputMapping[7] = SInputEvent::kEvent_InputReset_Down;
		m_InputProfile.m_InputMapping[4] = SInputEvent::kEvent_InputA6_Down;
		m_InputProfile.m_InputMapping[5] = SInputEvent::kEvent_InputA5_Down;
		m_InputProfile.m_InputMapping[2] = SInputEvent::kEvent_InputA4_Down;
		m_InputProfile.m_InputMapping[3] = SInputEvent::kEvent_InputA3_Down;
		m_InputProfile.m_InputMapping[1] = SInputEvent::kEvent_InputA2_Down;
		m_InputProfile.m_InputMapping[0] = SInputEvent::kEvent_InputA1_Down;
		m_InputProfile.m_InputMapping[Hash("povhatdown")] = SInputEvent::kEvent_InputDown_Down;
		m_InputProfile.m_InputMapping[Hash("povhatup")] = SInputEvent::kEvent_InputUp_Down;
		m_InputProfile.m_InputMapping[Hash("povhatright")] = SInputEvent::kEvent_InputRight_Down;
		m_InputProfile.m_InputMapping[Hash("povhatleft")] = SInputEvent::kEvent_InputLeft_Down;
	}
	else if (m_JoystickProfile == Hash("Logitech Dual Action"))
	{
		m_InputProfile.m_InputMapping[8] = SInputEvent::kEvent_InputQuit_Down;
		m_InputProfile.m_InputMapping[9] = SInputEvent::kEvent_InputReset_Down;
		m_InputProfile.m_InputMapping[6] = SInputEvent::kEvent_InputA6_Down;
		m_InputProfile.m_InputMapping[7] = SInputEvent::kEvent_InputA5_Down;
		m_InputProfile.m_InputMapping[0] = SInputEvent::kEvent_InputA4_Down;
		m_InputProfile.m_InputMapping[3] = SInputEvent::kEvent_InputA3_Down;
		m_InputProfile.m_InputMapping[2] = SInputEvent::kEvent_InputA2_Down;
		m_InputProfile.m_InputMapping[1] = SInputEvent::kEvent_InputA1_Down;
		m_InputProfile.m_InputMapping[Hash("povhatdown")] = SInputEvent::kEvent_InputDown_Down;
		m_InputProfile.m_InputMapping[Hash("povhatup")] = SInputEvent::kEvent_InputUp_Down;
		m_InputProfile.m_InputMapping[Hash("povhatright")] = SInputEvent::kEvent_InputRight_Down;
		m_InputProfile.m_InputMapping[Hash("povhatleft")] = SInputEvent::kEvent_InputLeft_Down;
	}
	else // keyboard & mouse
	{
		m_InputProfile.m_InputMapping[irr::KEY_ESCAPE] = SInputEvent::kEvent_InputQuit_Down;
		m_InputProfile.m_InputMapping[irr::KEY_BACK] = SInputEvent::kEvent_InputReset_Down;
		// I'm adding KEY_KEY_CODES_COUNT here to ensure that the mouse event enums don't conflict with the keyboard ones.
		m_InputProfile.m_InputMapping[irr::EMIE_RMOUSE_PRESSED_DOWN + irr::KEY_KEY_CODES_COUNT] = SInputEvent::kEvent_InputA6_Down;
		m_InputProfile.m_InputMapping[irr::EMIE_LMOUSE_PRESSED_DOWN + irr::KEY_KEY_CODES_COUNT] = SInputEvent::kEvent_InputA5_Down;
		m_InputProfile.m_InputMapping[irr::EMIE_RMOUSE_LEFT_UP] = SInputEvent::kEvent_InputA6_Up;
		m_InputProfile.m_InputMapping[irr::EMIE_LMOUSE_LEFT_UP] = SInputEvent::kEvent_InputA5_Up;
		m_InputProfile.m_InputMapping[irr::KEY_KEY_4] = SInputEvent::kEvent_InputA4_Down;
		m_InputProfile.m_InputMapping[irr::KEY_KEY_3] = SInputEvent::kEvent_InputA3_Down;
		m_InputProfile.m_InputMapping[irr::KEY_KEY_2] = SInputEvent::kEvent_InputA2_Down;
		m_InputProfile.m_InputMapping[irr::KEY_KEY_1] = SInputEvent::kEvent_InputA1_Down;
		m_InputProfile.m_InputMapping[irr::KEY_KEY_S] = SInputEvent::kEvent_InputDown_Down;
		m_InputProfile.m_InputMapping[irr::KEY_KEY_W] = SInputEvent::kEvent_InputUp_Down;
		m_InputProfile.m_InputMapping[irr::KEY_KEY_D] = SInputEvent::kEvent_InputRight_Down;
		m_InputProfile.m_InputMapping[irr::KEY_KEY_A] = SInputEvent::kEvent_InputLeft_Down;
	}
}