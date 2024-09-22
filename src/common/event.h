#ifndef GPLAY_COMMON_EVENT_H
#define GPLAY_COMMON_EVENT_H

namespace gplay {

enum class EventType {
    NONE = 0,
    KEY_PRESS,
    KEY_RELEASE,
    KEY_REPEAT,
    MOUSE_PRESS,
    MOUSE_RELEASE,
    MOUSE_POSITION,
    MOUSE_SCROLL,
    WINDOW_RESIZE
};

class Event {
private:
    EventType _event_type = EventType::NONE;
    bool _handled = false;

public:
    Event(EventType type) : _event_type(type) {}

    EventType GetEventType() const { return _event_type; }

    void SetHandled() { _handled = true; }
    inline bool IsHandled() { return _handled; }
};

class EventDispatcher {
private:
    Event& _event;

public:
    EventDispatcher(Event& event) : _event(event) {}

    template <typename T, typename F>
    bool Dispatch(EventType type, const F& func) {
        if (_event.GetEventType() == type) {
            T& event = static_cast<T&>(_event);
            func(event);
            _event.SetHandled();
            return true;
        }
        return false;
    }
};


class KeyEvent : public Event {
private:
    int _key;

public:
    KeyEvent(EventType type, int key)
        : Event(type), _key(key) {}

    inline int GetKey() { return _key; }
};

class MouseButtonEvent : public Event {
private:
    int _button;

public:
    MouseButtonEvent(EventType type, int button)
        : Event(type), _button(button) {}

    inline int GetButton() { return _button; }
};

class MousePositionEvent : public Event {
private:
    double _xpos, _ypos;

public:
    MousePositionEvent(double xpos, double ypos)
        : Event(EventType::MOUSE_POSITION), _xpos(xpos), _ypos(ypos) {}

    inline double GetXPos() { return _xpos; }
    inline double GetYPos() { return _ypos; }
};

class MouseScrollEvent : public Event {
private:
    double _xoffset, _yoffset;

public:
    MouseScrollEvent(double xoffset, double yoffset)
        : Event(EventType::MOUSE_SCROLL),
          _xoffset(xoffset),
          _yoffset(yoffset) {}

    inline double GetXOffset() { return _xoffset; }
    inline double GetYOffset() { return _yoffset; }
};

class WindowResizeEvent : public Event {
private:
    int _width, _height;

   public:
    WindowResizeEvent(int width, int height)
        : Event(EventType::WINDOW_RESIZE), _width(width), _height(height) {}

    inline int GetWidth() { return _width; }
    inline int GetHeight() { return _height; }
};

}  // namespace gplay

#endif // GPLAY_COMMON_EVENT_H
