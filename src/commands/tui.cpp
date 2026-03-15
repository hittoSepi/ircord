#include "../command.hpp"
#include "../command_context.hpp"
#include <ircord/tui/admin_tui.hpp>

namespace ircord::cli::commands {

class TuiCommand : public ICommand {
public:
    std::string name() const override { return "tui"; }
    std::string description() const override { return "Open interactive admin TUI"; }
    std::string usage() const override { return "ircord tui [--socket <path>]"; }
    CommandType type() const override { return CommandType::interactive; }

    int execute(CommandContext& ctx) override {
        std::string socket_path = ctx.flags.count("socket")
            ? ctx.flags["socket"] : "";

        tui::AdminTui tui_app(socket_path);
        return tui_app.run();
    }
};

std::unique_ptr<ICommand> make_tui() {
    return std::make_unique<TuiCommand>();
}

} // namespace ircord::cli::commands
