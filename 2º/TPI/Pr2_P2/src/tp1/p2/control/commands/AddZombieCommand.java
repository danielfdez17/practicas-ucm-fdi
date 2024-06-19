package tp1.p2.control.commands;

import static tp1.p2.view.Messages.error;

import tp1.p2.control.Command;
import tp1.p2.control.ExecutionResult;
import tp1.p2.logic.GameWorld;
import tp1.p2.logic.gameobjects.Zombie;
import tp1.p2.logic.gameobjects.ZombieFactory;
import tp1.p2.view.Messages;

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
	public ExecutionResult execute(GameWorld game) {
		Zombie z = ZombieFactory.spawnZombie(this.zombieIdx, game, this.col, this.row);
		if (!game.addItem(z, false)) {
			String error = error(Messages.INVALID_POSITION);
			return new ExecutionResult(error);
		}
		else {
			game.update();
			return new ExecutionResult(true);
		}
	}
	@Override
	public Command create(String[] parameters) {
		if (parameters.length == 3) {
			AddZombieCommand c = new AddZombieCommand();
			c.zombieIdx = Integer.parseInt(parameters[0]);
			c.col = Integer.parseInt(parameters[1]);
			c.row = Integer.parseInt(parameters[2]);
			if (!ZombieFactory.isValidZombie(this.zombieIdx) || (c.col < 0) || (c.col >= GameWorld.NUM_COLS) || (c.row < 0) || (c.row >= GameWorld.NUM_ROWS)) {
				System.out.println(Messages.INVALID_COMMAND);
				return null;
			}
			return c;
		}
		else if (parameters.length < 3) {
			System.out.println(Messages.COMMAND_PARAMETERS_MISSING);
			return null;
		}
		else {
			System.out.println(Messages.COMMAND_INCORRECT_PARAMETER_NUMBER);
			return null;
		}
	}
}