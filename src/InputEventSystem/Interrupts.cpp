#include <Arduino.h>
#include "Interrupts.h"

namespace BadgeOS
{
	namespace InputInterrupts
	{
		static constexpr uint32_t ACTION_MASK = 0xFFFF0000;
		static constexpr uint32_t DEVICE_MASK = 0x0000FFFF;

		static volatile uint32_t InputEventStateISR = 0;
		static uint32_t InputEventState;

		static inline void resetISREventState()
		{
			InputEventStateISR = 0;
		}

		static inline void setISREventDevice(Input::Device device)
		{
			InputEventStateISR = (InputEventStateISR & ~DEVICE_MASK) | static_cast<uint32_t>(device);
		}

		static inline void setISREventAction(Input::Action action)
		{
			InputEventStateISR = (InputEventStateISR & ~ACTION_MASK) | (static_cast<uint32_t>(action) << 16);
		}

		void buttonPrgISR()
		{
			static volatile bool pressedState = false;

			pressedState = !pressedState;

			resetISREventState();
			setISREventDevice(Input::Device::Button0);
			setISREventAction(pressedState ? Input::Action::Pressed : Input::Action::Released);
		}

		void initialise()
		{
			pinMode(KEY_BUILTIN, INPUT_PULLUP);

			// Force the button to start low, just in case.
			digitalWrite(KEY_BUILTIN, LOW);

			attachInterrupt(digitalPinToInterrupt(KEY_BUILTIN), buttonPrgISR, CHANGE);
		}

		void update()
		{
			noInterrupts();
			InputEventState = InputEventStateISR;
			resetISREventState();
			interrupts();
		}

		bool hasNewInputEvent()
		{
			return inputDevice() != Input::Device::None && inputAction() != Input::Action::None;
		}

		Input::Device inputDevice()
		{
			return static_cast<Input::Device>(InputEventState & DEVICE_MASK);
		}

		Input::Action inputAction()
		{
			return static_cast<Input::Action>((InputEventState & ACTION_MASK) >> 16);
		}
	}
}
