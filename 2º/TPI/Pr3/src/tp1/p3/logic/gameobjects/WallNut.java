package tp1.p3.logic.gameobjects;

import tp1.p3.logic.GameWorld;
import tp1.p3.view.Messages;

public class WallNut extends Plant {

	// CONSTANTS
	public static final int ENDURANCE = 10;
	public static final int COST = 50;
	
	// BUILDERS
	public WallNut() {
		super();
	}
	public WallNut(GameWorld game, int col, int row) {
		super(game, col, row);
		this.endurance = ENDURANCE;
		this.cost = COST;
		this.damage = 0;
	}

	// METHODS
	@Override
	protected String getSymbol() {
		return Messages.WALL_NUT_SYMBOL;
	}
	@Override
	public String getDescription() {
		return Messages.plantDescription(Messages.WALL_NUT_NAME_SHORTCUT, COST, 0, ENDURANCE);
	}
	@Override
	public String getName() {
		return Messages.WALL_NUT_NAME;
	}
	@Override
	public void update() {}
	@Override
	public int getCost() {
		return this.cost;
	}
	@Override
	public Plant spawn(GameWorld game, int col, int row) {
		return new WallNut(game, col, row);
	}
}
