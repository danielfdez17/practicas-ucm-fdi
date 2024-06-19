package tp1.p2.control.commands;

import static tp1.p2.view.Messages.error;

import tp1.p2.control.Command;
import tp1.p2.control.ExecutionResult;
import tp1.p2.logic.GameWorld;
import tp1.p2.logic.gameobjects.Plant;
import tp1.p2.logic.gameobjects.PlantFactory;
import tp1.p2.view.Messages;

public class AddPlantCommand extends Command implements Cloneable {

	// ATRIBUTES
	private int col;
	private int row;
	private String plantName;
	private boolean consumeCoins;
	
	// BUILDERS
	public AddPlantCommand() {
		this(true);
	}
	public AddPlantCommand(boolean consumeCoins) {
		this.consumeCoins = consumeCoins;
	}
	
	// METHODS
	@Override
	protected String getName() {
		return Messages.COMMAND_ADD_NAME;
	}
	@Override
	protected String getShortcut() {
		return Messages.COMMAND_ADD_SHORTCUT;
	}
	@Override
	public String getDetails() {
		return Messages.COMMAND_ADD_DETAILS;
	}
	@Override
	public String getHelp() {
		return Messages.COMMAND_ADD_HELP;
	}
	@Override
	public ExecutionResult execute(GameWorld game) {
		if(!game.addPlant(this.plantName, this.col, this.row)) {
			String error = "¡Esa posicion esta ocupada!";
			game.update(); // no creo que esté bien esto!!!!
			return new ExecutionResult(error);
		}
		else {
			game.update(); // no creo que esté bien esto!!!!
			return new ExecutionResult(true);
		}
	}
	@Override
	public Command create(String[] parameters) {
		if (parameters.length == 3) {
			AddPlantCommand c = new AddPlantCommand();
			c.plantName = parameters[0];
			c.col = Integer.parseInt(parameters[1]);
			c.row = Integer.parseInt(parameters[2]);
			if (!PlantFactory.isValidPlant(c.plantName) || c.col < 0 || c.col >= GameWorld.NUM_COLS || c.row < 0 || c.row >= GameWorld.NUM_ROWS) {
				System.out.println(Messages.UNKNOWN_COMMAND);
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