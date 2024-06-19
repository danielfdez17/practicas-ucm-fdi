package tp1.p2.control;

import static tp1.p2.view.Messages.error;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import tp1.p2.control.commands.AddPlantCommand;
import tp1.p2.control.commands.ExitCommand;
import tp1.p2.control.commands.HelpCommand;
import tp1.p2.control.commands.ListPlantsCommand;
import tp1.p2.control.commands.NoneCommand;
import tp1.p2.control.commands.ResetCommand;
import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

/**
 * Represents a user action in the game.
 *
 */
public abstract class Command {

	/* @formatter:off */
	private static final List<Command> AVAILABLE_COMMANDS = Arrays.asList(
		new AddPlantCommand(),
		new ListPlantsCommand(),
		new ResetCommand(),
		new HelpCommand(),
		new ExitCommand(),
		new NoneCommand()
	);
	/* @formatter:on */
	
	// ATRIBUTES
	private static Command defaultCommand;
	
	// BUILDERS
	public Command() {
		this(false);
	}
	public Command(boolean isDefault) { // se utiliza para el comando por defecto que es NoneCommand
		if (isDefault) {
			defaultCommand = this;			
		}
	}
	// METHODS
	// Checks the first word of the user input and creates the command if it is possible
	public static Command parse(String[] commandWords) {
		if (commandWords.length == 1 && commandWords[0].isEmpty()) {
			return defaultCommand;
		}
		for (Command command : AVAILABLE_COMMANDS) {
			if (command.matchCommand(commandWords[0])) { 
				String[] params = Arrays.copyOfRange(commandWords, 1, commandWords.length); // se elimina la primera palabra del array porque ya se sabe cuál es el comando
				return command.create(params);
			}
		}
		System.out.println(error(Messages.UNKNOWN_COMMAND));
		return null;
	}
	
	public static Iterable<Command> getAvailableCommands() {
		return Collections.unmodifiableList(AVAILABLE_COMMANDS);
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
	 */
	public abstract ExecutionResult execute(GameWorld game);

	// Creates an instance of the command once given the parametres by user
	public Command create(String[] parameters) { // comandos de una sola palabra (exit, none, list, help, reset sin parámetros)
		if (parameters.length != 0) {
			System.out.println(Messages.UNKNOWN_COMMAND);
			return null;
		}
		return this;
	}
}