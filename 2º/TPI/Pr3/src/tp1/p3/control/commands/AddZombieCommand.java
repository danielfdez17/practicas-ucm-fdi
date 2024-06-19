package tp1.p3.control.commands;

import tp1.p3.control.Command;
import tp1.p3.control.exceptions.CommandExecuteException;
import tp1.p3.control.exceptions.CommandParseException;
import tp1.p3.control.exceptions.GameException;
import tp1.p3.control.exceptions.InvalidPositionException;
import tp1.p3.logic.GameWorld;
import tp1.p3.logic.gameobjects.Zombie;
import tp1.p3.logic.gameobjects.ZombieFactory;
import tp1.p3.view.Messages;

public class AddZombieCommand extends Command {

	// ATRIBUTES
	private int zombieIdx;
	private int col;
	private int row;

	// BUILDERS
	public AddZombieCommand() {
		super(false);
	}
	public AddZombieCommand(int zombieIdx, int col, int row) {
		this.zombieIdx = zombieIdx;
		this.col = col;
		this.row = row;
	}

	// METHODS
	@Override
	protected String getName() {
		return Messages.COMMAND_ADD_ZOMBIE_NAME;
	}
	@Override
	protected String getShortcut() {
		return Messages.COMMAND_ADD_ZOMBIE_SHORTCUT;
	}
	@Override
	public String getDetails() {
		return Messages.COMMAND_ADD_ZOMBIE_DETAILS;
	}
	@Override
	public String getHelp() {
		return Messages.COMMAND_ADD_ZOMBIE_HELP;
	}
	@Override
	public boolean execute(GameWorld game) throws GameException {
		Zombie z = ZombieFactory.spawnZombie(this.zombieIdx, game, this.col, this.row);
		if (!game.addItem(z, false)) {
			throw new CommandExecuteException(Messages.INVALID_GAME_OBJECT);
		}
		else {
			// método para aumentar el contador de remainingZombies
			// game.addRemainingZombies() {
//				this.zombiesManager.addRemainingZombies();
//			  }
			game.update();
			return true;
		}
	}
	@Override
	public Command create(String[] parameters) throws GameException {
		try {
			AddZombieCommand c = new AddZombieCommand();
			if (parameters.length == 3) {
				c.zombieIdx = Integer.parseInt(parameters[0]);
				c.col = Integer.parseInt(parameters[1]);
				c.row = Integer.parseInt(parameters[2]);
				if ((c.col < 0) || (c.col > GameWorld.NUM_COLS) || (c.row < 0) || (c.row >= GameWorld.NUM_ROWS)) {
					throw new InvalidPositionException(Messages.INVALID_POSITION.formatted(parameters[1], parameters[2]));			
				}
				return c;
			}
			else if (parameters.length < 3) {
				throw new GameException(Messages.COMMAND_PARAMETERS_MISSING);
			}
			else {
				throw new GameException(Messages.COMMAND_INCORRECT_PARAMETER_NUMBER);
			}	
		} catch (NumberFormatException nfe) {
		    throw new CommandParseException(Messages.INVALID_POSITION.formatted(parameters[1], parameters[2]), nfe);
		  }
	}
}