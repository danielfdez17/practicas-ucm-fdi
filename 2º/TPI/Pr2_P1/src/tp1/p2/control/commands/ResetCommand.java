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
		return new ExecutionResult(true);
	}
	@Override
	public Command create(String[] parameters) {
		ResetCommand c = null;
		switch(parameters.length) {
		case 0:
			c = new ResetCommand();
			break;
		case 2:
			this.level = Level.valueOfIgnoreCase(parameters[0]);
			this.seed = Long.parseLong(parameters[1]);
			c = new ResetCommand(this.level, this.seed);
			break;
		}
		return c;
	}
}