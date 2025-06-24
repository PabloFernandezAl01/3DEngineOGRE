#pragma once

#include "SDL.h"

#include <ETypes.h>
#include <unordered_map>
#include <ESingleton.h>
#include <ConfigManager.h>
#include <vector>
#include <array>

/*
Input Manager. It has support for mouse, keyboard and multiple PS4 or XBOX controllers.
*/

namespace Input {

	class InputManager : public Core::ESingleton<InputManager>{

		friend ESingleton<InputManager>;

	public:

		enum class DIRECTIONS { LEFT, RIGHT, UP, DOWN };

		enum class MOUSEBUTTON : uint8_t {
			LEFT, MIDDLE, RIGHT, Count
		};

		enum class CONTROLLERSTICK : uint8_t {
			LEFT_STICK, RIGHT_STICK
		};

		enum class CONTROLLERTRIGGER : uint8_t {
			LEFT_TRIGGER, RIGHT_TRIGGER, N_TRIGGERS
		};

		// PS4 Mapping
		enum class PS4_CONTROLLER_BUTTONS : uint8_t {
			X , CIRCLE , SQUARE , TRIANGLE, SHARE, HOME, OPTIONS, L3, R3,
			L1, R1, UP_ARROW, DOWN_ARROW, LEFT_ARROW, RIGHT_ARROW, PANEL, Count = 16
		};

		// XBOX Mapping
		enum class XBOX_CONTROLLER_BUTTONS : uint8_t {
			A, B, X, Y , BACK, GUIDE, START, LSB, RSB,
			LR, RB, UP_ARROW, DOWN_ARROW, LEFT_ARROW, RIGHT_ARROW, PANEL, Count = 16
		};

		enum class ButtonState {
			None, JustDown, Down, Up
		};

		// Keyboard

		enum class KB_LETTERS {
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Count
		};

		enum class KB_NUMBERS {
			Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, Count
		};

		enum class KB_SPECIALKEYS {
			RETURN, ESCAPE, BACKSPACE, TAB, SPACE, RIGHT, LEFT, DOWN, UP, LCTRL, LSHIFT, LALT, RCTRL, RSHIFT, RALT, Count
		};

		~InputManager();

		bool Valid() override;

		// Called in the main loop to check is window is closed
		bool HandleInput(SDL_Event& e);

		void UpdateKeyState(ButtonState& key);

		/*
			Nombres de eventos:

			Down: Una tecla esta siendo pulsada
			Up: Una tecla no esta siendo pulsada
			Pressed: Una tecla acaba de ser pulsada
			Released: Una tecla acaba de ser soltada
		*/

		// Keyboard
		bool AnyKeyPressed();
		bool AnyKeyReleased();

		bool IsLetterPressed(const KB_LETTERS& l);
		bool IsLetterDown(const KB_LETTERS& l);
		bool IsLetterUp(const KB_LETTERS& l);
		bool IsLetterReleased(const KB_LETTERS& l);

		bool IsNumberPressed(const KB_NUMBERS& n);
		bool IsNumberDown(const KB_NUMBERS& n);
		bool IsNumberUp(const KB_NUMBERS& n);
		bool IsNumberReleased(const KB_NUMBERS& n);

		bool IsSpecialKeyPressed(const KB_SPECIALKEYS& s);
		bool IsSpecialKeyDown(const KB_SPECIALKEYS& s);
		bool IsSpecialKeyUp(const KB_SPECIALKEYS& s);
		bool IsSpecialKeyReleased(const KB_SPECIALKEYS& s);

		// Mouse
		bool HasMouseMoved();

		bool HasMouseWheelMoved();

		bool IsMouseButtonDown(const MOUSEBUTTON& b);

		bool IsMouseButtonUp(const MOUSEBUTTON& b);

		bool IsMouseButtonPressed(const MOUSEBUTTON& b);

		bool IsMouseButtonReleased(const MOUSEBUTTON& b);

		CRefVector2D GetAbsoluteMousePosition() const;

		CRefVector2D GetMousePositionDelta() const;

		int GetMouseWheelScroll() const;


		// Controller
		int ConnectedControllersCount();

		bool AnyControllerButtonPressed();

		bool AnyControllerButtonReleased();

		bool AnyControllerAxisMotion();

		bool AnyControllerConnected();

		bool AnyControllerDisconnected();

		// With id

			bool IsControllerButtonPressedWithId(const PS4_CONTROLLER_BUTTONS& button, int id);

			bool IsControllerButtonDownWithId(const PS4_CONTROLLER_BUTTONS& button, int id);

			bool IsControllerButtonReleasedWithId(const PS4_CONTROLLER_BUTTONS& button, int id);

			float GetLeftTriggerValueWithId(int id);

			float GetRightTriggerValueWithId(int id);

			bool IsLeftTriggerDownWithId(int id);

			bool IsRightTriggerDownWithId(int id);

			float GetLeftStickHorizontalValueWithId(int id);

			float GetLeftStickVerticalValueWithId(int id);

			float GetRightStickHorizontalValueWithId(int id);

			float GetRightStickVerticalValueWithId(int id);

			bool HasLeftStickMovedWithId(int id);

			bool HasRightStickMovedWithId(int id);


			// Without id

				bool IsControllerButtonPressed(const PS4_CONTROLLER_BUTTONS& button);

				bool IsControllerButtonDown(const PS4_CONTROLLER_BUTTONS& button);

				bool IsControllerButtonReleased(const PS4_CONTROLLER_BUTTONS& button);

				float GetLeftTriggerValue();

				float GetRightTriggerValue();

				bool IsLeftTriggerDown();

				bool IsRightTriggerDown();

				float GetLeftStickHorizontalValue();

				float GetLeftStickVerticalValue();

				float GetRightStickHorizontalValue();

				float GetRightStickVerticalValue();

				bool HasLeftStickMoved();

				bool HasRightStickMoved();



		private:

			InputManager();
			InputManager(bool closeWithEscape, int KB_Jump, int KB_Action, std::vector<int> KB_movements, int CT_Jump, int CT_Action);
			InputManager(const ConfigData& data);

			bool InitSDLInput();
			void CloseSDLInput();

			SDL_Scancode ConvertToScancode(const KB_LETTERS& letter);
			SDL_Scancode ConvertToScancode(const KB_NUMBERS& number);
			SDL_Scancode ConvertToScancode(const KB_SPECIALKEYS& specialKey);

			KB_LETTERS ConvertToLetter(const SDL_Scancode& scancode);
			KB_NUMBERS ConvertToNumbers(const SDL_Scancode& scancode);
			KB_SPECIALKEYS ConvertToSpecialKeys(const SDL_Scancode& scancode);


			// Clear the state
			void ClearState();

			// Update the state with a new event
			void Update(const SDL_Event& event);

			// --------- MOUSE & KB ------------

			void LetterPressed(const KB_LETTERS& letter);
			void NumberPressed(const KB_NUMBERS& number);
			void SpecialKeyPressed(const KB_SPECIALKEYS& specialkey);

			void LetterReleased(const KB_LETTERS& letter);
			void NumberReleased(const KB_NUMBERS& number);
			void SpecialKeyReleased(const KB_SPECIALKEYS& specialkey);

			void OnKeyDown();

			void OnKeyUp();

			void OnMouseMotion(const SDL_Event& event);

			void OnMouseButtonChange(const SDL_Event& event, bool isDown);

			void OnMouseWheelMotion(const SDL_Event& event);


			bool closeWithEscape{};
			bool valid{};

			bool isKeyUpEvent_{};
			bool isKeyDownEvent_{};

			bool isMouseMotionEvent_{};
			bool isMouseWheelEvent_{};
			bool isMouseButtonEventDown_{};
			bool isMouseButtonEventUp_{};


			Vector2D mousePos_{};
			Vector2D mousePosDelta_{};
			std::array<bool, 3> mbState_{};
			int wheelMotionY_{};
			const Uint8* kbState_{};


			// Keyboard keys
			ButtonState letters[(int)KB_LETTERS::Count]{};
			ButtonState numbers[(int)KB_NUMBERS::Count]{};
			ButtonState specialKeys[(int)KB_SPECIALKEYS::Count]{};


			// ----- CONTROLLER -------

			struct ControllerData {
				SDL_GameController* controller{};
				SDL_JoystickID id{};
				std::string name;
				std::vector<ButtonState> buttonsStates;
				Vector2D triggers; // X for LEFT trigger, Y for RIGHT trigger
				std::pair<Vector2D, Vector2D> joysticks;
			};

			bool InitControllers();

			void AddController(int which);

			void RemoveController(int which);

			void ControllerButtonPressed(const SDL_Event& event);

			void ControllerButtonReleased(const SDL_Event& event);

			void UpdateControllersButtons();

			void OnControllerAxisMotion(const SDL_Event& event);

			void ReadSticksValues();


			std::unordered_map<int, ControllerData> controllers{};

			bool isAxisMotionEvent_{};
			bool isControllerButtonDownEvent_{};
			bool isControllerButtonUpEvent_{};
			bool controllerConnected_{};
			bool controllerDisconnected_{};

			int lastInputReceivedController{};

			int numControllersConnected{};


			// ------------ BINDING DATA ------------

			// Keyboard
			int KB_Jump{};
			int KB_Action{};
			std::vector<int> KB_movements{};

			// Controller
			int CT_Jump{};
			int CT_Action{};

	};
}