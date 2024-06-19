package tp1.p3.control;

import static tp1.p3.view.Messages.error;

import java.io.IOException;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import tp1.p3.control.Command;
import tp1.p3.control.commands.AddPlantCheatCommand;
import tp1.p3.control.commands.AddPlantCommand;
import tp1.p3.control.commands.AddZombieCommand;
import tp1.p3.control.commands.CatchCommand;
import tp1.p3.control.commands.ExitCommand;
import tp1.p3.control.commands.HelpCommand;
import tp1.p3.control.commands.ListPlantsCommand;
import tp1.p3.control.commands.ListZombiesCommand;
import tp1.p3.control.commands.NoneCommand;
import tp1.p3.control.commands.ResetCommand;
import tp1.p3.control.commands.ShowRecordCommand;
import tp1.p3.control.exceptions.CommandParseException;
import tp1.p3.control.exceptions.GameException;
import tp1.p3.logic.GameWorld;
import tp1.p3.view.Messages;

/**
 * Represents a user action in the game.
 *
 */
public abstract class Command {

	// CONSTANTS
	/* @formatter:off */
	private static final List<Command> AVAILABLE_COMMANDS = Arrays.asList(
		new AddPlantCommand(),
		new ListPlantsCommand(),
		new ResetCommand(),
		new HelpCommand(),
		new ExitCommand(),
		new NoneCommand(),
		new ListZombiesCommand(),
		new AddZombieCommand(),
		new AddPlantCheatCommand(),
		new CatchCommand(),
		new ShowRecordCommand()
	);
	/* @formatter:on */

	// ATRIBUTES
	private static Command defaultCommand;
	
	// BUILDERS
	public Command() {
		this(false);
	}
	public Command(boolean isDefault) {
		if (isDefault) {
			defaultCommand = this;			
		}
	}

	// METHODS
	// Checks the first word of the user input and creates the command if it is possible
	public static Command parse(String[] commandWords) throws GameException {
		if (commandWords.length == 1 && commandWords[0].isEmpty()) {
			return defaultCommand;
		}
		for (Command command : AVAILABLE_COMMANDS) {
			if (command.matchCommand(commandWords[0])) { 
				String[] params = Arrays.copyOfRange(commandWords, 1, commandWords.length);
				return command.create(params);
			}
		}
		throw new CommandParseException(Messages.UNKNOWN_COMMAND);
	}

	public static Iterable<Command> getAvailableCommands() {
		return Collections.unmodifiableList(AVAILABLE_COMMANDS);
	}

	public static void newCycle() {
		for(Command c : AVAILABLE_COMMANDS) {
			c.newCycleStarted();
		}
	}
	// Returns the command name
	abstract protected String getName();
	// Returns the command shortcut
	abstract protected String getShortcut();
	// Returns the command details
	abstract public String getDetails();
	// Returs the help to use the command
	abstract public String getHelp();
	// Checks if the this command is the defualt command
	public boolean isDefaultAction() {
		return Command.defaultCommand == this;
	}
	// Checks if the user input is a valid command
	public boolean matchCommand(String token) {
		String shortcut = getShortcut();
		String name = getName();
		return shortcut.equalsIgnoreCase(token) || name.equalsIgnoreCase(token)
				|| (isDefaultAction() && "".equals(token));
	}

	/**
	 * Execute the command.
	 * 
	 * @param game Where to execute the command.
	 * 
	 * @return {@code true} if game board must be printed {@code false} otherwise.
	 * 
	 * @throws GameException if there is an error executing the command.
	 * @throws IOException 
	 * @throws  
	 */
	public abstract boolean execute(GameWorld game) throws GameException/*TODO, IOException*/;

	public Command create(String[] parameters) throws GameException {
		  if (parameters.length != 0) {
		    throw new CommandParseException(Messages.COMMAND_INCORRECT_PARAMETER_NUMBER);
		  }
		  return this;
		}

	/**
	 * Notifies the {@link Command} that a new cycle has started.
	 */
	protected void newCycleStarted() {
	}
}