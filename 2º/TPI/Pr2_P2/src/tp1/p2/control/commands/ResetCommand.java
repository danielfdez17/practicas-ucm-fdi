package tp1.p2.control.commands;

import static tp1.p2.view.Messages.error;

import tp1.p2.control.Command;
import tp1.p2.control.ExecutionResult;
import tp1.p2.control.Level;
import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

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
	public ExecutionResult execute(GameWorld game) {
		if (this.with_parameters) {
			game.reset(this.level, this.seed);			
		}
		else {
			game.reset();						
		}
		System.out.println(Messages.CONFIGURED_LEVEL.formatted(level));
		System.out.println(Messages.CONFIGURED_SEED.formatted(seed));
		return new ExecutionResult(true);
	}
	@Override
	public Command create(String[] parameters) {
		if (parameters.length == 0) {
			return new ResetCommand();
		}
		else if (parameters.length == 2) {
			this.level = Level.valueOfIgnoreCase(parameters[0]);
			this.seed = Long.parseLong(parameters[1]);
			return new ResetCommand(this.level, this.seed);
		}
		else if (parameters.length < 2) {
			System.out.println(error(Messages.COMMAND_PARAMETERS_MISSING));
			return null;
		}
		else {
			System.out.println(error(Messages.COMMAND_INCORRECT_PARAMETER_NUMBER));
			return null;
		}
	}
}