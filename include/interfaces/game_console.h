#pragma once

struct i_game_console {
    virtual	~i_game_console() = 0;
    virtual void activate() = 0;
    virtual void initialize() = 0;
    virtual void hide() = 0;
    virtual void clear() = 0;
    virtual bool is_visible() = 0;
    virtual void set_parent() = 0;
    virtual void shutdown() = 0;
};