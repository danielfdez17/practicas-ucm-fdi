package tp1.p3.control.commands;


import tp1.p3.control.Command;
import tp1.p3.control.exceptions.CommandExecuteException;
import tp1.p3.control.exceptions.CommandParseException;
import tp1.p3.control.exceptions.GameException;
import tp1.p3.control.exceptions.InvalidPositionException;
import tp1.p3.logic.GameWorld;
import tp1.p3.logic.gameobjects.Plant;
import tp1.p3.logic.gameobjects.PlantFactory;
import tp1.p3.view.Messages;

public class AddPlantCheatCommand extends Command implements Cloneable {

	// ATRIBUTES
	private int col;
	private int row;
	private String plantName;
	private boolean consumeCoins;

	// BUILDERS
	public AddPlantCheatCommand() {
		this(false);
	}
	public AddPlantCheatCommand(boolean consumeCoins) {
		this.consumeCoins = consumeCoins;
	}

	// METHODS
	@Override
	protected String getName() {
		return Messages.COMMAND_CHEAT_PLANT_NAME;
	}
	@Override
	protected String getShortcut() {
		return Messages.COMMAND_CHEAT_PLANT_SHORTCUT;
	}
	@Override
	public String getDetails() {
		return Messages.COMMAND_CHEAT_PLANT_DETAILS;
	}
	@Override
	public String getHelp() {
		return Messages.COMMAND_CHEAT_PLANT_HELP;
	}
	@Override
	public boolean execute(GameWorld game) throws GameException {
		Plant p = PlantFactory.spawnPlant(plantName, game, col, row);
		if(!game.addItem(p, this.consumeCoins)) {
			throw new CommandExecuteException(Messages.INVALID_GAME_OBJECT);
		}
		else {
			game.update();
			return true;
		}
	}
	@Override
	public Command create(String[] parameters) throws GameException {
		try {
			if (parameters.length == 3) {
				AddPlantCheatCommand c = new AddPlantCheatCommand();
				c.plantName = parameters[0];
				c.col = Integer.parseInt(parameters[1]);
				c.row = Integer.parseInt(parameters[2]);
				if ((c.col < 0) || (c.col >= GameWorld.NUM_COLS) || (c.row < 0) || (c.row >= GameWorld.NUM_ROWS)) {
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