package tp1.p2.control.commands;

import static tp1.p2.view.Messages.error;

import tp1.p2.control.Command;
import tp1.p2.control.ExecutionResult;
import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class CatchCommand extends Command {

	// ATRIBUTES
	private static boolean caughtSunThisCycle;
	private int col;
	private int row;

	// BUILDERS
	public CatchCommand() {
		super(false);
		caughtSunThisCycle = false;
	}
	public CatchCommand(int col, int row) {
		this.col = col;
		this.row = row;
	}
	
	// METHODS
	@Override
	protected void newCycleStarted() {
		caughtSunThisCycle = false;
	}
	@Override
	protected String getName() {
		return Messages.COMMAND_CATCH_NAME;
	}
	@Override
	protected String getShortcut() {
		return Messages.COMMAND_CATCH_SHORTCUT;
	}
	@Override
	public String getDetails() {
		return Messages.COMMAND_CATCH_DETAILS;
	}
	@Override
	public String getHelp() {
		return Messages.COMMAND_CATCH_HELP;
	}
	@Override
	public ExecutionResult execute(GameWorld game) {
		caughtSunThisCycle = game.tryToCatchObject(this.col, this.row);			
		return new ExecutionResult(true);
	}
	@Override
	public Command create(String[] parameters) {
		if (parameters.length == 2) {
			CatchCommand c = new CatchCommand();
			c.col = Integer.parseInt(parameters[0]);
			c.row = Integer.parseInt(parameters[1]);
			if ((c.col < 0) || (c.col >= GameWorld.NUM_COLS) || (c.row < 0) || (c.row >= GameWorld.NUM_ROWS)) {
				System.out.println(error(Messages.INVALID_COMMAND));
				return null;
			}
			else {
				return c;
			}
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