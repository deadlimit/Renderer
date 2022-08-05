#include "InputManager.h"
#include "Subsystems/EditorCamera/EditorCamera.h"
#include "Engine.h"
#include <iostream>
#include "imgui.h"
#include <unordered_map>
#include <map>


namespace InputManager {

    //IMGUI-key values are not the same as GLFW
    static std::unordered_map<int, int> convertedKeys = {

    {GLFW_KEY_W, ImGuiKey_W },
    {GLFW_KEY_TAB, ImGuiKey_Tab},
    {GLFW_KEY_LEFT, ImGuiKey_LeftArrow},
    {GLFW_KEY_RIGHT, ImGuiKey_RightArrow},
    {GLFW_KEY_UP,  ImGuiKey_UpArrow},
    {GLFW_KEY_DOWN, ImGuiKey_DownArrow},
    {GLFW_KEY_PAGE_UP, ImGuiKey_PageUp},
    {GLFW_KEY_PAGE_DOWN, ImGuiKey_PageDown},
    {GLFW_KEY_HOME, ImGuiKey_Home},
    {GLFW_KEY_END, ImGuiKey_End},
    {GLFW_KEY_INSERT, ImGuiKey_Insert},
    {GLFW_KEY_DELETE, ImGuiKey_Delete},
    {GLFW_KEY_BACKSPACE, ImGuiKey_Backspace},
    {GLFW_KEY_SPACE, ImGuiKey_Space},
    {GLFW_KEY_ENTER, ImGuiKey_Enter },
    {GLFW_KEY_ESCAPE ,ImGuiKey_Escape },
    {GLFW_KEY_APOSTROPHE ,ImGuiKey_Apostrophe },
    {GLFW_KEY_COMMA ,ImGuiKey_Comma },
    {GLFW_KEY_MINUS ,ImGuiKey_Minus },
    {GLFW_KEY_PERIOD, ImGuiKey_Period },
    {GLFW_KEY_SLASH ,ImGuiKey_Slash },
    {GLFW_KEY_SEMICOLON, ImGuiKey_Semicolon },
    {GLFW_KEY_EQUAL ,ImGuiKey_Equal },
    {GLFW_KEY_LEFT_BRACKET, ImGuiKey_LeftBracket },
    {GLFW_KEY_BACKSLASH, ImGuiKey_Backslash },
    {GLFW_KEY_RIGHT_BRACKET, ImGuiKey_RightBracket },
    {GLFW_KEY_GRAVE_ACCENT, ImGuiKey_GraveAccent },
    {GLFW_KEY_CAPS_LOCK, ImGuiKey_CapsLock },
    {GLFW_KEY_SCROLL_LOCK, ImGuiKey_ScrollLock },
    {GLFW_KEY_NUM_LOCK, ImGuiKey_NumLock },
    {GLFW_KEY_PRINT_SCREEN, ImGuiKey_PrintScreen },
    {GLFW_KEY_PAUSE, ImGuiKey_Pause },
    {GLFW_KEY_KP_0, ImGuiKey_Keypad0 },
    {GLFW_KEY_KP_1, ImGuiKey_Keypad1 },
    {GLFW_KEY_KP_2, ImGuiKey_Keypad2 },
    {GLFW_KEY_KP_3, ImGuiKey_Keypad3 },
    {GLFW_KEY_KP_4, ImGuiKey_Keypad4 },
    {GLFW_KEY_KP_5, ImGuiKey_Keypad5 },
    {GLFW_KEY_KP_6, ImGuiKey_Keypad6 },
    {GLFW_KEY_KP_7, ImGuiKey_Keypad7 },
    {GLFW_KEY_KP_8, ImGuiKey_Keypad8 },
    {GLFW_KEY_KP_9, ImGuiKey_Keypad9 },
    {GLFW_KEY_KP_DECIMAL, ImGuiKey_KeypadDecimal },
    {GLFW_KEY_KP_DIVIDE, ImGuiKey_KeypadDivide },
    {GLFW_KEY_KP_MULTIPLY, ImGuiKey_KeypadMultiply },
    {GLFW_KEY_KP_SUBTRACT, ImGuiKey_KeypadSubtract },
    {GLFW_KEY_KP_ADD, ImGuiKey_KeypadAdd },
    {GLFW_KEY_KP_ENTER, ImGuiKey_KeypadEnter },
    {GLFW_KEY_KP_EQUAL, ImGuiKey_KeypadEqual },
    {GLFW_KEY_LEFT_SHIFT, ImGuiKey_LeftShift },
    {GLFW_KEY_LEFT_CONTROL, ImGuiKey_LeftCtrl },
    {GLFW_KEY_LEFT_ALT, ImGuiKey_LeftAlt },
    {GLFW_KEY_LEFT_SUPER, ImGuiKey_LeftSuper },
    {GLFW_KEY_RIGHT_SHIFT, ImGuiKey_RightShift },
    {GLFW_KEY_RIGHT_CONTROL, ImGuiKey_RightCtrl },
    {GLFW_KEY_RIGHT_ALT, ImGuiKey_RightAlt },
    {GLFW_KEY_RIGHT_SUPER, ImGuiKey_RightSuper },
    {GLFW_KEY_MENU, ImGuiKey_Menu },
    {GLFW_KEY_0, ImGuiKey_0 },
    {GLFW_KEY_1, ImGuiKey_1 },
    {GLFW_KEY_2, ImGuiKey_2 },
    {GLFW_KEY_3, ImGuiKey_3 },
    {GLFW_KEY_4, ImGuiKey_4 },
    {GLFW_KEY_5, ImGuiKey_5 },
    {GLFW_KEY_6, ImGuiKey_6 },
    {GLFW_KEY_7, ImGuiKey_7 },
    {GLFW_KEY_8, ImGuiKey_8 },
    {GLFW_KEY_9, ImGuiKey_9 },
    {GLFW_KEY_A, ImGuiKey_A },
    {GLFW_KEY_B, ImGuiKey_B },
    {GLFW_KEY_C, ImGuiKey_C },
    {GLFW_KEY_D, ImGuiKey_D },
    {GLFW_KEY_E, ImGuiKey_E },
    {GLFW_KEY_F, ImGuiKey_F },
    {GLFW_KEY_G, ImGuiKey_G },
    {GLFW_KEY_H, ImGuiKey_H },
    {GLFW_KEY_I, ImGuiKey_I },
    {GLFW_KEY_J, ImGuiKey_J },
    {GLFW_KEY_K, ImGuiKey_K },
    {GLFW_KEY_L, ImGuiKey_L },
    {GLFW_KEY_M, ImGuiKey_M },
    {GLFW_KEY_N, ImGuiKey_N },
    {GLFW_KEY_O, ImGuiKey_O },
    {GLFW_KEY_P, ImGuiKey_P },
    {GLFW_KEY_Q, ImGuiKey_Q },
    {GLFW_KEY_R, ImGuiKey_R },
    {GLFW_KEY_S, ImGuiKey_S },
    {GLFW_KEY_T, ImGuiKey_T },
    {GLFW_KEY_U, ImGuiKey_U },
    {GLFW_KEY_V, ImGuiKey_V },
    {GLFW_KEY_W, ImGuiKey_W },
    {GLFW_KEY_X, ImGuiKey_X },
    {GLFW_KEY_Y, ImGuiKey_Y },
    {GLFW_KEY_Z, ImGuiKey_Z },
    {GLFW_KEY_F1, ImGuiKey_F1 },
    {GLFW_KEY_F2, ImGuiKey_F2 },
    {GLFW_KEY_F3, ImGuiKey_F3 },
    {GLFW_KEY_F4, ImGuiKey_F4 },
    {GLFW_KEY_F5, ImGuiKey_F5 },
    {GLFW_KEY_F6, ImGuiKey_F6 },
    {GLFW_KEY_F7, ImGuiKey_F7 },
    {GLFW_KEY_F8, ImGuiKey_F8 },
    {GLFW_KEY_F9, ImGuiKey_F9 },
    {GLFW_KEY_F10, ImGuiKey_F10 },
    {GLFW_KEY_F11, ImGuiKey_F11 },
    {GLFW_KEY_F12, ImGuiKey_F12 },
    };
  
    std::map<int, InputAction> keyCallbacks;
    std::map<int, InputAction> mouseCallbacks;
    std::map<int, InputAction>::iterator it;

    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod) {

        ImGuiIO& io = ImGui::GetIO();

        io.AddKeyEvent(convertedKeys[key], action);

        //Do nothing if viewport isn't focused or if key is not a registered callback
        if (io.WantCaptureKeyboard || keyCallbacks.find(key) == keyCallbacks.end())
            return; 

        //TODO move to function
        if (action == GLFW_PRESS && keyCallbacks[key].status & BUTTON_COLD) {
            keyCallbacks[key].status &= ~BUTTON_COLD; //Button is no longer cold
            keyCallbacks[key].status |= BUTTON_INIT | BUTTON_ACTIVE; //Mark button for initilisation
        } 
        else if (action == GLFW_RELEASE && keyCallbacks[key].status & BUTTON_ACTIVE)
            keyCallbacks[key].status |= BUTTON_RELEASED;
        
    }

    void CursorCallback(GLFWwindow* window, double xPos, double yPos) {

        ImGuiIO& io = ImGui::GetIO();

        io.AddMousePosEvent(xPos, yPos);
        
        if (io.WantCaptureMouse)
            return;
    }

    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        ImGuiIO& io = ImGui::GetIO();

        io.AddMouseButtonEvent(button, action);

        if (io.WantCaptureMouse || mouseCallbacks.find(button) == mouseCallbacks.end())
            return;

        //TODO move to function
        if (action == GLFW_PRESS && mouseCallbacks[button].status & BUTTON_COLD) {
            mouseCallbacks[button].status &= ~BUTTON_COLD;
            mouseCallbacks[button].status |= BUTTON_INIT | BUTTON_ACTIVE;
        }
        else if (action == GLFW_RELEASE && mouseCallbacks[button].status & BUTTON_ACTIVE) {
            mouseCallbacks[button].status |= BUTTON_RELEASED;
        }
           
    }

    void Init() {
        glfwSetKeyCallback(Engine::MainWindow, KeyCallback);
        glfwSetCursorPosCallback(Engine::MainWindow, CursorCallback);
        glfwSetMouseButtonCallback(Engine::MainWindow, MouseButtonCallback);
    }

    void RegisterCallback(InputType type, const int& key, const InputAction& inputActions) {
        
        std::map<int, InputAction>& callbackMap = (type == InputType::KEY ? keyCallbacks : mouseCallbacks);
        
        callbackMap[key] = inputActions;
    }

    void UpdateCallbacks(std::map<int, InputAction>& callbacks) {

        std::map<int, InputAction>::iterator& callbackIterator = callbacks.begin();

        while (callbackIterator != callbacks.end()) {

            if (callbackIterator->second.status & BUTTON_ACTIVE) {

                //If button was released
                if (callbackIterator->second.status & BUTTON_RELEASED) {
                    if (callbackIterator->second.end != nullptr)
                        callbackIterator->second.end();

                    callbackIterator->second.status = BUTTON_COLD;
                    continue;
                }

                //If button was pressed for the first time
                if (callbackIterator->second.status & BUTTON_INIT) {
                    callbackIterator->second.status &= ~BUTTON_INIT;
                    if (callbackIterator->second.start != nullptr)
                        callbackIterator->second.start();
                }

                callbackIterator->second.run();

            }
            callbackIterator++;
        }

    }


    void HandleInput() {
        ImGuiIO& io = ImGui::GetIO();

        if (io.WantCaptureKeyboard) {
            return;
        }

        UpdateCallbacks(keyCallbacks);
        UpdateCallbacks(mouseCallbacks);
    }
}

