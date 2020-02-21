#include <Arduino.h>
#include "InputEventSystem.h"
#include "Interrupts.h"

namespace BadgeOS
{
	void InputEventSystem::setEventHandler(EventHandler handler)
	{
		m_EventHandler = handler;
	}

	void InputEventSystem::update()
	{
		while ( createNextEvent() )
		{
			if ( m_EventHandler )
			{
				m_EventHandler(m_CurrentEvent);
			}
		}
	}

	bool InputEventSystem::createNextEvent()
	{
		const Input::Event lastEvent = m_CurrentEvent;
		const TimevalMs now = millis();
		const bool newEventExists = InputInterrupts::hasNewInputEvent();

		if ( !newEventExists )
		{
			// If the last event was a device press and the hold time has
			// passed, create a hold event for the device.
			if ( lastEvent.action == Input::Action::Pressed &&
				 now - lastEvent.timestamp >= Input::BUTTON_HOLD_TIME_MS )
			{
				m_CurrentEvent.device = lastEvent.device;
				m_CurrentEvent.action = Input::Action::Held;
				m_CurrentEvent.timestamp = now;

				return true;
			}

			// No event to send, so ignore.
			return false;
		}

		const Input::Device newDevice = InputInterrupts::inputDevice();
		const Input::Action newAction = InputInterrupts::inputAction();

		// If the new input event is a different device and the last input event was not a release,
		// create a release event for the last device first.
		if ( newDevice != lastEvent.device && lastEvent.action != Input::Action::Released )
		{
			m_CurrentEvent.device = lastEvent.device;
			m_CurrentEvent.action = Input::Action::Released;
			m_CurrentEvent.timestamp = now;

			return true;
		}

		// Make sure that we are generating a new event and not re-sending one from a previous iteration
		// in the same update() call.
		if ( lastEvent.device == newDevice && lastEvent.action == newAction )
		{
			return false;
		}

		m_CurrentEvent.device = newDevice;
		m_CurrentEvent.action = newAction;
		m_CurrentEvent.timestamp = now;

		return true;
	}
}
