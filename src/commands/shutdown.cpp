#include "../command.hpp"
#include "../command_context.hpp"

namespace ircord::cli::commands {

class ShutdownCommand : public ICommand {
public:
    std::string name() const override { return "shutdown"; }
    std::string description() const override { return "Shut down the server"; }
    std::string usage() const override { return "ircord shutdown"; }
    CommandType type() const override { return CommandType::fire_and_forget; }

    int execute(CommandContext& ctx) override {
        auto resp = ctx.send_and_wait("shutdown");
        if (!resp) {
            ctx.error("No response from server (timeout)");
            return 1;
        }

        auto& r = *resp;
        if (r.value("ok", false)) {
            ctx.print("Server shutting down...");
        } else {
            ctx.error("Error: " + r.value("error", "unknown"));
            return 1;
        }
        return 0;
    }
};

std::unique_ptr<ICommand> make_shutdown() {
    return std::make_unique<ShutdownCommand>();
}

} // namespace ircord::cli::commands
