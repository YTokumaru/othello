#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <functional>

/**
 * @brief Title screen
 *
 */
class TitleScreen
{
private:
  ftxui::ScreenInteractive* screen_ptr;
  std::function<void(void)> onStart;
  std::function<void(void)> onSetting;
  std::function<void(void)> onQuit;

public:
  TitleScreen(ftxui::ScreenInteractive &t_screen,
    std::function<void(void)> t_onStart,
    std::function<void(void)> t_onSetting,
    std::function<void(void)> t_onQuit);
  ~TitleScreen() = default;

  int display();
};

class SettingScreen
{
private:
  /* data */
public:
  SettingScreen(/* args */);
  ~SettingScreen();
};

class ResultScreen
{
private:
  /* data */
public:
  ResultScreen(/* args */);
  ~ResultScreen();
};

enum class GameState { TITLE, SETTING, GAME, RESULT };


#endif// GAME_STATE_HPP