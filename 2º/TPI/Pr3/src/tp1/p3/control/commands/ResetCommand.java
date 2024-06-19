package tp1.p3.control.commands;


import tp1.p3.control.Command;
import tp1.p3.control.Level;
import tp1.p3.control.exceptions.CommandParseException;
import tp1.p3.control.exceptions.GameException;
import tp1.p3.logic.GameWorld;
import tp1.p3.view.Messages;

public class ResetCommand extends Command {

	// ATRIBUTES
	private Level level;
	private long seed;
	private boolean with_parameters;
	
	// BUILDERS
	public ResetCommand() {
		super(false);
		this.with_parameters = false;
	}
	public ResetCommand(Level level, long seed) {
		this.level = level;
		this.seed = seed;
		this.with_parameters = true;
	}
	
	// METHODS
	@Override
	protected String getName() {
		return Messages.COMMAND_RESET_NAME;
	}
	@Override
	protected String getShortcut() {
		return Messages.COMMAND_RESET_SHORTCUT;
	}
	@Override
	public String getDetails() {
		return Messages.COMMAND_RESET_DETAILS;
	}
	@Override
	public String getHelp() {
		return Messages.COMMAND_RESET_HELP;
	}
	@Override
	public boolean execute(GameWorld game) throws GameException {
		if (this.with_parameters) {
			game.reset(this.level, this.seed);			
			System.out.println(Messages.CONFIGURED_LEVEL.formatted(this.level));
			System.out.println(Messages.CONFIGURED_SEED.formatted(this.seed));
		}
		else {
			game.reset();
			System.out.println(Messages.CONFIGURED_LEVEL.formatted(game.getLevel()));
			System.out.println(Messages.CONFIGURED_SEED.formatted(game.getSeed()));

		}
		return true;
	}
	@Override
	public Command create(String[] parameters) throws GameException {
		try {
			if (parameters.length == 0) {
				return new ResetCommand();
			}
			else if (parameters.length == 2) {
				Level lvl = Level.valueOfIgnoreCase(parameters[0]);
				Long number = Long.parseLong(parameters[1]);
				return new ResetCommand(lvl, number);
			}
			else if (parameters.length < 2) {
				throw new GameException(Messages.COMMAND_PARAMETERS_MISSING);
			}
			else {
				throw new GameException(Messages.COMMAND_INCORRECT_PARAMETER_NUMBER);
			}
		} catch (NumberFormatException nfe) {
			throw new CommandParseException("Invalid parameters type " + parameters[0] + " " + parameters[1]);
		}
	}
}