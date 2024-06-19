package tp1.p3.control.commands;

import tp1.p3.control.Command;
import tp1.p3.control.exceptions.CommandExecuteException;
import tp1.p3.control.exceptions.CommandParseException;
import tp1.p3.control.exceptions.GameException;
import tp1.p3.control.exceptions.InvalidPositionException;
import tp1.p3.control.exceptions.NotCatchablePositionException;
import tp1.p3.logic.GameWorld;
import tp1.p3.view.Messages;

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
	public boolean execute(GameWorld game) throws GameException {
		if (!caughtSunThisCycle) {
			caughtSunThisCycle = game.tryToCatchObject(this.col, this.row);	
			if (!caughtSunThisCycle) {
				throw new NotCatchablePositionException(Messages.INVALID_POSITION.formatted(this.col, this.row));
			}
			return true;
		}
		else {
			throw new CommandExecuteException(Messages.SUN_ALREADY_CAUGHT);
		}
	}
	@Override
	public Command create(String[] parameters) throws GameException {
		try {
			if (parameters.length == 2) {
				this.col = Integer.parseInt(parameters[0]);
				this.row = Integer.parseInt(parameters[1]);
				if ((this.col < 0) || (this.col >= GameWorld.NUM_COLS) || (this.row < 0) || (this.row >= GameWorld.NUM_ROWS)) {
					throw new InvalidPositionException(Messages.INVALID_POSITION.formatted(parameters[0], parameters[1]));
				}
				return this;
			}
			else if (parameters.length < 2) {
				throw new GameException(Messages.COMMAND_PARAMETERS_MISSING);
			}
			else {
				throw new GameException(Messages.COMMAND_INCORRECT_PARAMETER_NUMBER);
			}
		} catch(NumberFormatException nfe) {
			throw new CommandParseException(Messages.INVALID_POSITION.formatted(parameters[0], parameters[1]), nfe);
		}
	}
}