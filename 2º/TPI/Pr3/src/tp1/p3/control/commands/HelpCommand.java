package tp1.p3.control.commands;

import tp1.p3.control.Command;
import tp1.p3.control.exceptions.GameException;
import tp1.p3.logic.GameWorld;
import tp1.p3.view.Messages;

public class HelpCommand extends Command {

	// METHODS
	@Override
	protected String getName() {
		return Messages.COMMAND_HELP_NAME;
	}
	@Override
	protected String getShortcut() {
		return Messages.COMMAND_HELP_SHORTCUT;
	}
	@Override
	public String getDetails() {
		return Messages.COMMAND_HELP_DETAILS;
	}
	@Override
	public String getHelp() {
		return Messages.COMMAND_HELP_HELP;
	}
	@Override
	public boolean execute(GameWorld game) throws GameException {
		StringBuilder buffer = new StringBuilder(Messages.HELP_AVAILABLE_COMMANDS);
		for (Command command : Command.getAvailableCommands()) {
			/* @formatter:off */
			buffer.append(Messages.LINE_SEPARATOR);
			buffer.append(command.getDetails() + ": " + command.getHelp());
			/* @formatter:on */
		}
		System.out.println(buffer.toString());
		return true;
	}
}