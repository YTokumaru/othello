#include <game_state.hpp>

/* Title Screen */
TitleScreen::TitleScreen(ftxui::ScreenInteractive &t_screen,
  std::function<void(void)> t_onStart,
  std::function<void(void)> t_onSetting,
  std::function<void(void)> t_onQuit)
  : screen_ptr(&t_screen), onStart(std::move(t_onStart)), onSetting(std::move(t_onSetting)), onQuit(std::move(t_onQuit))
{
  // onStart();
}

int TitleScreen::display()
{
  using namespace ftxui;

  auto logo = vbox({
    text(R"(       █  ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄   ▄▄ ▄▄▄▄▄▄▄ ▄▄▄     ▄▄▄     ▄▄▄▄▄▄▄  ███████)"),
    text(R"(      ██ █       █       █  █ █  █       █   █   █   █   █       █ ██████)"),
    text(R"(     ███ █   ▄   █▄     ▄█  █▄█  █    ▄▄▄█   █   █   █   █   ▄   █ █████)"),
    text(R"(    ████ █  █ █  █ █   █ █       █   █▄▄▄█   █   █   █   █  █ █  █ ████)"),
    text(R"(   █████ █  █▄█  █ █   █ █   ▄   █    ▄▄▄█   █▄▄▄█   █▄▄▄█  █▄█  █ ███)"),
    text(R"(  ██████ █       █ █   █ █  █ █  █   █▄▄▄█       █       █       █ ██)"),
    text(R"( ███████ █▄▄▄▄▄▄▄█ █▄▄▄█ █▄▄█ █▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█ █)"),
  });

  const std::vector<std::string> entries = {
    "Play",
    "Options",
    "Quit",
  };
  const std::vector<std::function<void(void)>> callbacks = {
  onStart,
  onSetting,
  onQuit,
  };
  int selected = 0;

  MenuOption option;
  option.on_enter = screen_ptr->ExitLoopClosure();
  auto menu = Menu(&entries, &selected, option);

  auto intro_screen = Renderer(menu, [&] {
    return vbox({
      logo | center | flex_grow,
      text(""),
      menu->Render() | center | flex_shrink | border,
    });
  });

  screen_ptr->Loop(intro_screen);
  callbacks[static_cast<unsigned int>(selected)]();
  return EXIT_SUCCESS;
}